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
 * edd.c
 * Ethernet DMA MAC Driver,
 * for GEM GXL core part no. IP7014, from rev 1p05 up
 * for GEM XL  core part no. IP7012, from rev 1p01 up
 * and XGM GXL core part no. IP716,  from rev 1p01 up
 *
 * Main source file
 *****************************************************************************/

#include "cdn_stdint.h"
#include "cdn_errno.h"
#include "cdn_log.h"
#include "cps.h"
#include "cps_drv.h"
#include "emac_registers.h"

#include "cedi_if.h"
#include "cedi_priv.h"
#include "cedi_structs_if.h"
#include "cedi_obj_if.h"
#include "cedi_sanity.h"
#include "edd_int.h"

extern volatile uint32_t* const specAddBottomReg[32];

/******************************************************************************
 * Register addresses tables
 *****************************************************************************/
static volatile uint32_t* const intDisableReg[15] = {
    CEDI_RegOff(int_q1_disable),
    CEDI_RegOff(int_q2_disable),
    CEDI_RegOff(int_q3_disable),
    CEDI_RegOff(int_q4_disable),
    CEDI_RegOff(int_q5_disable),
    CEDI_RegOff(int_q6_disable),
    CEDI_RegOff(int_q7_disable),
    CEDI_RegOff(int_q8_disable),
    CEDI_RegOff(int_q9_disable),
    CEDI_RegOff(int_q10_disable),
    CEDI_RegOff(int_q11_disable),
    CEDI_RegOff(int_q12_disable),
    CEDI_RegOff(int_q13_disable),
    CEDI_RegOff(int_q14_disable),
    CEDI_RegOff(int_q15_disable)
};

static volatile uint32_t* const intStatusReg[15] = {
    CEDI_RegOff(int_q1_status),
    CEDI_RegOff(int_q2_status),
    CEDI_RegOff(int_q3_status),
    CEDI_RegOff(int_q4_status),
    CEDI_RegOff(int_q5_status),
    CEDI_RegOff(int_q6_status),
    CEDI_RegOff(int_q7_status),
    CEDI_RegOff(int_q8_status),
    CEDI_RegOff(int_q9_status),
    CEDI_RegOff(int_q10_status),
    CEDI_RegOff(int_q11_status),
    CEDI_RegOff(int_q12_status),
    CEDI_RegOff(int_q13_status),
    CEDI_RegOff(int_q14_status),
    CEDI_RegOff(int_q15_status)
};

static volatile uint32_t* const frerControlRegA[16] = {
    CEDI_RegOff(frer_control_1_a),
    CEDI_RegOff(frer_control_2_a),
    CEDI_RegOff(frer_control_3_a),
    CEDI_RegOff(frer_control_4_a),
    CEDI_RegOff(frer_control_5_a),
    CEDI_RegOff(frer_control_6_a),
    CEDI_RegOff(frer_control_7_a),
    CEDI_RegOff(frer_control_8_a),
    CEDI_RegOff(frer_control_9_a),
    CEDI_RegOff(frer_control_10_a),
    CEDI_RegOff(frer_control_11_a),
    CEDI_RegOff(frer_control_12_a),
    CEDI_RegOff(frer_control_13_a),
    CEDI_RegOff(frer_control_14_a),
    CEDI_RegOff(frer_control_15_a),
    CEDI_RegOff(frer_control_16_a)
};

static volatile uint32_t* const frerControlRegB[16] = {
    CEDI_RegOff(frer_control_1_b),
    CEDI_RegOff(frer_control_2_b),
    CEDI_RegOff(frer_control_3_b),
    CEDI_RegOff(frer_control_4_b),
    CEDI_RegOff(frer_control_5_b),
    CEDI_RegOff(frer_control_6_b),
    CEDI_RegOff(frer_control_7_b),
    CEDI_RegOff(frer_control_8_b),
    CEDI_RegOff(frer_control_9_b),
    CEDI_RegOff(frer_control_10_b),
    CEDI_RegOff(frer_control_11_b),
    CEDI_RegOff(frer_control_12_b),
    CEDI_RegOff(frer_control_13_b),
    CEDI_RegOff(frer_control_14_b),
    CEDI_RegOff(frer_control_15_b),
    CEDI_RegOff(frer_control_16_b)
};

static volatile uint32_t* const gemAxiXactsReadReg[16] = {
    CEDI_RegOff(gem_axi_xacts_rd_q0),
    CEDI_RegOff(gem_axi_xacts_rd_q1),
    CEDI_RegOff(gem_axi_xacts_rd_q2),
    CEDI_RegOff(gem_axi_xacts_rd_q3),
    CEDI_RegOff(gem_axi_xacts_rd_q4),
    CEDI_RegOff(gem_axi_xacts_rd_q5),
    CEDI_RegOff(gem_axi_xacts_rd_q6),
    CEDI_RegOff(gem_axi_xacts_rd_q7),
    CEDI_RegOff(gem_axi_xacts_rd_q8),
    CEDI_RegOff(gem_axi_xacts_rd_q9),
    CEDI_RegOff(gem_axi_xacts_rd_q10),
    CEDI_RegOff(gem_axi_xacts_rd_q11),
    CEDI_RegOff(gem_axi_xacts_rd_q12),
    CEDI_RegOff(gem_axi_xacts_rd_q13),
    CEDI_RegOff(gem_axi_xacts_rd_q14),
    CEDI_RegOff(gem_axi_xacts_rd_q15),
};

static volatile uint32_t* const gemAxiXactsWriteReg[16] = {
    CEDI_RegOff(gem_axi_xacts_wr_q0),
    CEDI_RegOff(gem_axi_xacts_wr_q1),
    CEDI_RegOff(gem_axi_xacts_wr_q2),
    CEDI_RegOff(gem_axi_xacts_wr_q3),
    CEDI_RegOff(gem_axi_xacts_wr_q4),
    CEDI_RegOff(gem_axi_xacts_wr_q5),
    CEDI_RegOff(gem_axi_xacts_wr_q6),
    CEDI_RegOff(gem_axi_xacts_wr_q7),
    CEDI_RegOff(gem_axi_xacts_wr_q8),
    CEDI_RegOff(gem_axi_xacts_wr_q9),
    CEDI_RegOff(gem_axi_xacts_wr_q10),
    CEDI_RegOff(gem_axi_xacts_wr_q11),
    CEDI_RegOff(gem_axi_xacts_wr_q12),
    CEDI_RegOff(gem_axi_xacts_wr_q13),
    CEDI_RegOff(gem_axi_xacts_wr_q14),
    CEDI_RegOff(gem_axi_xacts_wr_q15),
};

static volatile uint32_t* const qControlReg[16] = {
        CEDI_RegOff(q0_control),
        CEDI_RegOff(q1_control),
        CEDI_RegOff(q2_control),
        CEDI_RegOff(q3_control),
        CEDI_RegOff(q4_control),
        CEDI_RegOff(q5_control),
        CEDI_RegOff(q6_control),
        CEDI_RegOff(q7_control),
        CEDI_RegOff(q8_control),
        CEDI_RegOff(q9_control),
        CEDI_RegOff(q10_control),
        CEDI_RegOff(q11_control),
        CEDI_RegOff(q12_control),
        CEDI_RegOff(q13_control),
        CEDI_RegOff(q14_control),
        CEDI_RegOff(q15_control)
};

volatile uint32_t* const qStatusReg[16] = {
        CEDI_RegOff(q0_status),
        CEDI_RegOff(q1_status),
        CEDI_RegOff(q2_status),
        CEDI_RegOff(q3_status),
        CEDI_RegOff(q4_status),
        CEDI_RegOff(q5_status),
        CEDI_RegOff(q6_status),
        CEDI_RegOff(q7_status),
        CEDI_RegOff(q8_status),
        CEDI_RegOff(q9_status),
        CEDI_RegOff(q10_status),
        CEDI_RegOff(q11_status),
        CEDI_RegOff(q12_status),
        CEDI_RegOff(q13_status),
        CEDI_RegOff(q14_status),
        CEDI_RegOff(q15_status),
};


/******************************************************************************
 * Initial static declarations
 *****************************************************************************/
static struct emac_regs *getMmslRegs(CEDI_PrivateData *pD);

/******************************************************************************
 * Private Driver functions
 *****************************************************************************/
/* Checks, if private data descrives Express MAC
 * @param[in] pD pointer to PrivateData's structure
 * @return true if eMac
 * @return false if not eMac or eMac is not required by config
 */
bool checkIfEmac(const CEDI_PrivateData* pD, const char* funcName) {
    bool isEmac = false;

    /* First, check if eMac is required by configuration */
    if (pD->cfg.incExpressTraffic != 0U) {

        if (pD->macType == CEDI_MAC_TYPE_EMAC) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                    "ERROR: %s can not be called for eMac.\n", funcName);
            isEmac = true;
        }
    }

    return isEmac;
}

static uint8_t CmpBuffs(void *buf1, void *buf2, uint32_t size)
{
    uint8_t *buf18 = buf1;
    uint8_t *buf28 = buf2;
    uint8_t i;
    uint8_t result = 0U;

    for (i = 0U; i < size; i++){
        if(buf18[i] != buf28[i]){
            result = 1U;
            break;
        }
    }

    return result;
}

uint8_t WriteRegAndVerify(volatile uint32_t *address, uint32_t value)
{
    uint32_t status;
    uint32_t reg;

    CPS_UncachedWrite32(address, value);
    reg = CPS_UncachedRead32(address);

    if (reg == value){
        status = CDN_EOK;
    }
    else {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                "Error: Register %p verification failed, written:%08x read:%08x \n",
                address, value, reg);
        status = CDN_EIO;
    }

    return status;
}

static uint8_t WriteRegAndVerifyMasked(volatile uint32_t* address,
                       uint32_t value, uint32_t mask)
{
    uint8_t retVal;
    uint32_t reg;
    CPS_UncachedWrite32(address, value);
    reg = CPS_UncachedRead32(address);

    value &= mask;
    reg &= mask;

    if (reg == value){
        retVal = 0U;
    } else {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
            "Error: Register %p verification failed, written:%08x read:%08x \n",
            address, value, reg);
        retVal = 1U;
    }

    return retVal;
}

uint8_t IsGem1p09(const CEDI_PrivateData *pD)
{
    uint8_t result = 0U;
    switch(pD->hwCfg.moduleId){
    case GEM_GXL_MODULE_ID_V0:
        if (pD->hwCfg.moduleRev >= 0x0109U) {
            result = 1U;
        } else {
            result = 0U;
        }
        break;
    case GEM_GXL_MODULE_ID_V1:
    case GEM_GXL_MODULE_ID_V2:
    case GEM_AUTO_MODULE_ID_V0:
    case GEM_AUTO_MODULE_ID_V1:
    case GEM_10G_MODULE_ID_V0:
    case GEM_10G_MODULE_ID_V1:
        result = 1U;
        break;
    default:
        result = 0U;
        break;
    }
    return result;
}

static uint8_t IsGem1p11_(uint16_t moduleId, uint16_t moduleRev)
{
    int isSupported = 0;

    switch (moduleId){
    case GEM_GXL_MODULE_ID_V0:
    case GEM_GXL_MODULE_ID_V1:
    case GEM_GXL_MODULE_ID_V2:
    case GEM_AUTO_MODULE_ID_V0:
    case GEM_AUTO_MODULE_ID_V1:
    case GEM_10G_MODULE_ID_V0:
    case GEM_10G_MODULE_ID_V1:
    if (moduleRev >= 0x010B)
        isSupported = 1;
    break;
    }
    return isSupported;
}

uint8_t IsGem1p11(const CEDI_PrivateData* pD)
{
    return IsGem1p11_(pD->hwCfg.moduleId, pD->hwCfg.moduleRev);
}

uint8_t IsGem1p12(const CEDI_PrivateData* pD)
{
    uint8_t isSupported = 0;

    switch (pD->hwCfg.moduleId){
    case GEM_GXL_MODULE_ID_V0:
    case GEM_GXL_MODULE_ID_V1:
    case GEM_GXL_MODULE_ID_V2:
    case GEM_AUTO_MODULE_ID_V0:
    case GEM_AUTO_MODULE_ID_V1:
    case GEM_10G_MODULE_ID_V0:
    case GEM_10G_MODULE_ID_V1:
    if (pD->hwCfg.moduleRev >= 0x010CU) {
        isSupported = 1;
    }
    break;
    default:
    // default
    break;
    }
    return isSupported;
}

static uint8_t IsGem1p13_(uint16_t moduleId, uint16_t moduleRev)
{
    uint8_t isGem1p13 = 0;

    switch (moduleId){
    case GEM_GXL_MODULE_ID_V0:
    case GEM_GXL_MODULE_ID_V1:
    case GEM_GXL_MODULE_ID_V2:
    case GEM_AUTO_MODULE_ID_V0:
    case GEM_AUTO_MODULE_ID_V1:
    case GEM_10G_MODULE_ID_V0:
    case GEM_10G_MODULE_ID_V1:
    if (moduleRev >= 0x010D) {
        isGem1p13 = 1U;
    }
    break;
    default:
    // default
    break;
    }
    return isGem1p13;
}

uint8_t IsGem1p13(const CEDI_PrivateData* pD)
{
    return IsGem1p13_(pD->hwCfg.moduleId, pD->hwCfg.moduleRev);
}

uint32_t checkFunctionSupport(const CEDI_PrivateData* pD,
                             uint8_t (*IsGemVersion)(const CEDI_PrivateData* pD),
                             const char* funcName)
{
    uint32_t status = CDN_EOK;
    uint8_t isSupported;

    isSupported = IsGemVersion(pD);
    if (isSupported == 0U) {
        status = CDN_ENOTSUP;

        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                "Warning: Feature is not supported by this GEM version. Called by: %s\n", funcName);
    }

    return status;
}

uint8_t IsEnstSupported(const CEDI_PrivateData *pD)
{
    uint8_t result = 0U;
    switch(pD->hwCfg.moduleId){
    case GEM_GXL_MODULE_ID_V1:
    case GEM_GXL_MODULE_ID_V2:
    case GEM_AUTO_MODULE_ID_V0:
    case GEM_AUTO_MODULE_ID_V1:
    case GEM_10G_MODULE_ID_V0:
    case GEM_10G_MODULE_ID_V1:
        result = ((pD->hwCfg.exclude_qbv) == 0U)? 1U : 0U ;
        break;
    default:
        result = 0U;
        break;
    }
    return result;
}

uint8_t IsSetMinIpgSupported(const CEDI_PrivateData *pD)
{
    uint8_t result = 0U;
    switch(pD->hwCfg.moduleId){
    case GEM_GXL_MODULE_ID_V1:
    case GEM_GXL_MODULE_ID_V2:
    case GEM_AUTO_MODULE_ID_V0:
    case GEM_AUTO_MODULE_ID_V1:
        result = (pD->hwCfg.moduleRev >= 0x010C) ? 1U : 0U ;
        break;
    case GEM_10G_MODULE_ID_V0:
    case GEM_10G_MODULE_ID_V1:
        result = (pD->hwCfg.moduleRev >= 0x010D) ? 1U : 0U ;
        break;
    default:
        result = 0U;
        break;
    }
    return result;
}

static uint8_t is2p5GSupported(const CEDI_DesignCfg *hwCfg)
{
    uint8_t result;

    switch(hwCfg->moduleId){
    case GEM_AUTO_MODULE_ID_V1:
    case GEM_GXL_MODULE_ID_V2:
    case GEM_10G_MODULE_ID_V0:
    case GEM_10G_MODULE_ID_V1:
        result = 1U;
        break;
    default:
        result = 0U;
        break;
    }

    return result;
}

uint8_t IsLockupSupported(void *pD)
{
    return IsGem1p11(pD);
}

/* align value of "size" to size of pointer and return it.*/
static uint32_t alignedToPtr(uint32_t size)
{
    uint8_t alignment = (uint8_t) (sizeof(uintptr_t));
    uint8_t misalignment = ((alignment - 1U) & (uint8_t)size);
    uint32_t aligned = size;
    if (0U != misalignment) {
        aligned += alignment;
        aligned -= misalignment;
    }
    return (aligned);
}


uint8_t isIntrptModerateThresholdSupported(const CEDI_PrivateData* pD)
{
    uint8_t isSupported = IsGem1p11(pD);

    if (pD->hwCfg.intrpt_mod==0)
    isSupported = 0;

    return isSupported;
}

static uint32_t checkSpeedSupport(const CEDI_Config* cfg, const CEDI_DesignCfg* hwCfg, CEDI_IfSpeed speed)
{
    CEDI_IfSpeed lowSpeed = CEDI_SPEED_10M;
        CEDI_IfSpeed highSpeed = (is2p5GSupported(hwCfg) != 0U) ? CEDI_SPEED_2500M : CEDI_SPEED_1000M;
        uint32_t status;
    CEDI_Interface ifce = cfg->ifTypeSel;

    switch(ifce) {
        case CEDI_IFSP_MII:
            highSpeed = CEDI_SPEED_100M;
            break;
        case CEDI_IFSP_GMII:
            highSpeed = CEDI_SPEED_1000M;
            break;
        case CEDI_IFSP_RGMII:
            highSpeed = CEDI_SPEED_1000M;
            break;
        case CEDI_IFSP_BASE_X:
            lowSpeed = CEDI_SPEED_1000M;
            break;
        case CEDI_IFSP_XGMII:
        case CEDI_IFSP_USXGMII:
            lowSpeed = CEDI_SPEED_100M;
            highSpeed = CEDI_SPEED_25G;
            break;
                default:
            /* Speeds for SGMII interface are available
               from range 10M to 1000M/2500M */
            break;
    }

    if ((speed > highSpeed) || (speed < lowSpeed)) {
        status = CDN_ENOTSUP;
    } else {
        status = CDN_EOK;
    }

    return status;
}

uint32_t isHighSpeedSupported(const CEDI_Config* cfg, const CEDI_DesignCfg* hwCfg)
{
    uint8_t isSupported;
    uint32_t retVal;
    const CEDI_Interface* ifTypeSel = &(cfg->ifTypeSel);

    /* High-Speed is required only for CEDI_IFSP_XGMII and
       CEDI_IFSP_USXGMII */
    if ((*ifTypeSel == CEDI_IFSP_XGMII) || (*ifTypeSel == CEDI_IFSP_USXGMII)) {
        /* check if GEM version support High-Speed mode */
        isSupported = IsGem1p13_(hwCfg->moduleId, hwCfg->moduleRev);

        if (0U != isSupported) {
            /* check if hs_mac_config register exists */
            isSupported = hwCfg->gem_high_speed;
        }
    } else {
        /* interface need not High-Speed HW define */
        isSupported = 1U;
    }

    if (0U == isSupported) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                   "Warning: High-Speed mode is disabled by HW.");
    }

    retVal = (isSupported ? CDN_EOK : CDN_ENOTSUP);

    return retVal;
}

uint32_t isPcs25gSupported(const CEDI_Config* cfg, const CEDI_DesignCfg* hwCfg)
{
    uint32_t isSupported;
    bool isPcs = (hwCfg->no_pcs == 0U);
    CEDI_Interface ifce = cfg->ifTypeSel;

    /* PCS25G is only supported when is included into design and choosen
       interface is XGMII. IP version need not be checked, cos it is in
       driver initialization */
    if ((ifce == CEDI_IFSP_USXGMII) && (isPcs)) {
        isSupported = CDN_EOK;
    } else {
        isSupported = CDN_ENOTSUP;
    }

    if (isSupported != CDN_EOK) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                "WARNING: PCS25G is not supported. PCS: %u Interface: %u\n",
                isPcs, ifce);
    }

    return isSupported;
}

/* Check if FEC for PCS25G is supported
 * @param[in] pD - pointer to specific driver's data
 * @return CDN_EOK if is supported
 * @return CDN_ENOTSUP if PCS25G is not included into design, if %P_IFSP_XGMII
 * interface is not choosen or FEC is not included into design
 */
static uint32_t isFecSupported(const CEDI_PrivateData* pD)
{
    uint32_t isSupported;

    /* FEC needs to properly working USXGMII and HS. It is not checked
     * here cos driver do it during initialization process */
    isSupported = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));

    if (isSupported == CDN_EOK) {
        /* check if FEC is defined by HW */
        if (pD->hwCfg.gem_usx_include_fec == 0U) {
            isSupported = CDN_ENOTSUP;
        }

        if (isSupported != CDN_EOK) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                    "FEC is not included to this GEM configuration");
        }
    }

    return isSupported;
}

/* Some interfaces have to use PCS. Function checks, if PCS is supported by HW
 * and if driver is properly configured for it. Returns '1U' when PCS is needed
 * and defined by HW or when PCS is not needed Returns '0U" when PCS is needed,
 * but HW conditions are not satisfied.
 * @param[in] pD pointer to specific driver's PrivateData structure
 * @return 'CDN_EOK' if supported or not needed
 * @return 'CDN_ENOTSUP' if not supported
 */
static uint32_t isPcsSupported(const CEDI_Config* cfg, const CEDI_DesignCfg* hwCfg)
{
    uint32_t isSupported;
    const bool isPcs = (hwCfg->no_pcs == 0U);
    const CEDI_Interface ifType = cfg->ifTypeSel;

    /* PCS have to be defined for: CEDI_IFSP_SGMII,
     * CEDI_IFSP_BASE_X and CEDI_IFSP_USXGMII */
    if ((ifType == CEDI_IFSP_SGMII) || (ifType == CEDI_IFSP_BASE_X)) {
        isSupported = (isPcs ? CDN_EOK : CDN_ENOTSUP);
    }
        else if (ifType == CEDI_IFSP_USXGMII) {
        isSupported = isPcs25gSupported(cfg, hwCfg);
    }
        else {
        /* chosen interface don't need PCS */
        isSupported = CDN_EOK;
    }

    if (isSupported != CDN_EOK) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
            "Error: config struct specifies interface type (%u) which requires"\
            " PCS but this is not supported by EMAC HW.\n", ifType);
    }

    return isSupported;
}

/* These functions intentionally violate MISRA C rules, to allow pointer
 * casts and/or manipulations required for driver operation. */

/* Adds register base address to offset, in-place */
void addRegBase(const CEDI_PrivateData *pD, volatile uint32_t **ptr)
{
    *ptr = (volatile uint32_t*)((volatile uint8_t*)(*ptr) +
                    pD->cfg.regBase);
}

/* Casts unsigned integer (as uintptr_t) to pointer.
 * Purpose of each call of this function should be known. */
uint32_t *uintptrToPtrU32(uintptr_t addr)
{
    return ((uint32_t *)addr);
}

/* Casts registers base address, represented as integer, to pointer to struct */
static struct emac_regs *regBaseToPtr(uintptr_t regBase)
{
    return ((struct emac_regs *)regBase);
}

/* Calculates address to be used as beginning of TX/RX descriptor address list
 * in memory allocated by user, after private data (pD).
 * Second parameter defines offset, relative to pD. */
static uintptr_t *calcDescListStartAddr(CEDI_PrivateData *pD, uint32_t offset)
{
    return ((uintptr_t *)((uint8_t *)pD + offset));
}

/* Casts Rx descriptor virtual address, represented as integer,
 * to pointer of sppropriate CEDI_RxDesc* type */
CEDI_RxDesc *rxDescAddrToPtr(uintptr_t descAddr)
{
    return ((CEDI_RxDesc *)descAddr);
}

/* Adds value of offset (which may be positive or negative) to Rx descriptor
 * pointer, in-place. Offset should have relatively small absolute value */
void moveRxDescAddr(CEDI_RxDesc **ptr, int32_t offset)
{
    if (offset > ((int32_t)0) ) {
        *ptr = (CEDI_RxDesc *)(((uintptr_t)*ptr) + (uintptr_t) offset);
    } else {
        *ptr = (CEDI_RxDesc *)(((uintptr_t)*ptr) - ((uintptr_t) (offset*(-1))));
    }
}

/* end of pointer-related functions. */

void getJumboFramesRx(const CEDI_PrivateData *pD, uint8_t *enable)
{
    *enable= (uint8_t) (EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__READ(
            CPS_UncachedRead32(&(pD->regs->network_config))));
}

/** Get pointer of qx_control register for given queue. */
volatile uint32_t* getQxControlRegAddr(const CEDI_PrivateData *pD, uint8_t queueNum) {
    volatile uint32_t *ptr = (uint32_t *) qControlReg[queueNum];
    addRegBase(pD, &ptr);
    return ptr;
}

/** Get pointer of qx_status register for given queue. */
volatile uint32_t* getQxStatusRegAddr(const CEDI_PrivateData *pD, uint8_t queueNum) {
    volatile uint32_t *ptr = (uint32_t *) qStatusReg[queueNum];
    addRegBase(pD, &ptr);
    return ptr;
}

static void getFullDuplex(const CEDI_PrivateData *pD, uint8_t *enable)
{
    *enable= (uint8_t) (EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__READ(
            CPS_UncachedRead32(&(pD->regs->network_config))));

}

static struct emac_regs *getMmslRegs(CEDI_PrivateData *pD)
{
    CEDI_PrivateData *ppD;
    if (pD->macType == CEDI_MAC_TYPE_EMAC) {
        ppD = pD->otherMac;
    } else {
        ppD = pD;
    }
    return (ppD->regs);

}

/** Enable or disable TX extended BD mode for given queue */
static uint32_t setTxQBDExtendedModeEn(const CEDI_PrivateData *pD, uint8_t queueNum, bool enable) {
    uint32_t status = CDN_EOK;
    // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
    if (pD->hwCfg.gem_vm == false) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
        status = CDN_ENOTSUP;
    }
    // check of queue number
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.txQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t val = CPS_UncachedRead32(regPtr);
        EMAC_REGS__Q_CONTROL__TX_BD_EXTENDED_MODE_EN__MODIFY(val, enable ? 1U : 0U);
        status = WriteRegAndVerify(regPtr, val);
    }
    return status;
}

/** Enable or disable RX extended BD mode for given queue */
static uint32_t setRxQBDExtendedModeEn(const CEDI_PrivateData *pD, uint8_t queueNum, bool enable) {
    uint32_t status = CDN_EOK;
    // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
    if (pD->hwCfg.gem_vm == false) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
        status = CDN_ENOTSUP;
    }
    // check of queue number
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t val = CPS_UncachedRead32(regPtr);
        EMAC_REGS__Q_CONTROL__RX_BD_EXTENDED_MODE_EN__MODIFY(val, enable ? 1U : 0U);
        status = WriteRegAndVerify(regPtr, val);
    }
    return status;
}

/* Calculate the descriptor sizes (in bytes) for a given DMA config (in pD) */
static void calcDescriptorSizes(const CEDI_Config *config, bool gem_vm,
        uint16_t txDescSize[CEDI_MAX_TX_QUEUES],
        uint16_t rxDescSize[CEDI_MAX_RX_QUEUES]) {

    /* use 1 contiguous block for Tx descriptor lists
     * and another contiguous block for Rx descriptor lists */
    uint8_t q;
    for (q = 0U; q < config->txQs; q++) {
        txDescSize[q] = CEDI_TWO_BD_WORD_SIZE;
    }
    for (q = 0U; q < config->rxQs; q++) {
        rxDescSize[q] = CEDI_TWO_BD_WORD_SIZE;
    }

    // DMA address bus width. 0 =32b , 1=64b
    if (CEDI_DMA_ADDR_BUS_WIDTH_32 != config->dmaAddrBusWidth) {
        for (q = 0U; q < config->txQs; q++) {
            txDescSize[q] += CEDI_TWO_BD_WORD_SIZE;
        }
        for (q = 0U; q < config->rxQs; q++) {
            rxDescSize[q] += CEDI_TWO_BD_WORD_SIZE;
        }
    }

    // if gem_vm is enabled (qx_status and qx_control registers available)
    if (gem_vm == true) {
        // adjust values for all queues
        for (q = 0U; q < config->txQs; q++) { // tx
            if (0U != config->enTxExtBD[q]) {
                txDescSize[q] += CEDI_TWO_BD_WORD_SIZE;
            }
        }
        for (q = 0U; q < config->rxQs; q++) { // rx
            if (0U != config->enRxExtBD[q]) {
                rxDescSize[q] += CEDI_TWO_BD_WORD_SIZE;
            }
        }
    } else { // adjust for all queues by the same amount
        if (0U != config->enTxExtBD[0]) {
            for (q = 0U; q < config->txQs; q++) { // tx
                txDescSize[q] += CEDI_TWO_BD_WORD_SIZE;
            }
        }
        if (0U != config->enRxExtBD[0]) {
            for (q = 0U; q < config->rxQs; q++) { // rx
                rxDescSize[q] += CEDI_TWO_BD_WORD_SIZE;
            }
        }
    }
    for (q=0; q< config->txQs; q++){
        vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s, q %d: tx desc size %d, rx %d\n",
                __func__, q, txDescSize[q], rxDescSize[q]);
    }
}

/* Calculate the size of contiguous block of Tx descriptor lists */
static uint32_t sumTxDescriptorsListSize(const CEDI_Config *config,
        uint16_t txDescSize[CEDI_MAX_TX_QUEUES]) {
    uint16_t q;
    uint32_t sumTxDescSize = 0U;

    for (q = 0U; q < config->txQs; q++) {
        /* allow 1 extra for "endstop" descriptor */
        sumTxDescSize += txDescSize[q] * ((uint32_t) ((config->txQLen)[q]) + CEDI_MIN_TXBD);
    }
    return sumTxDescSize;
}

/* Calculate the size of contiguous block of Rx descriptor lists */
static uint32_t sumRxDescriptorsListSize(const CEDI_Config *config,
        uint16_t rxDescSize[CEDI_MAX_RX_QUEUES]) {
    uint16_t q;
    uint32_t sumRxDescSize = 0U;

    for (q = 0U; q < config->rxQs; q++) {
        /* allow 1 extra for "endstop" descriptor */
        sumRxDescSize += rxDescSize[q] * ((uint32_t) ((config->rxQLen)[q]) + CEDI_MIN_RXBD);
    }
    return sumRxDescSize;
}

/* Calculate number of TX descriptors for all queues */
static uint32_t numTxDescriptors(const CEDI_Config *config)
{
    uint16_t i;
    uint32_t sumTxDesc = 0U;

    for (i=0U; i<config->txQs; i++) {
        /* allow 1 extra for "endstop" descriptor */
        sumTxDesc += ((uint32_t)((config->txQLen)[i])+CEDI_MIN_TXBD);
    }
    return (sumTxDesc);
}

static uint32_t numRxDescriptors(const CEDI_Config *config)
{
    uint16_t i;
    uint32_t sumRxDesc = 0U;

    for (i=0U; i<config->rxQs; i++) {
        /* allow 1 extra for "endstop" descriptor */
        sumRxDesc += ((uint32_t)((config->rxQLen)[i])+CEDI_MIN_RXBD);
    }
    return (sumRxDesc);
}

static uint32_t initTxDescLists(CEDI_PrivateData *pD)
{
    uint32_t status = CDN_EOK;
    uint8_t q;
    uint32_t offset;

    /* set start of Tx vAddr lists - place in pD block after
     * privateData struct */
    offset = alignedToPtr((uint32_t) sizeof(CEDI_PrivateData));

    pD->txQueue[0U].vAddrList = calcDescListStartAddr(pD, offset);
    for (q=0U; q<pD->txQs; q++) {
        if (0U != CEDI_ResetTxQ(pD, q)) {
            status = CDN_EINVAL;
            break;
        }
    }

    return status;
}

/* Initialise Rx descriptor lists - also in pD block, after the Tx ones */
static uint32_t initRxDescLists(CEDI_PrivateData *pD)
{
    uint8_t q;
    uint32_t pAddr, i, status = CDN_EOK;
    uint32_t offset;
    uintptr_t vAddr;
    CEDI_RxQueue *rxQ;
    CEDI_RxDesc* descPtr;

    /* set start of Rx vAddr lists after Tx lists */
    offset = ((uint32_t) (alignedToPtr((uint16_t)sizeof(CEDI_PrivateData))) +
                ((uint16_t)sizeof(uintptr_t))*(numTxDescriptors(&(pD->cfg))));
    pD->rxQueue[0U].rxBufVAddr = calcDescListStartAddr(pD, offset);

    for (q=0U; q<pD->cfg.rxQs; q++) {

        rxQ = &(pD->rxQueue[q]);
        rxQ->numRxDesc = pD->cfg.rxQLen[q] + CEDI_MIN_RXBD;

        if (findQBaseAddr(pD, q, rxQ, &pAddr, &vAddr)) {
            status = CDN_EINVAL;
            break;
        }
        rxQ->rxDescStart = rxDescAddrToPtr(vAddr);

        /* initialise the descriptors */
        descPtr = rxQ->rxDescStart;
        for (i = 0U; i<rxQ->numRxDesc; i++) {
            CPS_UncachedWrite32((uint32_t *)
                    &descPtr->word[0U], (uint32_t)((0U != i)?0U:(CEDI_RXD_WRAP|CEDI_RXD_USED)));
            CPS_UncachedWrite32((uint32_t *)
                    &(descPtr->word[1U]), CEDI_RXD_EMPTY);
            moveRxDescAddr(&descPtr, pD->rxDescriptorSize[q]);
        }

        if (0U!=CEDI_ResetRxQ(pD, q, 0U)) {
            status = CDN_EINVAL;
            break;
        }
    }

    return status;
}

/* return the number of priority queues available in the h/w config */
static uint8_t maxHwQs(struct emac_regs *regBase) {
    uint8_t qCount = 1U;
    uint32_t reg = CPS_UncachedRead32(&(regBase->designcfg_debug6));
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE2__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE3__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE4__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE5__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE6__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE7__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE8__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE9__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE10__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE11__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE12__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE13__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE14__READ(reg)) {
        qCount++;
    }
    if (0U != EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE15__READ(reg)) {
        qCount++;
    }
    return (qCount);
}

static void disableAllInterrupts(const CEDI_PrivateData *pD)
{
    volatile uint32_t *regPtr = NULL;
    uint8_t i;

    for (i = 1U; i < pD->numQs; i++) {
        regPtr = intDisableReg[i-1U];
        addRegBase(pD, &regPtr);
        CPS_REG_WRITE(regPtr, 0xFFFFFFFFU);
    }
    /* disable interrupts for PCS25G module if exists */
    if (pD->hwCfg.no_pcs == 0U) {
        CPS_REG_WRITE(&(pD->regs->usx_interrupt_disable_register), 0xFFFFFFFFU);
    }
    CPS_UncachedWrite32(&(pD->regs->int_disable), 0xFFFFFFFFU);
}

static void clearAllInterruptsByWrite(const CEDI_PrivateData *pD)
{
    volatile uint32_t *regPtr = NULL;
    uint8_t i;

    for (i = 1U; i < pD->numQs; i++) {
        regPtr = intStatusReg[i-1U];
        addRegBase(pD, &regPtr);
        CPS_UncachedWrite32(regPtr, 0xFFFFFFFFU);
    }
    CPS_UncachedWrite32(&(pD->regs->int_status), 0xFFFFFFFFU);
}

static void clearAllInterruptsByRead(const CEDI_PrivateData *pD)
{
    /* Read function is not used to get register value, but only
       for inform HW that interrupt mark was read by SW */
    (void)CPS_UncachedRead32(&(pD->regs->int_status));

    volatile uint32_t *regPtr = NULL;
    uint8_t i;

    for (i = 1U; i < pD->numQs; i++) {
        regPtr = intStatusReg[i-1U];
        addRegBase(pD, &regPtr);
        (void)CPS_UncachedRead32(regPtr);
    }

}

static void clearAllInterrupts(const CEDI_PrivateData *pD)
{
    if (0U==pD->hwCfg.irq_read_clear) {
        clearAllInterruptsByWrite(pD);
    }
    else {
        clearAllInterruptsByRead(pD);
    }

    /* clear interrupts for PCS25G module if exists.
       PCS25G interrupts are cleared by write '1' */
    if (pD->hwCfg.no_pcs == 0U) {
        CPS_REG_WRITE(&(pD->regs->usx_interrupt_disable_register), 0xFFFFFFFFU);
    }

}

/* Return all registers to reset values */
static uint32_t initAllRegs(const CEDI_PrivateData *pD)
{
    uint32_t status = CDN_EOK;

    status |= WriteRegAndVerify(&(pD->regs->network_control), 0U);
    status |= WriteRegAndVerify(&(pD->regs->network_config), 0U);

    if (0!=pD->hwCfg.user_io) {
        status |= WriteRegAndVerify(&(pD->regs->user_io_register), 0U);
    }

    CPS_UncachedWrite32(&(pD->regs->transmit_status), 0U);
    CPS_UncachedWrite32(&(pD->regs->receive_status), 0U);
    CPS_UncachedWrite32(&(pD->regs->int_disable), 0xFFFFFFFFU);
    status |= WriteRegAndVerify(&(pD->regs->phy_management), 0U);

    status |= WriteRegAndVerify(&(pD->regs->pbuf_txcutthru),
                ((1 << pD->hwCfg.tx_pbuf_addr) - 1));
    status |= WriteRegAndVerify(&(pD->regs->pbuf_rxcutthru),
                ((1 << pD->hwCfg.rx_pbuf_addr) - 1));

    status |= WriteRegAndVerify(&(pD->regs->jumbo_max_length), 0x00002800U);

    if (pD->hwCfg.ext_fifo_interface != 0){
    if (CEDI_MAC_TYPE_EMAC != pD->macType)
        status |= WriteRegAndVerify(&(pD->regs->external_fifo_interface), 0U);
    }

    if (pD->hwCfg.axi != 0U) {
        status |= WriteRegAndVerify(&(pD->regs->axi_max_pipeline), 0x00000101U);
    }

    if ((CEDI_MAC_TYPE_EMAC != pD->macType) && (pD->hwCfg.pbuf_rsc != 0)) {
        status |= WriteRegAndVerify(&(pD->regs->rsc_control), 0U);
    }

    status |= WriteRegAndVerify(&(pD->regs->int_moderation), 0U);
    status |= WriteRegAndVerify(&(pD->regs->sys_wake_time), 0U);

    status |= WriteRegAndVerify(&(pD->regs->hash_bottom), 0U);
    status |= WriteRegAndVerify(&(pD->regs->hash_top), 0U);
    status |= WriteRegAndVerify(&(pD->regs->wol_register), 0U);

    status |= WriteRegAndVerify(&(pD->regs->stretch_ratio), 0U);

    status |= WriteRegAndVerify(&(pD->regs->stacked_vlan), 0U);
    status |= WriteRegAndVerify(&(pD->regs->tx_pfc_pause), 0U);
    status |= WriteRegAndVerify(&(pD->regs->mask_add1_bottom), 0U);
    status |= WriteRegAndVerify(&(pD->regs->mask_add1_top), 0U);
    status |= WriteRegAndVerify(&(pD->regs->dma_addr_or_mask), 0U);
    status |= WriteRegAndVerify(&(pD->regs->rx_ptp_unicast), 0U);
    status |= WriteRegAndVerify(&(pD->regs->tx_ptp_unicast), 0U);

    if (pD->hwCfg.tsu != 0U) {
        status |= WriteRegAndVerify(&(pD->regs->tsu_nsec_cmp), 0U);
        status |= WriteRegAndVerify(&(pD->regs->tsu_sec_cmp), 0U);
        status |= WriteRegAndVerify(&(pD->regs->tsu_msb_sec_cmp), 0U);
    }

    status |= WriteRegAndVerify(&(pD->regs->dpram_fill_dbg), 0U);

    if (0U == pD->hwCfg.no_pcs){
        if (pD->macType != CEDI_MAC_TYPE_EMAC){
            uint32_t mask = (EMAC_REGS__PCS_CONTROL__COLLISION_TEST__MASK
                     | EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__MASK
                     | EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__MASK
                     | EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__MASK);

            status |= WriteRegAndVerifyMasked(&(pD->regs->pcs_control), 0U, mask);
            status |= WriteRegAndVerify(&(pD->regs->pcs_an_adv), 0U);
            status |= WriteRegAndVerify(&(pD->regs->pcs_an_np_tx), 0U);
        }
    }

    if (pD->hwCfg.pfc_multi_quantum == 0){
        status |= WriteRegAndVerify(&(pD->regs->tx_pause_quantum), 0x0000FFFFU);
    } else {
        status |= WriteRegAndVerify(&(pD->regs->tx_pause_quantum), 0xFFFFFFFFU);
        status |= WriteRegAndVerify(&(pD->regs->tx_pause_quantum1), 0xFFFFFFFFU);
        status |= WriteRegAndVerify(&(pD->regs->tx_pause_quantum2), 0xFFFFFFFFU);
        status |= WriteRegAndVerify(&(pD->regs->tx_pause_quantum3), 0xFFFFFFFFU);
    }

    CPS_UncachedWrite32(&(pD->regs->rx_lpi), 0U);
    CPS_UncachedWrite32(&(pD->regs->rx_lpi_time), 0U);
    CPS_UncachedWrite32(&(pD->regs->tx_lpi), 0U);
    CPS_UncachedWrite32(&(pD->regs->tx_lpi_time), 0U);
    status |= WriteRegAndVerify(&(pD->regs->dpram_fill_dbg), 0U);

    if (pD->hwCfg.exclude_cbs == 0) {
        status |= WriteRegAndVerify(&(pD->regs->cbs_control), 0U);
        status |= WriteRegAndVerify(&(pD->regs->cbs_idleslope_q_a), 0U);
        status |= WriteRegAndVerify(&(pD->regs->cbs_idleslope_q_b), 0U);
    }

    if (pD->hwCfg.dma_addr_width != 0){
        status |= WriteRegAndVerify(&(pD->regs->upper_tx_q_base_addr), 0U);
        status |= WriteRegAndVerify(&(pD->regs->upper_rx_q_base_addr), 0U);
    }

    if ((pD->hwCfg.tsu != 0U) && (pD->hwCfg.rx_pkt_buffer != 0U)
    && (pD->hwCfg.tx_pkt_buffer != 0U)) {
        status |= WriteRegAndVerify(&(pD->regs->tx_bd_control), 0U);
        status |= WriteRegAndVerify(&(pD->regs->rx_bd_control), 0U);
    }

    return status;
}

/* Internal struct used to check, that selected callbacks hav non-null adresses */
struct CbSelectionCheck {
        uint32_t flags;
        void *ptr;
};

/* Check if selected PCS25G callbacks have non-null adresses.
 * @params interrupts bit-flags defining callback selection
 * @return 0U if success (not NULL)
 * @return OR'd combination of evenets whose Cb function pointers are NULL
 */
static uint8_t pcs25gCbNullChecker(const CEDI_Callbacks *cb, uint32_t interrupts)
{
    struct CbSelectionCheck selectionCheck[] = {
            {((uint32_t)CEDI_EV_PCS25G_FEC_CORRECT | (uint32_t)CEDI_EV_PCS25G_FEC_UNCORRECT), cb->fecError},
            {((uint32_t)CEDI_EV_PCS25G_FEC_BLOCK_LOCK), cb->syncEvent},
            {((uint32_t)CEDI_EV_PCS25G_BER), cb->highBitError},
            {0U, NULL}
    };

    struct CbSelectionCheck* callback = selectionCheck;
    uint8_t nullCallbacks = 0U;

    while (callback->flags != 0U) {
        if (((interrupts & callback->flags) != 0U) && (callback->ptr == NULL)) {
            nullCallbacks |= callback->flags;
        }
        callback++;
    }

    return nullCallbacks;
}

/* Check the selected callback(s) have non-NULL call addresses.
 * Test all events selected, returning any with NULL callbacks.
 * @param checkSelection - bit-flags defining callback selection
 * @return 0 if all OK (not NULL)
 * @return OR'd combination of events whose cb function pointers are NULL
 */
static uint32_t callbacksNullCheck(const CEDI_Callbacks *cb, uint32_t checkSelection)
{
    uint32_t nullCbEvents = 0U;
    uint32_t selection = checkSelection;

    struct CbSelectionCheck check[] = {
        { ((uint32_t)CEDI_EV_TX_COMPLETE | (uint32_t)CEDI_EV_TX_USED_READ), cb->txEvent },
        { ((uint32_t)CEDI_EV_RX_COMPLETE), cb->rxFrame },        { ((uint32_t)CEDI_EV_TX_UNDERRUN | (uint32_t)CEDI_EV_TX_RETRY_EX_LATE_COLL | (uint32_t)CEDI_EV_TX_FR_CORRUPT), cb->txError },
        { ((uint32_t)CEDI_EV_RX_USED_READ | (uint32_t)CEDI_EV_RX_OVERRUN), cb->rxError },
        { ((uint32_t)CEDI_EV_MAN_FRAME), cb->phyManComplete },
        { ((uint32_t)CEDI_EV_HRESP_NOT_OK), cb->hrespError },
        { ((uint32_t)CEDI_EV_PCS_LP_PAGE_RX), cb->lpPageRx },
        { ((uint32_t)CEDI_EV_PCS_AN_COMPLETE), cb->anComplete },
        { ((uint32_t)CEDI_EV_PCS_LINK_CHANGE_DET), cb->linkChange },
        { ((uint32_t)CEDI_EV_PAUSE_FRAME_TX | (uint32_t)CEDI_EV_PAUSE_TIME_ZERO | (uint32_t)CEDI_EV_PAUSE_NZ_QU_RX), cb->pauseEvent },
        { ((uint32_t)CEDI_EV_LPI_CH_RX), cb->lpiStatus },
        { ((uint32_t)CEDI_EV_WOL_RX), cb->wolEvent },
        { ((uint32_t)CEDI_EV_EXT_INTR), cb->extInpIntr },
        { ((uint32_t)CEDI_EV_PTP_TX_DLY_REQ | (uint32_t)CEDI_EV_PTP_TX_SYNC), cb->ptpPriFrameTx },
        { ((uint32_t)CEDI_EV_PTP_TX_PDLY_REQ | (uint32_t)CEDI_EV_PTP_TX_PDLY_RSP), cb->ptpPeerFrameTx },
        { ((uint32_t)CEDI_EV_PTP_RX_DLY_REQ | (uint32_t)CEDI_EV_PTP_RX_SYNC), cb->ptpPriFrameRx },
        { ((uint32_t)CEDI_EV_PTP_RX_PDLY_REQ | (uint32_t)CEDI_EV_PTP_RX_PDLY_RSP), cb->ptpPeerFrameRx },
        { ((uint32_t)CEDI_EV_TSU_SEC_INC | (uint32_t)CEDI_EV_TSU_TIME_MATCH), cb->tsuEvent },
        { ((uint32_t)CEDI_EV_RX_LOCKUP | (uint32_t)CEDI_EV_TX_LOCKUP), cb->lockupEvent },

        { (0U), (0U) }
    };

    struct CbSelectionCheck *ptr_check = check;
    while ((ptr_check->flags != 0U) && (selection != 0U)) {
        if (((selection & ptr_check->flags) != 0U) && (ptr_check->ptr == NULL)) {
            nullCbEvents |= ptr_check->flags;
            selection &= ~ptr_check->flags;
        }
        ptr_check++;
    }

    if (0U != nullCbEvents) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                "Error: Callback = NULL for event(s) 0x%08X\n", nullCbEvents);
    }

    return (nullCbEvents);
}

/* initializing the upper 32 bit buffer queue base addresses from config */
static uint32_t initUpper32BuffQAddr(CEDI_PrivateData *pD)
{
    uint32_t regData;
    uint32_t status = CDN_EOK;

    regData = 0U;

    if (pD->hwCfg.dma_addr_width != 0){
    EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__MODIFY(
        regData, pD->cfg.upper32BuffTxQAddr);

    status |= WriteRegAndVerify(&(pD->regs->upper_tx_q_base_addr), regData);

    regData = 0U;
    EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__MODIFY(
        regData, pD->cfg.upper32BuffRxQAddr);

    status |= WriteRegAndVerify(&(pD->regs->upper_rx_q_base_addr), regData);
    }

    return status;
}

static uint32_t checkAxiPipeline(const CEDI_Config* config, const CEDI_DesignCfg* hwCfg)
{
    uint8_t axiMaxPipelineBits;
    uint32_t axiPipelineFifoDepth;
    uint32_t status = CDN_EOK;

    if (hwCfg->axi != 0U) {

        if (IsGem1p13_(hwCfg->moduleId, hwCfg->moduleRev) == 1U) {
            axiMaxPipelineBits = (uint8_t)CEDI_AXI_MAX_PIPELINE_BITS_1P13;
        } else {
            axiMaxPipelineBits = (uint8_t)CEDI_AXI_MAX_PIPELINE_BITS_1P12;
        }

        if (hwCfg->axi_access_pipeline_bits > axiMaxPipelineBits) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "*** ERROR: Incorrect axi_access_pipeline_bits was read from"\
                "hardware register");
            status = CDN_EIO;
        }

        if (CDN_EOK == status) {

            axiPipelineFifoDepth = (uint32_t)((uint32_t)1U<<(uint32_t)hwCfg->axi_access_pipeline_bits);

            if (config->ar2rMaxPipeline > axiPipelineFifoDepth) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "*** ERROR: ar2rMaxPipeline requested "\
                        "value (%u) greater than fifo depth (%u)\n",
                        config->ar2rMaxPipeline, axiPipelineFifoDepth, axiPipelineFifoDepth);
                status = CDN_EINVAL;
            }
        }

        if (CDN_EOK == status) {
            /* value of max pipeline must not greater than fifo depth */
            if (config->aw2bMaxPipeline > axiPipelineFifoDepth) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "*** ERROR: aw2bMaxPipeline requested "\
                            "value (%u) greater than fifo depth (%u)\n",
                            config->aw2bMaxPipeline, axiPipelineFifoDepth, axiPipelineFifoDepth);
                status = CDN_EINVAL;
            }
        }
    }

    return status;
}

/* Initialise axi_max_pipeline register from config struct */
static uint32_t initAxiMaxPipelineReg(const CEDI_PrivateData *pD)
{
    const CEDI_Config *config = &(pD->cfg);
    uint32_t regVal;
    volatile uint32_t* regAddr;
    uint8_t status = CDN_EOK;

    if (pD->hwCfg.axi != 0U) {

        regAddr = &(pD->regs->axi_max_pipeline);
        regVal = CPS_REG_READ(regAddr);

        EMAC_REGS__AXI_MAX_PIPELINE__AW2B_MAX_PIPELINE__MODIFY(regVal, config->aw2bMaxPipeline);
        EMAC_REGS__AXI_MAX_PIPELINE__AR2R_MAX_PIPELINE__MODIFY(regVal, config->ar2rMaxPipeline);

        status = WriteRegAndVerify(regAddr, regVal);
    }

    return status;
}

/* Initialise Network Control register from config struct */
static uint32_t initNetControlReg(const CEDI_PrivateData *pD)
{
    const CEDI_Config *config = &(pD->cfg);
    uint32_t regVal = 0U;
    uint32_t regTemp;
    volatile uint32_t* regAddr = &(pD->regs->network_control);
    uint32_t retVal = CDN_EOK;


    /* Disable everything first to be safe */
    CPS_REG_WRITE(regAddr, regVal);

    if (0U != config->enableMdio) {
        EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__SET(regVal);
    }

        if (0U != config->altSgmiiEn) {
        EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__SET(regVal);
    }

    if ((config->ifTypeSel == CEDI_IFSP_XGMII) || (config->ifTypeSel == CEDI_IFSP_USXGMII)) {
        EMAC_REGS__NETWORK_CONTROL__ENABLE_HS_MAC__SET(regVal);
    }

    if ((config->ifTypeSel < CEDI_IFSP_XGMII) && (config->ifSpeedSel == CEDI_SPEED_2500M)) {
        EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__SET(regVal);
    }

        if (0U != config->storeUdpTcpOffset) {
        EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__SET(regVal);
    }

        /* for ext. TSU require tsu configured */
    if (((config->enExtTsuPort) != 0U) && (pD->hwCfg.tsu != 0U)) {
        EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__SET(regVal);
    }

        /* pfc multi quantum functionality */
    if(0U != config->pfcMultiQuantum) {
        EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__SET(regVal);
    }

    /* clear stats */
    EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__SET(regVal);

    CPS_REG_WRITE(regAddr, regVal);

    regTemp = CPS_REG_READ(regAddr);

    // clear write only bit
    regVal  &= ~EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__MASK;
    regTemp &= ~EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__MASK;

    if (regVal != regTemp) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                "Error: Register %p verification failed, written:%08x read:%08x \n",
                regAddr, regVal, regTemp);

        retVal = CDN_EIO;
    }

    return retVal;
}
/* Check, if register is supported by this GEM version. If is, initialize register.
   If not, everything is okay, driver dont put values there. */
static uint32_t initHsMacConfigReg(const CEDI_PrivateData* pD)
{
    const CEDI_Config *cfg = &(pD->cfg);
    uint32_t reg;
    uint32_t status;

    status = (cfg->ifTypeSel >= CEDI_IFSP_XGMII) ? CDN_EOK : CDN_ENOTSUP;

    if (CDN_EOK == status) {
        /* initialize hs_mac_config register */
        reg = CPS_REG_READ(&(pD->regs->hs_mac_config));

        EMAC_REGS__HS_MAC_CONFIG__PREAMBLE_IN_CRC_TX__MODIFY(reg, cfg->preInCrcTx);
        EMAC_REGS__HS_MAC_CONFIG__PREAMBLE_IN_CRC_RX__MODIFY(reg, cfg->preInCrcRx);
        EMAC_REGS__HS_MAC_CONFIG__HS_MAC_SPEED__MODIFY(reg, ((uint8_t)cfg->ifSpeedSel - 1U));

        status = WriteRegAndVerify(&(pD->regs->hs_mac_config), reg);
    } else {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                "High speed mode was not chosen. Register not changed.");
    }

    return status;
}

static uint32_t initUsxControlReg(CEDI_PrivateData* pD, const CEDI_Pcs25gCfg* pcsCfg)
{
    uint32_t status;
    volatile uint32_t* regAddr = &(pD->regs->usx_control_register);
    uint32_t regVal;

    /* Clear register */
    CPS_REG_WRITE(regAddr, 0U);

    /* These bits must be set the same as in High Speed MAC config register */
    regVal  = EMAC_REGS__USX_CONTROL_REGISTER__HS_MAC_SPEED__WRITE((uint8_t)pD->cfg.ifSpeedSel - 1U);

    regVal |= EMAC_REGS__USX_CONTROL_REGISTER__SERDES_RATE__WRITE(pcsCfg->serdesRate);

    if (pcsCfg->rxScrBypass) {
        EMAC_REGS__USX_CONTROL_REGISTER__RX_SCR_BYPASS__SET(regVal);
    }

    if (pcsCfg->txScrBypass) {
        EMAC_REGS__USX_CONTROL_REGISTER__TX_SCR_BYPASS__SET(regVal);
    }

    if(isFecSupported(pD) == CDN_EOK) {
        if (pcsCfg->fecErrInd) {
            EMAC_REGS__USX_CONTROL_REGISTER__FEC_ENA_ERR_IND__SET(regVal);
        }

        if (pcsCfg->fecEnable) {
            EMAC_REGS__USX_CONTROL_REGISTER__FEC_ENABLE__SET(regVal);
        }
    }

    if (!pcsCfg->rxDatapathEnable) {
        EMAC_REGS__USX_CONTROL_REGISTER__RX_SYNC_RESET__SET(regVal);
        pD->isRxDatapathEnabled = false;
    } else {
        pD->isRxDatapathEnabled = true;
    }

    if (pcsCfg->txDatapathEnable) {
        EMAC_REGS__USX_CONTROL_REGISTER__TX_DATAPATH_EN__SET(regVal);
        pD->isTxDatapathEnabled = true;
    }

    status = WriteRegAndVerify(regAddr, regVal);

    return status;
}


/* set Rx buffer sizes for Q>0 */
static uint32_t setRxQBufferSizes(const CEDI_PrivateData *pD, const CEDI_Config *config)
{
    uint32_t reg, q;
    volatile uint32_t *regPtr = NULL;
    uint32_t status = CDN_EOK;

    if (pD->cfg.rxQs <= 1U) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s: function only supported when cfg.rxQs>0", __func__);
        status = CDN_ENOTSUP; // function is not applicable if there is only one queue
    }
    if (CDN_EOK == status) {
        // if gem_vm is enabled (qx_status and qx_control registers available)
        if (pD->hwCfg.gem_vm == true) {
            // use new per-queue control registers
            for (q = 1U; q < (pD->cfg.rxQs); q++) {
                volatile uint32_t *regPtr = getQxControlRegAddr(pD, q);

                reg = CPS_UncachedRead32(regPtr);
                EMAC_REGS__Q_CONTROL__RX_BUF_SIZE__MODIFY(reg, config->rxBufLength[q]);
                status = WriteRegAndVerify(regPtr, reg);
                if (status != CDN_EOK) {
                    break;
                }
            }

        } else {
            // use older method
            volatile uint32_t* const dmaRxbufSizeReg[15U] = {
                CEDI_RegOff(dma_rxbuf_size_q1),
                CEDI_RegOff(dma_rxbuf_size_q2),
                CEDI_RegOff(dma_rxbuf_size_q3),
                CEDI_RegOff(dma_rxbuf_size_q4),
                CEDI_RegOff(dma_rxbuf_size_q5),
                CEDI_RegOff(dma_rxbuf_size_q6),
                CEDI_RegOff(dma_rxbuf_size_q7),
                CEDI_RegOff(dma_rxbuf_size_q8),
                CEDI_RegOff(dma_rxbuf_size_q9),
                CEDI_RegOff(dma_rxbuf_size_q10),
                CEDI_RegOff(dma_rxbuf_size_q11),
                CEDI_RegOff(dma_rxbuf_size_q12),
                CEDI_RegOff(dma_rxbuf_size_q13),
                CEDI_RegOff(dma_rxbuf_size_q14),
                CEDI_RegOff(dma_rxbuf_size_q15)
            };

            for (q=1U; q<pD->cfg.rxQs; q++) {
                reg = 0U;
                EMAC_REGS__DMA_RXBUF_SIZE_Q__DMA_RX_Q_BUF_SIZE__MODIFY(
                                        reg, config->rxBufLength[q]);
                regPtr = dmaRxbufSizeReg[q-1U];
                addRegBase(pD, &regPtr);
                status = WriteRegAndVerify(regPtr, reg);
                if (CDN_EIO == status) {
                    break;
                }
            }
        }
    }
    return status;
}

/* Initialise DMA Config register from config struct */
static uint32_t initDmaConfigReg(const CEDI_PrivateData *pD)
{
    const CEDI_Config *config = &(pD->cfg);
    uint32_t regTmp = 0U, status = CDN_EOK;

    // convert enums to uint32_t (enum values are as defined in dma_config register)
    EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__MODIFY(regTmp, (uint32_t) (config->dmaDataBurstLen));
    EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__MODIFY(regTmp, config->rxPktBufSize);
    EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__MODIFY(regTmp, config->txPktBufSize);
    EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__MODIFY(regTmp, (uint32_t) (config->dmaAddrBusWidth));

    if (0U != (config->dmaEndianism & (uint8_t)CEDI_END_SWAP_DESC)) {
        EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__SET(regTmp);
    }
    if (0U != (config->dmaEndianism & (uint8_t)CEDI_END_SWAP_DATA)) {
        EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__SET(regTmp);
    }

    if (0U != (config->chkSumOffEn & (uint8_t)CEDI_CFG_CHK_OFF_TX)) {
        EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__SET(regTmp);
    }

    if (0U != (config->dmaCfgFlags & (uint8_t)CEDI_CFG_DMA_DISC_RXP)) {
        EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__SET(regTmp);
    }

    if (0U != (config->dmaCfgFlags & (uint8_t)CEDI_CFG_DMA_FRCE_RX_BRST)) {
        EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__SET(regTmp);
    }

    if (0U != (config->dmaCfgFlags & (uint8_t)CEDI_CFG_DMA_FRCE_TX_BRST)) {
        EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__SET(regTmp);
    }

    // for configurations with gem_vm these parameters are in qx_control registers
    EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__MODIFY(regTmp, (uint32_t) (config->enTxExtBD[0]));
    EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__MODIFY(regTmp, (uint32_t) (config->enRxExtBD[0]));
    EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__MODIFY(regTmp, config->rxBufLength[0U]);



    status = WriteRegAndVerify(&(pD->regs->dma_config), regTmp);

    // when parameters are written to dma_config register, the same value must be set for all
    // qx_control registers if available:

    // if gem_vm is enabled (qx_status and qx_control registers available):
    if (pD->hwCfg.gem_vm == true) {
        // rx buf size
        if (status == CDN_EOK) {
            status = CEDI_SetRxQBufferSize(pD, 0U, config->rxBufLength[0]); // set rx buf size for q0
        }
        if ((status == CDN_EOK) && (pD->rxQs > 1U)) {
            status = setRxQBufferSizes(pD, config); // set rx buf size for rest of queues (if available)
        }
        if (status == CDN_EOK) {
            uint8_t q;
            for (q = 0U; q < pD->cfg.rxQs; q++) { // set rx bd enable for all queues
                status = setRxQBDExtendedModeEn(pD, q, config->enRxExtBD[q]);
                if (status != CDN_EOK) {
                    break;
                }
            }
        }
        if (status == CDN_EOK) {
            uint8_t q;
            for (q = 0U; q < pD->cfg.txQs; q++) { // set tx bd enable for all queues
                status = setTxQBDExtendedModeEn(pD, q, config->enTxExtBD[q]);
                if (status != CDN_EOK) {
                    break;
                }
            }
        }
    }

    return status;
}

/* Initialise Network Config register from config struct */
static uint32_t initNetConfigReg(const CEDI_PrivateData *pD)
{
    const CEDI_Config *config = &(pD->cfg);
    uint32_t regVal = 0U;
    volatile uint32_t* regAddr = &(pD->regs->network_config);

    /* The following covers MII/GMII/RGMII/SGMII and BASE_X, i.e.
       excludes XGMII and SERDES where the high speed enable
       overrides all this anyway. */
    if (config->ifTypeSel <= CEDI_IFSP_BASE_X) {
        if (config->ifSpeedSel >= CEDI_SPEED_1000M) {
            EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__SET(regVal);
        } else if (config->ifSpeedSel > CEDI_SPEED_10M) {
            EMAC_REGS__NETWORK_CONFIG__SPEED__SET(regVal);
        }
    }

    if ((config->ifTypeSel == CEDI_IFSP_SGMII)  ||
        (config->ifTypeSel == CEDI_IFSP_BASE_X) ||
        (config->ifTypeSel == CEDI_IFSP_USXGMII))
    {
        EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__SET(regVal);
    }

    if (config->ifTypeSel == CEDI_IFSP_SGMII) {
        EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__SET(regVal);
    }

    if (0U != config->uniDirEnable) {
        EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__SET(regVal);
    }

    if (0U != config->enRxBadPreamble) {
        EMAC_REGS__NETWORK_CONFIG__NSP_ACCEPT__SET(regVal);
    }

    if (0U != config->fullDuplex) {
        EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__SET(regVal);
    }

    if (0U != config->enRxHalfDupTx) {
        EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__SET(regVal);
    }

    if (0U != config->ignoreIpgRxEr) {
        EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__SET(regVal);
    }

    if (0U != config->rxJumboFrEn) {
        EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__SET(regVal);
    }

    if (0U != config->rx1536ByteEn) {
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__SET(regVal);
    }

    if (0U != config->extAddrMatch) {
        EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__SET(regVal);
    }

    EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__MODIFY(regVal, config->rxBufOffset);

    if (0U != config->rxLenErrDisc) {
        EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__SET(regVal);
    }

    EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__MODIFY(regVal, config->mdcPclkDiv);

    EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__MODIFY(regVal, config->dmaBusWidth);

    if (0U != config->disCopyPause) {
        EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__SET(regVal);
    }

    if (0U != (config->chkSumOffEn & CEDI_CFG_CHK_OFF_RX)) {
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__SET(regVal);
    }

    return WriteRegAndVerify(regAddr, regVal);
}




/*****************  Hardware Revision Compatibility Tests  *******************/

/* Return non-zero if h/w includes stateless offloads */
static uint32_t offloadsSupport(const CEDI_PrivateData *pD)
{
    uint32_t result;
    if (0U != (((pD->hwCfg.moduleId==GEM_GXL_MODULE_ID_V0)
        && (pD->hwCfg.moduleRev>=OFFLOADS_GEM_GXL_REV))
    || (pD->hwCfg.moduleId==GEM_GXL_MODULE_ID_V1)
    || (pD->hwCfg.moduleId==GEM_GXL_MODULE_ID_V2)
        || (pD->hwCfg.moduleId==GEM_AUTO_MODULE_ID_V0)
        || (pD->hwCfg.moduleId==GEM_AUTO_MODULE_ID_V1)
        || (pD->hwCfg.moduleId==GEM_10G_MODULE_ID_V0)
        || (pD->hwCfg.moduleId==GEM_10G_MODULE_ID_V1)
)) {

        result = 1U;

    }
    else {

        result = 0U;
    }
    return result;
}

/* Return non-zero if h/w includes 24bit sub-ns timer increment resolution */
uint32_t subNsTsuInc24bSupport(const CEDI_PrivateData *pD)
{
     uint32_t result;
     if (pD==NULL) {
        result = 0U;
     } else {
     /* resolution increase came in at r1p06f2 */
        if (0U != ((pD->hwCfg.moduleId==GEM_GXL_MODULE_ID_V0)
            && (pD->hwCfg.moduleRev==0x0106U)
            && (pD->hwCfg.fixNumber>=2U))
            || ((pD->hwCfg.moduleId==GEM_GXL_MODULE_ID_V0)
            && (pD->hwCfg.moduleRev>0x0106U))
        || (pD->hwCfg.moduleId>=GEM_GXL_MODULE_ID_V1)
        || (pD->hwCfg.moduleId>=GEM_GXL_MODULE_ID_V2)
            || (pD->hwCfg.moduleId==GEM_AUTO_MODULE_ID_V0)
            || (pD->hwCfg.moduleId==GEM_AUTO_MODULE_ID_V1)
        || (pD->hwCfg.moduleId==GEM_10G_MODULE_ID_V0)
        || (pD->hwCfg.moduleId==GEM_10G_MODULE_ID_V1)

) {

            result = 1U;

        } else {

            result = 0U;
        }
    }
    return result;
}

/* Read DesignConfig Debug registers into privateData for faster access.
 * pD must point to a privateData struct with cfg.regBase set */
static void readDesignConfig(CEDI_PrivateData *pD)
{
    uint32_t reg;
    uint8_t cond;

    /* read in revision & number of queues, which are also set by defs file */
    pD->hwCfg.numQueues = maxHwQs(pD->regs);

    reg = CPS_UncachedRead32(&(pD->regs->revision_reg));

    pD->hwCfg.moduleId =(uint16_t)
            EMAC_REGS__REVISION_REG__MODULE_IDENTIFICATION_NUMBER__READ(reg);
    pD->hwCfg.moduleRev =(uint16_t)
            EMAC_REGS__REVISION_REG__MODULE_REVISION__READ(reg);
    pD->hwCfg.fixNumber =(uint8_t)
#ifdef EMAC_REGS__REVISION_REG__FIX_NUMBER__READ
            EMAC_REGS__REVISION_REG__FIX_NUMBER__READ(reg);
#else
            0;
#endif

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug1));
    pD->hwCfg.no_pcs =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__READ(reg);
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__SERDES__READ
    pD->hwCfg.serdes =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__SERDES__READ(reg);
#endif
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__RDC_50__READ
    pD->hwCfg.RDC_50 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__RDC_50__READ(reg);
#endif
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__TDC_50__READ
    pD->hwCfg.TDC_50 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__TDC_50__READ(reg);
#endif
    pD->hwCfg.int_loopback =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__INT_LOOPBACK__READ(reg);
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__NO_INT_LOOPBACK__READ
    pD->hwCfg.no_int_loopback =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__NO_INT_LOOPBACK__READ(reg);
#else
    pD->hwCfg.no_int_loopback = !(pD->hwCfg.int_loopback);
#endif
    pD->hwCfg.ext_fifo_interface =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__EXT_FIFO_INTERFACE__READ(reg);

#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV1__READ
    pD->hwCfg.apb_rev1 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV1__READ(reg);
#endif
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV2__READ
    pD->hwCfg.apb_rev2 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV2__READ(reg);
#endif
    pD->hwCfg.user_io =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__USER_IO__READ(reg);
    pD->hwCfg.user_out_width =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__USER_OUT_WIDTH__READ(reg);
    pD->hwCfg.user_in_width =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__USER_IN_WIDTH__READ(reg);
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__NO_SCAN_PINS__READ
    pD->hwCfg.no_scan_pins =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__NO_SCAN_PINS__READ(reg);
#endif
    pD->hwCfg.no_stats =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__NO_STATS__READ(reg);
    pD->hwCfg.no_snapshot =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__NO_SNAPSHOT__READ(reg);
    pD->hwCfg.irq_read_clear =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__IRQ_READ_CLEAR__READ(reg);
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__READ
    /* need both compile-time test for macro and runtime test for feature
       support, to allow regression against older h/w */
    if (0U != offloadsSupport(pD)) {
        pD->hwCfg.exclude_cbs =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__READ(reg);
    }
#else
    pD->hwCfg.exclude_cbs = 1U;
#endif

#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_QBV__READ
        pD->hwCfg.exclude_qbv =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_QBV__READ(reg);
#else
        pD->hwCfg.exclude_qbv = 1U;

#endif

    pD->hwCfg.dma_bus_width =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__DMA_BUS_WIDTH__READ(reg);
    pD->hwCfg.axi_cache_value =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG1__AXI_CACHE_VALUE__READ(reg);

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug2));
    pD->hwCfg.jumbo_max_length =(uint16_t)
            EMAC_REGS__DESIGNCFG_DEBUG2__JUMBO_MAX_LENGTH__READ(reg);
    pD->hwCfg.hprot_value =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG2__HPROT_VALUE__READ(reg);
    pD->hwCfg.rx_pkt_buffer =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG2__RX_PKT_BUFFER__READ(reg);
    pD->hwCfg.tx_pkt_buffer =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG2__TX_PKT_BUFFER__READ(reg);
    pD->hwCfg.rx_pbuf_addr =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG2__RX_PBUF_ADDR__READ(reg);
    pD->hwCfg.tx_pbuf_addr =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG2__TX_PBUF_ADDR__READ(reg);
    pD->hwCfg.axi =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG2__AXI__READ(reg);

    /* designcfg_debug2: tx_pbuf_addr (Bit 29:26)
     * "Takes the value of the `gem_tx_pbuf_addr DEFINE or
     * zero if pbuf_address is decimal 16" */
    if (pD->hwCfg.rx_pkt_buffer && !pD->hwCfg.rx_pbuf_addr)
        pD->hwCfg.rx_pbuf_addr = MAX_PKT_BUF_SIZE;
    if (pD->hwCfg.tx_pkt_buffer && !pD->hwCfg.tx_pbuf_addr)
        pD->hwCfg.tx_pbuf_addr = MAX_PKT_BUF_SIZE;

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug3));
    pD->hwCfg.num_spec_add_filters =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG3__NUM_SPEC_ADD_FILTERS__READ(reg);

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug5));
    pD->hwCfg.rx_fifo_cnt_width =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__RX_FIFO_CNT_WIDTH__READ(reg);
    pD->hwCfg.tx_fifo_cnt_width =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__TX_FIFO_CNT_WIDTH__READ(reg);
    pD->hwCfg.tsu =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__TSU__READ(reg);
    pD->hwCfg.phy_ident =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__PHY_IDENT__READ(reg);
    pD->hwCfg.dma_bus_width_def =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__DMA_BUS_WIDTH_DEF__READ(reg);
    pD->hwCfg.mdc_clock_div =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__MDC_CLOCK_DIV__READ(reg);
    pD->hwCfg.endian_swap_def =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__ENDIAN_SWAP_DEF__READ(reg);
    pD->hwCfg.rx_pbuf_size_def =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__RX_PBUF_SIZE_DEF__READ(reg);
    pD->hwCfg.tx_pbuf_size_def =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__TX_PBUF_SIZE_DEF__READ(reg);
    pD->hwCfg.rx_buffer_length_def =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__RX_BUFFER_LENGTH_DEF__READ(reg);
    pD->hwCfg.tsu_clk =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__TSU_CLK__READ(reg);
    pD->hwCfg.axi_prot_value =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG5__AXI_PROT_VALUE__READ(reg);

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug6));
    pD->hwCfg.tx_pbuf_queue_segment_size =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG6__TX_PBUF_QUEUE_SEGMENT_SIZE__READ(reg);
    pD->hwCfg.ext_tsu_timer =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG6__EXT_TSU_TIMER__READ(reg);
    pD->hwCfg.tx_add_fifo_if =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG6__TX_ADD_FIFO_IF__READ(reg);
    pD->hwCfg.host_if_soft_select =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG6__HOST_IF_SOFT_SELECT__READ(reg);
    pD->hwCfg.dma_addr_width =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__READ(reg);
    pD->hwCfg.pfc_multi_quantum =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG6__PFC_MULTI_QUANTUM__READ(reg);
    /* Offloads features: first available in GEM_GXL rev 1p07- */
    if (0U != offloadsSupport(pD)) {
#ifdef EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__READ
        pD->hwCfg.pbuf_lso = (uint8_t)
                (EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__READ(reg));
#else
        pD->hwCfg.pbuf_lso = 0U;
#endif
#ifdef EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__READ
        pD->hwCfg.pbuf_rsc =(uint8_t)
                EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__READ(reg);
#else
        pD->hwCfg.pbuf_rsc = 0U;
#endif
        pD->hwCfg.intrpt_mod = 1U;
        pD->hwCfg.hdr_split = 1U;
    } else {
        pD->hwCfg.pbuf_lso = 0U;
        pD->hwCfg.pbuf_rsc = 0U;
        pD->hwCfg.intrpt_mod = 0U;
        pD->hwCfg.hdr_split = 0U;
    }
    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug7));
    pD->hwCfg.tx_pbuf_num_segments_q0 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q0__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q1 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q1__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q2 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q2__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q3 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q3__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q4 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q4__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q5 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q5__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q6 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q6__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q7 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q7__READ(reg);

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug8));
    pD->hwCfg.num_type1_screeners =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE1_SCREENERS__READ(reg);
    pD->hwCfg.num_type2_screeners =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE2_SCREENERS__READ(reg);
    pD->hwCfg.num_scr2_ethtype_regs =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_ETHTYPE_REGS__READ(reg);
    pD->hwCfg.num_scr2_compare_regs =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_COMPARE_REGS__READ(reg);

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug9));
    pD->hwCfg.tx_pbuf_num_segments_q8 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q8__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q9 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q9__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q10 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q10__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q11 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q11__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q12 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q12__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q13 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q13__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q14 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q14__READ(reg);
    pD->hwCfg.tx_pbuf_num_segments_q15 =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q15__READ(reg);

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug10));
    pD->hwCfg.axi_access_pipeline_bits =(uint8_t)
          EMAC_REGS__DESIGNCFG_DEBUG10__AXI_ACCESS_PIPELINE_BITS__READ(reg);
    pD->hwCfg.rx_pbuf_data =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG10__RX_PBUF_DATA__READ(reg);
    pD->hwCfg.tx_pbuf_data =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG10__TX_PBUF_DATA__READ(reg);

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug12));
    cond = (uint8_t)EMAC_REGS__DESIGNCFG_DEBUG12__GEM_HAS_CB__READ(reg);
    pD->hwCfg.num_cb_streams = 0U;
    if (0U != cond) {
        pD->hwCfg.num_cb_streams =(uint8_t)
            EMAC_REGS__DESIGNCFG_DEBUG12__GEM_NUM_CB_STREAMS__READ(reg);
    }
    pD->hwCfg.gem_vm = (bool) EMAC_REGS__DESIGNCFG_DEBUG12__GEM_VM__READ(reg);

    /* check if high-speed mode is supported by GEM */
    pD->hwCfg.gem_high_speed = EMAC_REGS__DESIGNCFG_DEBUG12__GEM_HIGH_SPEED__READ(reg);

    /* read design configuration for USXGMII */
    if((pD->hwCfg.no_pcs == 0U) && (IsGem1p13(pD))) {
        reg = CPS_REG_READ(&(pD->regs->designcfg_debug13));
        pD->hwCfg.gem_usx_include_fec = (uint8_t)EMAC_REGS__DESIGNCFG_DEBUG13__GEM_USX_INCLUDE_FEC__READ(reg);
    } else {
        pD->hwCfg.gem_usx_include_fec = 0U;
    }
    pD->hwCfg.lockup_supported = IsLockupSupported(pD);

}


/* Handle interrupts related to autonegotiation process */
static void handleAutoNegInterrupts(CEDI_PrivateData *pD, uint32_t isrReg)
{
    uint32_t retVal, regVal;
    uint8_t linkState;
    CEDI_AnNextPage nullNp;

    /************************* AN LP Page Rx ***************************/
    if (0U != EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__READ(isrReg))
    {
        if (0U != pD->basePageExp) {
            pD->lpPageRx.nextPage = 0U;
            /* Read base page data */
            retVal = CEDI_GetLpAbilityPage(pD,
                        &(pD->lpPageRx.lpPageDat.lpBasePage));
            if (CDN_EOK != retVal) {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "ISR: General interrupts: CEDI_GetLpAbilityPage "\
                    "returned with code: %u\n", retVal);
            }
        }
        else {
            pD->lpPageRx.nextPage = 1;
            /* Read next page data */
            retVal = CEDI_GetLpNextPage(pD,
                        &(pD->lpPageRx.lpPageDat.lpNextPage));
            if (CDN_EOK != retVal) {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "ISR: General interrupts: CEDI_GetLpNextPage "\
                    "returned with code: %u\n", retVal);
            }
        }

        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "EMAC (0x%08X) AN Link Partner %s Page Rx\n",
                (uint32_t)pD->cfg.regBase,
                (0U != pD->basePageExp)?"Base":"Next");
        if (0U != pD->basePageExp) {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "LpNextPage: %u  LpAck: %u  FullDuplex: %u  HalfDuplex: %u  Pause Capability: %u RemoteFault: %u\n",
                    pD->lpPageRx.lpPageDat.lpBasePage.ablInfo.defLpAbl.lpNextPage,
                    pD->lpPageRx.lpPageDat.lpBasePage.ablInfo.defLpAbl.lpAck,
                    pD->lpPageRx.lpPageDat.lpBasePage.ablInfo.defLpAbl.fullDuplex,
                    pD->lpPageRx.lpPageDat.lpBasePage.ablInfo.defLpAbl.halfDuplex,
                    pD->lpPageRx.lpPageDat.lpBasePage.ablInfo.defLpAbl.pauseCap,
                    pD->lpPageRx.lpPageDat.lpBasePage.ablInfo.defLpAbl.remFlt);
        }

        /* write Null message next page as default, can be overridden in callback or later */
        nullNp.ack2 = 0U;
        nullNp.message = 0x001U;
        nullNp.msgPage = 1U;
        nullNp.np = 0U;
        retVal = CEDI_SetNextPageTx(pD, &nullNp);
        if (CDN_EOK != retVal) {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                "ISR: General interrupts: CEDI_SetNextPageTx "\
                "returned with code: %u\n", retVal);
        }

        (*(pD->cb.lpPageRx))(pD, &(pD->lpPageRx));

        pD->basePageExp = 0U;
    }

    /************************* AN Complete *****************************/
    if (0U != EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__READ(isrReg))
    {
        pD->basePageExp = 1U;
        pD->autoNegActive = 0U;

        regVal = CPS_UncachedRead32(&(pD->regs->network_status));
        pD->anStatus.duplexRes =(uint8_t)
                EMAC_REGS__NETWORK_STATUS__MAC_FULL_DUPLEX__READ(regVal);
        pD->anStatus.linkState =(uint8_t)
                EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__READ(regVal);
        pD->anStatus.pauseRxRes =(uint8_t)
                EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_RX_EN__READ(regVal);
        pD->anStatus.pauseTxRes =(uint8_t)
                EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_TX_EN__READ(regVal);

        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "EMAC (0x%08X) Auto-negotiation Complete\n",
                (uint32_t)pD->cfg.regBase);

        (*(pD->cb.anComplete))(pD, &(pD->anStatus));
    }

    /*********************** Link State Change *************************/
    if (0U != EMAC_REGS__INT_STATUS__LINK_CHANGE__READ(isrReg))
    {
        if (0U != pD->autoNegActive) {
            retVal = CEDI_GetLinkStatus(pD, &linkState);
            if (CDN_EOK != retVal) {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "ISR: General interrupts: CEDI_GetLinkStatus "\
                    "returned with code: %u\n", retVal);
            }
        }
        else {
            linkState = (uint8_t)EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__READ(
                    CPS_UncachedRead32(&(pD->regs->network_status)));
        }

        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "EMAC (0x%08X) Link State changed - state = %u\n",
                (uint32_t)pD->cfg.regBase, linkState);

        (*(pD->cb.linkChange))(pD, linkState);
    }
}

/* Interrupts related to Q0 and entire core.
 * Also applies to Express MAC */
static void handleGeneralInterupts(CEDI_PrivateData *pD, uint8_t *handled)
{
    uint32_t isrReg, regVal;
    uint32_t events = 0;
    uint16_t dat16;
    uint8_t  qNum=0U, cond1, cond2, cond3;


    /* test for any ISR bits set */
    /* read Interrupt Status Register */
    isrReg = CPS_UncachedRead32(&(pD->regs->int_status));

    if (0U != isrReg) {

        *handled = 1;

        /* do clear-write if required */
        if (0U==pD->hwCfg.irq_read_clear) {
            CPS_UncachedWrite32(&(pD->regs->int_status), isrReg);
        }

        /*** test all intr status bits & do associated callbacks ***/

        /************************ PHY MDIO Frame Tx'd **********************/
        if (0U != EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__READ(isrReg))
        {
            regVal = CPS_UncachedRead32(&(pD->regs->phy_management));
            cond1 = (EMAC_REGS__PHY_MANAGEMENT__OPERATION__READ(regVal)==2U)?1U:0U;
            dat16 =(uint16_t) (EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__READ(regVal));
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "EMAC (0x%08X) PHY Management Frame sent to PHY(0x%02X) "\
                    "reg=0x%02X - %s operation, data=0x%04X\n",
                    (uint32_t)(pD->cfg).regBase,
                    EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__READ(regVal),
                    EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__READ(regVal),
                    (0U != cond1)?"read":"write",
                            dat16);

            (*(pD->cb.phyManComplete))(pD, cond1, dat16);
        }
        /****************************** TxEvent ****************************/

        cond1 =(uint8_t)EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__READ(isrReg);
        cond2 = (uint8_t)EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__READ(isrReg);

        if ((0U != cond1) || (0U !=cond2))
        {
            events = (0U != cond1)?((uint32_t)CEDI_EV_TX_USED_READ):0U;
            events |= (0U != cond2)?((uint32_t)CEDI_EV_TX_COMPLETE):0U;

            /* report both events in one callback call */


            (*(pD->cb.txEvent))(pD, events, qNum);
        }

        /****************************** TxError ****************************/

        cond1 = (uint8_t)EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__READ(isrReg);
        cond2 = (uint8_t)EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__READ(isrReg);
        cond3 =(uint8_t) EMAC_REGS__INT_STATUS__AMBA_ERROR__READ(isrReg);

        if ((0U != cond1) || (0U != cond2) || (0U != cond3))
        {
            events = (0U != cond1)?(uint32_t)CEDI_EV_TX_UNDERRUN:0U;
            events |= (0U != cond2)?(uint32_t)CEDI_EV_TX_RETRY_EX_LATE_COLL:0U;
            events |= (0U != cond3)?(uint32_t)CEDI_EV_TX_FR_CORRUPT:0U;
    #ifdef DEBUG
            /* read Q ptr for debug */
            regVal = CPS_UncachedRead32(&(pD->regs->transmit_q_ptr));
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
            "EMAC (0x%08X) Tx Error:0x%08X queue:%u tx_q_ptr:"\
            "0x%08X  isr0=%08X\n", (uint32_t)pD->cfg.regBase,
            events, qNum, regVal, isrReg);
    #endif
           (*(pD->cb.txError))(pD, events, qNum);
        }


        /*************************** RxFrame *******************************/
        if (0U != EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__READ(isrReg))
        {
            (*(pD->cb.rxFrame))(pD, qNum);
        }

        /*************************** RxError *******************************/

        cond1 = (uint8_t)(EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__READ(isrReg));
        cond2 = (uint8_t)(EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__READ(isrReg));

        if ((0U != cond1) || (0U != cond2))
        {
            events = (0U != cond1)?(uint32_t)CEDI_EV_RX_USED_READ:0U;
            events |= (0U != cond2)?(uint32_t)CEDI_EV_RX_OVERRUN:0U;

            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "EMAC (0x%08X) Rx Error:0x%08X queue:%u\n",
                    (uint32_t)pD->cfg.regBase, events, qNum);
            (*(pD->cb.rxError))(pD, events, qNum);
        }

        /************************ HResp not OK Event ***********************/
        if (0U != EMAC_REGS__INT_STATUS__RESP_NOT_OK__READ(isrReg))
        {
            DbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "EMAC (0x%08X) HResp not OK, queue:%u\n",
                    (uint32_t)pD->cfg.regBase, qNum);

            (*(pD->cb.hrespError))(pD, qNum);
        }

        handleAutoNegInterrupts(pD, isrReg);

        /************************ Pause Event ******************************/
        cond1 = (uint8_t)(EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__READ(isrReg));
        cond2 = (uint8_t)(EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__READ(isrReg));
        cond3 = (uint8_t)(EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__READ(isrReg));

        if ((0U != cond1) || (0U !=  cond2) || (0U != cond3))
        {
            events = (0U != cond1)?(uint32_t)CEDI_EV_PAUSE_FRAME_TX:0U;
            events |= (0U != cond2)?(uint32_t)CEDI_EV_PAUSE_TIME_ZERO:0U;
            events |= (0U != cond3)?(uint32_t)CEDI_EV_PAUSE_NZ_QU_RX:0U;

            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "EMAC (0x%08X) Pause Event, type:0x%08X\n",
                    (uint32_t)pD->cfg.regBase, events);

            (*(pD->cb.pauseEvent))(pD, events);
        }

        /***************** PTP Primary Frame Tx Event **********************/
        cond1 = (uint8_t)(EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__READ(isrReg));
        cond2 = (uint8_t)(EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__READ(isrReg));

        if ((0U != cond1) || (0U !=cond2))
        {
            events = (0U != cond1)?(uint32_t)CEDI_EV_PTP_TX_DLY_REQ:0U;
            events |= (0U != cond2)?(uint32_t)CEDI_EV_PTP_TX_SYNC:0U;

            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "EMAC (0x%08X) PTP Primary Frame Tx, type:0x%08X\n",
                    (uint32_t)pD->cfg.regBase, events);

            if (CDN_EOK != CEDI_GetPtpFrameTxTime(pD, &(pD->ptpTime))) {
                pD->ptpTime.secsUpper = 0U;
                pD->ptpTime.secsLower = 0U;
                pD->ptpTime.nanosecs = 0U;
            }
            (*(pD->cb.ptpPriFrameTx))(pD, events, &(pD->ptpTime));
        }

        /******************* PTP Peer Frame Tx Event ***********************/
        cond1 =(uint8_t)(EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__READ(isrReg));
        cond2 =(uint8_t)(EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__READ(isrReg));

        if ((0U != cond1) || (0U !=cond2))
        {
            events = (0U != cond1)?(uint32_t)CEDI_EV_PTP_TX_PDLY_REQ:0U;
            events |= (0U != cond2)?(uint32_t)CEDI_EV_PTP_TX_PDLY_RSP:0U;

            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "EMAC (0x%08X) PTP Peer Frame Tx, type:0x%08X\n",
                    (uint32_t)pD->cfg.regBase, events);

            if (CDN_EOK != CEDI_GetPtpPeerFrameTxTime(pD, &(pD->ptpTime))) {
                pD->ptpTime.secsUpper = 0U;
                pD->ptpTime.secsLower = 0U;
                pD->ptpTime.nanosecs = 0U;
            }
            (*(pD->cb.ptpPeerFrameTx))(pD, events, &(pD->ptpTime));
        }

        /***************** PTP Primary Frame Rx Event **********************/
        cond1 =(uint8_t)(EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__READ(isrReg));
        cond2 =(uint8_t) (EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__READ(isrReg));

        if ((0U != cond1) || (0U !=cond2))
        {
            events = (0U != cond1)?(uint32_t)CEDI_EV_PTP_RX_DLY_REQ:0U;
            events |= (0U != cond2)?(uint32_t)CEDI_EV_PTP_RX_SYNC:0U;

            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "EMAC (0x%08X) PTP Primary Frame Rx, type:0x%08X\n",
                    (uint32_t)pD->cfg.regBase, events);

            if (CDN_EOK != CEDI_GetPtpFrameRxTime(pD, &(pD->ptpTime))) {
                pD->ptpTime.secsUpper = 0U;
                pD->ptpTime.secsLower = 0U;
                pD->ptpTime.nanosecs = 0U;
            }
            (*(pD->cb.ptpPriFrameRx))(pD, events, &(pD->ptpTime));
        }

        /******************* PTP Peer Frame Rx Event ***********************/
        cond1 =(uint8_t) (EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__READ(isrReg));
        cond2 =(uint8_t) (EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__READ(isrReg));

        if ((0U != cond1) || (0U !=cond2))
        {
            events = (0U != cond1)?(uint32_t)CEDI_EV_PTP_RX_PDLY_REQ:0U;
            events |= (0U != cond2)?(uint32_t)CEDI_EV_PTP_RX_PDLY_RSP:0U;

            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "EMAC (0x%08X) PTP Peer Frame Rx, type:0x%08X\n",
                    (uint32_t)pD->cfg.regBase, events);

            if (CDN_EOK != CEDI_GetPtpPeerFrameRxTime(pD, &(pD->ptpTime))) {
                pD->ptpTime.secsUpper = 0U;
                pD->ptpTime.secsLower = 0U;
                pD->ptpTime.nanosecs = 0U;
            }
            (*(pD->cb.ptpPeerFrameRx))(pD, events, &(pD->ptpTime));
        }

        /************************* Lockup detect Event *******************************/
     if(EMAC_REGS__INT_STATUS__TX_LOCKUP_DETECTED__READ(isrReg) != 0)
        events = CEDI_EV_TX_LOCKUP;
     if(EMAC_REGS__INT_STATUS__RX_LOCKUP_DETECTED__READ(isrReg) != 0)
        events |= CEDI_EV_RX_LOCKUP;

     if (events & (CEDI_EV_TX_LOCKUP | CEDI_EV_RX_LOCKUP)){
         vDbgMsg(DBG_GEN_MSG, DBG_FYI, "EMAC (0x%08X) Lockup Event, type:0x%08X\n",
             (uint32_t)pD->cfg.regBase, events);
         (*(pD->cb.lockupEvent))(pD, events);
     }


        /************************* TSU Event *******************************/
        cond1 =(uint8_t)(EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__READ(isrReg));
        cond2 =(uint8_t)(EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__READ(isrReg));

        if ((0U != cond1) || (0U !=cond2))
        {
            events = (0U != cond1)?(uint32_t)CEDI_EV_TSU_SEC_INC:0U;
            events |= (0U != cond2)?(uint32_t)CEDI_EV_TSU_TIME_MATCH:0U;

            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "EMAC (0x%08X) TSU Event, type:0x%08X\n",
                    (uint32_t)pD->cfg.regBase, events);

            (*(pD->cb.tsuEvent))(pD, events);
        }

        /************************* LPI Status Change ***********************/
        if (0U != EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__READ(isrReg))
        {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "EMAC (0x%08X) LPI Status change Event\n",

                    (uint32_t)pD->cfg.regBase);

            (*(pD->cb.lpiStatus))(pD);
        }

        /************************* Wake On LAN Event ***********************/
        if (0U != EMAC_REGS__INT_STATUS__WOL_INTERRUPT__READ(isrReg))
        {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "EMAC (0x%08X) Wake on LAN Event\n",
                    (uint32_t)pD->cfg.regBase);

            (*(pD->cb.wolEvent))(pD);
        }

        /****************** External Input Interrupt Event *****************/
        if (0U != EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__READ(isrReg))
        {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "EMAC (0x%08X) External Input Interrupt\n",
                    (uint32_t)pD->cfg.regBase);

            (*(pD->cb.extInpIntr))(pD);
        }

    }
}
static void handlePcs25gInterrupts(CEDI_PrivateData* pD, uint8_t* handled)
{
    uint32_t eventsReg;
    uint32_t reg;
    uint32_t val;
    uint32_t eventVal;
    CEDI_FecError fecError;
    bool handleInterrupt;

    /* check, if any interrupts was occured */
    eventsReg  = CPS_REG_READ(&(pD->regs->usx_interrupt_status_register));

    if (eventsReg != 0U) {

        *handled = 1U;

        /* clear interrupt status register */
        CPS_REG_WRITE(&(pD->regs->usx_interrupt_status_register), 0xFFFFFFFFU);

        /* FEC correct/uncorrect error event */
        handleInterrupt = (0U != EMAC_REGS__USX_INTERRUPT_STATUS_REGISTER__FEC_CORRECTABLE_ERROR__READ(eventsReg)) ||
                          (0U != EMAC_REGS__USX_INTERRUPT_STATUS_REGISTER__FEC_UNCORRECTABLE_ERROR__READ(eventsReg));

        if (handleInterrupt) {
            reg = CPS_REG_READ(&(pD->regs->usx_fec_error_counter));

            /* clear register */
            CPS_REG_WRITE(&(pD->regs->usx_fec_error_counter), 0U);

            fecError.uncorrect = EMAC_REGS__USX_FEC_ERROR_COUNTER__FEC_BLOCK_ERROR_COUNT__READ(reg);
            fecError.correct = EMAC_REGS__USX_FEC_ERROR_COUNTER__FEC_BLOCK_CORRECTED_COUNT__READ(reg);
            eventVal = eventsReg &
                       (EMAC_REGS__USX_INTERRUPT_STATUS_REGISTER__FEC_CORRECTABLE_ERROR__MASK |
                        EMAC_REGS__USX_INTERRUPT_STATUS_REGISTER__FEC_UNCORRECTABLE_ERROR__MASK);

            (*(pD->cb.fecError))(pD, eventVal, &fecError);
        }

        /* Block lock status change event */
        handleInterrupt = (0U != EMAC_REGS__USX_INTERRUPT_STATUS_REGISTER__BLOCK_LOCKED__READ(eventsReg));

        if (handleInterrupt) {
            reg = CPS_REG_READ(&(pD->regs->usx_status_register));
            /* clear register */
            CPS_REG_WRITE(&(pD->regs->usx_status_register), 0U);

            val = EMAC_REGS__USX_STATUS_REGISTER__BLOCK_LOCK__READ(reg);

            (*(pD->cb.syncEvent))(pD, (uint8_t)val);
        }

        /* High bit error status trigger event */
        handleInterrupt = (0U != EMAC_REGS__USX_INTERRUPT_STATUS_REGISTER__HI_BIT_ERROR__READ(eventsReg));

        if (handleInterrupt) {
            reg = CPS_REG_READ(&(pD->regs->usx_bit_error_counter));
            /* clear register */
            CPS_REG_WRITE(&(pD->regs->usx_bit_error_counter), 0U);

            (*(pD->cb.highBitError))(pD, reg);
        }
    }
}
static void readQueueIsrReg(const CEDI_PrivateData *pD, uint8_t qNum, uint32_t *isrReg)
{
    volatile uint32_t *regPtr = NULL;

    if (qNum > 0U)
    {
        regPtr = intStatusReg[qNum-1U];
        addRegBase(pD, &regPtr);
        *isrReg = CPS_UncachedRead32(regPtr);
    }
}

static void handleQnInterupts(CEDI_PrivateData *pD, uint8_t *handled)
{
    uint32_t isrReg;
    uint32_t events;
    uint8_t  qNum, cond1, cond2, cond3;
    volatile uint32_t *regPtr = NULL;

    /* test for any ISR bits set */

    for (qNum=pD->numQs-1U; qNum>0U; qNum--) {
        /* read Interrupt Status Register */
        readQueueIsrReg(pD, qNum, &isrReg);

        if (0U != isrReg) {

            *handled = 1U;

            /* do clear-write if required */
            if ((0U==pD->hwCfg.irq_read_clear) && (qNum < 16U)) {
                regPtr = intStatusReg[qNum-1U];
                addRegBase(pD, &regPtr);
                CPS_UncachedWrite32(regPtr, isrReg);
            }

            /****************************** TxEvent ****************************/
            cond2 = (uint8_t)EMAC_REGS__INT_Q_STATUS1__TRANSMIT_COMPLETE__READ(isrReg);
            if (0U != cond2)
            {
                events = (0U != cond2)?(uint32_t)CEDI_EV_TX_COMPLETE:0U;

                /* report both events in one callback call */

                (*(pD->cb.txEvent))(pD, events, qNum);
            }

            /****************************** TxError ****************************/

            cond2 = 0U;

            cond2 = (uint8_t)(EMAC_REGS__INT_Q_STATUS1__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__READ(
                             isrReg));
            cond3 = (uint8_t)(EMAC_REGS__INT_Q_STATUS1__AMBA_ERROR__READ(isrReg));

            if ( (0U != cond2) || (0U != cond3))
            {
                events = 0U;
                events |= (0U != cond2)?(uint32_t)CEDI_EV_TX_RETRY_EX_LATE_COLL:0U;
                events |= (0U != cond3)?(uint32_t)CEDI_EV_TX_FR_CORRUPT:0U;

#ifdef DEBUG
                /* read Q ptr for debug */
                if ((qNum > 0U) && (qNum < 16U))
                {
            uint32_t regVal;
                    regPtr = transmitPtrReg[qNum-1U];
                    addRegBase(pD, &regPtr);
                    regVal = CPS_UncachedRead32(regPtr);

                    vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                            "EMAC (0x%08X) Tx Error:0x%08X queue:%u tx_q_ptr:"\
                            "0x%08X  isr0=%08X\n", (uint32_t)pD->cfg.regBase,
                            events, qNum, regVal, isrReg);
                }
#endif
                (*(pD->cb.txError))(pD, events, qNum);
            }

            /*************************** RxFrame *******************************/
            if (0U != EMAC_REGS__INT_Q_STATUS1__RECEIVE_COMPLETE__READ(isrReg))
            {
                (*(pD->cb.rxFrame))(pD, qNum);
            }

            /*************************** RxError *******************************/
            cond1 = 0U;
            cond2 = 0U;

            cond1 =(uint8_t)(EMAC_REGS__INT_Q_STATUS1__RX_USED_BIT_READ__READ(isrReg));

        // for 1p11 GEM release and newer receive overrun is common for all queues
        if (IsGem1p11(pD) == 1){
        cond2 =(uint8_t)(EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__READ(isrReg));
        }

            if ( (0U != cond2) || (0U != cond1))
            {
                events = (0U != cond1)?(uint32_t)CEDI_EV_RX_USED_READ:0U;
                events |= (0U != cond2)?(uint32_t)CEDI_EV_RX_OVERRUN:0U;

                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                        "EMAC (0x%08X) Rx Error:0x%08X queue:%u\n",
                        (uint32_t)pD->cfg.regBase, events, qNum);
                (*(pD->cb.rxError))(pD, events, qNum);
            }
            /************************ HResp not OK Event ***********************/
            if (0U != EMAC_REGS__INT_Q_STATUS1__RESP_NOT_OK__READ(isrReg))
            {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                        "EMAC (0x%08X) HResp not OK, queue:%u\n",
                        (uint32_t)pD->cfg.regBase, qNum);

                (*(pD->cb.hrespError))(pD, qNum);
            }

        }
    } /* for qNum */
}

static void fillEnableQ0ExclusiveEvents(uint32_t events, uint32_t *regVal)
{
    if (0U != (events & (uint32_t)CEDI_EV_MAN_FRAME)) {
        EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_USED_READ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_UNDERRUN)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PCS_LINK_CHANGE_DET)) {
        EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PCS_AN_COMPLETE)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PCS_LP_PAGE_RX)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TSU_SEC_INC)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TSU_TIME_MATCH)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__SET(*regVal);
    }


    if (0U != (events & (uint32_t)CEDI_EV_RX_OVERRUN)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PAUSE_NZ_QU_RX)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PAUSE_TIME_ZERO)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PAUSE_FRAME_TX)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_EXT_INTR)) {
        EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_RX_DLY_REQ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_RX_SYNC)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_TX_DLY_REQ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_TX_SYNC)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_RX_PDLY_REQ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_RX_PDLY_RSP)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_TX_PDLY_REQ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_TX_PDLY_RSP)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_LPI_CH_RX)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_WOL_RX)) {
        EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__SET(*regVal);
    }


    if (0U != (events & (uint32_t)CEDI_EV_RX_LOCKUP)) {
     EMAC_REGS__INT_ENABLE__ENABLE_RX_LOCKUP_DETECTED_INTERRUPT__SET
        (*regVal);
    }
    if (0U != (events & (uint32_t)CEDI_EV_TX_LOCKUP)) {
     EMAC_REGS__INT_ENABLE__ENABLE_TX_LOCKUP_DETECTED_INTERRUPT__SET
        (*regVal);
    }
}

static void enableQ0Events(CEDI_PrivateData *pD, uint32_t events)
{
    uint32_t regVal = 0U;

    fillEnableQ0ExclusiveEvents(events, &regVal);

    if (0U != (events & (uint32_t)CEDI_EV_RX_COMPLETE)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_RX_USED_READ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_RETRY_EX_LATE_COLL)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_FR_CORRUPT)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_COMPLETE)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_HRESP_NOT_OK)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);
    }


    CPS_UncachedWrite32(&(pD->regs->int_enable), regVal);
}

static void enableQnEvents(const CEDI_PrivateData *pD, uint32_t events, uint8_t queueNum)
{
    uint32_t regVal = 0U;
    volatile uint32_t *regPtr = NULL;
    uint8_t i;

    volatile uint32_t* const intEnableReg[15U] = {
        CEDI_RegOff(int_q1_enable),
        CEDI_RegOff(int_q2_enable),
        CEDI_RegOff(int_q3_enable),
        CEDI_RegOff(int_q4_enable),
        CEDI_RegOff(int_q5_enable),
        CEDI_RegOff(int_q6_enable),
        CEDI_RegOff(int_q7_enable),
        CEDI_RegOff(int_q8_enable),
        CEDI_RegOff(int_q9_enable),
        CEDI_RegOff(int_q10_enable),
        CEDI_RegOff(int_q11_enable),
        CEDI_RegOff(int_q12_enable),
        CEDI_RegOff(int_q13_enable),
        CEDI_RegOff(int_q14_enable),
        CEDI_RegOff(int_q15_enable)
    };

    if (0U != (events & (uint32_t)CEDI_EV_RX_COMPLETE)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_RX_USED_READ)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_RETRY_EX_LATE_COLL)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_FR_CORRUPT)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_COMPLETE)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_HRESP_NOT_OK)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);
    }

    /* write to interrupt enable register */
    if (queueNum==CEDI_ALL_QUEUES) {
        for (i = 1U; i < pD->numQs; i++) {
            regPtr = intEnableReg[i-1U];
            addRegBase(pD, &regPtr);
            CPS_UncachedWrite32(regPtr, regVal);
        }
    }
    if (queueNum < 16U) {
        regPtr = intEnableReg[queueNum-1U];
        addRegBase(pD, &regPtr);
        CPS_UncachedWrite32(regPtr, regVal);
    }
}

static void fillDisableQ0ExclusiveEvents(uint32_t events, uint32_t *regVal)
{

    if (0U != (events & (uint32_t)CEDI_EV_MAN_FRAME)) {
        EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_USED_READ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_UNDERRUN)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PCS_LINK_CHANGE_DET)) {
        EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PCS_AN_COMPLETE)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PCS_LP_PAGE_RX)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TSU_SEC_INC)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TSU_TIME_MATCH)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_RX_OVERRUN)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PAUSE_NZ_QU_RX)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PAUSE_TIME_ZERO)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PAUSE_FRAME_TX)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_EXT_INTR)) {
        EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_RX_DLY_REQ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_RX_SYNC)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_TX_DLY_REQ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_TX_SYNC)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_RX_PDLY_REQ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_RX_PDLY_RSP)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_TX_PDLY_REQ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_PTP_TX_PDLY_RSP)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_LPI_CH_RX)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_WOL_RX)) {
        EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__SET(*regVal);
    }


    if (0U != (events & (uint32_t)CEDI_EV_RX_LOCKUP)) {
     EMAC_REGS__INT_DISABLE__DISABLE_RX_LOCKUP_DETECTED_INTERRUPT__SET
        (*regVal);
    }
    if (0U != (events & (uint32_t)CEDI_EV_TX_LOCKUP)) {
     EMAC_REGS__INT_DISABLE__DISABLE_TX_LOCKUP_DETECTED_INTERRUPT__SET
        (*regVal);
    }
}

static void disableQ0Events(CEDI_PrivateData *pD, uint32_t events)
{
    uint32_t regVal = 0U;

    fillDisableQ0ExclusiveEvents(events, &regVal);

    if (0U != (events & (uint32_t)CEDI_EV_RX_COMPLETE)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_RX_USED_READ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_RETRY_EX_LATE_COLL)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_FR_CORRUPT)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_COMPLETE)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_HRESP_NOT_OK)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);
    }

    CPS_UncachedWrite32(&(pD->regs->int_disable), regVal);
}

static void disableQnEvents(const CEDI_PrivateData *pD, uint32_t events, uint8_t queueNum)
{
    uint32_t regVal = 0U;
    volatile uint32_t *regPtr = NULL;
    uint8_t i;

    if (0U != (events & (uint32_t)CEDI_EV_RX_COMPLETE)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_RX_USED_READ)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_RETRY_EX_LATE_COLL)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_FR_CORRUPT)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_TX_COMPLETE)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)CEDI_EV_HRESP_NOT_OK)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);
    }

    /* write to interrupt disable register */
    if (queueNum==CEDI_ALL_QUEUES) {
        for (i = 1U; i < pD->numQs; i++) {
            regPtr = intDisableReg[i-1U];
            addRegBase(pD, &regPtr);
            CPS_UncachedWrite32(regPtr, regVal);
        }
    }
    if ((queueNum < 16U) && (queueNum > 0U)) {
        regPtr = intDisableReg[queueNum-1U];
        addRegBase(pD, &regPtr);
        CPS_UncachedWrite32(regPtr, regVal);
    }
}

static void fillGetQ0ExclusiveEventEnable(CEDI_PrivateData *pD, uint32_t *ret, uint32_t regVal)
{
    if (0U != EMAC_REGS__INT_MASK__MANAGEMENT_DONE_INTERRUPT_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_MAN_FRAME;
    }

    if (0U != EMAC_REGS__INT_MASK__TRANSMIT_USED_BIT_READ_INTERRUPT_MASK__READ(
            regVal)) {
        *ret |= (uint32_t)CEDI_EV_TX_USED_READ;
    }

    if (0U != EMAC_REGS__INT_MASK__TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK__READ(
            regVal))  {
        *ret |= (uint32_t)CEDI_EV_TX_UNDERRUN;
    }

    if (pD->hwCfg.no_pcs == 0){
    if (0U != EMAC_REGS__INT_MASK__LINK_CHANGE_INTERRUPT_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_PCS_LINK_CHANGE_DET;
    }

    if (0U != EMAC_REGS__INT_MASK__PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_PCS_AN_COMPLETE;
    }

    if (0U != EMAC_REGS__INT_MASK__PCS_LINK_PARTNER_PAGE_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_PCS_LP_PAGE_RX;
    }
    }

    if (0U != EMAC_REGS__INT_MASK__TSU_SECONDS_REGISTER_INCREMENT_MASK__READ(
                                         regVal)) {
    *ret |= (uint32_t)CEDI_EV_TSU_SEC_INC;
    }

    if (0U != EMAC_REGS__INT_MASK__TSU_TIMER_COMPARISON_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_TSU_TIME_MATCH;
    }

    if (0U != EMAC_REGS__INT_MASK__RECEIVE_OVERRUN_INTERRUPT_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_RX_OVERRUN;
    }

    if (0U != EMAC_REGS__INT_MASK__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK__READ(
            regVal)) {
        *ret |= (uint32_t)CEDI_EV_PAUSE_NZ_QU_RX;
    }

    if (0U != EMAC_REGS__INT_MASK__PAUSE_TIME_ZERO_INTERRUPT_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_PAUSE_TIME_ZERO;
    }

    if (0U != EMAC_REGS__INT_MASK__PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK__READ(
            regVal)) {
        *ret |= (uint32_t)CEDI_EV_PAUSE_FRAME_TX;
    }

    if (0U != EMAC_REGS__INT_MASK__EXTERNAL_INTERRUPT_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_EXT_INTR;
    }

    if (0U != EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_RECEIVED_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_PTP_RX_DLY_REQ;
    }

    if (0U != EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_RECEIVED_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_PTP_RX_SYNC;
    }

    if (0U != EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK__READ(
            regVal)) {
        *ret |= (uint32_t)CEDI_EV_PTP_TX_DLY_REQ;
    }

    if (0U != EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_TRANSMITTED_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_PTP_TX_SYNC;
    }

    if (0U != EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_RECEIVED_MASK__READ(
            regVal)) {
        *ret |= (uint32_t)CEDI_EV_PTP_RX_PDLY_REQ;
    }

    if (0U != EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_RECEIVED_MASK__READ(
            regVal)) {
        *ret |= (uint32_t)CEDI_EV_PTP_RX_PDLY_RSP;
    }

    if (0U != EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK__READ(
            regVal)) {
        *ret |= (uint32_t)CEDI_EV_PTP_TX_PDLY_REQ;
    }

    if (0U != EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK__READ(
            regVal)) {
        *ret |= (uint32_t)CEDI_EV_PTP_TX_PDLY_RSP;
    }

    if (0U != EMAC_REGS__INT_MASK__RX_LPI_INDICATION_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_LPI_CH_RX;
    }

    if (0U != EMAC_REGS__INT_MASK__WOL_EVENT_RECEIVED_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_WOL_RX;
    }


    if (0U != EMAC_REGS__INT_MASK__RX_LOCKUP_DETECTED_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_RX_LOCKUP;
    }
    if (0U != EMAC_REGS__INT_MASK__TX_LOCKUP_DETECTED_MASK__READ(regVal)) {
        *ret |= (uint32_t)CEDI_EV_TX_LOCKUP;
    }

}

static void getQ0EventEnable(CEDI_PrivateData *pD, uint32_t *events)
{
    uint32_t ret = 0U;
    uint32_t regVal = 0U;
    regVal = ~CPS_UncachedRead32(&(pD->regs->int_mask));

    if (0U == IsGem1p11(pD)){
    regVal &= ~EMAC_REGS__INT_MASK__RX_LOCKUP_DETECTED_MASK__MASK;
    regVal &= ~EMAC_REGS__INT_MASK__TX_LOCKUP_DETECTED_MASK__MASK;
    }
    if (0U != regVal) {

        fillGetQ0ExclusiveEventEnable(pD, &ret, regVal);

        if (0U != EMAC_REGS__INT_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__READ(regVal)) {
            ret |= (uint32_t)CEDI_EV_RX_COMPLETE;
        }

        if (0U != EMAC_REGS__INT_MASK__RECEIVE_USED_BIT_READ_INTERRUPT_MASK__READ(
                regVal)) {
            ret |= (uint32_t)CEDI_EV_RX_USED_READ;
        }

#ifdef EMAC_REGS__INT_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK__READ
        if (0U != EMAC_REGS__INT_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK__READ(
                regVal)) {
            ret |= (uint32_t)CEDI_EV_TX_RETRY_EX_LATE_COLL;
        }
#endif

        if (0U != EMAC_REGS__INT_MASK__AMBA_ERROR_INTERRUPT_MASK__READ(regVal)) {
            ret |= (uint32_t)CEDI_EV_TX_FR_CORRUPT;
        }

        if (0U != EMAC_REGS__INT_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__READ(regVal)) {
            ret |= (uint32_t)CEDI_EV_TX_COMPLETE;
        }

        if (0U != EMAC_REGS__INT_MASK__RESP_NOT_OK_INTERRUPT_MASK__READ(regVal)) {
            ret |= (uint32_t)CEDI_EV_HRESP_NOT_OK;
        }

    }
    (*events) = ret;
}

static void getQnEventEnable(const CEDI_PrivateData *pD, uint32_t *events, uint8_t queueNum)
{
    uint32_t ret = 0U;
    uint32_t regVal = 0U;
    volatile uint32_t *regPtr = NULL;

    volatile uint32_t* const intMaskReg[15U] = {
        CEDI_RegOff(int_q1_mask),
        CEDI_RegOff(int_q2_mask),
        CEDI_RegOff(int_q3_mask),
        CEDI_RegOff(int_q4_mask),
        CEDI_RegOff(int_q5_mask),
        CEDI_RegOff(int_q6_mask),
        CEDI_RegOff(int_q7_mask),
        CEDI_RegOff(int_q8_mask),
        CEDI_RegOff(int_q9_mask),
        CEDI_RegOff(int_q10_mask),
        CEDI_RegOff(int_q11_mask),
        CEDI_RegOff(int_q12_mask),
        CEDI_RegOff(int_q13_mask),
        CEDI_RegOff(int_q14_mask),
        CEDI_RegOff(int_q15_mask)
    };

    if (queueNum > 0U)
    {
        regPtr = intMaskReg[queueNum-1U];
        addRegBase(pD, &regPtr);
        regVal = ~CPS_UncachedRead32(regPtr);

        if (0U != regVal) {
            if (0U != EMAC_REGS__INT_Q_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__READ(
                    regVal)) {
                ret |= (uint32_t)CEDI_EV_RX_COMPLETE;
            }

            if (0U != EMAC_REGS__INT_Q_MASK__RX_USED_INTERRUPT_MASK__READ(
                    regVal)) {
                ret |= (uint32_t)CEDI_EV_RX_USED_READ;
            }

                if (0U != EMAC_REGS__INT_Q_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK__READ(
                    regVal)) {
                ret |= (uint32_t)CEDI_EV_TX_RETRY_EX_LATE_COLL;
            }

            if (0U != EMAC_REGS__INT_Q_MASK__AMBA_ERROR_INTERRUPT_MASK__READ(regVal)) {
                ret |= (uint32_t)CEDI_EV_TX_FR_CORRUPT;
            }

            if (0U != EMAC_REGS__INT_Q_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__READ(
                    regVal)) {
                ret |= (uint32_t)CEDI_EV_TX_COMPLETE;
            }

            if (0U != EMAC_REGS__INT_Q_MASK__RESP_NOT_OK_INTERRUPT_MASK__READ(regVal)) {
                ret |= (uint32_t)CEDI_EV_HRESP_NOT_OK;
            }
        }
    }
    (*events) = ret;
}

static void setFrerRedundancyTag(const CEDI_FrameEliminationConfig* fec, uint32_t *reg)
{
    if (fec->seqNumIdentification == CEDI_SEQ_NUM_IDEN_TAG) {
        EMAC_REGS__FRER_CONTROL_A__USE_R_TAG__SET(*reg);
    } else {
        if (fec->seqNumIdentification == CEDI_SEQ_NUM_IDEN_OFFSET) {
            EMAC_REGS__FRER_CONTROL_A__USE_R_TAG__CLR(*reg);
        }
    }
}

static void getFrerRedundancyTag(CEDI_FrameEliminationConfig* fec, uint32_t reg)
{
    if (0U != EMAC_REGS__FRER_CONTROL_A__USE_R_TAG__READ(reg)) {
        fec->seqNumIdentification = CEDI_SEQ_NUM_IDEN_TAG;
    } else {
        fec->seqNumIdentification = CEDI_SEQ_NUM_IDEN_OFFSET;
    }
}

static void calcNumQueueSegs(const CEDI_PrivateData *pD, uint32_t *numQSegs)
{
    uint8_t i;
    const uint32_t segs[16] = {
        pD->hwCfg.tx_pbuf_num_segments_q0,
        pD->hwCfg.tx_pbuf_num_segments_q1,
        pD->hwCfg.tx_pbuf_num_segments_q2,
        pD->hwCfg.tx_pbuf_num_segments_q3,
        pD->hwCfg.tx_pbuf_num_segments_q4,
        pD->hwCfg.tx_pbuf_num_segments_q5,
        pD->hwCfg.tx_pbuf_num_segments_q6,
        pD->hwCfg.tx_pbuf_num_segments_q7,
        pD->hwCfg.tx_pbuf_num_segments_q8,
        pD->hwCfg.tx_pbuf_num_segments_q9,
        pD->hwCfg.tx_pbuf_num_segments_q10,
        pD->hwCfg.tx_pbuf_num_segments_q11,
        pD->hwCfg.tx_pbuf_num_segments_q12,
        pD->hwCfg.tx_pbuf_num_segments_q13,
        pD->hwCfg.tx_pbuf_num_segments_q14,
        pD->hwCfg.tx_pbuf_num_segments_q15
    };

    *numQSegs = 0U;

    for (i=0U; i<pD->numQs; i++) {
        if (segs[i] < 16U) {
            *numQSegs += 1U<<segs[i];
        } else {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n",
                    "Warning: Wrong tx_pbuf_num_segments read from hardware "\
                    "register, setting to 15");
            *numQSegs += (uint32_t) 1UL << 15U;
        }
    }
}

static void initExpressMacPD(CEDI_PrivateData *epD, const CEDI_Config* cfg, const CEDI_Callbacks* cb)
{

    uint32_t pmacTxDescListSize = 0U;
    uint32_t pmacRxDescListSize = 0U;
    uint16_t txDescSize[CEDI_MAX_TX_QUEUES];
    uint16_t rxDescSize[CEDI_MAX_RX_QUEUES];

    /* For eMac otherMac indicates on pMac */
    calcDescriptorSizes(cfg, epD->otherMac->hwCfg.gem_vm, txDescSize, rxDescSize);

    pmacTxDescListSize = sumTxDescriptorsListSize(cfg, txDescSize);
    pmacRxDescListSize = sumRxDescriptorsListSize(cfg, rxDescSize);

    vDbgMsg(DBG_GEN_MSG,DBG_CRIT, "%d:%s: pmac tx size %d pmac rx size %d\n", __LINE__, __func__, pmacTxDescListSize, pmacRxDescListSize);

    epD->macType = CEDI_MAC_TYPE_EMAC;

    epD->cfg = *cfg;
    epD->cb = *cb;
    epD->cfg.regBase += CEDI_EXPRESS_MAC_REGS_OFFSET;
    epD->regs = regBaseToPtr(epD->cfg.regBase);

    epD->cfg.rxQs = 1U;
    epD->cfg.txQs = 1U;
    epD->numQs = 1U;
    epD->cfg.rxQLen[0] = epD->cfg.eRxQLen[0];
    epD->cfg.txQLen[0] = epD->cfg.eTxQLen[0];
    epD->ptpTime.nanosecs = 0U;

    epD->rxQs = epD->cfg.rxQs;
    epD->txQs = epD->cfg.txQs;
    epD->frerEnabled[0] = 0U;

    epD->cfg.txQPhyAddr += pmacTxDescListSize;
    epD->cfg.rxQPhyAddr += pmacRxDescListSize;
    epD->cfg.txQAddr += pmacTxDescListSize;
    epD->cfg.rxQAddr += pmacRxDescListSize;

    /* Check for overflows in lower 32 bits of TX/RX physical addresses */
    if (epD->cfg.txQPhyAddr < cfg->txQPhyAddr) {
        epD->cfg.upper32BuffTxQAddr++;
    }
    if (epD->cfg.rxQPhyAddr < cfg->rxQPhyAddr) {
        epD->cfg.upper32BuffRxQAddr++;
    }
}

static uint32_t checkBufferSegmentsDistribution(const CEDI_PrivateData *pD)
{
    uint32_t numTxSegs, numQSegs;
    uint32_t txPbufQSegSize = pD->hwCfg.tx_pbuf_queue_segment_size;
    uint32_t status = CDN_EOK;
    CEDI_PrivateData *epD = NULL;
    uint32_t eNumTxSegs, eNumQSegs;
    uint32_t eTxPbufQSegSize, eNumQSegsShift;



    /* sanity-check multi-queue packet buffer segments and distribution */
    if ((pD->numQs>1U) && (pD->hwCfg.tx_pkt_buffer != 0U))
    {

        if (txPbufQSegSize >= pD->hwCfg.tx_pbuf_addr) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "Error: H/w configuration specifies Tx segment size %u, "\
                    "must be less than Tx pbuf addr (%u)\n",
                    txPbufQSegSize,
                    pD->hwCfg.tx_pbuf_addr);
            status = CDN_ENOTSUP;
        }

        if (txPbufQSegSize < 16U) {
            numTxSegs = 1<<txPbufQSegSize;
        } else {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n",
                    "Warning: Wrong tx_pbuf_queue_segment_size read from hardware "\
                    "register, using 15 for further checking");
            numTxSegs = 1U << 15U;
        }

        if (numTxSegs<pD->numQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Error: H/w configuration specifies %u"\
                    " queues but only %u packet buffer segments\n",
                    pD->numQs, numTxSegs);
            status = CDN_ENOTSUP;
        }

        calcNumQueueSegs(pD, &numQSegs);

        if (numQSegs>numTxSegs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "Error: H/w configuration allocates %u Tx packet buffer"\
                    " segments to queues out of %u total\n", numQSegs, numTxSegs);
            status = CDN_ENOTSUP;
        }
        if (0U != pD->cfg.incExpressTraffic) {
            epD = pD->otherMac;

            eTxPbufQSegSize = epD->hwCfg.tx_pbuf_queue_segment_size;
            if (eTxPbufQSegSize > 15U) {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n",
                        "Warning: Wrong tx_pbuf_queue_segment_size read from hardware "\
                        "register (Express MAC), using 15 for further checking");
                eNumTxSegs = 1U << 15U;
            } else {
                eNumTxSegs = 1U << eTxPbufQSegSize;
            }

            eNumQSegsShift = epD->hwCfg.tx_pbuf_num_segments_q0;
            if (eNumQSegsShift > 15U) {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n",
                        "Warning: Wrong tx_pbuf_num_segments_q0 read from hardware "\
                        "register (Express MAC), using 15 for further checking");
                eNumQSegs = 1U << 15;
            } else {
                eNumQSegs = 1U << eNumQSegsShift;
            }

            if (eNumQSegs>eNumTxSegs) {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                        "Error: H/w configuration (Express MAC) allocates %u Tx packet buffer"\
                        " segments to queues out of %u total\n", eNumQSegs, eNumTxSegs);
                status = CDN_ENOTSUP;
            }
        }
    }
    return status;
}

static void disableUnusedQueues(CEDI_PrivateData *pD,
                const CEDI_Config *config)
{
    uint8_t i;

    for (i = config->txQs; i < pD->hwCfg.numQueues; i++) {
        setTxQueueDisableBit(pD, i, 1U);
    }

    for (i = config->rxQs; i < pD->hwCfg.numQueues; i++) {
        setRxQueueDisableBit(pD, i, 1U);
    }
}

static uint32_t checkNumQueues(const CEDI_Config *config, const CEDI_DesignCfg* hwCfg)
{
    uint32_t retVal = CDN_EOK;
    bool condition = ((config->rxQs == 0U) || (config->rxQs > hwCfg->numQueues) ||
                      (config->txQs == 0U) || (config->txQs > hwCfg->numQueues));


    if (condition) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                "Error: out-of-range numQs parameter");
        retVal = CDN_EINVAL;
    }

    return retVal;
}

static uint32_t checkRxQLengths(const CEDI_Config *config)
{
    uint8_t i;
    uint32_t retVal = CDN_EOK;

    for (i=0U; i<config->rxQs; i++) {
        if (config->rxQLen[i] > CEDI_MAX_RBQ_LENGTH) {
            retVal = CDN_EINVAL;
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "Error: out-of-range rxQLen(%u) parameter\n", i);
            break;
        }
    }
    return retVal;
}

static uint32_t descAddrNullCheck(const CEDI_Config *config)
{
    uint32_t retVal = CDN_EOK;
    bool condition = (config->txQAddr==0U) || (config->txQPhyAddr==0U) ||
                     (config->rxQAddr==0U) || (config->rxQPhyAddr==0U);

    if (condition) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                "Error: NULL Tx or Rx descriptor address parameter");
        retVal = CDN_EINVAL;
    }
    return retVal;
}

static uint32_t checkTxQLengths(const CEDI_Config *config)
{
    uint8_t i;
    uint32_t retVal = CDN_EOK;
    for (i=0U; i<config->txQs; i++) {
        if (config->txQLen[i]>CEDI_MAX_TBQ_LENGTH) {
            retVal = CDN_EINVAL;
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "Error: out-of-range txQLen(%u) parameter\n", i);
            break;
        }
    }
    return retVal;
}

static uint32_t checkDmaAddressingWidth(const CEDI_Config *config, const CEDI_DesignCfg* hwCfg)
{
    uint32_t retVal = CDN_EOK;

    if ((config->dmaAddrBusWidth == (uint8_t)CEDI_DMA_ADDR_BUS_WIDTH_64) &&
            (hwCfg->dma_addr_width == (uint8_t)CEDI_DMA_ADDR_BUS_WIDTH_32))
    {
        //vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
        //        "Error: 64-bit DMA addressing not supported in h/w config");
        //retVal = CDN_EINVAL;
    }

    return retVal;
}

static uint32_t checkPacketBuffSizes(const CEDI_Config *config)
{
    uint32_t retVal = CDN_EOK;
    uint8_t i;

    if ((config->txPktBufSize>1U) || (config->rxPktBufSize>3U)) {
        retVal = CDN_EINVAL;
    }

    if (CDN_EOK == retVal) {
        for (i = 0U; i < config->rxQs; i++) {
            if (config->rxBufLength[i] == 0U) {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: Invalid Packet buffer size or Rx buffer length");
                retVal = CDN_EINVAL;
                break;
            }
        }
    }

    return retVal;
}

static uint32_t checkDmaBusWidth(const CEDI_Config *config, const CEDI_DesignCfg *hwCfg)
{
    uint32_t retVal = CDN_EOK;
    uint8_t HwDmaBusWidth = hwCfg->dma_bus_width;
    uint32_t dmaBusWidth = (uint32_t)1UL << config->dmaBusWidth;

    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "1 << config->dmaBusWidth = %u, "\
            "pD->hwCfg.dma_bus_width = %u\n", dmaBusWidth, HwDmaBusWidth);

    if (dmaBusWidth > HwDmaBusWidth) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                "Error: Requested DMA bus width greater than h/w allows");
        retVal = CDN_EOK;
    }

    return retVal;
}

static uint32_t checkRxBuffDescAlignment(const CEDI_Config *config)
{
    uint32_t retVal = CDN_EOK;
    uint32_t alignment;

    /* enforce 32- or 64-bit alignment for RX buffers only */
    if (config->dmaBusWidth == CEDI_DMA_BUS_WIDTH_32) {
        alignment = 4U;
    } else {  /* expect 64-bit word alignment for 64/128-bit bus */
        alignment = 8U;
    }

    if ((config->rxQPhyAddr % alignment) != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                "Error: bad alignment of descriptor list memory");
        retVal = CDN_EINVAL;
    }

    return retVal;
}

static uint32_t initTxRxDescLists(CEDI_PrivateData *pD, const CEDI_Config *config)
{
    uint32_t status = CDN_EOK;

    calcDescriptorSizes(config, pD->hwCfg.gem_vm, pD->txDescriptorSize, pD->rxDescriptorSize);

    /* DMA config register */
    initDmaConfigReg(pD);

    /* writing the upper 32 bit buffer queue base address from config */
    if (CDN_EOK != initUpper32BuffQAddr(pD))
        status = CDN_EINVAL;

    if (CDN_EOK == status) {
        if (CDN_EOK != initTxDescLists(pD)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (CDN_EOK != initRxDescLists(pD)) {
            status = CDN_EINVAL;
        }
    }

    return status;
}

static uint32_t initHardwareScreeners(const CEDI_PrivateData *pD)
{
    uint32_t retVal = CDN_EOK;
    uint8_t i;
    uint8_t buffEq;
    CEDI_T1Screen clrT1ScrnRead;
    CEDI_T2Screen clrT2ScrnRead;
    CEDI_T1Screen clrT1Scrn = {0, 0, 0, 0, 0};
    CEDI_T2Screen clrT2Scrn = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (i = 0U; i<(pD->hwCfg.num_type1_screeners - 1U); i++) {

        retVal = CEDI_SetType1ScreenReg(pD, i, &clrT1Scrn);

        if (CDN_EOK != retVal) {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "Probe: Hardware initialization: CEDI_SetType1ScreenReg "\
                     "returned with code: %u\n", retVal);
        }

        if (CDN_EOK == retVal) {
            retVal = CEDI_GetType1ScreenReg(pD, i, &clrT1ScrnRead);

            if (CDN_EOK != retVal) {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                        "Probe: Hardware initialization: CEDI_GetType1ScreenReg "\
                        "returned with code: %u\n", retVal);
            }
        }

        if (CDN_EOK == retVal) {
            buffEq = CmpBuffs(&clrT1Scrn, &clrT1ScrnRead, sizeof(clrT1Scrn));
            if (buffEq != 0U) {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: Written and read screener T1 are different\n");
                retVal = CDN_EIO;
            }
        }

        if (CDN_EOK != retVal) {
            break;
        }

    }

    if (CDN_EOK == retVal){
        for (i = 0U; i<(pD->hwCfg.num_type2_screeners - 1U); i++) {

            retVal = CEDI_SetType2ScreenReg(pD, i, &clrT2Scrn);

            if (CDN_EOK != retVal) {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                        "Probe: Hardware initialization: CEDI_SetType2ScreenReg "\
                         "returned with code: %u\n", retVal);
            }

            if (CDN_EOK == retVal) {
                retVal = CEDI_GetType2ScreenReg(pD, i, &clrT2ScrnRead);

                if (CDN_EOK != retVal) {
                    vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                            "Probe: Hardware initialization: CEDI_GetType2ScreenReg "\
                            "returned with code: %u\n", retVal);
                }
            }

            if (CDN_EOK == retVal) {
                buffEq = CmpBuffs(&clrT2Scrn, &clrT2ScrnRead, sizeof(clrT2Scrn));
                if (buffEq != 0U) {
                    vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: Written and read screener T2 are different\n");
                    retVal = CDN_EIO;
                }
            }

            if (CDN_EOK != retVal) {
                break;
            }

        }
    }

    return retVal;
}

static uint32_t initHardwareHashAddr(const CEDI_PrivateData *pD)
{
    uint32_t hash1 = 1U, hash2 = 1U;
    uint32_t retVal;

    retVal = CEDI_SetHashAddr(pD, 0U, 0U);

    if (CDN_EOK == retVal) {
        retVal = CEDI_GetHashAddr(pD, &hash1, &hash2);
    } else {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI,
            "Probe: Hardware initialization: CEDI_SetHashAddr "\
            "returned with code: %u\n", retVal);
    }

    if (CDN_EOK == retVal) {
        if ((hash1 != 0U) || (hash2 != 0U)){
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: Written and read hash address are different\n");
            retVal = CDN_EIO;
        }
    } else {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI,
            "Probe: Hardware initialization: CEDI_GetHashAddr "\
            "returned with code: %u\n", retVal);
    }

    return retVal;
}

static void SetAutoNegEnable(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg = CPS_UncachedRead32(&(pD->regs->pcs_control));
    /* Must not do a read-modify-write with soft reset bit set otherwise
       will cause any writes to be ignored... */
    EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__CLR(reg);

    if (0U != enable) {
        EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__SET(reg);
    } else {
        EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__CLR(reg);
        pD->autoNegActive = 0U;
    }

    CPS_UncachedWrite32(&(pD->regs->pcs_control), reg);
}

static void GetAutoNegEnable(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t reg = CPS_UncachedRead32(&(pD->regs->pcs_control));
    *enable = (uint8_t) EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__READ(reg);
}


static uint32_t initHardwareAutoNeg(CEDI_PrivateData *pD)
{
    uint32_t retVal = CDN_EOK;
    uint32_t isPcsSelect;
    uint32_t regVal;
    uint8_t enable;

    regVal = CPS_REG_READ(&(pD->regs->network_config));
    isPcsSelect = EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__READ(regVal);

    if (0U != isPcsSelect) {
        SetAutoNegEnable(pD, 0U);
        GetAutoNegEnable(pD, &enable);

        if (enable != 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: Written and read auto negotiation enable are diffrent\n");
            retVal = CDN_EIO;
        }

        pD->anLinkStat = 1U;
        pD->anRemFault = 0U;
    }

    return retVal;
}

static uint32_t initSpecAddrRegs(const CEDI_PrivateData* pD)
{
    uint8_t i;
    uint32_t retVal = CDN_EOK;

    for (i = 1U; i<= pD->hwCfg.num_spec_add_filters; i++) {

        retVal = CEDI_DisableSpecAddr(pD, i);

        if (CDN_EOK != retVal) {
            break;
        }
    }

    return retVal;
}

static uint32_t initTxRxStatus(const CEDI_PrivateData* pD)
{
    uint32_t retVal;
    uint32_t flags;

    flags = CEDI_TXS_USED_READ | CEDI_TXS_COLLISION | CEDI_TXS_RETRY_EXC |
            CEDI_TXS_FRAME_ERR | CEDI_TXS_TX_COMPLETE | CEDI_TXS_UNDERRUN |
            CEDI_TXS_LATE_COLL | CEDI_TXS_HRESP_ERR;

    retVal = CEDI_ClearTxStatus(pD, flags);

    if (retVal == CDN_EOK) {
        flags = CEDI_RXS_NO_BUFF | CEDI_RXS_FRAME_RX |
                CEDI_RXS_OVERRUN | CEDI_RXS_HRESP_ERR;

        retVal = CEDI_ClearRxStatus(pD, flags);
    }

    return retVal;
}

static uint32_t initStatsRegs(const CEDI_PrivateData* pD)
{
    uint32_t retVal;

    retVal = CEDI_ClearStats(pD);

    if (CDN_EINVAL == retVal) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                "Probe: Hardware initialization: CEDI_ClearStats "\
                 "returned with code: %u\n", retVal);
     }

    return retVal;
}

static uint32_t initHardware(CEDI_PrivateData *pD)
{
    uint8_t i;
    uint32_t retVal = CDN_EOK;
    uint32_t status = CDN_EOK;

    uint8_t expressTrafficPresent = 0U;
    CEDI_PrivateData *epD = NULL;

    typedef uint32_t (*FuncPtr)(const CEDI_PrivateData*);

    /* Table with function pointers to initialize basic registers */
    FuncPtr initRegFunc[] = {
            initNetControlReg,
            initNetConfigReg,
            initAxiMaxPipelineReg,
            initSpecAddrRegs,
            initTxRxStatus,
            initStatsRegs,
            initHsMacConfigReg,
            initHardwareHashAddr,
            initHardwareScreeners
    };

    for (i = 0U; i < (sizeof(initRegFunc)/sizeof(FuncPtr)); i++) {
        status = (*(initRegFunc[i]))(pD);

        if ((status != CDN_EOK) && (status != CDN_ENOTSUP)) {
            retVal = status;
            break;
        }
    }

    if (CDN_EOK == retVal) {

        if (0U != pD->cfg.incExpressTraffic) {
            expressTrafficPresent = 1U;
            epD = pD->otherMac;
        }

        if (0U != expressTrafficPresent) {
            for (i = 0U; i < (sizeof(initRegFunc)/sizeof(FuncPtr)); i++) {
                status = (*(initRegFunc[i]))(epD);

                if ((status != CDN_EOK) && (status != CDN_ENOTSUP)) {
                    retVal = status;
                    break;
                }
            }
        }
    }

    /* PCS - PCS Select is set by initNetConfigReg */
    if (CDN_EOK == retVal) {
        retVal = initHardwareAutoNeg(pD);
    }

        if (CDN_EOK == retVal) {
    /* User outputs */
        status = CEDI_WriteUserOutputs(pD, 0U);

        if ((CDN_EOK != status) && (CDN_ENOTSUP != status)) {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                "Probe: Hardware initialization: CEDI_WriteUserOutputs "\
                "returned with code: %u\n", status);
            retVal = status;
        }
    }

    if (CDN_EOK == retVal) {
        if (pD->cfg.rxQs > 1U) {
            status = setRxQBufferSizes(pD, &(pD->cfg));
            if ((CDN_EOK != status) && (CDN_ENOTSUP != status)) {
                retVal = status;
            }
        }
    }

    return retVal;
}

/******************************************************************************
 * Public Driver functions
 * ***************************************************************************/

uint32_t CEDI_Probe(CEDI_Config *config, CEDI_SysReq *sysReq)
{
    uint32_t regTmp, regVal;
    uint32_t status = CEDI_ProbeSF(config, sysReq);
    uint32_t sumAllDesc;
    uint16_t txDescSize[CEDI_MAX_TX_QUEUES] = { 0 }, rxDescSize[CEDI_MAX_RX_QUEUES] = { 0 },
            sumTxDesc, sumRxDesc;
    struct emac_regs *regAddr;
    uint8_t paramErr = 0, numQs, q;
    uint16_t i;

    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s entered (regBase %p)\n", __func__,
                        (void *)config->regBase);

        if (0U != (config->regBase % sizeof(uint32_t))) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s\n", "Error: regBase address not 32-bit aligned");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        /* Module ID check */
        regAddr = regBaseToPtr(config->regBase);
        regVal = CPS_UncachedRead32(&(regAddr->revision_reg));
        regTmp = EMAC_REGS__REVISION_REG__MODULE_IDENTIFICATION_NUMBER__READ(
                        regVal);
        if ((regTmp!=GEM_GXL_MODULE_ID_V0) &&
            (regTmp!=GEM_GXL_MODULE_ID_V1) &&
            (regTmp!=GEM_GXL_MODULE_ID_V2) &&
            (regTmp!=GEM_AUTO_MODULE_ID_V0) &&
            (regTmp!=GEM_AUTO_MODULE_ID_V1) &&
            (regTmp!=GEM_10G_MODULE_ID_V1) &&
            (regTmp!=GEM_10G_MODULE_ID_V0) &&
            (regTmp!=GEM_XL_MODULE_ID)) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "Warning: Module ID uknown - 0x%04X read, \n",
                    regTmp);
        } else {
    #ifdef EMAC_REGS__REVISION_REG__FIX_NUMBER__READ
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "Module ID = 0x%03X, design rev = 0x%04X, fix no. = %u\n",
                    regTmp,
                    EMAC_REGS__REVISION_REG__MODULE_REVISION__READ(regVal),
                    EMAC_REGS__REVISION_REG__FIX_NUMBER__READ(regVal)
                    );
    #else
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Module ID = 0x%04X, design rev = 0x%04X\n", regTmp,
                    EMAC_REGS__REVISION_REG__MODULE_REVISION__READ(regVal));
    #endif
        }

        /* limit numbers of queues to what is available */
        numQs = maxHwQs(regAddr);

        if (config->rxQs>numQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                "Warning: Too many Rx queues requested (%u), only %u in h/w config\n",
                config->rxQs, numQs);
            config->rxQs = numQs;
        }
        if (config->txQs>numQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                "Warning: Too many Tx queues requested (%u), only %u in h/w config\n",
                    config->txQs, numQs);
            config->txQs = numQs;
        }

        regTmp = EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__READ(
                    CPS_UncachedRead32(&(regAddr->designcfg_debug6)));

        // DMA address bus width. 0 =32b , 1=64b
        if ((config->dmaAddrBusWidth == CEDI_DMA_ADDR_BUS_WIDTH_64) && (!regTmp))
        {
            //vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
            //          "Warning: 64-bit DMA addressing not supported in h/w config");
            config->dmaAddrBusWidth = CEDI_DMA_ADDR_BUS_WIDTH_64;//CEDI_DMA_ADDR_BUS_WIDTH_32;
        }

        for (i=0U; i<config->rxQs; i++)
        {
            if (config->rxQLen[i]>CEDI_MAX_RBQ_LENGTH)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "config->rxQLen(%u) (=%u) greater than maximum limit (%u)\n",
                    i, config->rxQLen[i], CEDI_MAX_RBQ_LENGTH);
                paramErr = 1;
                break;
            }
        }
        if (0U == paramErr) {
            for (i=0U; i<config->txQs; i++)
            {
                if (config->txQLen[i]>CEDI_MAX_TBQ_LENGTH)
                {
                    vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                        "config->txQLen(%u) (=%u) greater than maximum limit (%u)\n",
                        i, config->txQLen[i], CEDI_MAX_TBQ_LENGTH);
                    paramErr = 1;
                    break;
                }
            }
        }

        if (0U != paramErr)
        {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: parameter out of range");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        /* check, if 802.3br is enabled */
        regVal = CPS_UncachedRead32(&(regAddr->designcfg_debug12));
        if (0U == (EMAC_REGS__DESIGNCFG_DEBUG12__GEM_HAS_802P3_BR__READ(regVal))) {
            config->incExpressTraffic = 0U;
        }

        /* required memory allocations */

        /* descriptor list sizes */
        calcDescriptorSizes(config,
                (1U == (EMAC_REGS__DESIGNCFG_DEBUG12__GEM_VM__READ(regVal))) ? true : false,
                txDescSize, rxDescSize);

        sumTxDesc = (uint16_t) numTxDescriptors(config);
        sysReq->txDescListSize = sumTxDescriptorsListSize(config, txDescSize);
        if (0U != config->incExpressTraffic) {
            // assume express mac has 1 queue
            sumTxDesc += (uint16_t) config->eTxQLen[0] + CEDI_MIN_TXBD;
            // descriptor size for express mac is the same as for pmac Q0
            sysReq->txDescListSize += ((uint16_t) config->eTxQLen[0] + CEDI_MIN_TXBD) * txDescSize[0];
        }

        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "txQSize = %u\n", sysReq->txDescListSize);
        for (q = 0U; q < config->txQs; q++) {
            vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "txDescSize (q%u) = %u bytes\n", q, txDescSize[q]);
        }

        sumRxDesc = (uint16_t) numRxDescriptors(config);
        sysReq->rxDescListSize = sumRxDescriptorsListSize(config, rxDescSize);
        if (0U != config->incExpressTraffic) {
            // assume express mac has 1 queue
            sumRxDesc += (uint16_t) config->eRxQLen[0] + CEDI_MIN_RXBD;
            // descriptor size for express mac is the same as for pmac Q0
            sysReq->rxDescListSize += ((uint16_t) config->eRxQLen[0] + CEDI_MIN_RXBD) * rxDescSize[0];
        }

        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "rxQSize = %u\n", sysReq->rxDescListSize);
        for (q = 0U; q < config->rxQs; q++) {
            vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "rxDescSize (q%u) = %u bytes\n", q, rxDescSize[q]);
        }

        sumAllDesc = (uint32_t)sumTxDesc + (uint32_t)sumRxDesc;

        /* privateData including vAddr lists */
        sysReq->privDataSize = alignedToPtr((uint32_t)(sizeof(CEDI_PrivateData)))
                                      + ((uint32_t)(sizeof(uintptr_t))*sumAllDesc);
        if (0U != config->incExpressTraffic) {
        /* express mac private data */
        sysReq->privDataSize += alignedToPtr((uint32_t)(sizeof(CEDI_PrivateData)))
            + (((uint32_t)(config->eTxQLen[0])+CEDI_MIN_TXBD)*(uint32_t)(sizeof(uintptr_t)))
            + (((uint32_t)(config->eRxQLen[0])+CEDI_MIN_RXBD)*(uint32_t)(sizeof(uintptr_t)));
        }
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "privDataSize = %u bytes\n",
                sysReq->privDataSize);
        sysReq->statsSize = (uint32_t) sizeof(CEDI_Statistics);
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "statsSize = %u bytes\n",
                sysReq->statsSize);

    }
    return status;
}

uint32_t CEDI_GetAsfInfo(const CEDI_PrivateData* pD, CEDI_AsfInfo* asfInfo)
{
    uint32_t asfMask;
    uint16_t moduleId, revision;
    uint32_t reg;
    struct emac_regs *regAddr;
    uint32_t status = CEDI_GetAsfInfoSF(pD, asfInfo);
    uint8_t incExpressTraffic = 0;
    uintptr_t regBase;

    if (CDN_EOK == status) {
        if (pD->regs == NULL) {
            status = CDN_EINVAL;
        } else {
            regBase = (uintptr_t)(pD->regs);
        }
    }

    if (CDN_EOK == status) {

        asfMask = EMAC_REGS__DESIGNCFG_DEBUG11__ECC_SRAM__MASK
                | EMAC_REGS__DESIGNCFG_DEBUG11__DAP_PROTECTION__MASK
                | EMAC_REGS__DESIGNCFG_DEBUG11__CSR_PROTECTION__MASK
                | EMAC_REGS__DESIGNCFG_DEBUG11__PROTECT_TSU__MASK
                | EMAC_REGS__DESIGNCFG_DEBUG11__ASF_INTEGRITY_PROT__MASK
                | EMAC_REGS__DESIGNCFG_DEBUG11__ASF_TRANS_TO_PROT__MASK
                | EMAC_REGS__DESIGNCFG_DEBUG11__ASF_HOST_PAR__MASK
                | EMAC_REGS__DESIGNCFG_DEBUG11__ASF_PROT_TX_SCHED__MASK;

        asfInfo->asfCount = 0;
        asfInfo->asfRegBases[0] = 0;
        asfInfo->asfRegBases[1] = 0;

        regAddr = regBaseToPtr(regBase);
        reg = CPS_UncachedRead32(&(regAddr->revision_reg));
        moduleId = EMAC_REGS__REVISION_REG__MODULE_IDENTIFICATION_NUMBER__READ(reg);
        revision = EMAC_REGS__REVISION_REG__MODULE_REVISION__READ(reg);

        if (IsGem1p11_(moduleId, revision) == 0) {
            asfMask = 0;
        }
        asfInfo->asfVersion = IsGem1p13_(moduleId, revision) ? 2U : 1U;
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(regAddr->designcfg_debug12));
        incExpressTraffic = EMAC_REGS__DESIGNCFG_DEBUG12__GEM_HAS_802P3_BR__READ(reg);

        reg = CPS_UncachedRead32(&(regAddr->designcfg_debug11));
        if ((reg & asfMask) != 0){
            asfInfo->asfCount = 1;
            asfInfo->asfRegBases[0] = regBase + CEDI_ASF_REGS_OFFSET;

            if (incExpressTraffic && !IsGem1p13_(moduleId, revision)){
                asfInfo->asfCount = 2;
                asfInfo->asfRegBases[1] = regBase + CEDI_EXPRESS_MAC_REGS_OFFSET + CEDI_ASF_REGS_OFFSET;
            }
        }
    }
    return status;
}

static uint32_t checkStatsRegAddr(const CEDI_Config* cfg, const CEDI_DesignCfg* hwCfg)
{
    uint32_t retVal = CDN_EOK;

    if ((0U == hwCfg->no_stats) && (cfg->statsRegs == 0U)) {
        /* Statistic registers are required by HW, but any adress was passed by SW */
        retVal = CDN_EINVAL;
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s",
                "Error: NULL statistics struct address\n");
    }

    return retVal;
}

static uint32_t checkMultiQuantum(const CEDI_Config* cfg, const CEDI_DesignCfg* hwCfg)
{
    uint32_t retVal = CDN_EOK;

    if ((0U == hwCfg->pfc_multi_quantum) && (cfg->pfcMultiQuantum == 1U)) {
        /* Statistic registers are required by HW, but any adress was passed by SW */
        retVal = CDN_EINVAL;
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s",
                "Error: pfc Multiple quantum not supported by h/w\n");
    }

    return retVal;
}

/* Wrapper to checkSpeedSupport function. Used only in validateConfiguration to pack
   it inside array with function pointers */
static uint32_t _checkSpeedSupport(const CEDI_Config* cfg, const CEDI_DesignCfg* hwCfg)
{
    return checkSpeedSupport(cfg, hwCfg, cfg->ifSpeedSel);
}

static uint32_t validateConfiguration(const CEDI_Config* cfg, const CEDI_DesignCfg* hwCfg)
{
    /* Array of functions which validate configuration with constant values */
    typedef uint32_t (*CfgValidFuncPtr)(const CEDI_Config*);

    CfgValidFuncPtr validateCfgFunc[] = {
            checkRxQLengths,
            checkTxQLengths,
            descAddrNullCheck,
            checkPacketBuffSizes,
            checkRxBuffDescAlignment
    };

    typedef uint32_t (*HwCfgValidFuncPtr)(const CEDI_Config*, const CEDI_DesignCfg*);

    HwCfgValidFuncPtr validateHwCfgFunc[] = {
            checkDmaAddressingWidth,
            checkDmaBusWidth,
            checkNumQueues,
            checkStatsRegAddr,
            checkMultiQuantum,
            checkAxiPipeline,
            _checkSpeedSupport,
            isPcsSupported,
            isHighSpeedSupported
    };


    uint32_t size = (uint32_t)(sizeof(validateCfgFunc)/sizeof(CfgValidFuncPtr));
    uint8_t i;
    uint32_t retVal = CDN_EOK;

    for (i = 0U; i < size; i++) {
        /* Each function returns CDN_EINVAL when configuration validation
           was not passed or CDN_EOK if success */
        retVal = (*(validateCfgFunc[i]))(cfg);

        if (CDN_EOK != retVal) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                    "ERROR: Invalid configruation parameters, with return code: %u. Checker number: %u\n",
                    retVal, i);
        }
    }




    if (CDN_EOK == retVal) {
        /* Check configuration parameters which need be compared with
           hardware parameters */
        size = (uint32_t)(sizeof(validateHwCfgFunc)/sizeof(HwCfgValidFuncPtr));

        for (i = 0U; i < size; i++) {
            retVal = (*(validateHwCfgFunc[i]))(cfg, hwCfg);
            /* Here could be CDN_EOK, CDN_EINVAL, CDN_ENOTSUP or CDN_EIO */
            if (CDN_EOK != retVal) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                        "ERROR: Config don't meet the requirements of hardware, with return code: %u. Checker number: %u\n",
                        retVal, i);
                break;
            }
        }
    }

    return retVal;
}

static void initializeDriverData(CEDI_PrivateData* pD, const CEDI_Config* cfg, const CEDI_Callbacks* cb)
{
    uint8_t i;
    uint32_t privateDataSize;

    /* Copy config & callbacks into private data */
    pD->cfg = *cfg;
    pD->cb = *cb;

    pD->anLinkStat = 0U;
    pD->anRemFault = 0U;
    pD->autoNegActive = 0U;
    pD->basePageExp = 1U;
    pD->ptpTime.nanosecs = 0U;

    pD->rxQs = pD->cfg.rxQs;
    pD->txQs = pD->cfg.txQs;
    pD->numQs = pD->hwCfg.numQueues;


    pD->isTxDatapathEnabled = false;
    pD->isRxDatapathEnabled = (pD->cfg.ifTypeSel == CEDI_IFSP_USXGMII);

    for(i = 0U; i < (pD->numQs - 1U); i++) {
        pD->frerEnabled[i] = 0U;
    }

    if (cfg->incExpressTraffic != 0U) {
        privateDataSize =  (uint32_t)alignedToPtr((uint16_t)(sizeof(CEDI_PrivateData)));
        privateDataSize += (uint32_t)(numTxDescriptors(cfg) * sizeof(uintptr_t));
        privateDataSize += (uint32_t)(numRxDescriptors(cfg) * sizeof(uintptr_t));

        pD->macType = CEDI_MAC_TYPE_PMAC;
        pD->otherMac = (CEDI_PrivateData *)((uint8_t *)pD + privateDataSize);

        pD->otherMac->otherMac = pD;

    } else {
        pD->macType = CEDI_MAC_TYPE_MAC;
        pD->otherMac = NULL;
    }

}

uint32_t CEDI_Init(CEDI_PrivateData *pD, const CEDI_Config *config, const CEDI_Callbacks *callbacks)
{
    uint32_t status = CDN_EOK;
    uint32_t paramErr = 0U;

    CEDI_PrivateData *epD = NULL;

    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s entered (regBase %08X)\n", __func__, (uint32_t)config->regBase);

    /* parameter validation */
    status = CEDI_InitSF(pD, config, callbacks);

    if (CDN_EOK == status) {
        /* Read HW design config into PD*/
        pD->regs = regBaseToPtr(config->regBase);
        readDesignConfig(pD);

        /* Validate configuration with HW design config */
        status = validateConfiguration(config, &(pD->hwCfg));
    }

    if (CDN_EOK == status) {

        /* Validate callbacks for PCS25G */
        paramErr = pcs25gCbNullChecker(callbacks, config->pcs25gEvEnable);

        /* Validate callbacks */
        paramErr |= callbacksNullCheck(callbacks, config->intrEnable);

        status = (paramErr == 0U) ? CDN_EOK : CDN_EINVAL;
    }

    if (CDN_EOK == status) {

        initializeDriverData(pD, config, callbacks);

        disableUnusedQueues(pD, &(pD->cfg));

        /* ensure all interrupt sources disabled */
        disableAllInterrupts(pD);
        /* ensure ISRs are cleared */
        clearAllInterrupts(pD);

        status = initAllRegs(pD);
    }

    if (CDN_EOK == status) {

        if (0U != pD->cfg.incExpressTraffic) {
            epD = pD->otherMac;

            if (epD != NULL) {
                initExpressMacPD(epD, &(pD->cfg), &(pD->cb));
                readDesignConfig(epD);
                status = initAllRegs(epD);
            }
        }
    }

    if (CDN_EOK == status) {
        status = checkBufferSegmentsDistribution(pD);
    }

    /* Initialise driver internal data and Tx & Rx descriptor lists */
    if (CDN_EOK == status) {
        status = initTxRxDescLists(pD, config);
        if ((0U != config->incExpressTraffic) && (CDN_EOK == status)) {
            status = initTxRxDescLists(epD, config);
        }
    }

    /* Initialise hardware */
    if (CDN_EOK == status) {
        status = initHardware(pD);
    }

    return status;
}

void CEDI_Destroy(CEDI_PrivateData *pD)
{
    uint32_t status = CEDI_DestroySF(pD);
    CEDI_PrivateData *epD = NULL;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType) {
                status = CDN_EINVAL;
            } else {
                epD = pD->otherMac;
                if (epD==NULL)  {
                    status = CDN_EINVAL;
                }
            }
        }
    }

    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s entered (regBase %08X)\n", __func__,
                (uint32_t)pD->cfg.regBase);

        CEDI_AbortTx(pD);
        CEDI_DisableRx(pD);

      /* disable interrupts & ... */
        disableAllInterrupts(pD);

        if (0U != pD->cfg.incExpressTraffic) {
            CEDI_AbortTx(epD);
            CEDI_DisableRx(epD);
            disableAllInterrupts(epD);
        }
    }
}

uint32_t CEDI_SetEventEnable(CEDI_PrivateData *pD, uint32_t events, uint8_t enable,
        uint8_t queueNum)
{
    uint32_t paramErr;
    uint32_t status = CEDI_SetEventEnableSF(pD, enable);

    if (CDN_EOK == status) {
        if ((queueNum>=pD->numQs) && (queueNum!=CEDI_ALL_QUEUES)) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "*** Error: Invalid parameter, queueNum: %u\n", queueNum);
            status = CDN_EINVAL;
        }
    }

    /* test for invalid events */
    if (CDN_EOK == status) {
        if ((events &(~(((queueNum==0U) || (queueNum==CEDI_ALL_QUEUES))
                        ?(uint32_t)CEDI_EVSET_ALL_Q0_EVENTS:(uint32_t)CEDI_EVSET_ALL_QN_EVENTS)))!=0) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "*** Error: Invalid parameter, events: 0x%08X (queueNum=%u)\n",
                    events, queueNum);
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0U != events) {
            if (0U != enable) { /* enable!=0, i.e. enabling specified events */

                paramErr=callbacksNullCheck(&(pD->cb), events);
                if (0U!=paramErr){
                    vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                        "*** Error: Callback =NULL for event(s) 0x%08X\n", paramErr);
                    status = CDN_EINVAL;
                }
                if (CDN_EOK == status) {
                    if ((queueNum==0U) || (queueNum==CEDI_ALL_QUEUES)) {
                        enableQ0Events(pD, events);
                    }
                    if (queueNum>0) {
                        enableQnEvents(pD, events, queueNum);
                    }
                }
            }
            else  /* enable==0, i.e. disabling specified events */
            {
                if ((queueNum==0U) || (queueNum==CEDI_ALL_QUEUES)) {
                    disableQ0Events(pD, events);
                }
                if (queueNum>0) {
                    disableQnEvents(pD, events, queueNum);
                }
            }
        }
    }
    return status;
}

void CEDI_Start(CEDI_PrivateData *pD)
{
    uint32_t status = CEDI_StartSF(pD);
    uint32_t retVal;
    CEDI_PrivateData *epD = NULL;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType) {
                status = CDN_EINVAL;
            } else {
                epD = pD->otherMac;
                if (epD==NULL)  {
                    status = CDN_EINVAL;
                }
            }
        }
    }
    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s entered (regBase %08X)\n", __func__,
                (uint32_t)pD->cfg.regBase);

        /* enable events for all queues */
        retVal = CEDI_SetEventEnable(pD, pD->cfg.intrEnable,
                                    1, CEDI_ALL_QUEUES);

                /* set interrupts for USXGMII when exists and used */
        //if (retVal == CDN_EOK) {
        //    retVal = CEDI_SetPcs25gEventEnable(pD, pD->cfg.pcs25gEvEnable, true);
        //    if (retVal == CDN_ENOTSUP) {
        //        retVal = CDN_EOK;
        //    }
        //}

        if (CDN_EOK != retVal) {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                "CEDI_Start: Set event enable "\
                "returned with code: %u\n", retVal);
        }

        CEDI_EnableRx(pD);
        CEDI_EnableTx(pD);

        if ((retVal == CDN_EOK) && (0U != pD->cfg.incExpressTraffic)) {

            //retVal = CEDI_SetPcs25gEventEnable(epD, pD->cfg.pcs25gEvEnable, true);
            //if ((retVal == CDN_ENOTSUP) || (retVal == CDN_EOK)) {
                retVal = CEDI_SetEventEnable(epD, pD->cfg.intrEnable, 1, 0);
           // }

            if (CDN_EOK != retVal) {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "CEDI_Start: Set event enable "\
                    "(express MAC) returned with code: %u\n", retVal);
            }
            CEDI_EnableRx(epD);
            CEDI_EnableTx(epD);
        }

    }
}

void CEDI_Stop(CEDI_PrivateData *pD)
{
    uint32_t status = CEDI_StopSF(pD);
    uint32_t t;
    CEDI_PrivateData *epD = NULL;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType) {
                status = CDN_EINVAL;
            } else {
                epD = pD->otherMac;
                if (epD==NULL)  {
                    status = CDN_EINVAL;
                }
            }
        }
    }

    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s entered (regBase %08X)\n", __func__,
                (uint32_t)pD->cfg.regBase);

        /* Halt any Tx after present frame has finished */
        CEDI_StopTx(pD);
        for (t=10000; (t && (CEDI_Transmitting(pD))); t--) {;}
        if (0U != CEDI_Transmitting(pD)) { // this function returns 0 or 1
            CEDI_AbortTx(pD);
        }

        CEDI_DisableRx(pD);

        if (0U != pD->cfg.incExpressTraffic) {
            CEDI_StopTx(epD);
            for (t=10000; (t && (CEDI_Transmitting(epD))) != 0U; t--) {;}
            if (0U != CEDI_Transmitting(epD)) { // this function returns 0 or 1
                CEDI_AbortTx(epD);
            }

            CEDI_DisableRx(pD);
        }

        /* disable all interrupt sources */
        disableAllInterrupts(pD);

        if ((0U != pD->cfg.incExpressTraffic) && (epD != NULL)) {
            disableAllInterrupts(epD);
        }
    }
}

uint32_t CEDI_Isr(CEDI_PrivateData *pD)
{
    uint32_t status = CEDI_IsrSF(pD);
    uint8_t handled = 0U;
    uint32_t isrReg;
    CEDI_PrivateData *epD = NULL;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType) {
                //status = CDN_EINVAL;
		epD = pD;
            } else {
                epD = pD->otherMac;
                if (epD==NULL) {
                    status = CDN_EINVAL;
                }
            }
        }
    }


    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            isrReg = CPS_UncachedRead32(&(pD->regs->mmsl_int_status));
            if (0U != isrReg)
            {
                handled = 1;
                if (NULL != pD->cb.mmslEvent) {
                    (*(pD->cb.mmslEvent))(pD, isrReg);
                }
                if (0U==pD->hwCfg.irq_read_clear) {
                    CPS_UncachedWrite32(&(pD->regs->mmsl_int_status), isrReg);
                }
            }
            handleGeneralInterupts(epD, &handled);

            if (pD->cfg.ifTypeSel == CEDI_IFSP_USXGMII) {
                handlePcs25gInterrupts(epD, &handled);
            }
        }

        handleQnInterupts(pD, &handled);
        handleGeneralInterupts(pD, &handled);
        if (pD->cfg.ifTypeSel == CEDI_IFSP_USXGMII) {
            handlePcs25gInterrupts(pD, &handled);
        }
    }

    if (CDN_EOK == status) {
        if (0U == handled) {
            status = CDN_ECANCELED;
        }
    }

    return status;
}

uint32_t CEDI_GetEventEnable(CEDI_PrivateData *pD, uint8_t queueNum, uint32_t *event)
{
    uint32_t status = CEDI_GetEventEnableSF(pD, event);

    if (CDN_EOK == status) {
        if (queueNum>=pD->numQs) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum==0) {
            getQ0EventEnable(pD, event);
        }
        else
        {
            getQnEventEnable(pD, event, queueNum);
        }
    }
    return status;
}

uint32_t CEDI_SetIntrptModerate(CEDI_PrivateData *pD, uint8_t txIntDelay,
                                        uint8_t rxIntDelay)
{
    uint32_t status = CEDI_SetIntrptModerateSF(pD, txIntDelay, rxIntDelay);
    uint32_t reg;

    if (CDN_EOK == status) {
        if ((pD->hwCfg.intrpt_mod==0) && (txIntDelay || rxIntDelay)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->int_moderation));
        EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__MODIFY(reg, txIntDelay);
        EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__MODIFY(reg, rxIntDelay);
        CPS_UncachedWrite32(&(pD->regs->int_moderation), reg);
    }
    return status;
}

uint32_t CEDI_GetIntrptModerate(CEDI_PrivateData *pD, uint8_t *txIntDelay,
                                        uint8_t *rxIntDelay)
{
    uint32_t status = CEDI_GetIntrptModerateSF(pD, txIntDelay, rxIntDelay);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (pD->hwCfg.intrpt_mod==0) {
            *txIntDelay = 0U;
            *rxIntDelay = 0U;
        } else {
            reg = CPS_UncachedRead32(&(pD->regs->int_moderation));
            *txIntDelay= (uint8_t) EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__READ(reg);
            *rxIntDelay= (uint8_t) EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__READ(reg);
        }
    }
    return status;
}


static uint32_t setGemNormalSpeed(CEDI_PrivateData* pD, CEDI_IfSpeed speedSel)
{
    volatile uint32_t* netConfig;
    volatile uint32_t* netControl;
    uint32_t netConfigVal;
    uint32_t netControlVal;
    uint32_t status;

    status = checkSpeedSupport(&(pD->cfg), &(pD->hwCfg), speedSel);

    if (status == CDN_EOK) {
        netConfig = &(pD->regs->network_config);
        netControl = &(pD->regs->network_control);

        netConfigVal = CPS_REG_READ(netConfig);
        netControlVal = CPS_REG_READ(netControl);

        EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__CLR(netControlVal);

        if (speedSel == CEDI_SPEED_10M) {
            EMAC_REGS__NETWORK_CONFIG__SPEED__CLR(netConfigVal);
            EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__CLR(netConfigVal);
        } else if (speedSel == CEDI_SPEED_100M) {
            EMAC_REGS__NETWORK_CONFIG__SPEED__SET(netConfigVal);
            EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__CLR(netConfigVal);
        } else if (speedSel == CEDI_SPEED_1000M) {
            EMAC_REGS__NETWORK_CONFIG__SPEED__CLR(netConfigVal);
            EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__SET(netConfigVal);
        } else {
            /* condition for speedSel = CEDI_SPEED_2500M */
            EMAC_REGS__NETWORK_CONFIG__SPEED__CLR(netConfigVal);
            EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__SET(netConfigVal);
                        EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__SET(netControlVal);
                    }

        CPS_REG_WRITE(netConfig, netConfigVal);
        CPS_REG_WRITE(netControl, netControlVal);
    }

    return status;
}

static uint32_t setGemHighSpeed(CEDI_PrivateData* pD, CEDI_IfSpeed speedSel)
{
    uint32_t status = CDN_EOK;
    volatile uint32_t* regAddr;
    uint32_t regVal;

    if (speedSel == CEDI_SPEED_10M) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "ERROR: Cannot set CEDI_SPEED_10M for high-speed mode");
        status = CDN_EINVAL;
    }

    if (status == CDN_EOK) {
        regAddr = &(pD->regs->hs_mac_config);
        regVal = CPS_REG_READ(regAddr);
        /* correct speedSel due to High Speed mode */
        EMAC_REGS__HS_MAC_CONFIG__HS_MAC_SPEED__MODIFY(regVal, ((uint8_t)speedSel - 1U));
        CPS_REG_WRITE(regAddr, regVal);

        /* Instead input signals driven directly into PCS from hs_mac_control
           register HW use another register, dedicated for USXGMII */
        if (pD->hwCfg.no_pcs == 0U) {
            regAddr = &(pD->regs->usx_control_register);
            regVal = CPS_REG_READ(regAddr);
            EMAC_REGS__USX_CONTROL_REGISTER__HS_MAC_SPEED__MODIFY(regVal, (uint8_t) speedSel - 1U);
            CPS_REG_WRITE(regAddr, regVal);
        }
    }

    return status;
}

uint32_t CEDI_SetIfSpeed(CEDI_PrivateData *pD, CEDI_IfSpeed speedSel)
{
    uint32_t status;

    CEDI_PrivateData *epD = NULL;
    uint32_t (*setGemSpeed)(CEDI_PrivateData*, CEDI_IfSpeed);

    status = CEDI_SetIfSpeedSF(pD, speedSel);

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType) {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setIfSpeed can not be called for express MAC.");
                status = CDN_EINVAL;
            }
            epD = pD->otherMac;
        }
    }

    if (CDN_EOK == status) {
        if ((pD->cfg.ifTypeSel == CEDI_IFSP_XGMII) ||
            (pD->cfg.ifTypeSel == CEDI_IFSP_USXGMII)) {
            setGemSpeed = &setGemHighSpeed;
        } else {
            setGemSpeed = &setGemNormalSpeed;
        }

        status = setGemSpeed(pD, speedSel);
        if (CDN_EOK == status) {
            /* incExpressTraffic is checked before */
            if (epD != NULL) {
                status = setGemSpeed(epD, speedSel);
            }
        }

    }
    return status;
}

static void getNormalSpeed(const CEDI_PrivateData* pD, CEDI_IfSpeed* ifSpeed)
{
    uint32_t netCfgVal;
    uint32_t netCtrlVal;

    netCfgVal = CPS_REG_READ(&(pD->regs->network_config));

    if (0U != EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__READ(netCfgVal)) {
        *ifSpeed = CEDI_SPEED_1000M;
    } else if (0U != EMAC_REGS__NETWORK_CONFIG__SPEED__READ(netCfgVal)) {
        *ifSpeed = CEDI_SPEED_100M;
    } else {
        *ifSpeed = CEDI_SPEED_10M;
    }

    netCtrlVal = CPS_REG_READ(&(pD->regs->network_control));
    if (0U != EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__READ(netCtrlVal)) {
        *ifSpeed = CEDI_SPEED_2500M;
    }
}

static uint32_t getHighSpeed(const CEDI_PrivateData* pD, CEDI_IfSpeed* ifSpeed)
{
    uint32_t regVal;
    uint8_t speedNum;
    uint32_t status = CDN_EOK;

    const static CEDI_IfSpeed ifceSpeeds[6] = {
            CEDI_SPEED_100M,
            CEDI_SPEED_1000M,
            CEDI_SPEED_2500M,
            CEDI_SPEED_5G,
            CEDI_SPEED_10G,
            CEDI_SPEED_25G
    };

    regVal = CPS_REG_READ(&(pD->regs->hs_mac_config));
    speedNum = (uint8_t)EMAC_REGS__HS_MAC_CONFIG__HS_MAC_SPEED__READ(regVal);

    if (speedNum < CEDI_HS_AVAILABLE_SPEEDS_NUM) {
        *ifSpeed = ifceSpeeds[speedNum];
    } else {
        status = CDN_EIO;
    }

    return status;
}

uint32_t CEDI_GetIfSpeed(CEDI_PrivateData *pD, CEDI_IfSpeed *speedSel)
{
    uint32_t status = CEDI_GetIfSpeedSF(pD, speedSel);

    if (CDN_EOK == status) {
        if((pD->cfg.ifTypeSel == CEDI_IFSP_USXGMII) ||
           (pD->cfg.ifTypeSel == CEDI_IFSP_XGMII)) {
            status = getHighSpeed(pD, speedSel);
        } else {
            getNormalSpeed(pD, speedSel);
        }
    }
    return status;
}

void CEDI_SetJumboFramesRx(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetJumboFramesRxSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetJumboFramesRx(const CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetJumboFramesRxSF(pD, enable);

    if (CDN_EOK == status ){
        getJumboFramesRx(pD, enable);
    }

    return status;
}

uint32_t CEDI_SetJumboFrameRxMaxLen(CEDI_PrivateData *pD, uint16_t length)
{
    uint32_t status = CEDI_SetJumboFrameRxMaxLenSF(pD, length);
    uint32_t reg;
    uint8_t enabled;

    if (CDN_EOK == status) {
        getJumboFramesRx(pD, &enabled);
        reg = CPS_UncachedRead32(&(pD->regs->jumbo_max_length));
        if (0U != enabled) {
            CEDI_SetJumboFramesRx(pD, 0);
        }
        EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__MODIFY(reg, length);
        CPS_UncachedWrite32(&(pD->regs->jumbo_max_length), reg);
        if (0U != enabled) {
            CEDI_SetJumboFramesRx(pD, 1);
        }
    }
    return status;
}


uint32_t CEDI_SetUniDirEnable(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetUniDirEnableSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setUniDirEnable can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
    return status;
}

uint32_t CEDI_GetUniDirEnable(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetUniDirEnableSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= (uint8_t) EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }
    return status;
}

uint32_t CEDI_SetTxChecksumOffload(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetTxChecksumOffloadSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U == pD->hwCfg.tx_pkt_buffer) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s entered: enable = %u\n",
                                    __func__, enable);

        reg = CPS_UncachedRead32(&(pD->regs->dma_config));
        if (0U != enable) {
            EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__SET(reg);
        } else {
            EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->dma_config), reg);
    }
    return status;
}

uint32_t CEDI_GetTxChecksumOffload(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetTxChecksumOffloadSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= (uint8_t)EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__READ(
                CPS_UncachedRead32(&(pD->regs->dma_config)));
    }
    return status;
}

uint32_t CEDI_SetRxBufOffset(CEDI_PrivateData *pD, uint8_t offset)
{
    uint32_t status = CEDI_SetRxBufOffsetSF(pD, offset);
    uint32_t reg;

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (offset>3)  {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__MODIFY(reg, offset);
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
    return status;
}

uint32_t CEDI_GetRxBufOffset(CEDI_PrivateData *pD, uint8_t *offset)
{
    uint32_t status = CEDI_GetRxBufOffsetSF(pD, offset);

    if (CDN_EOK == status) {
        *offset= (uint8_t) EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }
    return status;
}


/** Set the DMA receive buffer size in external AMBA (AHB/AXI) system memory for the given queue -
 * the size of buffer to use in main system memory when writing received data */
uint32_t CEDI_SetRxQBufferSize(const CEDI_PrivateData *pD, uint8_t queueNum,
            uint8_t bufferSizeMultiple64Bytes) {
    uint32_t status = CEDI_SetRxQBufferSizeSF(pD, bufferSizeMultiple64Bytes);

    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t val = CPS_UncachedRead32(regPtr);
        EMAC_REGS__Q_CONTROL__RX_BUF_SIZE__MODIFY(val, bufferSizeMultiple64Bytes);
        status = WriteRegAndVerify(regPtr, val);
    }
    return status;
}

/** Read the DMA receive buffer size in external AMBA (AHB/AXI) system memory for the given queue -
 * the size of buffer to use in main system memory when writing received data */
uint32_t CEDI_GetRxQBufferSize(CEDI_PrivateData *pD, uint8_t queueNum,
        uint8_t bufferSizeMultiple64Bytes) {
    uint32_t status = CEDI_GetRxQBufferSizeSF(pD);

    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t reg_val = CPS_UncachedRead32(regPtr);
        bufferSizeMultiple64Bytes = (uint8_t) EMAC_REGS__Q_CONTROL__RX_BUF_SIZE__READ(reg_val);
    }
    return status;
}

/** Select the per queue max Rx burst length to use on the AMBA (AHB/AXI)
 * when writing frame data to external memory. */
uint32_t CEDI_SetRxQBurstLength(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_BurstLen burstLength) {
    uint32_t status = CEDI_SetRxQBurstLengthSF(pD, burstLength);

    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t val = CPS_UncachedRead32(regPtr);

        EMAC_REGS__Q_CONTROL__MAX_RX_BURST_LEN__MODIFY(val, (uint32_t) burstLength);
        status = WriteRegAndVerify(regPtr, val);
    }
    return status;
}

/** Read max Rx burst length per queue to use on the AMBA (AHB/AXI)
 * when writing frame data to external memory. */
uint32_t CEDI_GetRxQBurstLength(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_BurstLen burstLength) {
    uint32_t status = CEDI_GetRxQBurstLengthSF(pD, burstLength);

    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t burst_len_val = EMAC_REGS__Q_CONTROL__MAX_RX_BURST_LEN__READ(CPS_UncachedRead32(regPtr));
        // convert an integer to enum
        switch (burst_len_val) {
            case (uint32_t) CEDI_BURST_LEN_1: burstLength = CEDI_BURST_LEN_1; break;
            case (uint32_t) CEDI_BURST_LEN_2: burstLength = CEDI_BURST_LEN_2; break;
            case (uint32_t) CEDI_BURST_LEN_4: burstLength = CEDI_BURST_LEN_4; break;
            case (uint32_t) CEDI_BURST_LEN_8: burstLength = CEDI_BURST_LEN_8; break;
            case (uint32_t) CEDI_BURST_LEN_16: burstLength = CEDI_BURST_LEN_16; break;
            case (uint32_t) CEDI_BURST_LEN_32: burstLength = CEDI_BURST_LEN_32; break;
            case (uint32_t) CEDI_BURST_LEN_64: burstLength = CEDI_BURST_LEN_64; break;
            case (uint32_t) CEDI_BURST_LEN_128: burstLength = CEDI_BURST_LEN_128; break;
            case (uint32_t) CEDI_BURST_LEN_256: burstLength = CEDI_BURST_LEN_256; break;
            default:
                status = CDN_EINVAL; break;
        }
    }
    return status;
}

/** Select the per queue max Tx burst length to use on the AMBA (AHB/AXI)
 * when reading frame data from external memory. */
uint32_t CEDI_SetTxQBurstLength(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_BurstLen burstLength) {
    uint32_t status = CEDI_SetTxQBurstLengthSF(pD, burstLength);

    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.txQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t val = CPS_UncachedRead32(regPtr);

        EMAC_REGS__Q_CONTROL__MAX_TX_BURST_LEN__MODIFY(val, (uint32_t) burstLength);
        status = WriteRegAndVerify(regPtr, val);
    }
    return status;
}

/** Read max Tx burst length per queue to use on the AMBA (AHB/AXI)
 * when reading frame data from external memory. */
uint32_t CEDI_GetTxQBurstLength(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_BurstLen burstLength) {
    uint32_t status = CEDI_GetTxQBurstLengthSF(pD, burstLength);

    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.txQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t burst_len_val = EMAC_REGS__Q_CONTROL__MAX_TX_BURST_LEN__READ(CPS_UncachedRead32(regPtr));
        // convert an integer to enum
        switch (burst_len_val) {
            case (uint32_t) CEDI_BURST_LEN_1: burstLength = CEDI_BURST_LEN_1; break;
            case (uint32_t) CEDI_BURST_LEN_2: burstLength = CEDI_BURST_LEN_2; break;
            case (uint32_t) CEDI_BURST_LEN_4: burstLength = CEDI_BURST_LEN_4; break;
            case (uint32_t) CEDI_BURST_LEN_8: burstLength = CEDI_BURST_LEN_8; break;
            case (uint32_t) CEDI_BURST_LEN_16: burstLength = CEDI_BURST_LEN_16; break;
            case (uint32_t) CEDI_BURST_LEN_32: burstLength = CEDI_BURST_LEN_32; break;
            case (uint32_t) CEDI_BURST_LEN_64: burstLength = CEDI_BURST_LEN_64; break;
            case (uint32_t) CEDI_BURST_LEN_128: burstLength = CEDI_BURST_LEN_128; break;
            case (uint32_t) CEDI_BURST_LEN_256: burstLength = CEDI_BURST_LEN_256; break;
            default:
                status = CDN_EINVAL; break;
        }
    }
    return status;
}

void CEDI_Set1536ByteFramesRx(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_Set1536ByteFramesRxSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

void CEDI_SetRxChecksumOffload(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetRxChecksumOffloadSF(pD, enable);

    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s entered: enable = %u\n",
                                    __func__, enable);

        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetRxChecksumOffload(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetRxChecksumOffloadSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= (uint8_t) EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }
    return status;
}

void CEDI_SetFcsRemove(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetFcsRemoveSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetFcsRemove(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetFcsRemoveSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= (uint8_t) EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }
    return status;
}

uint32_t CEDI_SetRxDmaDataAddrMask(CEDI_PrivateData *pD, uint8_t enableBit,
        uint8_t bitValues)
{
    uint32_t reg = 0U;
    uint32_t status = CEDI_SetRxDmaDataAddrMaskSF(pD, enableBit, bitValues);

    if (CDN_EOK == status) {
        EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__MODIFY(reg, enableBit);
        EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__MODIFY(reg, bitValues);
        CPS_UncachedWrite32(&(pD->regs->dma_addr_or_mask), reg);
    }
    return status;
}

uint32_t CEDI_GetRxDmaDataAddrMask(CEDI_PrivateData *pD, uint8_t *enableBit,
        uint8_t *bitValues)
{
    uint32_t status = CEDI_GetRxDmaDataAddrMaskSF(pD, enableBit, bitValues);
    uint32_t reg;

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->dma_addr_or_mask));
        *enableBit = (uint8_t)EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__READ(reg);
        *bitValues = (uint8_t)EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__READ(reg);
    }
    return status;
}

void CEDI_SetRxBadPreamble(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t regVal;
    uint32_t status;
    volatile uint32_t* regAddr;

    status = CEDI_SetRxBadPreambleSF(pD, enable);

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->network_config);
        regVal = CPS_REG_READ (regAddr);

                if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__NSP_ACCEPT__SET(regVal);
        } else {
            EMAC_REGS__NETWORK_CONFIG__NSP_ACCEPT__CLR(regVal);
        }

        CPS_REG_WRITE(regAddr, regVal);
    }
}

uint32_t CEDI_GetRxBadPreamble(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_GetRxBadPreambleSF(pD, enable);

    if (CDN_EOK == status) {
        regVal = CPS_REG_READ(&(pD->regs->network_config));

                *enable= (uint8_t)EMAC_REGS__NETWORK_CONFIG__NSP_ACCEPT__READ(regVal);
            }

    return status;
}

uint32_t CEDI_SetFullDuplex(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetFullDuplexSF(pD, enable);
    CEDI_PrivateData *epD = NULL;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setIfSpeed can not be called for express MAC.");
                status = CDN_EINVAL;
            }
            epD = pD->otherMac;
        }
    }
    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s entered: set to %s duplex\n",
                __func__, (0U != enable)?"full":"half");

        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
        if (0U != pD->cfg.incExpressTraffic) {
            reg = CPS_UncachedRead32(&(epD->regs->network_config));
            if (0U != enable) {
                EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__SET(reg);
            } else {
                EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__CLR(reg);
            }
            CPS_UncachedWrite32(&(epD->regs->network_config), reg);
        }
    }
    return status;
}

uint32_t CEDI_GetFullDuplex(const CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetFullDuplexSF(pD, enable);

    if (CDN_EOK == status) {
        getFullDuplex(pD, enable);
    }
    return status;
}

void CEDI_SetIgnoreFcsRx(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetIgnoreFcsRxSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetIgnoreFcsRx(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetIgnoreFcsRxSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= (uint8_t)EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }

    return status;
}

void CEDI_SetRxHalfDuplexInTx(const CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetRxHalfDuplexInTxSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetRxHalfDuplexInTx(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetRxHalfDuplexInTxSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= (uint8_t) EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }

    return status;
}

uint32_t CEDI_SetPreambleCrcCover(CEDI_PrivateData *pD, CEDI_PreCrcCover txCrcPreCover, CEDI_PreCrcCover rxCrcPreCover)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t* regAddr;

    status = CEDI_SetPreambleCrcCoverSF(pD, txCrcPreCover, rxCrcPreCover);

        if (CDN_EOK == status) {
        status = (pD->cfg.ifTypeSel >= CEDI_IFSP_XGMII) ? CDN_EOK : CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {

                regAddr = &(pD->regs->hs_mac_config);

        reg = CPS_REG_READ(regAddr);

                EMAC_REGS__HS_MAC_CONFIG__PREAMBLE_IN_CRC_TX__MODIFY(reg, txCrcPreCover);
        EMAC_REGS__HS_MAC_CONFIG__PREAMBLE_IN_CRC_RX__MODIFY(reg, rxCrcPreCover);

        CPS_REG_WRITE(regAddr, reg);
    }

    return status;
}

uint32_t CEDI_GetPreambleCrcCover(CEDI_PrivateData *pD, CEDI_PreCrcCover *txCrcPreCover, CEDI_PreCrcCover *rxCrcPreCover)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t* regAddr;

    status = CEDI_GetPreambleCrcCoverSF(pD, txCrcPreCover, rxCrcPreCover);

        if (CDN_EOK == status) {
        status = (pD->cfg.ifTypeSel >= CEDI_IFSP_XGMII) ? CDN_EOK : CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
                regAddr = &(pD->regs->hs_mac_config);

        reg = CPS_REG_READ(regAddr);

                *txCrcPreCover = EMAC_REGS__HS_MAC_CONFIG__PREAMBLE_IN_CRC_TX__READ(reg);
        *rxCrcPreCover = EMAC_REGS__HS_MAC_CONFIG__PREAMBLE_IN_CRC_RX__READ(reg);

    }

    return status;
}

uint32_t CEDI_GetIfCapabilities(const CEDI_PrivateData *pD, uint32_t *cap)
{
    uint32_t status = CEDI_GetIfCapabilitiesSF(pD, cap);

    if (CDN_EOK == status) {

        *cap = 0U;

// TODO: temporary detection based on header-data splitting until get LSO-related define
#ifdef EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ
        *cap |= CEDI_CAP_LSO;
#endif
// TODO: RSC, RSS, ...
    }

    return status;
}

/******************************** Pause Control ******************************/

void CEDI_SetPauseEnable(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetPauseEnableSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }

}

uint32_t CEDI_GetPauseEnable(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetPauseEnableSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= (uint8_t) EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }

    return status;
}

void CEDI_TxPauseFrame(CEDI_PrivateData *pD)
{
    uint32_t reg;
    uint32_t status = CEDI_TxPauseFrameSF(pD);

    if (CDN_EOK == status)  {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__SET(reg);
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
}

void CEDI_TxZeroQPause(CEDI_PrivateData *pD)
{
    uint32_t reg;
    uint32_t status = CEDI_TxZeroQPauseSF(pD);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__SET(reg);
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
}

uint32_t CEDI_GetRxPauseQuantum(CEDI_PrivateData *pD, uint16_t *value)
{
    uint32_t status = CEDI_GetRxPauseQuantumSF(pD, value);

    if (CDN_EOK == status) {
        *value = (uint8_t) EMAC_REGS__PAUSE_TIME__QUANTUM__READ(
                CPS_UncachedRead32(&(pD->regs->pause_time)));
    }
    return status;
}

uint32_t CEDI_SetTxPauseQuantum(CEDI_PrivateData *pD, uint16_t value, uint8_t qpriority)
{
    uint32_t status = CEDI_SetTxPauseQuantumSF(pD, value, qpriority);
    uint32_t reg;

    if (CDN_EOK == status) {
        if ((pD->hwCfg.pfc_multi_quantum==0)
                            && (qpriority>0)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        switch (qpriority) {
        default:
        case 0:
            reg = CPS_UncachedRead32(&(pD->regs->tx_pause_quantum));
            EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__MODIFY(reg, value);
            CPS_UncachedWrite32(&(pD->regs->tx_pause_quantum), reg);
            break;
        case 1:
            reg = CPS_UncachedRead32(&(pD->regs->tx_pause_quantum));
            EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__MODIFY(reg, value);
            CPS_UncachedWrite32(&(pD->regs->tx_pause_quantum), reg);
            break;
        case 2:
            reg = CPS_UncachedRead32(&(pD->regs->tx_pause_quantum1));
            EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__MODIFY(reg, value);
            CPS_UncachedWrite32(&(pD->regs->tx_pause_quantum1), reg);
            break;
        case 3:
            reg = CPS_UncachedRead32(&(pD->regs->tx_pause_quantum1));
            EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__MODIFY(reg, value);
            CPS_UncachedWrite32(&(pD->regs->tx_pause_quantum1), reg);
            break;
        case 4:
            reg = CPS_UncachedRead32(&(pD->regs->tx_pause_quantum2));
            EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__MODIFY(reg, value);
            CPS_UncachedWrite32(&(pD->regs->tx_pause_quantum2), reg);
            break;
        case 5:
            reg = CPS_UncachedRead32(&(pD->regs->tx_pause_quantum2));
            EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__MODIFY(reg, value);
            CPS_UncachedWrite32(&(pD->regs->tx_pause_quantum2), reg);
            break;
        case 6:
            reg = CPS_UncachedRead32(&(pD->regs->tx_pause_quantum3));
            EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__MODIFY(reg, value);
            CPS_UncachedWrite32(&(pD->regs->tx_pause_quantum3), reg);
            break;
        case 7:
            reg = CPS_UncachedRead32(&(pD->regs->tx_pause_quantum3));
            EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__MODIFY(reg, value);
            CPS_UncachedWrite32(&(pD->regs->tx_pause_quantum3), reg);
            break;
        }
    }
    return status;
}

uint32_t CEDI_GetTxPauseQuantum(CEDI_PrivateData *pD, uint16_t *value, uint8_t qpriority)
{
    uint32_t status = CEDI_GetTxPauseQuantumSF(pD, value, qpriority);

    if (CDN_EOK == status) {
        if ((pD->hwCfg.pfc_multi_quantum==0)
                            && (qpriority>0)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        switch(qpriority){
        default:
        case 0:
            *value= (uint16_t)EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__READ(
                        CPS_UncachedRead32(&(pD->regs->tx_pause_quantum)));
            break;
        case 1:
            *value= (uint16_t)EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__READ(
                        CPS_UncachedRead32(&(pD->regs->tx_pause_quantum)));
            break;
        case 2:
            *value= (uint16_t)EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__READ(
                        CPS_UncachedRead32(&(pD->regs->tx_pause_quantum1)));
            break;
        case 3:
            *value= (uint16_t)EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__READ(
                        CPS_UncachedRead32(&(pD->regs->tx_pause_quantum1)));
            break;
        case 4:
            *value= (uint16_t)EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__READ(
                        CPS_UncachedRead32(&(pD->regs->tx_pause_quantum2)));
            break;
        case 5:
            *value= (uint16_t)EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__READ(
                        CPS_UncachedRead32(&(pD->regs->tx_pause_quantum2)));
            break;
        case 6:
            *value= (uint16_t)EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__READ(
                        CPS_UncachedRead32(&(pD->regs->tx_pause_quantum3)));
            break;
        case 7:
            *value= (uint16_t)EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__READ(
                        CPS_UncachedRead32(&(pD->regs->tx_pause_quantum3)));
            break;
        }
    }

    return status;
}

void CEDI_SetCopyPauseDisable(CEDI_PrivateData *pD, uint8_t disable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetCopyPauseDisableSF(pD, disable);

    if (CDN_EOK == status)  {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != disable) {
            EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetCopyPauseDisable(CEDI_PrivateData *pD, uint8_t *disable)
{
    uint32_t status = CEDI_GetCopyPauseDisableSF(pD, disable);

    if (CDN_EOK == status) {
        *disable= (uint8_t) EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }

    return status;
}

void CEDI_SetPfcPriorityBasedPauseRx(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetPfcPriorityBasedPausSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
}

uint32_t CEDI_GetPfcPriorityBasedPauseRx(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetPfcPriorityBasedPausSF(pD, enable);

    if (CDN_EOK == status) {
        *enable = (uint8_t) EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__READ(
                CPS_UncachedRead32(&(pD->regs->network_control)));
    }
    return status;
}

uint32_t CEDI_TxPfcPriorityBasedPause(CEDI_PrivateData *pD)
{
    uint8_t fullDup = 1;
    uint32_t status = CEDI_TxPfcPriorityBasedPauseSF(pD);
    uint32_t reg;

    if (CDN_EOK == status) {
        getFullDuplex(pD, &fullDup);
        if (0U == fullDup) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        if (0U == CEDI_GetTxEnabled(pD)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__SET(reg);
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
    return status;
}

uint32_t CEDI_SetTxPfcPauseFrameFields(CEDI_PrivateData *pD, uint8_t priEnVector,
            uint8_t zeroQSelVector)
{
    uint32_t status = CEDI_SetTxPfcPauseFrameFieldSF(pD);
    uint32_t reg = 0U;

    if (CDN_EOK == status) {
        EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__MODIFY(reg, priEnVector);
        EMAC_REGS__TX_PFC_PAUSE__VECTOR__MODIFY(reg, zeroQSelVector);
        CPS_UncachedWrite32(&(pD->regs->tx_pfc_pause), reg);
    }
    return status;
}

uint32_t CEDI_GetTxPfcPauseFrameFields(CEDI_PrivateData *pD, uint8_t *priEnVector,
            uint8_t *zeroQSelVector)
{
    uint32_t status = CEDI_GetTxPfcPauseFrameFieldSF(pD, priEnVector, zeroQSelVector);
    uint32_t reg = 0U;

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->tx_pfc_pause));
        *priEnVector = (uint8_t) EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__READ(reg);
        *zeroQSelVector = (uint8_t) EMAC_REGS__TX_PFC_PAUSE__VECTOR__READ(reg);
    }
    return status;
}

uint32_t CEDI_SetEnableMultiPfcPauseQuantum(CEDI_PrivateData *pD, uint8_t enMultiPfcPause)
{
    uint32_t status = CEDI_SetEnableMultiPfcPauseQSF(pD, enMultiPfcPause);
    uint32_t regVal = 0U;

    if (CDN_EOK == status) {
        if ((pD->hwCfg.pfc_multi_quantum==0U) && (enMultiPfcPause==1U)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        regVal = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__MODIFY(regVal, enMultiPfcPause);

        CPS_UncachedWrite32(&(pD->regs->network_control), regVal);
    }
    return status;
}

uint32_t CEDI_GetEnableMultiPfcPauseQuantum(CEDI_PrivateData *pD, uint8_t *enMultiPfcPause)
{
    uint32_t status = CEDI_GetEnableMultiPfcPauseQSF(pD, enMultiPfcPause);
    uint32_t regVal = 0U;

    if (CDN_EOK == status) {
        regVal = CPS_UncachedRead32(&(pD->regs->network_control));
        *enMultiPfcPause = (uint8_t) EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__READ(regVal);
    }
    return status;
}


/****************************** Loopback Control *****************************/

/**
 * Enable or disable loop back mode in the EMAC.
 * @param pD - driver private state info specific to this instance
 * @param mode - enum selecting mode enable/disable:
 *    CEDI_SERDES_LOOPBACK :select loopback mode in PHY transceiver, if
 *        available
 *    CEDI_LOCAL_LOOPBACK  :select internal loopback mode. Tx and Rx should be
 *                        :disabled when enabling or disabling this mode.
 *                        :Only available if int_loopback defined.
 *    CEDI_NO_LOOPBACK     :disable loopback mode
 * @return CDN_ENOTSUP if CEDI_SERDES_LOOPBACK selected and no_pcs defined, or
 *    if CEDI_LOCAL_LOOPBACK selected and either
 *        (no_int_loopback defined or PCS mode is selected)
 * @return CDN_ENOTSUP if CEDI_LOCAL_LOOPBACK selected and no_int_loopback defined
 * @return 0 otherwise.
 */
uint32_t CEDI_SetLoopback(CEDI_PrivateData *pD, uint8_t mode)
{
    uint32_t reg;
    uint32_t status = CEDI_SetLoopbackSF(pD, mode);
    uint32_t pcsControlReg = 0;
    uint32_t pcsSelect;

    if (CDN_EOK == status) {
        if ((pD->hwCfg.no_pcs && (mode == CEDI_SERDES_LOOPBACK)) ||
            (pD->hwCfg.no_int_loopback && (mode == CEDI_LOCAL_LOOPBACK))) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        pcsSelect = EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__READ(CPS_REG_READ(&(pD->regs->network_config)));
        if ((pcsSelect != 0U) && (mode == CEDI_LOCAL_LOOPBACK)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));

        /* Check if PCS registers exists */
        if ( 0U == pD->hwCfg.no_pcs) {
            pcsControlReg = CPS_UncachedRead32(&(pD->regs->pcs_control));
        }

        EMAC_REGS__NETWORK_CONTROL__LOOPBACK__CLR(reg);

        if (mode == CEDI_LOCAL_LOOPBACK) {
            EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__SET(reg);
            EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__CLR(pcsControlReg);
        } else if (mode == CEDI_SERDES_LOOPBACK) {
            EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__CLR(reg);
            EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__SET(pcsControlReg);
        } else {  /* CEDI_NO_LOOPBACK */
            EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__CLR(reg);
            EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__CLR(pcsControlReg);
        }

        CPS_UncachedWrite32(&(pD->regs->network_control), reg);

        if ( 0U == pD->hwCfg.no_pcs) {
            /* Must not do a read-modify-write with soft reset bit set otherwise
               will cause any writes to be ignored... */
            EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__CLR(pcsControlReg);
            CPS_UncachedWrite32(&(pD->regs->pcs_control), pcsControlReg);
        }
    }
    return status;
}

uint32_t CEDI_GetLoopback(CEDI_PrivateData *pD, uint8_t *mode)
{
    uint32_t status = CEDI_GetLoopbackSF(pD, mode);
    uint32_t reg;
    uint32_t reg2;

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
	if ( 0U == pD->hwCfg.no_pcs) {
            reg2 = CPS_UncachedRead32(&(pD->regs->pcs_control));
            if (0U != EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__READ(reg2)) {
               *mode= CEDI_SERDES_LOOPBACK;
            }
	} 
        else
            if (0U != EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__READ(reg)) {
               *mode= CEDI_LOCAL_LOOPBACK;
            } else {
               *mode= CEDI_NO_LOOPBACK;
            }
    }

    return status;
}

/**************************** PTP/1588 Support *******************************/

void CEDI_SetUnicastPtpDetect(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetUnicastPtpDetectSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
}

uint32_t CEDI_GetUnicastPtpDetect(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetUnicastPtpDetectSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= (uint8_t) EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__READ(
                CPS_UncachedRead32(&(pD->regs->network_control)));
    }

    return status;
}

uint32_t CEDI_SetPtpRxUnicastIpAddr(CEDI_PrivateData *pD, uint32_t rxAddr)
{
    uint32_t status = CEDI_SetPtpRxUnicastIpAddrSF(pD, rxAddr);
    uint32_t reg = 0U;
    uint8_t enabled = 0U;

    if (CDN_EOK == status) {
        status = CEDI_GetUnicastPtpDetect(pD, &enabled);
        if ((CDN_EOK == status) && (0U != enabled)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        EMAC_REGS__RX_PTP_UNICAST__ADDRESS__MODIFY(reg, rxAddr);
        CPS_UncachedWrite32(&(pD->regs->rx_ptp_unicast), reg);
    }
    return status;
}

uint32_t CEDI_GetPtpRxUnicastIpAddr(CEDI_PrivateData *pD, uint32_t *rxAddr)
{
    uint32_t status = CEDI_GetPtpRxUnicastIpAddrSF(pD, rxAddr);

    if (CDN_EOK == status) {
        *rxAddr= EMAC_REGS__RX_PTP_UNICAST__ADDRESS__READ(
                CPS_UncachedRead32(&(pD->regs->rx_ptp_unicast)));
    }
    return status;
}

uint32_t CEDI_SetPtpTxUnicastIpAddr(CEDI_PrivateData *pD, uint32_t txAddr)
{
    uint32_t reg = 0U;
    uint32_t status = CEDI_SetPtpRxUnicastIpAddrSF(pD, txAddr);
    uint8_t enabled = 0U;

    if (CDN_EOK == status) {
        status = CEDI_GetUnicastPtpDetect(pD, &enabled);

        if ((CDN_EOK == status) && (0U != enabled)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        EMAC_REGS__TX_PTP_UNICAST__ADDRESS__MODIFY(reg, txAddr);
        CPS_UncachedWrite32(&(pD->regs->tx_ptp_unicast), reg);
    }
    return status;
}

uint32_t CEDI_GetPtpTxUnicastIpAddr(CEDI_PrivateData *pD, uint32_t *txAddr)
{
    uint32_t status = CEDI_GetPtpTxUnicastIpAddrSF(pD, txAddr);

    if (CDN_EOK == status) {
        *txAddr= EMAC_REGS__TX_PTP_UNICAST__ADDRESS__READ(
                CPS_UncachedRead32(&(pD->regs->tx_ptp_unicast)));
    }
    return status;
}

uint32_t CEDI_Set1588Timer(CEDI_PrivateData *pD, const CEDI_1588TimerVal *timeVal)
{
    uint32_t status = CEDI_Set1588TimerSF(pD, timeVal);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U ==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: set1588Timer can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->tsu_timer_msb_sec));
        EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__MODIFY(reg, timeVal->secsUpper);
        CPS_UncachedWrite32(&(pD->regs->tsu_timer_msb_sec), reg);
        /* write lower bits 2nd, for synchronised secs update */
        reg = 0U;
        EMAC_REGS__TSU_TIMER_SEC__TIMER__MODIFY(reg, timeVal->secsLower);
        CPS_UncachedWrite32(&(pD->regs->tsu_timer_sec), reg);
        reg = 0U;
        EMAC_REGS__TSU_TIMER_NSEC__TIMER__MODIFY(reg, timeVal->nanosecs);
        CPS_UncachedWrite32(&(pD->regs->tsu_timer_nsec), reg);
    }
    return status;
}

uint32_t CEDI_Get1588Timer(CEDI_PrivateData *pD, CEDI_1588TimerVal *timeVal)
{
    uint32_t status = CEDI_Get1588TimerSF(pD, timeVal);
    uint32_t reg, first;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        first = EMAC_REGS__TSU_TIMER_NSEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_timer_nsec)));
        timeVal->secsLower = EMAC_REGS__TSU_TIMER_SEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_timer_sec)));
        timeVal->secsUpper = (uint16_t)EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_timer_msb_sec)));
        /* test for nsec rollover */

        reg = CPS_UncachedRead32(&(pD->regs->tsu_timer_nsec));
        if (first>(EMAC_REGS__TSU_TIMER_NSEC__TIMER__READ(reg))) {
            /* if so, use later read & re-read seconds
             * (assume all done within 1s) */
            timeVal->nanosecs = EMAC_REGS__TSU_TIMER_NSEC__TIMER__READ(reg);
            timeVal->secsLower = EMAC_REGS__TSU_TIMER_SEC__TIMER__READ(
                    CPS_UncachedRead32(&(pD->regs->tsu_timer_sec)));
            timeVal->secsUpper = (uint16_t)EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__READ(
                    CPS_UncachedRead32(&(pD->regs->tsu_timer_msb_sec)));
        } else {
            timeVal->nanosecs = first;
        }

    }

    return status;
}

uint32_t CEDI_Adjust1588Timer(CEDI_PrivateData *pD, int32_t nSecAdjust)
{
    uint32_t status = CEDI_Adjust1588TimerSF(pD, nSecAdjust);
    uint32_t reg;
    /* Absolute value */
    uint32_t nSecAdjustAbs;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: adjust1588Timer can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = 0U;
        if (nSecAdjust<0) {
            EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__SET(reg);
            nSecAdjustAbs = -nSecAdjust;
        } else {
            nSecAdjustAbs = nSecAdjust;
        }

        EMAC_REGS__TSU_TIMER_ADJUST__INCREMENT_VALUE__MODIFY(reg, nSecAdjustAbs);
        CPS_UncachedWrite32(&(pD->regs->tsu_timer_adjust), reg);
    }
    return status;
}

uint32_t CEDI_Set1588TimerInc(CEDI_PrivateData *pD,
                             const CEDI_TimerIncrement *incSettings)
{
    uint32_t status = CEDI_Set1588TimerIncSF(pD, incSettings);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: set1588TimerInc can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
#ifdef  EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__MODIFY
        reg = 0U;
        EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__MODIFY(reg,
                           incSettings->subNsInc);
        if (0U != subNsTsuInc24bSupport(pD)) {
            EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__MODIFY(reg,
                              incSettings->lsbSubNsInc);
        }
        CPS_UncachedWrite32(&(pD->regs->tsu_timer_incr_sub_nsec), reg);

        reg = 0U;
        EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__MODIFY(reg,
                            incSettings->nanoSecsInc);
        EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__MODIFY(reg,
                            incSettings->altNanoSInc);
        EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__MODIFY(reg,
                            incSettings->altIncCount);
        CPS_UncachedWrite32(&(pD->regs->tsu_timer_incr), reg);

#else
        reg = 0U;
        EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__TIMER__MODIFY(reg,
                                                        incSettings->subNsInc);
        CPS_UncachedWrite32(&(pD->regs->tsu_timer_incr_sub_nsec), reg);

        reg = 0U;
        EMAC_REGS__TSU_TIMER_INCR__COUNT__MODIFY(reg, incSettings->nanoSecsInc);
        EMAC_REGS__TSU_TIMER_INCR__ALT_COUNT__MODIFY(reg,
                            incSettings->altNanoSInc);
        EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__MODIFY(reg, incSettings->altIncCount);
        CPS_UncachedWrite32(&(pD->regs->tsu_timer_incr), reg);
#endif
    }

    return status;
}

uint32_t CEDI_Get1588TimerInc(CEDI_PrivateData *pD, CEDI_TimerIncrement *incSettings)
{
    uint32_t status = CEDI_Get1588TimerIncSF(pD, incSettings);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: get1588TimerInc can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
#ifdef  EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__READ
        reg = CPS_UncachedRead32(&(pD->regs->tsu_timer_incr_sub_nsec));
        incSettings->subNsInc = (uint16_t)
                    EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__READ(reg);
        if (0U != subNsTsuInc24bSupport(pD)) {
            incSettings->lsbSubNsInc = (uint8_t)
                    EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__READ(reg);
        } else {
            incSettings->lsbSubNsInc = 0U;
        }
        reg = CPS_UncachedRead32(&(pD->regs->tsu_timer_incr));
        incSettings->nanoSecsInc =(uint8_t)
                    EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__READ(reg);
        incSettings->altNanoSInc = (uint8_t)
                    EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__READ(reg);
        incSettings->altIncCount = (uint8_t)EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__READ(reg);
#else
        incSettings->subNsInc = (uint16_t)EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_timer_incr_sub_nsec)));
        incSettings->lsbSubNsInc = 0U;
        reg = CPS_UncachedRead32(&(pD->regs->tsu_timer_incr));
        incSettings->nanoSecsInc = EMAC_REGS__TSU_TIMER_INCR__COUNT__READ(reg);
        incSettings->altNanoSInc = EMAC_REGS__TSU_TIMER_INCR__ALT_COUNT__READ(reg);
        incSettings->altIncCount = (uint8_t)EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__READ(reg);
#endif
    }

    return status;
}

uint32_t CEDI_SetTsuTimerCompVal(CEDI_PrivateData *pD,
                                const CEDI_TsuTimerVal *timeVal)
{
    uint32_t status = CEDI_SetTsuTimerCompValSF(pD, timeVal);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = 0U;
        EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__MODIFY(reg, timeVal->secsUpper);
        CPS_UncachedWrite32(&(pD->regs->tsu_msb_sec_cmp), reg);
        reg = 0U;
        EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__MODIFY(reg, timeVal->secsLower);
        CPS_UncachedWrite32(&(pD->regs->tsu_sec_cmp), reg);
        /* tsu_nsec_cmp must be written last */
        reg = 0U;
        EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__MODIFY(reg, timeVal->nanosecs);
        CPS_UncachedWrite32(&(pD->regs->tsu_nsec_cmp), reg);
    }
    return status;
}

uint32_t CEDI_GetTsuTimerCompVal(CEDI_PrivateData *pD, CEDI_TsuTimerVal *timeVal)
{
    uint32_t status = CEDI_GetTsuTimerCompValSF(pD, timeVal);

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        timeVal->nanosecs = EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_nsec_cmp)));
        timeVal->secsLower = EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_sec_cmp)));
        timeVal->secsUpper = (uint16_t)EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_msb_sec_cmp)));
    }
    return status;
}

uint32_t CEDI_GetPtpFrameTxTime(CEDI_PrivateData *pD, CEDI_1588TimerVal *timeVal)
{
    uint32_t status = CEDI_GetPtpFrameTxTimeSF(pD, timeVal);

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        timeVal->nanosecs = EMAC_REGS__TSU_PTP_TX_NSEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_ptp_tx_nsec)));
        timeVal->secsLower = EMAC_REGS__TSU_PTP_TX_SEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_ptp_tx_sec)));
        timeVal->secsUpper = (uint16_t)EMAC_REGS__TSU_PTP_TX_MSB_SEC__TIMER_SECONDS__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_ptp_tx_msb_sec)));
    }
    return status;
}

uint32_t CEDI_GetPtpFrameRxTime(CEDI_PrivateData *pD, CEDI_1588TimerVal *timeVal)
{
    uint32_t status = CEDI_GetPtpFrameRxTimeSF(pD, timeVal);

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        timeVal->nanosecs = EMAC_REGS__TSU_PTP_RX_NSEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_ptp_rx_nsec)));
        timeVal->secsLower = EMAC_REGS__TSU_PTP_RX_SEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_ptp_rx_sec)));
        timeVal->secsUpper = (uint16_t) EMAC_REGS__TSU_PTP_RX_MSB_SEC__TIMER_SECONDS__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_ptp_rx_msb_sec)));
    }
    return status;
}

uint32_t CEDI_GetPtpPeerFrameTxTime(CEDI_PrivateData *pD, CEDI_1588TimerVal *timeVal)
{
    uint32_t status = CEDI_GetPtpPeerFrameTxTimeSF(pD, timeVal);

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        timeVal->nanosecs = EMAC_REGS__TSU_PEER_TX_NSEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_peer_tx_nsec)));
        timeVal->secsLower = EMAC_REGS__TSU_PEER_TX_SEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_peer_tx_sec)));
        timeVal->secsUpper = (uint16_t)EMAC_REGS__TSU_PEER_TX_MSB_SEC__TIMER_SECONDS__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_peer_tx_msb_sec)));
    }
    return status;
}

uint32_t CEDI_GetPtpPeerFrameRxTime(CEDI_PrivateData *pD, CEDI_1588TimerVal *timeVal)
{
    uint32_t status = CEDI_GetPtpPeerFrameRxTimeSF(pD, timeVal);

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        timeVal->nanosecs = EMAC_REGS__TSU_PEER_RX_NSEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_peer_rx_nsec)));
        timeVal->secsLower = EMAC_REGS__TSU_PEER_RX_SEC__TIMER__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_peer_rx_sec)));
        timeVal->secsUpper = (uint16_t)EMAC_REGS__TSU_PEER_RX_MSB_SEC__TIMER_SECONDS__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_peer_rx_msb_sec)));
    }
    return status;
}

uint32_t CEDI_Get1588SyncStrobeTime(CEDI_PrivateData *pD, CEDI_1588TimerVal *timeVal)
{
    uint32_t status = CEDI_Get1588SyncStrobeTimeSF(pD, timeVal);

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        timeVal->nanosecs = EMAC_REGS__TSU_STROBE_NSEC__STROBE__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_strobe_nsec)));
        timeVal->secsLower = EMAC_REGS__TSU_STROBE_SEC__STROBE__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_strobe_sec)));
        timeVal->secsUpper = (uint16_t)
                EMAC_REGS__TSU_STROBE_MSB_SEC__STROBE__READ(
                CPS_UncachedRead32(&(pD->regs->tsu_strobe_msb_sec)));
    }
    return status;
}

uint32_t CEDI_SetExtTsuPortEnable(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetExtTsuPortEnableSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setExtTsuPortEnable can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }
    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.ext_tsu_timer) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }

    return status;
}

uint32_t CEDI_GetExtTsuPortEnable(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetExtTsuPortEnableSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= 0U;
        if (0U==pD->hwCfg.tsu) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getExtTsuPortEnable can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        *enable = (uint8_t) EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__READ(
                CPS_UncachedRead32(&(pD->regs->network_control)));
    }
    return status;
}

uint32_t CEDI_Set1588OneStepTxSyncEnable(CEDI_PrivateData *pD, uint8_t enable)
{

    uint32_t status = CEDI_Set1588OneStepTxSyncEnaSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }

    return status;
}

uint32_t CEDI_Get1588OneStepTxSyncEnable(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_Get1588OneStepTxSyncEnaSF(pD, enable);

    if (CDN_EOK == status){
        *enable = 0U;
        if (0U != pD->hwCfg.tsu)
        {
            *enable = (uint8_t) EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__READ(
                CPS_UncachedRead32(&(pD->regs->network_control)));
        }
    }

    return status;
}

/****************************** Time Stamping *********************************/

/* Check if at least one Rx Queue has BD Extended Mode field enabled. */
static bool atLeastOneRxQHasBDExtModeEnabled(CEDI_PrivateData *pD) {
    bool result = false;
    uint8_t perQueueValuesToCheck = 1U;
    uint8_t q;
    // if qx_control registers available, check all per queue values
    if (pD->hwCfg.gem_vm == true) {
        perQueueValuesToCheck = pD->cfg.rxQs;
    }
    for (q = 0U; q < perQueueValuesToCheck; q++) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s: q%d: rx ts: %d\n", __func__, q, pD->cfg.enRxExtBD[q]);
        if (pD->cfg.enRxExtBD[q] == 1U) {
            result = true;
            break;
        }
    }
    return result;
}

/* Check if at least one Tx Queue has BD Extended Mode field enabled. */
static bool atLeastOneTxQHasBDExtModeEnabled(CEDI_PrivateData *pD) {
    bool result = false;
    uint8_t perQueueValuesToCheck = 1U;
    uint8_t q;
    // if qx_control registers available, check all per queue values
    if (pD->hwCfg.gem_vm == true) {
        perQueueValuesToCheck = pD->cfg.txQs;
    }
    for (q = 0U; q < perQueueValuesToCheck; q++) {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s: q%d: tx ts: %d\n", __func__, q, pD->cfg.enTxExtBD[q]);
        if (pD->cfg.enTxExtBD[q] == 1U) {
            result = true;
            break;
        }
    }
    return result;
}

/* Set the Desc Time Stamp Mode. Applies for all queues if gem_vm is set. */
uint32_t CEDI_SetDescTimeStampMode(CEDI_PrivateData *pD, CEDI_TxTsMode txMode,
        CEDI_RxTsMode rxMode) {
    uint32_t status = CEDI_SetDescTimeStampModeSF(pD, txMode, rxMode);
    uint32_t regData;

    if (CDN_EOK == status) {
        if (((atLeastOneTxQHasBDExtModeEnabled(pD) == false) && (txMode != CEDI_TX_TS_DISABLED))
                || ((atLeastOneRxQHasBDExtModeEnabled(pD) == false) && (rxMode != CEDI_RX_TS_DISABLED))) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s", "ERROR: Time stamping not enabled in DMA config ");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "setting tx mode %d, rx mode %d\n", txMode, rxMode);
        regData = CPS_UncachedRead32(&(pD->regs->tx_bd_control));
        EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__MODIFY(regData, txMode);
        CPS_UncachedWrite32(&(pD->regs->tx_bd_control), regData);

        regData = CPS_UncachedRead32(&(pD->regs->rx_bd_control));
        EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__MODIFY(regData, rxMode);
        CPS_UncachedWrite32(&(pD->regs->rx_bd_control), regData);
    }

    return status;
}

uint32_t CEDI_GetDescTimeStampMode(CEDI_PrivateData *pD, CEDI_TxTsMode* txMode,
                                    CEDI_RxTsMode* rxMode)
{
    uint32_t status = CEDI_GetDescTimeStampModeSF(pD, txMode, rxMode);
    uint32_t regData;
    uint32_t mode;

    if (CDN_EOK == status) {
        if ((atLeastOneRxQHasBDExtModeEnabled(pD) == false)
                && (atLeastOneTxQHasBDExtModeEnabled(pD) == false)) { //former version does not make sense
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        regData = CPS_UncachedRead32(&(pD->regs->tx_bd_control));
        mode = EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__READ(regData);
        *txMode = (CEDI_TxTsMode)mode;
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "getting tx mode %d, \n", mode);

        regData = CPS_UncachedRead32(&(pD->regs->rx_bd_control));
        mode = EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__READ(regData);
        *rxMode = (CEDI_RxTsMode)mode;
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "getting rx mode %d \n", mode);
    }
    return status;
}

uint32_t CEDI_SetStoreRxTimeStamp(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetStoreRxTimeStampSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
    return status;
}

uint32_t CEDI_GetStoreRxTimeStamp(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetStoreRxTimeStampSF(pD, enable);

    if (CDN_EOK == status) {
        *enable = 0U;
        if (0U==pD->hwCfg.tsu) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        *enable = (uint8_t) EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__READ(
                CPS_UncachedRead32(&(pD->regs->network_control)));
    }
    return status;
}

/********************** PCS Control/Auto-negotiation *************************/

uint32_t CEDI_ResetPcs(CEDI_PrivateData *pD)
{
    uint32_t status = CEDI_ResetPcsSF(pD);
    uint32_t reg;

    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s entered (regBase %08X)\n", __func__,
                (uint32_t)pD->cfg.regBase);
        if (0U != pD->hwCfg.no_pcs) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: resetPcs can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pcs_control));
        EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__SET(reg);
        CPS_UncachedWrite32(&(pD->regs->pcs_control), reg);

        pD->basePageExp = 1U;
        pD->autoNegActive = 0U;
    }

    return status;
}

uint32_t CEDI_GetPcsReady(CEDI_PrivateData *pD, uint8_t *ready)
{
    uint32_t status = CEDI_GetPcsReadySF(pD, ready);

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_pcs) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getPcsReady can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        *ready = (0U==EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__READ(
                CPS_UncachedRead32(&(pD->regs->pcs_control))));
    }
    return status;
}

uint32_t CEDI_StartAutoNegotiation(CEDI_PrivateData *pD,
                                  const CEDI_AnAdvPage *advDat)
{
    uint32_t status = CEDI_StartAutoNegotiationSF(pD, advDat);
    uint32_t reg;
    uint32_t event;

    if (CDN_EOK == status) {
        if ((pD->hwCfg.no_pcs) ||
           (EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__READ(
                CPS_UncachedRead32(&(pD->regs->network_config))))) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: startAutoNegotiation can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->autoNegActive) {
            status = CDN_EBUSY;
        }
    }

    //check if we have an event for auto negotiation complete:
    if (CDN_EOK == status) {
        status = CEDI_GetEventEnable(pD, 0, &event);
    }

    if ((CDN_EOK == status) && ((event & (uint32_t)CEDI_EV_PCS_AN_COMPLETE) == 0)) {
        status = CDN_EINVAL;
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pcs_control));
        /* Must not do a read-modify-write with soft reset bit set otherwise
           will cause any writes to be ignored... */
        EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__CLR(reg);
        EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__SET(reg);
        CPS_UncachedWrite32(&(pD->regs->pcs_control), reg);

        status = CEDI_SetAnAdvPage(pD, advDat);
        if (CDN_EOK != status) {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                "CEDI_StartAutoNegotiation: CEDI_SetAnAdvPage "\
                "returned with code: %u\n", status);
        }
    }

    if (CDN_EOK == status) {
        pD->autoNegActive = 1U;
        pD->basePageExp = 1U;

        reg = CPS_UncachedRead32(&(pD->regs->pcs_control));
        /* Must not do a read-modify-write with soft reset bit set otherwise
           will cause any writes to be ignored... */
        EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__CLR(reg);
        EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__SET(reg);
        CPS_UncachedWrite32(&(pD->regs->pcs_control), reg);
    }
    return status;
}

uint32_t CEDI_SetAutoNegEnable(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetAutoNegEnableSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
    uint8_t sgmii;
    reg = CPS_UncachedRead32(&(pD->regs->network_config));
    sgmii = EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__READ(reg);
        if (pD->hwCfg.no_pcs || sgmii) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setAutoNegEnable can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        if (((enable) && pD->autoNegActive) != 0U) {
            status = CDN_EBUSY;
        }
    }

    if (CDN_EOK == status) {
        SetAutoNegEnable(pD, enable);
    }

    return status;
}

uint32_t CEDI_GetAutoNegEnable(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetAutoNegEnableSF(pD, enable);

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_pcs) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getAutoNegEnable can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
    GetAutoNegEnable(pD, enable);
    }
    return status;
}

/* internal utility for reading PCS status & maintaining
 * "read-once" functionality of link status & remote fault
 */
uint32_t readPcsStatus(CEDI_PrivateData *pD) {
    uint32_t reg = CPS_UncachedRead32(&(pD->regs->pcs_status));
    if (0U==EMAC_REGS__PCS_STATUS__LINK_STATUS__READ(reg)) {
        pD->anLinkStat = 0U;
    }
    if (1==EMAC_REGS__PCS_STATUS__REMOTE_FAULT__READ(reg)) {
        pD->anRemFault = 1U;
    }
    return (reg);
}

uint32_t CEDI_GetLinkStatus(CEDI_PrivateData *pD, uint8_t *status)
{
    uint32_t r_status = CDN_EOK;
    uint32_t reg;

    r_status = CEDI_GetLinkStatusSF(pD, status);

    if (0U == r_status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getLinkStatus can not be called for express MAC.");
                r_status = CDN_EINVAL;
            }
        }
    }

    if (0U == r_status) {
        reg = readPcsStatus(pD);
        /* return low if this has not been done yet */
        *status = pD->anLinkStat;

        pD->anLinkStat = (uint8_t)
                EMAC_REGS__PCS_STATUS__LINK_STATUS__READ(reg);
    }

    return (r_status);
}

uint32_t CEDI_GetAnRemoteFault(CEDI_PrivateData *pD, uint8_t *status)
{
    uint32_t r_status = CDN_EOK;
    uint32_t reg;

    r_status = CEDI_GetAnRemoteFaultSF(pD, status);

    if (0U == r_status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getAnRemoteFault can not be called for express MAC.");
                r_status = CDN_EINVAL;
            }
        }
    }

    if (0U == r_status) {
        reg = readPcsStatus(pD);
        /* return high if this has not been done yet */
        *status = pD->anRemFault;

        pD->anRemFault =(uint8_t)
                EMAC_REGS__PCS_STATUS__REMOTE_FAULT__READ(reg);
    }

    return (r_status);
}

uint32_t CEDI_GetAnComplete(CEDI_PrivateData *pD, uint8_t *status)
{
    uint32_t r_status = CDN_EOK;

    r_status = CEDI_GetAnCompleteSF(pD, status);

    if (0U == r_status) {
        if (0U != pD->hwCfg.no_pcs) {
            r_status = CDN_ENOTSUP;
        }
    }

    if (0U == r_status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getAnComplete can not be called for express MAC.");
                r_status = CDN_EINVAL;
            }
        }
    }

    if (0U == r_status) {
        *status = (uint8_t)EMAC_REGS__PCS_STATUS__AUTO_NEG_COMPLETE__READ(readPcsStatus(pD));
    }

    return (r_status);
}

uint32_t CEDI_SetAnAdvPage(CEDI_PrivateData *pD, const CEDI_AnAdvPage *advDat)
{
    uint32_t status = CEDI_SetAnAdvPageSF(pD, advDat);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_pcs) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setAnAdvPage can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = 0U;
        if (0U != advDat->fullDuplex) {
            EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__SET(reg);
        }
        if (0U != advDat->halfDuplex) {
            EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__SET(reg);
        }
        EMAC_REGS__PCS_AN_ADV__PAUSE__MODIFY(reg, advDat->pauseCap);
        EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__MODIFY(reg, advDat->remFlt);
        if (0U != advDat->nextPage) {
            EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__SET(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->pcs_an_adv), reg);
    }

    return status;
}

uint32_t CEDI_GetAnAdvPage(CEDI_PrivateData *pD, CEDI_AnAdvPage *advDat)
{
    uint32_t status = CEDI_GetAnAdvPageSF(pD, advDat);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_pcs) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getAnAdvPage can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pcs_an_adv));
        advDat->fullDuplex = (uint8_t)EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__READ(reg);
        advDat->halfDuplex = (uint8_t)EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__READ(reg);
        advDat->pauseCap = EMAC_REGS__PCS_AN_ADV__PAUSE__READ(reg);
        advDat->remFlt = EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__READ(reg);
        advDat->nextPage = (uint8_t)EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__READ(reg);
    }

    return status;
}

uint32_t CEDI_GetLpAbilityPage(CEDI_PrivateData *pD, CEDI_LpAbilityPage *lpAbl)
{
    uint32_t status = CEDI_GetLpAbilityPageSF(pD, lpAbl);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_pcs) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getLpAbilityPage can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pcs_an_lp_base));

        if (0U != EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__READ(
                CPS_UncachedRead32(&(pD->regs->network_config))))
        {
            /* SGMII mode format */
            lpAbl->sgmii = 1U;
            lpAbl->ablInfo.sgmLpAbl.speed =
                    EMAC_REGS__PCS_AN_LP_BASE__SPEED_RESERVED__READ(reg)>>1;
            lpAbl->ablInfo.sgmLpAbl.lpAck = (uint8_t)
                    (EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__READ(reg));
            lpAbl->ablInfo.sgmLpAbl.linkStatus =(uint8_t)
                    (EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__READ(reg));
            lpAbl->ablInfo.sgmLpAbl.duplex =(uint8_t)
                    (EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_REMOTE_FAULT_DUPLEX_MODE__READ(reg));
        }
        else
        {
            /* Default format */
            lpAbl->sgmii = 0U;
            lpAbl->ablInfo.defLpAbl.fullDuplex = (uint8_t)
                    EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_FULL_DUPLEX__READ(reg);
            lpAbl->ablInfo.defLpAbl.halfDuplex = (uint8_t)
                    EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_HALF_DUPLEX__READ(reg);
            lpAbl->ablInfo.defLpAbl.pauseCap =
                    EMAC_REGS__PCS_AN_LP_BASE__PAUSE__READ(reg);
            lpAbl->ablInfo.defLpAbl.lpAck = (uint8_t)
                    EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__READ(reg);
            lpAbl->ablInfo.defLpAbl.remFlt =(uint8_t)
                    EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_REMOTE_FAULT_DUPLEX_MODE__READ(reg);
            lpAbl->ablInfo.defLpAbl.lpNextPage =(uint8_t)
                    EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__READ(reg);
        }
    }

    return status;
}

uint32_t CEDI_GetPageRx(CEDI_PrivateData *pD)
{
    uint32_t retVal = 0U;
    uint32_t status = CEDI_GetPageRxSF(pD);

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_pcs) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getPageRx can not be called for express MAC.");
                status = CDN_ENOTSUP;
            }
        }
    }

    if (CDN_EOK == status) {
        retVal = (EMAC_REGS__PCS_AN_EXP__PAGE_RECEIVED__READ(
                  CPS_UncachedRead32(&(pD->regs->pcs_an_exp))));
    }

    return retVal;
}

uint32_t CEDI_SetNextPageTx(CEDI_PrivateData *pD, const CEDI_AnNextPage *npDat)
{
    uint32_t status = CEDI_SetNextPageTxSF(pD, npDat);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_pcs) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setNextPageTx can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = 0U;
        EMAC_REGS__PCS_AN_NP_TX__MESSAGE__MODIFY(reg, npDat->message);
        if (0U != npDat->ack2) {
            EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__SET(reg);
        }
        if (0U != npDat->msgPage) {
            EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__SET(reg);
        }
        if (0U != npDat->np) {
            EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__SET(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->pcs_an_np_tx), reg);
    }

    return status;
}

uint32_t CEDI_GetNextPageTx(CEDI_PrivateData *pD, CEDI_AnNextPage *npDat)
{
    uint32_t status = CEDI_GetNextPageTxSF(pD, npDat);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getNextPageTx can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pcs_an_np_tx));
        npDat->message = (uint16_t)EMAC_REGS__PCS_AN_NP_TX__MESSAGE__READ(reg);
        npDat->ack2 = (uint8_t)EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__READ(reg);
        npDat->msgPage = (uint8_t)EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__READ(reg);
        npDat->np = (uint8_t)EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__READ(reg);
    }

    return status;
}

uint32_t CEDI_GetLpNextPage(CEDI_PrivateData *pD, CEDI_LpNextPage *npDat)
{
    uint32_t status = CEDI_GetLpNextPageSF(pD, npDat);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getLpNextPage can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pcs_an_lp_np));
        npDat->message = (uint16_t) EMAC_REGS__PCS_AN_LP_NP__MESSAGE__READ(reg);
        npDat->toggle = (uint8_t) EMAC_REGS__PCS_AN_LP_NP__TOGGLE__READ(reg);
        npDat->ack2 = (uint8_t) EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE_2__READ(reg);
        npDat->msgPage = (uint8_t) EMAC_REGS__PCS_AN_LP_NP__MESSAGE_PAGE_INDICATOR__READ(reg);
        npDat->ack = (uint8_t) EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE__READ(reg);
        npDat->np = (uint8_t) EMAC_REGS__PCS_AN_LP_NP__NEXT_PAGE_TO_RECEIVE__READ(reg);
    }

    return status;
}

/**************************** PHY Management *********************************/

uint32_t CEDI_GetPhyId(CEDI_PrivateData *pD, uint32_t *phyId)
{
    uint32_t status = CEDI_GetPhyIdSF(pD, phyId);
    uint32_t reg, retVal;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getPhyId can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        if(0U != pD->hwCfg.phy_ident) {
            reg = CPS_UncachedRead32(&(pD->regs->pcs_phy_top_id));
            retVal = EMAC_REGS__PCS_PHY_TOP_ID__ID_CODE__READ(reg)<<16U;
            reg = CPS_UncachedRead32(&(pD->regs->pcs_phy_bot_id));
            retVal |= EMAC_REGS__PCS_PHY_BOT_ID__ID_CODE__READ(reg);
            *phyId= retVal;
        } else {
            status = CDN_ENOTSUP;
        }
    }

    return status;
}

uint32_t CEDI_SetMdioEnable(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetMdioEnableSF(pD, enable);
    uint32_t ncr;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setMdioEnable can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }
    if (CDN_EOK == status) {
        ncr = CPS_UncachedRead32(&(pD->regs->network_control));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__SET(ncr);
        } else {
            EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__CLR(ncr);
        }
        CPS_UncachedWrite32(&(pD->regs->network_control), ncr);
    }
    return status;
}

uint32_t CEDI_GetMdioEnable(CEDI_PrivateData *pD)
{
    uint32_t retVal = 0U;
    uint32_t status = CEDI_GetMdioEnableSF(pD);

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getMdioEnable can not be called for express MAC.");
                status = CDN_ENOTSUP;
            }
        }
    }
    if (CDN_EOK == status) {
        retVal = (EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__READ(
                CPS_UncachedRead32(&(pD->regs->network_control))));
    }

    return retVal;
}

/* Initiate a write or set address operation on the MDIO interface.
 * Clause 45 devices require a call to set the register address (if
 * this is changing since last access), and then a write or read
 * operation.
 * The command writes to the shift register, which starts output on
 * the MDIO interface. Write completion is signalled by the
 * phyManComplete callback, or by polling getMdioIdle.
 * @param pD - driver private state info specific to this instance
 * @param flags - combination of 2 bit-flags:
 *        if CEDI_MDIO_FLG_CLAUSE_45 present, specifies clause 45 PHY
 *        (else clause 22).
 *        if CEDI_MDIO_FLG_SET_ADDR present, specifies a set address operation
 *        (else do a write operation)  Ignored if not clause 45.
 * @param phyAddr - PHY address
 * @param devReg - device type (clause 45) or register address (clause 22)
 *           - enum CEDI_MdioDevType is available to specify the device type
 * @param addrData - register address (if CEDI_MDIO_FLG_SET_ADDR) or data to write
 */
uint32_t CEDI_PhyStartMdioWrite(CEDI_PrivateData *pD, uint8_t flags, uint8_t phyAddr,
        uint8_t devReg, uint16_t addrData)
{
    uint32_t status = CEDI_PhyStartMdioWriteSF(pD, flags, phyAddr, devReg);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: phyStartMdioWrite can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }
    if (CDN_EOK == status) {
        reg = 0U;
        EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__MODIFY(reg, addrData);
        EMAC_REGS__PHY_MANAGEMENT__WRITE10__MODIFY(reg, 2U);
        EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__MODIFY(reg, devReg);
        EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__MODIFY(reg, phyAddr);
        if ((flags & CEDI_MDIO_FLG_CLAUSE_45) && (flags & CEDI_MDIO_FLG_SET_ADDR)) {
            EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(reg, CEDI_PHY_ADDR_OP);
        } else {
            EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(reg, CEDI_PHY_WRITE_OP);
        }
        if ((flags & CEDI_MDIO_FLG_CLAUSE_45)==0U) {
            EMAC_REGS__PHY_MANAGEMENT__WRITE1__SET(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->phy_management), reg);
    }
    return status;
}

/* Initiate a read operation on the MDIO interface.  If clause 45, the
 * register address will need to be set by a preceding phyStartMdioWrite
 * call, unless same as for last operation. Completion is signalled by the
 * phyManComplete callback, which will return the read data by a pointer
 * parameter. Alternatively polling getMdioIdle will indicate when
 * the operation completes, then getMdioReadDat will return the data.
 * @param pD - driver private state info specific to this instance
 * @param flags - combination of 2 bit-flags:
 *        if CEDI_MDIO_FLG_CLAUSE_45 present, specifies clause 45 PHY
 *        (else clause 22).
 *        if CEDI_MDIO_FLG_INC_ADDR present, and clause 45, then address will
 *        be incremented after the read operation.
 * @param phyAddr - PHY address
 * @param devReg - device type (clause 45) or register address (clause 22)
 *           - enum CEDI_MdioDevType is available to specify the device type
 */
uint32_t CEDI_PhyStartMdioRead(CEDI_PrivateData *pD, uint8_t flags, uint8_t phyAddr,
        uint8_t devReg)
{
    uint32_t status = CEDI_PhyStartMdioReadSF(pD, flags, phyAddr, devReg);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: phyStartMdioRead can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }
    if (CDN_EOK == status) {
        reg = 0U;
        EMAC_REGS__PHY_MANAGEMENT__WRITE10__MODIFY(reg, 2U);
        EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__MODIFY(reg, devReg);
        EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__MODIFY(reg, phyAddr);
        if (0U != (flags & CEDI_MDIO_FLG_CLAUSE_45)) {
            if (0U != (flags & CEDI_MDIO_FLG_INC_ADDR)) {
                EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(reg,
                        CEDI_PHY_CL45_READ_INC_OP);
            }
            else {
                EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(reg,
                        CEDI_PHY_CL45_READ_OP);
            }
        } else {
            EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(reg, CEDI_PHY_CL22_READ_OP);
        }
        if ((flags & CEDI_MDIO_FLG_CLAUSE_45)==0U) {
            EMAC_REGS__PHY_MANAGEMENT__WRITE1__SET(reg);
        }

        CPS_UncachedWrite32(&(pD->regs->phy_management), reg);
    }
    return status;
}

uint32_t CEDI_GetMdioReadData(CEDI_PrivateData *pD, uint16_t *readData)
{
    uint32_t status = CEDI_GetMdioReadDataSF(pD, readData);

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getMdioReadData can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }
    if (CDN_EOK == status) {
        *readData = (uint16_t) EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__READ(
                CPS_UncachedRead32(&(pD->regs->phy_management)));
    }

    return status;
}

uint32_t CEDI_GetMdioIdle(CEDI_PrivateData *pD)
{
    uint32_t retVal = 1U;
    uint32_t status = CEDI_GetMdioIdleSF(pD);

    if (CDN_EOK != status) {
        retVal = 0U;
    }
    if (retVal == 1U) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getMdioIdle can not be called for express MAC.");
                retVal = 0U;
            }
        }
    }
    if (1U == retVal) {
        retVal = (EMAC_REGS__NETWORK_STATUS__MAN_DONE__READ(
                  CPS_UncachedRead32(&(pD->regs->network_status))));
    }
    return retVal;
}

/************************* Statistics Registers ******************************/

uint32_t CEDI_ReadStats(CEDI_PrivateData *pD)
{
    uint32_t status = CEDI_ReadStatsSF(pD);
    CEDI_Statistics *stats;

    if (CDN_EOK == status) {
        stats = ((CEDI_Statistics *)(pD->cfg.statsRegs));

        if (0U != pD->hwCfg.no_stats) {
           status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        stats->octetsTxLo = CPS_UncachedRead32(&(pD->regs->octets_txed_bottom));
        stats->octetsTxHi = (uint16_t) EMAC_REGS__OCTETS_TXED_TOP__COUNT__READ(
                             CPS_UncachedRead32(&(pD->regs->octets_txed_top)));
        stats->framesTx = CPS_UncachedRead32(&(pD->regs->frames_txed_ok));
        stats->broadcastTx = CPS_UncachedRead32(&(pD->regs->broadcast_txed));
        stats->multicastTx = CPS_UncachedRead32(&(pD->regs->multicast_txed));
        stats->pauseFrTx = (uint16_t)EMAC_REGS__PAUSE_FRAMES_TXED__COUNT__READ(
                            CPS_UncachedRead32(&(pD->regs->pause_frames_txed)));
        stats->fr64byteTx = CPS_UncachedRead32(&(pD->regs->frames_txed_64));
        stats->fr65_127byteTx = CPS_UncachedRead32(&(pD->regs->frames_txed_65));
        stats->fr128_255byteTx = CPS_UncachedRead32(&(pD->regs->frames_txed_128));
        stats->fr256_511byteTx = CPS_UncachedRead32(&(pD->regs->frames_txed_256));
        stats->fr512_1023byteTx = CPS_UncachedRead32(&(pD->regs->frames_txed_512));
        stats->fr1024_1518byteTx =
                                CPS_UncachedRead32(&(pD->regs->frames_txed_1024));
        stats->fr1519_byteTx = CPS_UncachedRead32(&(pD->regs->frames_txed_1519));
            stats->underrunFrTx = (uint16_t)EMAC_REGS__TX_UNDERRUNS__COUNT__READ(
                                CPS_UncachedRead32(&(pD->regs->tx_underruns)));
        stats->singleCollFrTx =
                            CPS_UncachedRead32(&(pD->regs->single_collisions));
        stats->multiCollFrTx =
                            CPS_UncachedRead32(&(pD->regs->multiple_collisions));
        stats->excessCollFrTx = (uint16_t)EMAC_REGS__EXCESSIVE_COLLISIONS__COUNT__READ(
                           CPS_UncachedRead32(&(pD->regs->excessive_collisions)));
        stats->lateCollFrTx = (uint16_t)EMAC_REGS__LATE_COLLISIONS__COUNT__READ(
                                CPS_UncachedRead32(&(pD->regs->late_collisions)));
        stats->carrSensErrsTx = (uint16_t)EMAC_REGS__CRS_ERRORS__COUNT__READ(
                                  CPS_UncachedRead32(&(pD->regs->crs_errors)));
        stats->deferredFrTx = CPS_UncachedRead32(&(pD->regs->deferred_frames));
        stats->alignErrsRx = (uint16_t)EMAC_REGS__ALIGNMENT_ERRORS__COUNT__READ(
                            CPS_UncachedRead32(&(pD->regs->alignment_errors)));
            stats->octetsRxLo = CPS_UncachedRead32(&(pD->regs->octets_rxed_bottom));
        stats->octetsRxHi = (uint16_t)EMAC_REGS__OCTETS_RXED_TOP__COUNT__READ(
                              CPS_UncachedRead32(&(pD->regs->octets_rxed_top)));
        stats->framesRx = CPS_UncachedRead32(&(pD->regs->frames_rxed_ok));
        stats->broadcastRx = CPS_UncachedRead32(&(pD->regs->broadcast_rxed));
        stats->multicastRx = CPS_UncachedRead32(&(pD->regs->multicast_rxed));
        stats->pauseFrRx = (uint16_t)EMAC_REGS__PAUSE_FRAMES_RXED__COUNT__READ(
                            CPS_UncachedRead32(&(pD->regs->pause_frames_rxed)));
        stats->fr64byteRx = CPS_UncachedRead32(&(pD->regs->frames_rxed_64));
        stats->fr65_127byteRx = CPS_UncachedRead32(&(pD->regs->frames_rxed_65));
        stats->fr128_255byteRx = CPS_UncachedRead32(&(pD->regs->frames_rxed_128));
        stats->fr256_511byteRx = CPS_UncachedRead32(&(pD->regs->frames_rxed_256));
        stats->fr512_1023byteRx =
                                CPS_UncachedRead32(&(pD->regs->frames_rxed_512));
        stats->fr1024_1518byteRx =
                                CPS_UncachedRead32(&(pD->regs->frames_rxed_1024));
        stats->fr1519_byteRx =
                                CPS_UncachedRead32(&(pD->regs->frames_rxed_1519));
        stats->undersizeFrRx = (uint16_t)EMAC_REGS__UNDERSIZE_FRAMES__COUNT__READ(
                              CPS_UncachedRead32(&(pD->regs->undersize_frames)));
        stats->oversizeFrRx = (uint16_t)EMAC_REGS__EXCESSIVE_RX_LENGTH__COUNT__READ(
                        CPS_UncachedRead32(&(pD->regs->excessive_rx_length)));
        stats->jabbersRx = (uint16_t)EMAC_REGS__RX_JABBERS__COUNT__READ(
                                CPS_UncachedRead32(&(pD->regs->rx_jabbers)));
        stats->fcsErrorsRx = (uint16_t)EMAC_REGS__FCS_ERRORS__COUNT__READ(
                                CPS_UncachedRead32(&(pD->regs->fcs_errors)));
        stats->lenChkErrRx = (uint16_t)EMAC_REGS__RX_LENGTH_ERRORS__COUNT__READ(
                              CPS_UncachedRead32(&(pD->regs->rx_length_errors)));
        stats->rxSymbolErrs = (uint16_t)EMAC_REGS__RX_SYMBOL_ERRORS__COUNT__READ(
                            CPS_UncachedRead32(&(pD->regs->rx_symbol_errors)));
        stats->rxResourcErrs =
                            CPS_UncachedRead32(&(pD->regs->rx_resource_errors));
        stats->overrunFrRx = (uint16_t)EMAC_REGS__RX_OVERRUNS__COUNT__READ(
                                CPS_UncachedRead32(&(pD->regs->rx_overruns)));
        stats->ipChksumErrs = (uint16_t)EMAC_REGS__RX_IP_CK_ERRORS__COUNT__READ(
                            CPS_UncachedRead32(&(pD->regs->rx_ip_ck_errors)));
        stats->tcpChksumErrs = (uint16_t)EMAC_REGS__RX_TCP_CK_ERRORS__COUNT__READ(
                            CPS_UncachedRead32(&(pD->regs->rx_tcp_ck_errors)));
        stats->udpChksumErrs = (uint16_t)EMAC_REGS__RX_UDP_CK_ERRORS__COUNT__READ(
                            CPS_UncachedRead32(&(pD->regs->rx_udp_ck_errors)));
        stats->dmaRxPBufFlush = (uint16_t)EMAC_REGS__AUTO_FLUSHED_PKTS__COUNT__READ(
                            CPS_UncachedRead32(&(pD->regs->auto_flushed_pkts)));
    }
    return status;
}

uint32_t CEDI_ClearStats(const CEDI_PrivateData *pD)
{
    uint32_t status = CEDI_ClearStatsSF(pD);
    uint32_t reg;
    volatile uint32_t* regAddr;

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_stats) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->network_control);
        reg = CPS_REG_READ(regAddr);
        EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__SET(reg);
        CPS_REG_WRITE(regAddr, reg);
    }

    return status;
}

uint32_t CEDI_TakeSnapshot(CEDI_PrivateData *pD)
{
    uint32_t status = CEDI_TakeSnapshotSF(pD);
    uint32_t reg;

    if (CDN_EOK == status) {
        if ((pD->hwCfg.no_snapshot != 0U) || (pD->hwCfg.no_stats != 0U)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__SET(reg);
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
    return status;
}

uint32_t CEDI_SetReadSnapshot(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetReadSnapshotSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        if ((pD->hwCfg.no_snapshot != 0U) || (pD->hwCfg.no_stats != 0U)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
    return status;
}

uint32_t CEDI_GetReadSnapshot(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetReadSnapshotSF(pD, enable);

    if (CDN_EOK == status) {
        if (pD->hwCfg.no_snapshot || pD->hwCfg.no_stats) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        *enable = (uint8_t)EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__READ(
                CPS_UncachedRead32(&(pD->regs->network_control)));
    }
    return status;
}

/************************ WakeOnLAN/EEE Support ******************************/

uint32_t CEDI_SetWakeOnLanReg(CEDI_PrivateData *pD, const CEDI_WakeOnLanReg *regVals)
{
    uint32_t status = CEDI_SetWakeOnLanRegSF(pD, regVals);
    uint32_t reg = 0U;

    if (CDN_EOK == status) {
        EMAC_REGS__WOL_REGISTER__ADDR__MODIFY(reg, regVals->wolReqAddr);
        if (0U != regVals->magPktEn) {
            EMAC_REGS__WOL_REGISTER__WOL_MASK_0__SET(reg);
        }
        if (0U != regVals->arpEn) {
            EMAC_REGS__WOL_REGISTER__WOL_MASK_1__SET(reg);
        }
        if (0U != regVals->specAd1En) {
            EMAC_REGS__WOL_REGISTER__WOL_MASK_2__SET(reg);
        }
        if (0U != regVals->multiHashEn) {
            EMAC_REGS__WOL_REGISTER__WOL_MASK_3__SET(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->wol_register), reg);
    }

    return status;
}

uint32_t CEDI_GetWakeOnLanReg(CEDI_PrivateData *pD, CEDI_WakeOnLanReg *regVals)
{
    uint32_t status = CEDI_GetWakeOnLanRegSF(pD, regVals);
    uint32_t reg = 0U;

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->wol_register));
        regVals->wolReqAddr = (uint16_t) EMAC_REGS__WOL_REGISTER__ADDR__READ(reg);
        regVals->magPktEn = (uint8_t) EMAC_REGS__WOL_REGISTER__WOL_MASK_0__READ(reg);
        regVals->arpEn = (uint8_t) EMAC_REGS__WOL_REGISTER__WOL_MASK_1__READ(reg);
        regVals->specAd1En = (uint8_t) EMAC_REGS__WOL_REGISTER__WOL_MASK_2__READ(reg);
        regVals->multiHashEn = (uint8_t) EMAC_REGS__WOL_REGISTER__WOL_MASK_3__READ(reg);
    }
    return status;
}

uint32_t CEDI_SetLpiTxEnable(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetLpiTxEnableSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
    return status;
}

uint32_t CEDI_GetLpiTxEnable(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetLpiTxEnableSF(pD, enable);
    if (CDN_EOK == status) {
        *enable = (uint8_t)EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__READ(
                CPS_UncachedRead32(&(pD->regs->network_control)));
    }
    return status;
}

uint32_t CEDI_GetLpiStats(CEDI_PrivateData *pD, CEDI_LpiStats *lpiStats)
{
    uint32_t status = CEDI_GetLpiStatsSF(pD, lpiStats);

    if (CDN_EOK == status) {
        lpiStats->rxLpiTrans = (uint16_t)EMAC_REGS__RX_LPI__COUNT__READ(
                CPS_UncachedRead32(&(pD->regs->rx_lpi)));
        lpiStats->rxLpiTime = EMAC_REGS__RX_LPI_TIME__LPI_TIME__READ(
                CPS_UncachedRead32(&(pD->regs->rx_lpi_time)));
        lpiStats->txLpiTrans = (uint16_t)EMAC_REGS__TX_LPI__COUNT__READ(
                CPS_UncachedRead32(&(pD->regs->tx_lpi)));
        lpiStats->txLpiTime = EMAC_REGS__TX_LPI_TIME__LPI_TIME__READ(
                CPS_UncachedRead32(&(pD->regs->tx_lpi_time)));
    }
    return status;
}

/**************************** Design Config **********************************/

uint32_t CEDI_GetDesignConfig(const CEDI_PrivateData *pD, CEDI_DesignCfg *hwCfg)
{
    uint32_t status = CEDI_GetDesignConfigSF(pD, hwCfg);

    if (CDN_EOK == status) {
        /* Copy h/w config into user-supplied struct */
        *hwCfg = pD->hwCfg;
    }
    return status;
}

/**************************** Debug Functionality ****************************/

uint32_t CEDI_SetWriteStatsEnable(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetWriteStatsEnableSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_stats) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
    return status;
}

uint32_t CEDI_GetWriteStatsEnable(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetWriteStatsEnableSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_stats) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        *enable = (uint8_t)EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__READ(reg);
    }
    return status;
}

uint32_t CEDI_IncStatsRegs(CEDI_PrivateData *pD)
{
    uint32_t status = CEDI_IncStatsRegsSF(pD);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_stats) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__SET(reg);
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
    return status;
}

void CEDI_SetRxBackPressure(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t ncr;
    uint32_t status = CEDI_SetRxBackPressureSF(pD, enable);

    if (CDN_EOK == status) {
        ncr = CPS_UncachedRead32(&(pD->regs->network_control));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__SET(ncr);
        } else {
            EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__CLR(ncr);
        }
        CPS_UncachedWrite32(&(pD->regs->network_control), ncr);
    }
}

uint32_t CEDI_GetRxBackPressure(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetRxBackPressureSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= (uint8_t)(EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__READ(
                CPS_UncachedRead32(&(pD->regs->network_control))));
    }

    return status;
}

uint32_t CEDI_SetCollisionTest(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetCollisionTestSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U != pD->hwCfg.no_pcs) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setCollisionTest can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }
    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pcs_control));
        // Must not do a read-modify-write with soft reset bit set otherwise
        // will cause any writes to be ignored...
        EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__CLR(reg);
        if (0U != enable) {
            EMAC_REGS__PCS_CONTROL__COLLISION_TEST__SET(reg);
        } else {
            EMAC_REGS__PCS_CONTROL__COLLISION_TEST__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->pcs_control), reg);
    }
    return status;
}

uint32_t CEDI_GetCollisionTest(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetCollisionTestSF(pD, enable);
    uint32_t reg;

    if (CDN_EOK == status) {
        if ((pD->hwCfg.no_pcs != 0U) || (enable==NULL)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getCollisionTest can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }
    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pcs_control));
        *enable = (uint8_t)(EMAC_REGS__PCS_CONTROL__COLLISION_TEST__READ(reg));
    }
    return status;
}

void CEDI_SetRetryTest(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetRetryTestSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0U != enable) {
            EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetRetryTest(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetRetryTestSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= (uint8_t) (EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__READ(
                CPS_UncachedRead32(&(pD->regs->network_config))));
    }

    return status;
}

uint32_t CEDI_WriteUserOutputs(CEDI_PrivateData *pD, uint16_t outVal)
{
    uint32_t status = CEDI_WriteUserOutputsSF(pD);
    uint32_t tmp;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.user_io) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: writeUserOutputs can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        tmp = 0U;
        EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__MODIFY(
                tmp, outVal);
        CPS_UncachedWrite32(&(pD->regs->user_io_register), tmp);
    }
    return status;
}

uint32_t CEDI_ReadUserOutputs(CEDI_PrivateData *pD, uint16_t *outVal)
{
    uint32_t status = CEDI_ReadUserOutputsSF(pD, outVal);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.user_io) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: readUserOutputs can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->user_io_register));
        *outVal = (uint16_t) EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__READ(reg);
    }
    return status;
}

uint32_t CEDI_SetUserOutPin(CEDI_PrivateData *pD, uint8_t pin, uint8_t state)
{
    uint32_t status = CEDI_SetUserOutPinSF(pD, state);
    uint32_t reg, val;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.user_io) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (pin>=pD->hwCfg.user_out_width) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setUserOutPin can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->user_io_register));
        val = EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__READ(reg);
        if(pin < 32U) {
            if (0U != state) {
                val |= (1U<<pin);
            }
            else {
                val &= ~(1U<<pin);
            }
        }
        EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__MODIFY(
                reg, val);
        CPS_UncachedWrite32(&(pD->regs->user_io_register), reg);
    }
    return status;
}

uint32_t CEDI_ReadUserInputs(CEDI_PrivateData *pD, uint16_t *inVal)
{
    uint32_t status = CEDI_ReadUserInputsSF(pD, inVal);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.user_io) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: readUserInputs can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->user_io_register));
        *inVal =(uint16_t)(EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_INPUTS__READ(reg));
    }
    return status;
}

uint32_t CEDI_GetUserInPin(CEDI_PrivateData *pD, uint8_t pin, uint8_t *state)
{
    uint32_t status = CEDI_GetUserInPinSF(pD, state);
    uint32_t reg, val;

    if (CDN_EOK == status) {
        if (0U==pD->hwCfg.user_io) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if (pin>=pD->hwCfg.user_in_width) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->user_io_register));
        val = EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_INPUTS__READ(reg);
        if (pin < 32) {
            *state = (0U != (val & (1U<<pin)))?1U:0U;
        } else {
            status = CDN_EINVAL;
        }
    }

    return status;
}


/* enable/disable reporting bad FCS inside RX descriptor  */
uint32_t CEDI_SetReportingBadFCS(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetReportingBadFCSSF(pD, enable);
    uint32_t regTmp;

#ifdef EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__READ
    if (CDN_EOK == status) {
        if (0U == IsGem1p09(pD)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        regTmp = CPS_UncachedRead32(&(pD->regs->dma_config));
        EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__MODIFY(regTmp, enable);
        CPS_UncachedWrite32(&(pD->regs->dma_config), regTmp);
    }

#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif
    return status;
}

/* get state(enabled/disabled) of reporting bad FCS inside RX descriptor  */
uint32_t CEDI_GetReportingBadFCS(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetReportingBadFCSSF(pD, enable);
    uint32_t regTmp;

#ifdef EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__READ
    if (CDN_EOK == status) {
        if (0U == IsGem1p09(pD)) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        regTmp = CPS_UncachedRead32(&(pD->regs->dma_config));
        *enable = (uint8_t) (EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__READ(regTmp));
    }
#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif
    return status;
}

/* enable/disable single step update correction field of PTP protocol  */
uint32_t CEDI_SetPtpSingleStep(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetPtpSingleStepSF(pD, enable);
    uint32_t regTmp;

#ifdef EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__MODIFY
    if (CDN_EOK == status) {
        if (0U == IsGem1p09(pD)) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        regTmp = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__MODIFY(regTmp, enable);
        CPS_UncachedWrite32(&(pD->regs->network_control), regTmp);
    }
#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif
    return status;
}

/* get state (enable/disable) of single step update
 * correction field of PTP protocol  */
uint32_t CEDI_GetPtpSingleStep(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetPtpSingleStepSF(pD, enable);
    uint32_t regTmp;

#ifdef EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__MODIFY
    if (CDN_EOK == status) {
        if (0U == IsGem1p09(pD)) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        regTmp = CPS_UncachedRead32(&(pD->regs->network_control));
        *enable = (uint8_t)EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__READ(regTmp);
    }
#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif
    return status;
}

/* enable/disable feature alowing execution MII operation on RGMII interface */
uint32_t CEDI_SetMiiOnRgmii(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status = CEDI_SetMiiOnRgmiiSF(pD, enable);
    uint32_t regTmp;

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: setMiiOnRgmii can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

#ifdef EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__MODIFY
    if (CDN_EOK == status) {
        if (0U == IsGem1p09(pD)) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        regTmp = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__MODIFY(regTmp, enable);
        CPS_UncachedWrite32(&(pD->regs->network_control), regTmp);
    }
#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif
    return status;
}

/* get state (enabled/disabled) feature alowing
 * execution MII operation on RGMII interface  */
uint32_t CEDI_GetMiiOnRgmii(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetMiiOnRgmiiSF(pD, enable);
    uint32_t regTmp;

#ifdef EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__MODIFY
    if (CDN_EOK == status) {
        if (0U == IsGem1p09(pD)) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        regTmp = CPS_UncachedRead32(&(pD->regs->network_control));
    *enable = (uint8_t)EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__READ(regTmp);
    }
#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif
    return status;
}

uint32_t CEDI_GetLinkFaultIndication(CEDI_PrivateData *pD, CEDI_LinkFaultIndication *linkFault)
{
    uint32_t status = CEDI_GetLinkFaultIndicationSF(pD, linkFault);
    uint32_t networkStatusReg;
    uint32_t linkFaultStatus;

    if (CDN_EOK == status) {
        if (0U == IsGem1p12(pD)) {
            status = (uint32_t)CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status)
    {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType) {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                    "Error: getLinkFaultIndication can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }

    if (CDN_EOK == status) {
        networkStatusReg = CPS_UncachedRead32(&(pD->regs->network_status));
        linkFaultStatus = EMAC_REGS__NETWORK_STATUS__LINK_FAULT_INDICATION__READ(networkStatusReg);

        switch (linkFaultStatus){
        case 0U:
            *linkFault = CEDI_LINK_FAULT_INDICATION_OK;
        break;
        case 1U:
            *linkFault = CEDI_LINK_FAULT_INDICATION_LOCAL_FAULT;
        break;
        case 2U:
            *linkFault = CEDI_LINK_FAULT_INDICATION_REMOTE_FAULT;
        break;
        case 3U:
            *linkFault = CEDI_LINK_FAULT_INDICATION_LINK_INTERRUPTION;
        break;
        default:
            // default
        break;
        }
    }

    return status;
}

uint32_t CEDI_SetFrameEliminationTagSize(CEDI_PrivateData *pD, CEDI_RedundancyTagSize tagSize)
{
    uint32_t status = CEDI_SetFrameEliminationTagSSF(pD, tagSize);
    uint32_t frerReg;

    if (CDN_EOK == status) {
        if (0U == IsGem1p12(pD)) {
            status = ((uint8_t)tagSize == (uint8_t)CEDI_REDUNDANCY_TAG_SIZE_4) ? 0U : (uint32_t)CDN_ENOTSUP;
        } else {
            frerReg = CPS_UncachedRead32(&(pD->regs->frer_red_tag));
            EMAC_REGS__FRER_RED_TAG__SIX_BYTE_TAG__MODIFY(frerReg, (uint32_t)tagSize);
            CPS_UncachedWrite32(&(pD->regs->frer_red_tag), frerReg);
        }
    }

    return status;
}

uint32_t CEDI_GetFrameEliminationTagSize(CEDI_PrivateData *pD, CEDI_RedundancyTagSize *tagSize)
{
    uint32_t status = CEDI_GetFrameEliminationTagSSF(pD, tagSize);
    uint32_t frerReg;
    uint32_t rTagSize;

    if (CDN_EOK == status) {
        if (0U == (pD->hwCfg.num_cb_streams)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        frerReg = CPS_UncachedRead32(&(pD->regs->frer_red_tag));
        rTagSize = EMAC_REGS__FRER_RED_TAG__SIX_BYTE_TAG__READ(frerReg);

        switch (rTagSize){
        case 0U:
            *tagSize = CEDI_REDUNDANCY_TAG_SIZE_4;
        break;
        case 1U:
            *tagSize = CEDI_REDUNDANCY_TAG_SIZE_6;
        break;
        default:
            // default
        break;
        }
    }

    return status;
}

uint32_t CEDI_SetFrameEliminationEnable(CEDI_PrivateData *pD, uint8_t queueNum, uint8_t enable)
{
    uint32_t status = CEDI_SetFrameEliminationEnabSF(pD, queueNum, enable);
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    if (CDN_EOK == status) {
        if (queueNum >= pD->rxQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of active RX queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0U == (pD->hwCfg.num_cb_streams)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->hwCfg.num_cb_streams) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of CB streams\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        pD->frerEnabled[queueNum] = enable;

        regPtr = frerControlRegA[queueNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);
        EMAC_REGS__FRER_CONTROL_A__EN_ELIMINATION__MODIFY(reg, enable);
        CPS_UncachedWrite32(regPtr, reg);
    }

    return status;
}

uint32_t CEDI_GetFrameEliminationEnable(const CEDI_PrivateData *pD, uint8_t queueNum, uint8_t *enable)
{
    uint32_t status = CEDI_GetFrameEliminationEnabSF(pD, queueNum, enable);
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    if (CDN_EOK == status) {
        if (queueNum >= pD->rxQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of active RX queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0U == (pD->hwCfg.num_cb_streams)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->hwCfg.num_cb_streams){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of CB streams\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regPtr = frerControlRegA[queueNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);
        *enable = (uint8_t)EMAC_REGS__FRER_CONTROL_A__EN_ELIMINATION__READ(reg);
    }

    return status;
}

uint32_t CEDI_SetFrameEliminationSeqRecRstTmrEnable(const CEDI_PrivateData *pD, uint8_t queueNum, uint8_t enable)
{
    uint32_t status = CEDI_SetFrameEliminationSeqRSF(pD, queueNum, enable);
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    if (CDN_EOK == status) {
        if (queueNum >= pD->rxQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of active RX queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0U == (pD->hwCfg.num_cb_streams)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->hwCfg.num_cb_streams){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of CB streams\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regPtr = frerControlRegA[queueNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);
        EMAC_REGS__FRER_CONTROL_A__EN_SEQRECRST_TIMER__MODIFY(reg, enable);
        CPS_UncachedWrite32(regPtr, reg);
    }

    return status;
}

uint32_t CEDI_GetFrameEliminationSeqRecRstTmrEnable(const CEDI_PrivateData *pD, uint8_t queueNum, uint8_t *enable)
{
    uint32_t status = CEDI_GetFrameEliminationSeqRSF(pD, queueNum, enable);
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    if (CDN_EOK == status) {
        if (queueNum >= pD->rxQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of active RX queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0U == (pD->hwCfg.num_cb_streams)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->hwCfg.num_cb_streams){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of CB streams\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regPtr = frerControlRegA[queueNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);
        *enable = (uint8_t) (EMAC_REGS__FRER_CONTROL_A__EN_SEQRECRST_TIMER__READ(reg));
    }

    return status;
}

uint32_t CEDI_SetFrameEliminationConfig(const CEDI_PrivateData *pD, uint8_t queueNum, const CEDI_FrameEliminationConfig* fec)
{
    uint32_t status = CEDI_SetFrameEliminationConfSF(pD, queueNum, fec);
    uint32_t reg;
    volatile uint32_t *regAPtr = NULL;
    volatile uint32_t *regBPtr = NULL;

    if (CDN_EOK == status) {
        if (queueNum >= pD->rxQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of active RX queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0U == (pD->hwCfg.num_cb_streams)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->hwCfg.num_cb_streams){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of CB streams\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
    /* Configuration values are static - not to be modified, if elimination is enabled */
        if (0U != pD->frerEnabled[queueNum]) {
            status = CDN_EINVAL;
        }

        if ((fec->enVectAlg > 1U) || (fec->seqNumIdentification > 1U)) {
            status = CDN_EINVAL;
        }

        if ((fec->offsetValue > 511U) || (fec->smemberStream1 > 15U) || (fec->smemberStream2 > 15U)) {
            status = CDN_EINVAL;
        }

        if ((fec->seqNumLength > 16U) || (fec->seqRecWindow > 63U)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regAPtr = frerControlRegA[queueNum];
        addRegBase(pD, &regAPtr);

        regBPtr = frerControlRegB[queueNum];
        addRegBase(pD, &regBPtr);

        reg = CPS_UncachedRead32(regAPtr);
        EMAC_REGS__FRER_CONTROL_A__EN_VECTOR_REC_ALG__MODIFY(reg, !!fec->enVectAlg);
            setFrerRedundancyTag(fec, &reg);
        EMAC_REGS__FRER_CONTROL_A__OFFSET_VALUE__MODIFY(reg, fec->offsetValue);
        EMAC_REGS__FRER_CONTROL_A__MEMBER_STREAM_1__MODIFY(reg, fec->smemberStream1);
        EMAC_REGS__FRER_CONTROL_A__MEMBER_STREAM_2__MODIFY(reg, fec->smemberStream2);
            CPS_UncachedWrite32(regAPtr, reg);
        reg = CPS_UncachedRead32(regBPtr);
        EMAC_REGS__FRER_CONTROL_B__SEQ_NUM_LENGTH__MODIFY(reg, fec->seqNumLength);
        EMAC_REGS__FRER_CONTROL_B__SEQ_REC_WINDOW__MODIFY(reg, fec->seqRecWindow);
            CPS_UncachedWrite32(regBPtr, reg);
    }

    return status;
}

uint32_t CEDI_GetFrameEliminationConfig(const CEDI_PrivateData *pD, uint8_t queueNum, CEDI_FrameEliminationConfig* fec)
{
    uint32_t status = CEDI_GetFrameEliminationConfSF(pD, queueNum, fec);
    uint32_t reg;
    volatile uint32_t *regAPtr = NULL;
    volatile uint32_t *regBPtr = NULL;

    if (CDN_EOK == status) {
        if (queueNum >= pD->rxQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of active RX queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0U == (pD->hwCfg.num_cb_streams)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->hwCfg.num_cb_streams){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of CB streams\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regAPtr = frerControlRegA[queueNum];
        addRegBase(pD, &regAPtr);

        regBPtr = frerControlRegB[queueNum];
        addRegBase(pD, &regBPtr);

        reg = CPS_UncachedRead32(regAPtr);
        fec->enVectAlg = (uint8_t)EMAC_REGS__FRER_CONTROL_A__EN_VECTOR_REC_ALG__READ(reg);
        getFrerRedundancyTag(fec, reg);
        fec->offsetValue = (uint16_t)EMAC_REGS__FRER_CONTROL_A__OFFSET_VALUE__READ(reg);
        fec->smemberStream1 = (uint8_t)EMAC_REGS__FRER_CONTROL_A__MEMBER_STREAM_1__READ(reg);
        fec->smemberStream2 = (uint8_t)EMAC_REGS__FRER_CONTROL_A__MEMBER_STREAM_2__READ(reg);
        reg = CPS_UncachedRead32(regBPtr);
        fec->seqNumLength = (uint8_t)EMAC_REGS__FRER_CONTROL_B__SEQ_NUM_LENGTH__READ(reg);
        fec->seqRecWindow = (uint8_t)EMAC_REGS__FRER_CONTROL_B__SEQ_REC_WINDOW__READ(reg);
    }

    return status;
}

uint32_t CEDI_SetFrameEliminationTagConfig(CEDI_PrivateData *pD, const CEDI_FrameEliminationTagConfig* fetc)
{
    uint32_t status = CEDI_SetFrameEliminationTagCSF(pD, fetc);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U == (pD->hwCfg.num_cb_streams)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (fetc->enStripRedTag > 1) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->frer_red_tag));
        EMAC_REGS__FRER_RED_TAG__REDUNDANCY_TAG__MODIFY(reg, fetc->redundancyTag);
        EMAC_REGS__FRER_RED_TAG__STRIP_R_TAG__MODIFY(reg, !!fetc->enStripRedTag);
        CPS_UncachedWrite32(&(pD->regs->frer_red_tag), reg);
    }

    return status;
}

uint32_t CEDI_GetFrameEliminationTagConfig(CEDI_PrivateData *pD, CEDI_FrameEliminationTagConfig* fetc)
{
    uint32_t status = CEDI_GetFrameEliminationTagCSF(pD, fetc);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U == (pD->hwCfg.num_cb_streams)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->frer_red_tag));
        fetc->redundancyTag = (uint16_t)EMAC_REGS__FRER_RED_TAG__REDUNDANCY_TAG__READ(reg);
        fetc->enStripRedTag = (uint8_t) EMAC_REGS__FRER_RED_TAG__STRIP_R_TAG__READ(reg);
    }

    return status;
}

uint32_t CEDI_SetFrameEliminationTimoutConfig(CEDI_PrivateData *pD, uint16_t timeout)
{
    uint32_t status = CEDI_SetFrameEliminationTimoSF(pD);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (!(pD->hwCfg.num_cb_streams)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->frer_timeout));
        EMAC_REGS__FRER_TIMEOUT__TIMEOUT__MODIFY(reg, timeout);
        CPS_UncachedWrite32(&(pD->regs->frer_red_tag), reg);
    }

    return status;
}

uint32_t CEDI_GetFrameEliminationStats(const CEDI_PrivateData *pD, uint8_t queueNum, CEDI_FrameEliminationStats* stats)
{
    uint32_t status = CEDI_GetFrameEliminationStatSF(pD, queueNum, stats);
    uint32_t reg;
    volatile uint32_t *regAPtr = NULL;
    volatile uint32_t *regBPtr = NULL;

    volatile uint32_t* const frerStatisticsRegA[16U] = {
        CEDI_RegOff(frer_statistics_1_a),
        CEDI_RegOff(frer_statistics_2_a),
        CEDI_RegOff(frer_statistics_3_a),
        CEDI_RegOff(frer_statistics_4_a),
        CEDI_RegOff(frer_statistics_5_a),
        CEDI_RegOff(frer_statistics_6_a),
        CEDI_RegOff(frer_statistics_7_a),
        CEDI_RegOff(frer_statistics_8_a),
        CEDI_RegOff(frer_statistics_9_a),
        CEDI_RegOff(frer_statistics_10_a),
        CEDI_RegOff(frer_statistics_11_a),
        CEDI_RegOff(frer_statistics_12_a),
        CEDI_RegOff(frer_statistics_13_a),
        CEDI_RegOff(frer_statistics_14_a),
        CEDI_RegOff(frer_statistics_15_a),
        CEDI_RegOff(frer_statistics_16_a)
    };

    volatile uint32_t* const frerStatisticsRegB[16U] = {
        CEDI_RegOff(frer_statistics_1_b),
        CEDI_RegOff(frer_statistics_2_b),
        CEDI_RegOff(frer_statistics_3_b),
        CEDI_RegOff(frer_statistics_4_b),
        CEDI_RegOff(frer_statistics_5_b),
        CEDI_RegOff(frer_statistics_6_b),
        CEDI_RegOff(frer_statistics_7_b),
        CEDI_RegOff(frer_statistics_8_b),
        CEDI_RegOff(frer_statistics_9_b),
        CEDI_RegOff(frer_statistics_10_b),
        CEDI_RegOff(frer_statistics_11_b),
        CEDI_RegOff(frer_statistics_12_b),
        CEDI_RegOff(frer_statistics_13_b),
        CEDI_RegOff(frer_statistics_14_b),
        CEDI_RegOff(frer_statistics_15_b),
        CEDI_RegOff(frer_statistics_16_b)
    };

    if (CDN_EOK == status) {
        if (queueNum >= pD->rxQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of active RX queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0U == (pD->hwCfg.num_cb_streams)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->hwCfg.num_cb_streams){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than number of CB streams\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regAPtr = frerStatisticsRegA[queueNum];
        addRegBase(pD, &regAPtr);

        regBPtr = frerStatisticsRegB[queueNum];
        addRegBase(pD, &regBPtr);

        reg = CPS_UncachedRead32(regAPtr);
        stats->latentErrors = (uint16_t) EMAC_REGS__FRER_STATISTICS_A__LATENT_ERRORS__READ(reg);
        stats->vecRecRogue = (uint16_t) EMAC_REGS__FRER_STATISTICS_A__VEC_REC_ROGUE__READ(reg);
        reg = CPS_UncachedRead32(regBPtr);
        stats->outOfOreder = (uint16_t) EMAC_REGS__FRER_STATISTICS_B__OUT_OF_ORDER__READ(reg);
        stats->seqRstCount = (uint16_t) EMAC_REGS__FRER_STATISTICS_B__SEQRST_COUNT__READ(reg);
    }

    return status;
}

uint32_t CEDI_GetEmac(CEDI_PrivateData *pD, CEDI_PrivateData **emacPrivateData)
{
    uint32_t status = CEDI_GetEmacSF(pD, (const CEDI_PrivateData**)emacPrivateData);

    if (CDN_EOK == status) {
        if (0U == (pD->cfg.incExpressTraffic)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        switch(pD->macType){
            case CEDI_MAC_TYPE_EMAC:
                *emacPrivateData = pD;
                break;
            case CEDI_MAC_TYPE_PMAC:
                *emacPrivateData = pD->otherMac;
                break;
            default:
                *emacPrivateData = NULL;
                status = CDN_ENOTSUP;
                break;
        }
    }
    return status;

}

uint32_t CEDI_GetPmac(CEDI_PrivateData *pD, CEDI_PrivateData **pmacPrivateData)
{
    uint32_t status = CEDI_GetPmacSF(pD, (const CEDI_PrivateData**)pmacPrivateData);

    if (CDN_EOK == status) {
        switch(pD->macType) {
            case CEDI_MAC_TYPE_EMAC:
                *pmacPrivateData = pD->otherMac;
                break;
            case CEDI_MAC_TYPE_PMAC:
                *pmacPrivateData = pD;
                break;
            default:
                *pmacPrivateData = NULL;
                status = CDN_ENOTSUP;
                break;
        }
    }
    return status;

}

uint32_t CEDI_GetMacType(const CEDI_PrivateData *pD, CEDI_MacType* macType)
{
    uint32_t status = CEDI_GetMacTypeSF(pD, macType);

    if (CDN_EOK == status) {
        *macType = pD->macType;
    }

    return status;
}

uint32_t CEDI_SetPreemptionConfig(CEDI_PrivateData *pD, const CEDI_PreemptionConfig* preCfg)
{
    uint32_t status = CEDI_SetPreemptionConfigSF(pD, preCfg);
    uint32_t reg;
    uint8_t current_ver_enable;
    uint8_t current_add_frag_size;
    uint8_t double_write_required = 0U;
    struct emac_regs *mmslRegs;

    if (CDN_EOK == status) {
        if ((preCfg->routeRxToPmac > 1U) || (preCfg->enPreeption > 1U) || (preCfg->enVerify > 1U)) {
            status = CDN_EINVAL;
        }
        if (preCfg->addFragSize > 3U) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0U == (pD->cfg.incExpressTraffic)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        mmslRegs = getMmslRegs(pD);
        reg = CPS_UncachedRead32(&(mmslRegs->mmsl_control));

        if (0U != preCfg->enPreeption) {
        EMAC_REGS__MMSL_CONTROL__MMSL_BYPASS__CLR(reg);
            CPS_UncachedWrite32(&(mmslRegs->mmsl_control), reg);
    }

        current_ver_enable = !(EMAC_REGS__MMSL_CONTROL__VERIFY_DISABLE__READ(reg));
        current_add_frag_size = (uint8_t) EMAC_REGS__MMSL_CONTROL__ADD_FRAG_SIZE__READ(reg);

        if (0U != preCfg->enPreeption)
        {
            if ((current_ver_enable != preCfg->enVerify) || (current_add_frag_size != preCfg->addFragSize)) {
            double_write_required = 1U;
            }
        }

        EMAC_REGS__MMSL_CONTROL__ROUTE_RX_TO_PMAC__MODIFY(reg, preCfg->routeRxToPmac);
        EMAC_REGS__MMSL_CONTROL__PRE_ENABLE__MODIFY(reg, !!preCfg->enPreeption);
        EMAC_REGS__MMSL_CONTROL__VERIFY_DISABLE__MODIFY(reg, !preCfg->enVerify);
        EMAC_REGS__MMSL_CONTROL__ADD_FRAG_SIZE__MODIFY(reg, preCfg->addFragSize);

        if (0U != double_write_required)
        {
            EMAC_REGS__MMSL_CONTROL__PRE_ENABLE__CLR(reg);
            CPS_UncachedWrite32(&(mmslRegs->mmsl_control), reg);
            EMAC_REGS__MMSL_CONTROL__PRE_ENABLE__SET(reg);
        }
        CPS_UncachedWrite32(&(mmslRegs->mmsl_control), reg);

        if (0U == preCfg->enPreeption) {
        EMAC_REGS__MMSL_CONTROL__MMSL_BYPASS__SET(reg);
            CPS_UncachedWrite32(&(mmslRegs->mmsl_control), reg);
    }
    }

    return status;
}

uint32_t CEDI_GetPreemptionConfig(CEDI_PrivateData *pD, CEDI_PreemptionConfig* preCfg)
{
    uint32_t status = CEDI_GetPreemptionConfigSF(pD, preCfg);
    uint32_t reg;
    struct emac_regs *mmslRegs;

    if (CDN_EOK == status) {
        if (0U == (pD->cfg.incExpressTraffic)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        mmslRegs = getMmslRegs(pD);
        reg = CPS_UncachedRead32(&(mmslRegs->mmsl_control));
        preCfg->routeRxToPmac = (uint8_t) EMAC_REGS__MMSL_CONTROL__ROUTE_RX_TO_PMAC__READ(reg);
        preCfg->enPreeption = (uint8_t) EMAC_REGS__MMSL_CONTROL__PRE_ENABLE__READ(reg);
        preCfg->enVerify = (uint8_t) (!(EMAC_REGS__MMSL_CONTROL__VERIFY_DISABLE__READ(reg)));
        preCfg->addFragSize = EMAC_REGS__MMSL_CONTROL__ADD_FRAG_SIZE__READ(reg);
    }
    return status;

}

uint32_t CEDI_PreemptionRestartVerification(CEDI_PrivateData *pD)
{
    uint32_t status = CEDI_PreemptionRestartVerifiSF(pD);
    uint32_t reg;
    struct emac_regs *mmslRegs;

    if (CDN_EOK == status) {
        if (0U == pD->cfg.incExpressTraffic) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        mmslRegs = getMmslRegs(pD);
        reg = CPS_UncachedRead32(&(mmslRegs->mmsl_control));
        EMAC_REGS__MMSL_CONTROL__RESTART_VER__SET(reg);
        CPS_UncachedWrite32(&(mmslRegs->mmsl_control), reg);
    }
    return status;
}

uint32_t CEDI_SetMmslEventEnable(CEDI_PrivateData *pD, uint32_t events, uint8_t enable)
{
    uint32_t status = CEDI_SetMmslEventEnableSF(pD, enable);
    struct emac_regs *mmslRegs;

    if (CDN_EOK == status) {
        if (0U == (pD->cfg.incExpressTraffic)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        mmslRegs = getMmslRegs(pD);
        if (0U != enable) {
            CPS_UncachedWrite32(&(mmslRegs->mmsl_int_enable), events);
        } else {
            CPS_UncachedWrite32(&(mmslRegs->mmsl_int_disable), events);
        }
    }
    return status;

}

uint32_t CEDI_GetMmslEventEnable(CEDI_PrivateData *pD, uint32_t* events)
{
    uint32_t status = CEDI_GetMmslEventEnableSF(pD, events);
    uint32_t reg;
    struct emac_regs *mmslRegs;
    /* if additional registers are added, following macro will change
     * and code will no longer compile (which is desired in this case).
     */
    uint32_t mask = ~EMAC_REGS__MMSL_INT_MASK__RESERVED_31_6__MASK;

    if (CDN_EOK == status) {
        if (0U == (pD->cfg.incExpressTraffic)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        mmslRegs = getMmslRegs(pD);
        reg = CPS_UncachedRead32(&(mmslRegs->mmsl_int_mask));
        *events = (~reg) & mask;
    }
    return status;
}

uint32_t CEDI_ReadMmslStats(CEDI_PrivateData *pD, CEDI_MmslStats* mmslStats)
{
    uint32_t status = CEDI_ReadMmslStatsSF(pD, mmslStats);
    uint32_t reg;
    struct emac_regs *mmslRegs;

    if (CDN_EOK == status) {
        if (0U == (pD->cfg.incExpressTraffic)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
    mmslRegs = getMmslRegs(pD);
        reg = CPS_UncachedRead32(&(mmslRegs->mmsl_err_stats));
        mmslStats->assErrorCount = (uint8_t) EMAC_REGS__MMSL_ERR_STATS__ASS_ERROR_COUNT__READ(reg);
        mmslStats->smdErrorCount = (uint8_t)EMAC_REGS__MMSL_ERR_STATS__SMD_ERR_COUNT__READ(reg);

        reg = CPS_UncachedRead32(&(mmslRegs->mmsl_ass_ok_count));
        mmslStats->assOkCount = EMAC_REGS__MMSL_ASS_OK_COUNT__ASS_OK_COUNT__READ(reg);

        reg = CPS_UncachedRead32(&(mmslRegs->mmsl_frag_count_rx));
        mmslStats->fragCountRx = EMAC_REGS__MMSL_FRAG_COUNT_RX__FRAG_COUNT_RX__READ(reg);

        reg = CPS_UncachedRead32(&(mmslRegs->mmsl_frag_count_tx));
        mmslStats->fragCountTx = EMAC_REGS__MMSL_FRAG_COUNT_TX__FRAG_COUNT_TX__READ(reg);
    }
    return status;
}

uint32_t CEDI_ReadMmslStatus(CEDI_PrivateData *pD, CEDI_MmslStatus* mmslStatus)
{
    uint32_t status = CEDI_ReadMmslStatusSF(pD, mmslStatus);
    uint32_t reg;
    struct emac_regs *mmslRegs;

    if (CDN_EOK == status) {
        if (0U == (pD->cfg.incExpressTraffic)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        mmslRegs = getMmslRegs(pD);
        reg = CPS_UncachedRead32(&(mmslRegs->mmsl_status));
        mmslStatus->preActive = (uint8_t) EMAC_REGS__MMSL_STATUS__PRE_ACTIVE__READ(reg);
        mmslStatus->respondStatus = EMAC_REGS__MMSL_STATUS__RESPOND_STATUS__READ(reg);
        mmslStatus->verifyStatus = EMAC_REGS__MMSL_STATUS__VERIFY_STATUS__READ(reg);

        mmslStatus->events = 0U;
        if (0U != EMAC_REGS__MMSL_STATUS__RCV_R_ERROR__READ(reg)) {
            mmslStatus->events |= CEDI_MMSL_EV_RCV_R_ERR;
        }
        if (0U != EMAC_REGS__MMSL_STATUS__RCV_V_ERROR__READ(reg)) {
            mmslStatus->events |= CEDI_MMSL_EV_RCV_V_ERR;
        }
        if (0U != EMAC_REGS__MMSL_STATUS__SMDS_ERROR__READ(reg)) {
            mmslStatus->events |= CEDI_MMSL_EV_SMDS_ERR;
        }
        if (0U != EMAC_REGS__MMSL_STATUS__SMDC_ERROR__READ(reg)) {
            mmslStatus->events |= CEDI_MMSL_EV_SMDC_ERR;
        }
        if (0U != EMAC_REGS__MMSL_STATUS__FRER_COUNT_ERR__READ(reg)) {
            mmslStatus->events |= CEDI_MMSL_EV_FR_COUNT_ERR;
        }
        if (0U != EMAC_REGS__MMSL_STATUS__SMD_ERROR__READ(reg)) {
            mmslStatus->events |= CEDI_MMSL_EV_SMD_ERR;
        }
    }
    return status;
}


uint32_t CEDI_GetMdioInState(CEDI_PrivateData *pD, uint8_t *state)
{
    uint32_t status = CEDI_GetMdioInStateSF(pD, state);

    if (CDN_EOK == status) {
        if (0U != pD->cfg.incExpressTraffic) {
            if (CEDI_MAC_TYPE_EMAC == pD->macType)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Error: getMdioInState can not be called for express MAC.");
                status = CDN_EINVAL;
            }
        }
    }
    if (CDN_EOK == status) {
        *state = (uint8_t) (EMAC_REGS__NETWORK_STATUS__MDIO_IN__READ(
                CPS_UncachedRead32(&(pD->regs->network_status))));
    }

    return status;
}

uint32_t CEDI_ReadReg(const CEDI_PrivateData *pD, uint32_t offs, uint32_t *data)
{
    uint32_t status = CEDI_ReadRegSF(pD, offs, data);

    if (CDN_EOK == status) {
        *data = CPS_UncachedRead32(uintptrToPtrU32(pD->cfg.regBase + offs));
    }
    return status;
}

uint32_t CEDI_WriteReg(const CEDI_PrivateData *pD, uint32_t offs, uint32_t data)
{
    uint32_t status = CEDI_WriteRegSF(pD, offs);

    if (CDN_EOK == status) {
        CPS_UncachedWrite32(uintptrToPtrU32(pD->cfg.regBase + offs), data);
    }
    return status;
}

uint32_t CEDI_SetIntrptModerateThreshold(CEDI_PrivateData* pD,
                    uint8_t txIntFrameThreshold,
                    uint8_t rxIntFrameThreshold)
{
    uint32_t status = CEDI_SetIntrptModerateThreshSF(pD, txIntFrameThreshold, rxIntFrameThreshold);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U == isIntrptModerateThresholdSupported(pD)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->int_moderation));
    /* first clear interrupt moderation */
        EMAC_REGS__INT_MODERATION__TX_INT_MOD_THRESH__MODIFY(reg, 0);
        EMAC_REGS__INT_MODERATION__RX_INT_MOD_THRESH__MODIFY(reg, 0);
        CPS_UncachedWrite32(&(pD->regs->int_moderation), reg);

        EMAC_REGS__INT_MODERATION__TX_INT_MOD_THRESH__MODIFY(reg, txIntFrameThreshold);
        EMAC_REGS__INT_MODERATION__RX_INT_MOD_THRESH__MODIFY(reg, rxIntFrameThreshold);
        CPS_UncachedWrite32(&(pD->regs->int_moderation), reg);
    }

    return status;
}

uint32_t CEDI_GetIntrptModerateThreshold(CEDI_PrivateData* pD,
                    uint8_t *txIntFrameThreshold,
                    uint8_t *rxIntFrameThreshold)
{
    uint32_t status = CEDI_GetIntrptModerateThreshSF(pD, txIntFrameThreshold, rxIntFrameThreshold);
    uint32_t reg;

    if (CDN_EOK == status) {
        if (0U == isIntrptModerateThresholdSupported(pD)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->int_moderation));
        *txIntFrameThreshold = EMAC_REGS__INT_MODERATION__TX_INT_MOD_THRESH__READ(reg);
        *rxIntFrameThreshold = EMAC_REGS__INT_MODERATION__RX_INT_MOD_THRESH__READ(reg);
    }

    return status;
}

uint32_t CEDI_SetLockupConfig(CEDI_PrivateData* pD, const CEDI_LockupConfig* lockupCfg)
{
    uint32_t status = CEDI_SetLockupConfigSF(pD, lockupCfg);
    uint32_t reg = 0;

    if (CDN_EOK == status) {
        if ((lockupCfg->enLockupRecovery > 1) ||
                (lockupCfg->enRxMacLockupMon > 1) ||
                (lockupCfg->enRxDmaLockupMon > 1) ||
                (lockupCfg->enTxMacLockupMon > 1) ||
                (lockupCfg->enTxDmaLockupMon > 1) ||
                (lockupCfg->dmaLockupTime > 0x7FF) ||
                (lockupCfg->txLockupTime > 0x7FF))
            status = CDN_EINVAL;
    }

    if (CDN_EOK == status) {
        if (0 == pD->hwCfg.lockup_supported)
            status = CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
        EMAC_REGS__LOCKUP_CONFIG__DMA_LOCKUP_TIME__MODIFY(reg, lockupCfg->dmaLockupTime);
        EMAC_REGS__LOCKUP_CONFIG__PRESCALER_VALUE__MODIFY(reg, lockupCfg->prescaler);
        EMAC_REGS__LOCKUP_CONFIG__LOCKUP_RECOVERY_EN__MODIFY(reg, lockupCfg->enLockupRecovery);
        EMAC_REGS__LOCKUP_CONFIG__RX_MAC_LOCKUP_MON_EN__MODIFY(reg, lockupCfg->enRxMacLockupMon);
        EMAC_REGS__LOCKUP_CONFIG__RX_DMA_LOCKUP_MON_EN__MODIFY(reg, lockupCfg->enRxDmaLockupMon);
        EMAC_REGS__LOCKUP_CONFIG__TX_MAC_LOCKUP_MON_EN__MODIFY(reg, lockupCfg->enTxMacLockupMon);
        EMAC_REGS__LOCKUP_CONFIG__TX_DMA_LOCKUP_MON_EN__MODIFY(reg, lockupCfg->enTxDmaLockupMon);
        CPS_UncachedWrite32(&(pD->regs->lockup_config), reg);

        reg = 0;

        EMAC_REGS__MAC_LOCKUP_TIME__RX_MAC_LOCKUP_TIME__MODIFY(reg, lockupCfg->rxLockupTime);
        EMAC_REGS__MAC_LOCKUP_TIME__TX_MAC_LOCKUP_TIME__MODIFY(reg, lockupCfg->txLockupTime);
        CPS_UncachedWrite32(&(pD->regs->mac_lockup_time), reg);

        reg = lockupCfg->enTxDmaTimers & ~EMAC_REGS__LOCKUP_CONFIG3__RESERVED_31_16__MASK;
        CPS_UncachedWrite32(&(pD->regs->lockup_config3), reg);
    }

    return status;
}

uint32_t CEDI_GetLockupConfig(CEDI_PrivateData* pD, CEDI_LockupConfig* lockupCfg)
{
    uint32_t status = CEDI_GetLockupConfigSF(pD, lockupCfg);
    uint32_t reg = 0;

    if (CDN_EOK == status) {
        if (0 == pD->hwCfg.lockup_supported)
            status = CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->lockup_config));
        lockupCfg->dmaLockupTime = EMAC_REGS__LOCKUP_CONFIG__DMA_LOCKUP_TIME__READ(reg);
        lockupCfg->prescaler = EMAC_REGS__LOCKUP_CONFIG__PRESCALER_VALUE__READ(reg);
        lockupCfg->enLockupRecovery = EMAC_REGS__LOCKUP_CONFIG__LOCKUP_RECOVERY_EN__READ(reg);
        lockupCfg->enRxMacLockupMon = EMAC_REGS__LOCKUP_CONFIG__RX_MAC_LOCKUP_MON_EN__READ(reg);
        lockupCfg->enRxDmaLockupMon = EMAC_REGS__LOCKUP_CONFIG__RX_DMA_LOCKUP_MON_EN__READ(reg);
        lockupCfg->enTxMacLockupMon = EMAC_REGS__LOCKUP_CONFIG__TX_MAC_LOCKUP_MON_EN__READ(reg);
        lockupCfg->enTxDmaLockupMon = EMAC_REGS__LOCKUP_CONFIG__TX_DMA_LOCKUP_MON_EN__READ(reg);

        reg = CPS_UncachedRead32(&(pD->regs->mac_lockup_time));
        lockupCfg->rxLockupTime = EMAC_REGS__MAC_LOCKUP_TIME__RX_MAC_LOCKUP_TIME__READ(reg);
        lockupCfg->txLockupTime = EMAC_REGS__MAC_LOCKUP_TIME__TX_MAC_LOCKUP_TIME__READ(reg);

        reg = CPS_UncachedRead32(&(pD->regs->lockup_config3));
        lockupCfg->enTxDmaTimers = reg & ~EMAC_REGS__LOCKUP_CONFIG3__RESERVED_31_16__MASK;
    }

    return status;
}

uint32_t CEDI_SetAxiQosConfig(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_AxiQosConfig* axiQosConfig)
{
    uint32_t status = CEDI_SetAxiQosConfigSF(pD, queueNum, axiQosConfig);
    uint32_t reg;
    volatile uint32_t* const axiQosReg[4] = {
    CEDI_RegOff(axi_qos_cfg_0),
    CEDI_RegOff(axi_qos_cfg_1),
    CEDI_RegOff(axi_qos_cfg_2),
    CEDI_RegOff(axi_qos_cfg_3),
    };

    if (CDN_EOK == status){
        if (queueNum > pD->cfg.txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                "Error: Queue number is bigger than supported queue number\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status){
    if (axiQosConfig->descriptorQos > 0xF)
        status = CDN_EINVAL;
    if (axiQosConfig->dataQos > 0xF)
        status = CDN_EINVAL;
    }

    if (CDN_EOK == status){
    if (0U == IsGem1p11(pD))
        status = CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
    if (pD->hwCfg.axi == 0U) {
        status = CDN_ENOTSUP;
    }
    }

    if (CDN_EOK == status){
    volatile uint32_t *regPtr = NULL;

    regPtr = axiQosReg[queueNum >> 2];
    addRegBase(pD, &regPtr);
    reg = CPS_UncachedRead32(regPtr);


    if (queueNum  == 0){
        EMAC_REGS__AXI_QOS_CFG_0__Q_0_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_0__Q_0_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }

    if (queueNum  == 1){
        EMAC_REGS__AXI_QOS_CFG_0__Q_1_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_0__Q_1_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 2){
        EMAC_REGS__AXI_QOS_CFG_0__Q_2_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_0__Q_2_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 3){
        EMAC_REGS__AXI_QOS_CFG_0__Q_3_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_0__Q_3_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 4){
        EMAC_REGS__AXI_QOS_CFG_1__Q_4_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_1__Q_4_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 5){
        EMAC_REGS__AXI_QOS_CFG_1__Q_5_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_1__Q_5_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 6){
        EMAC_REGS__AXI_QOS_CFG_1__Q_6_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_1__Q_6_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 7){
        EMAC_REGS__AXI_QOS_CFG_1__Q_7_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_1__Q_7_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 8){
        EMAC_REGS__AXI_QOS_CFG_2__Q_8_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_2__Q_8_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 9){
        EMAC_REGS__AXI_QOS_CFG_2__Q_9_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_2__Q_9_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 10){
        EMAC_REGS__AXI_QOS_CFG_2__Q_10_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_2__Q_10_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 11){
        EMAC_REGS__AXI_QOS_CFG_2__Q_11_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_2__Q_11_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 12){
        EMAC_REGS__AXI_QOS_CFG_3__Q_12_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_3__Q_12_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 13){
        EMAC_REGS__AXI_QOS_CFG_3__Q_13_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_3__Q_13_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 14){
        EMAC_REGS__AXI_QOS_CFG_3__Q_14_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_3__Q_14_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }
    if (queueNum  == 15){
        EMAC_REGS__AXI_QOS_CFG_3__Q_15_DESCR_QOS__MODIFY(reg, axiQosConfig->descriptorQos);
        EMAC_REGS__AXI_QOS_CFG_3__Q_15_DATA_QOS__MODIFY(reg, axiQosConfig->dataQos);
    }

    CPS_UncachedWrite32(regPtr, reg);
    }


    return status;
}

uint32_t CEDI_GetAxiQosConfig(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_AxiQosConfig* axiQosConfig)
{
    uint32_t status = CEDI_GetAxiQosConfigSF(pD, queueNum, axiQosConfig);
    uint32_t reg;
    volatile uint32_t* const axiQosReg[4] = {
    CEDI_RegOff(axi_qos_cfg_0),
    CEDI_RegOff(axi_qos_cfg_1),
    CEDI_RegOff(axi_qos_cfg_2),
    CEDI_RegOff(axi_qos_cfg_3),
    };

    if (CDN_EOK == status){
    if (queueNum > pD->cfg.txQs){
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
            "Error: Queue number is bigger than supported queue number\n");
        status = CDN_EINVAL;
    }
    }

    if (CDN_EOK == status){
    if (0U == IsGem1p11(pD))
        status = CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
    if (pD->hwCfg.axi == 0U) {
        status = CDN_ENOTSUP;
    }
    }

    if (CDN_EOK == status){
    volatile uint32_t *regPtr = NULL;

    regPtr = axiQosReg[queueNum >> 2];
    addRegBase(pD, &regPtr);
    reg = CPS_UncachedRead32(regPtr);


    if (queueNum  == 0){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_0__Q_0_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_0__Q_0_DATA_QOS__READ(reg);
    }

    if (queueNum  == 1){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_0__Q_1_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_0__Q_1_DATA_QOS__READ(reg);
    }
    if (queueNum  == 2){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_0__Q_2_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_0__Q_2_DATA_QOS__READ(reg);
    }
    if (queueNum  == 3){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_0__Q_3_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_0__Q_3_DATA_QOS__READ(reg);
    }
    if (queueNum  == 4){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_1__Q_4_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_1__Q_4_DATA_QOS__READ(reg);
    }
    if (queueNum  == 5){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_1__Q_5_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_1__Q_5_DATA_QOS__READ(reg);
    }
    if (queueNum  == 6){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_1__Q_6_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_1__Q_6_DATA_QOS__READ(reg);
    }
    if (queueNum  == 7){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_1__Q_7_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_1__Q_7_DATA_QOS__READ(reg);
    }
    if (queueNum  == 8){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_2__Q_8_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_2__Q_8_DATA_QOS__READ(reg);
    }
    if (queueNum  == 9){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_2__Q_9_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_2__Q_9_DATA_QOS__READ(reg);
    }
    if (queueNum  == 10){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_2__Q_10_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_2__Q_10_DATA_QOS__READ(reg);
    }
    if (queueNum  == 11){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_2__Q_11_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_2__Q_11_DATA_QOS__READ(reg);
    }
    if (queueNum  == 12){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_3__Q_12_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_3__Q_12_DATA_QOS__READ(reg);
    }
    if (queueNum  == 13){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_3__Q_13_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_3__Q_13_DATA_QOS__READ(reg);
    }
    if (queueNum  == 14){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_3__Q_14_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_3__Q_14_DATA_QOS__READ(reg);
    }
    if (queueNum  == 15){
        axiQosConfig->descriptorQos = EMAC_REGS__AXI_QOS_CFG_3__Q_15_DESCR_QOS__READ(reg);
        axiQosConfig->dataQos = EMAC_REGS__AXI_QOS_CFG_3__Q_15_DATA_QOS__READ(reg);
    }
    }

    return status;
}

uint32_t CEDI_SetAxiArbitrationCfg(CEDI_PrivateData* pD,
                                  const CEDI_AxiHostArbitrationCfg* axiCfg)
{
    volatile uint32_t* regAddr;
    uint32_t regVal;
    uint32_t status = CEDI_SetAxiArbitrationCfgSF(pD, axiCfg);

    if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->axi_host_arbitration);
        regVal = EMAC_REGS__AXI_HOST_ARBITRATION__AXI_WRITE_ARBITER__WRITE(axiCfg->axiWriterArbiter)
               | EMAC_REGS__AXI_HOST_ARBITRATION__AXI_READ_ARBITER__WRITE(axiCfg->axiReadArbiter)
               | EMAC_REGS__AXI_HOST_ARBITRATION__RX_DESCR_PRIOR__WRITE((axiCfg->rxDescPriorFixed) ? 0U : 1U)
               | EMAC_REGS__AXI_HOST_ARBITRATION__TX_DESCR_PRIOR__WRITE((axiCfg->txDescPriorFixed) ? 0U : 1U)
               | EMAC_REGS__AXI_HOST_ARBITRATION__TX_DATA_PRIOR__WRITE((axiCfg->txDataPriorFixed) ? 0U : 1U);

        CPS_REG_WRITE(regAddr, regVal);
    }

    return status;
}

uint32_t CEDI_GetAxiArbitrationCfg(const CEDI_PrivateData* pD,
                                  CEDI_AxiHostArbitrationCfg* axiCfg)
{
    volatile uint32_t* regAddr;
    uint32_t regVal;
    uint32_t tmpVal;
    uint32_t status = CEDI_GetAxiArbitrationCfgSF(pD, axiCfg);

    if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->axi_host_arbitration);
        regVal = CPS_REG_READ(regAddr);

        axiCfg->axiWriterArbiter = EMAC_REGS__AXI_HOST_ARBITRATION__AXI_WRITE_ARBITER__READ(regVal);
        axiCfg->axiReadArbiter = EMAC_REGS__AXI_HOST_ARBITRATION__AXI_READ_ARBITER__READ(regVal);

        tmpVal = EMAC_REGS__AXI_HOST_ARBITRATION__RX_DESCR_PRIOR__READ(regVal);
        axiCfg->rxDescPriorFixed = (tmpVal == 0U) ? true : false;

        tmpVal = EMAC_REGS__AXI_HOST_ARBITRATION__TX_DESCR_PRIOR__READ(regVal);
        axiCfg->txDescPriorFixed = (tmpVal == 0U) ? true : false;

        tmpVal = EMAC_REGS__AXI_HOST_ARBITRATION__TX_DATA_PRIOR__READ(regVal);
        axiCfg->txDataPriorFixed = (tmpVal == 0U) ? true : false;
    }

    return status;
}

uint32_t CEDI_SetAxiReqNum(CEDI_PrivateData* pD,
                                  uint8_t queueNum,
                                  CEDI_AxiChannelType axiChannel,
                                  const CEDI_AxiBuffCfg* axiBuffCfg)
{
    uint8_t status;
    volatile uint32_t* regAddr;
    uint32_t regVal;

    status = CEDI_SetAxiReqNumSF(pD, axiChannel, axiBuffCfg);

    if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "Error: Queue number %u is out of configured range. "
                    "Currently number of queues is configured to %u\n", queueNum, pD->txQs);

            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (axiChannel == CEDI_AXI_CHANNEL_READ) {
            regAddr = gemAxiXactsReadReg[queueNum];
        } else {
            regAddr = gemAxiXactsWriteReg[queueNum];
        }

        addRegBase(pD, &regAddr);

        /* Same mask either read and write direction */
        regVal = EMAC_REGS__GEM_AXI_XACTS_RD_QX__MAX_RX_DESCR_RD__WRITE(axiBuffCfg->maxRxDescrReqNum)
               | EMAC_REGS__GEM_AXI_XACTS_RD_QX__MAX_TX_DESCR_RD__WRITE(axiBuffCfg->maxTxDescrReqNum)
               | EMAC_REGS__GEM_AXI_XACTS_RD_QX__MAX_TX_DATA_RD__WRITE(axiBuffCfg->maxDataReqNum);

        CPS_REG_WRITE(regAddr, regVal);
    }

    return status;
}

uint32_t CEDI_GetAxiReqNum(const CEDI_PrivateData* pD,
                                  uint8_t queueNum,
                                  CEDI_AxiChannelType axiChannel,
                                  CEDI_AxiBuffCfg* axiBuffCfg)
{
    uint8_t status;
    volatile uint32_t* regAddr;
    uint32_t regVal;

    status = CEDI_GetAxiReqNumSF(pD, axiChannel, axiBuffCfg);

    if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "Error: Queue number %u is out of configured range. "
                    "Currently number of queues is configured to %u\n", queueNum, pD->txQs);

            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (axiChannel == CEDI_AXI_CHANNEL_READ) {
            regAddr = gemAxiXactsReadReg[queueNum];
        } else {
            regAddr = gemAxiXactsWriteReg[queueNum];
        }

        addRegBase(pD, &regAddr);

        regVal = CPS_REG_READ(regAddr);

        /* Same mask either read and write direction */
        axiBuffCfg->maxRxDescrReqNum = EMAC_REGS__GEM_AXI_XACTS_RD_QX__MAX_RX_DESCR_RD__READ(regVal);
        axiBuffCfg->maxTxDescrReqNum = EMAC_REGS__GEM_AXI_XACTS_RD_QX__MAX_TX_DESCR_RD__READ(regVal);
        axiBuffCfg->maxDataReqNum    = EMAC_REGS__GEM_AXI_XACTS_RD_QX__MAX_TX_DATA_RD__READ(regVal);

    }

    return status;
}

uint32_t CEDI_SetDeferOnLinkIntEnable(CEDI_PrivateData* pD, bool enable)
{
    uint32_t status;
    volatile uint32_t* regAddr;
    uint32_t regVal;

    status = CEDI_SetDeferOnLinkIntEnableSF(pD);

    if (CDN_EOK == status) {
            status = (pD->cfg.ifTypeSel >= CEDI_IFSP_XGMII) ? CDN_EOK : CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->hs_mac_config);
        regVal = CPS_REG_READ(regAddr);

        if (enable) {
            EMAC_REGS__HS_MAC_CONFIG__DEFER_ON_LINKINT_OS__SET(regVal);
        } else {
            EMAC_REGS__HS_MAC_CONFIG__DEFER_ON_LINKINT_OS__CLR(regVal);
        }

        CPS_REG_WRITE(regAddr, regVal);
    }
    return status;
}

uint32_t CEDI_GetDeferOnLinkIntEnable(CEDI_PrivateData* pD, bool* enable)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_GetDeferOnLinkIntEnableSF(pD, enable);

    if (CDN_EOK == status) {
        status = (pD->cfg.ifTypeSel >= CEDI_IFSP_XGMII) ? CDN_EOK : CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
        regVal = CPS_REG_READ(&(pD->regs->hs_mac_config));
        *enable = (EMAC_REGS__HS_MAC_CONFIG__DEFER_ON_LINKINT_OS__READ(regVal) != 0U);
    }

    return status;
}

bool isPcs25gDatapathsEnabled(const CEDI_PrivateData* pD, const char* funcName)
{
    /* functions are called separately to print both warning messages if needed */
    if (pD->isRxDatapathEnabled) {
               vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Cannot use %s when Rx datapath is enabled."
                       "Please, disable it first.\n", funcName);
    }

    if (pD->isTxDatapathEnabled) {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Cannot use %s when Tx datapath is enabled. "
                        "Please, disable it first.\n", funcName);
    }

    return (pD->isTxDatapathEnabled) || (pD->isRxDatapathEnabled);
}


uint32_t CEDI_SetPcs25gSerdesRate(CEDI_PrivateData* pD, CEDI_SerdesRate serdesRate)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t* regAddr;

    status = CEDI_SetPcs25gSerdesRateSF(pD, serdesRate);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->usx_control_register);
        regVal = CPS_REG_READ(regAddr);
        EMAC_REGS__USX_CONTROL_REGISTER__SERDES_RATE__MODIFY(regVal, serdesRate);
        CPS_REG_WRITE(regAddr, regVal);
    } else {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                "%s is not supported by this GEM version\n", __func__);
    }

    return status;
}

uint32_t CEDI_GetPcs25gSerdesRate(CEDI_PrivateData* pD, CEDI_SerdesRate* serdesRate)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t* regAddr;
    uint32_t serdesRateRead;

    static const CEDI_SerdesRate serdesTranslateArray[3] = {
            CEDI_SERDES_RATE_5G,
            CEDI_SERDES_RATE_10G,
            CEDI_SERDES_RATE_25G
    };

    status = CEDI_GetPcs25gSerdesRateSF(pD, serdesRate);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->usx_control_register);
        regVal = CPS_REG_READ(regAddr);
        serdesRateRead = EMAC_REGS__USX_CONTROL_REGISTER__SERDES_RATE__READ(regVal);

        if (serdesRateRead > 2U) {
            status = CDN_EIO;
        } else {
            *serdesRate = serdesTranslateArray[serdesRateRead];
        }

    } else {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                "%s is not supported by this GEM version\n", __func__);
    }

    return status;
}

uint32_t CEDI_SetPcs25gFecEnable(CEDI_PrivateData* pD, bool enable)
{
    uint32_t status;
    volatile uint32_t* regAddr;
    uint32_t regVal;

    status = CEDI_SetPcs25gFecEnableSF(pD);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isFecSupported(pD) ;
    }

    /* can change FEC value only if PCS Tx&Rx datapaths are disabled */
    if (CDN_EOK == status) {
        if (isPcs25gDatapathsEnabled(pD, __func__)) {
            status = CDN_EIO;
        }
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->usx_control_register);
        regVal = CPS_REG_READ(regAddr);

        if (enable) {
            EMAC_REGS__USX_CONTROL_REGISTER__FEC_ENABLE__SET(regVal);
        } else {
            EMAC_REGS__USX_CONTROL_REGISTER__FEC_ENABLE__CLR(regVal);
        }

        CPS_REG_WRITE(regAddr, regVal);
    }

    return status;
}

uint32_t CEDI_GetPcs25gFecEnable(const CEDI_PrivateData* pD, bool* enable)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_GetPcs25gFecEnableSF(pD, enable);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isFecSupported(pD) ;
    }

    if (CDN_EOK == status) {
        if(isPcs25gDatapathsEnabled(pD, __func__)) {
            status = CDN_EIO;
        }
    }

    if (CDN_EOK == status) {
        regVal = CPS_REG_READ(&(pD->regs->usx_control_register));
        *enable = (EMAC_REGS__USX_CONTROL_REGISTER__FEC_ENABLE__READ(regVal) != 0U);
    }

    return status;
}

uint32_t CEDI_SetPcs25gFecErrIndEnable(CEDI_PrivateData* pD, bool enable)
{
    volatile uint32_t* regAddr;
    uint32_t regVal;
    uint32_t status = CEDI_SetPcs25gFecErrIndEnablSF(pD);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isFecSupported(pD) ;
    }

    if (CDN_EOK == status) {
        if (pD->isRxDatapathEnabled) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Warning: Cannot use %s when Rx datapath is enabled."
                    "Please, disable it first\n", __func__);
            status = CDN_EIO;
        }
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->usx_control_register);
        regVal = CPS_REG_READ(regAddr);
        if (enable) {
            EMAC_REGS__USX_CONTROL_REGISTER__FEC_ENA_ERR_IND__SET(regVal);
        } else {
            EMAC_REGS__USX_CONTROL_REGISTER__FEC_ENA_ERR_IND__CLR(regVal);
        }
        CPS_REG_WRITE(regAddr, regVal);
    }
    return status;
}

uint32_t CEDI_GetPcs25gFecErrIndEnable(const CEDI_PrivateData* pD, bool* enable)
{
    uint32_t regVal;
    uint32_t status = CEDI_GetPcs25gFecErrIndEnablSF(pD, enable);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isFecSupported(pD) ;
    }

    if (CDN_EOK == status) {
        regVal = CPS_REG_READ(&(pD->regs->usx_control_register));
        *enable = EMAC_REGS__USX_CONTROL_REGISTER__FEC_ENA_ERR_IND__READ(regVal) != 0U;
    }
    return status;
}

uint32_t CEDI_GetPcs25gStatus(const CEDI_PrivateData* pD, CEDI_Pcs25gStatus* pcsStatus)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_GetPcs25gStatusSF(pD, pcsStatus);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        /* Read status from register */
        regVal = CPS_REG_READ(&(pD->regs->usx_status_register));

        pcsStatus->clockToleranceFault = EMAC_REGS__USX_STATUS_REGISTER__CTC_O_U_FLOW__READ(regVal);
        pcsStatus->highBer = EMAC_REGS__USX_STATUS_REGISTER__HI_BIT_ERROR__READ(regVal);
        pcsStatus->txFault = EMAC_REGS__USX_STATUS_REGISTER__TX_FAULT__READ(regVal);
        pcsStatus->rxFault = EMAC_REGS__USX_STATUS_REGISTER__RX_FAULT__READ(regVal);
        pcsStatus->blockLock = EMAC_REGS__USX_STATUS_REGISTER__BLOCK_LOCK__READ(regVal);
    }

    return status;
}

uint32_t CEDI_SetPcs25gOperationMode(CEDI_PrivateData* pD, CEDI_Pcs25gOperationMode opMode)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_SetPcs25gOperationModeSF(pD, opMode);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    /* can change PCS operation mode only if PCS Tx&Rx datapaths are disabled */
    if (CDN_EOK == status) {
        if (isPcs25gDatapathsEnabled(pD, __func__)) {
            status = CDN_EIO;
        }
    }

    if (CDN_EOK == status) {

        if (opMode == CEDI_MII_LOOPBACK_MODE) {
            regVal = EMAC_REGS__USX_TEST_CONTROL__MII_LPBK_EN__WRITE(1U);
        } else if (opMode == CEDI_SCRAMBLER_LOOPBACK_MODE) {
            regVal = EMAC_REGS__USX_TEST_CONTROL__SCR_LPBK_EN__WRITE(1U);
        } else {
            /* for CEDI_TEST_PATTERN_MODE contol bits are set to 0U */
            regVal = 0U;
        }

        CPS_REG_WRITE(&(pD->regs->usx_test_control), regVal);
    }

    return status;
}

uint32_t CEDI_GetPcs25gOperationMode(const CEDI_PrivateData* pD, CEDI_Pcs25gOperationMode* opMode)
{
    uint32_t status;
    uint32_t regVal;
    uint8_t mode;

    status = CEDI_GetPcs25gOperationModeSF(pD, opMode);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        regVal = CPS_REG_READ(&(pD->regs->usx_test_control));
        mode = (uint8_t)(regVal & (EMAC_REGS__USX_TEST_CONTROL__MII_LPBK_EN__MASK |
                                   EMAC_REGS__USX_TEST_CONTROL__SCR_LPBK_EN__MASK));

        if (mode == (uint8_t)CEDI_TEST_PATTERN_MODE) {
            *opMode = CEDI_TEST_PATTERN_MODE;
        } else if (mode == (uint8_t)CEDI_MII_LOOPBACK_MODE) {
            *opMode = CEDI_MII_LOOPBACK_MODE;
        } else if (mode == (uint8_t)CEDI_SCRAMBLER_LOOPBACK_MODE) {
            *opMode = CEDI_SCRAMBLER_LOOPBACK_MODE;
        } else {
            /* read value is invalid */
            status = CDN_EIO;
        }
    }

    return status;
}

uint32_t CEDI_GetPcs25gBitErrorCount(const CEDI_PrivateData* pD, uint32_t* bitErrorCount)
{
    uint32_t status = CEDI_GetPcs25gBitErrorCountSF(pD, bitErrorCount);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        *bitErrorCount = CPS_REG_READ(&(pD->regs->usx_bit_error_counter));

        /* reset counter */
        CPS_REG_WRITE(&(pD->regs->usx_bit_error_counter), 0U);
    }
    return status;
}

uint32_t CEDI_GetPcs25gFecErrorCount(const CEDI_PrivateData* pD, CEDI_FecError* fecError)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t* regAddr;

    status = CEDI_GetPcs25gFecErrorCountSF(pD, fecError);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->usx_fec_error_counter);
        regVal = CPS_REG_READ(regAddr);
        fecError->uncorrect = (uint16_t)EMAC_REGS__USX_FEC_ERROR_COUNTER__FEC_BLOCK_ERROR_COUNT__READ(regVal);
        fecError->correct = (uint16_t)EMAC_REGS__USX_FEC_ERROR_COUNTER__FEC_BLOCK_CORRECTED_COUNT__READ(regVal);

        /* reset counter */
        CPS_REG_WRITE(regAddr, 0U);
    }

    return status;
}

uint32_t CEDI_SetPcs25gEventEnable(CEDI_PrivateData* pD, uint32_t events, bool enable)
{
    uint32_t status;
    uint32_t cbNullError;

    status = CEDI_SetPcs25gEventEnableSF(pD);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        if (enable) {
            cbNullError = pcs25gCbNullChecker(&(pD->cb), events);

            if (cbNullError == 0U) {
                /* enable interrupts by write '1' to usx_interrupt_disable_register */
                CPS_REG_WRITE(&(pD->regs->usx_interrupt_enable_register), events);
            } else {
                status = CDN_EINVAL;
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Warning: Some callbacks are NULL pointers: %u", cbNullError);
            }
        } else {
            /* disable rest of interrupts by write '1' to usx_interrupt_disable_register */
            CPS_REG_WRITE(&(pD->regs->usx_interrupt_disable_register), events);
        }
    }

    return status;
}

uint32_t CEDI_GetPcs25gEventEnable(const CEDI_PrivateData* pD, uint32_t* events)
{
    uint32_t status = CEDI_GetPcs25gEventEnableSF(pD, events);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    /* masks are the same as flags for interrupts */
    if (CDN_EOK == status) {
        *events = CPS_REG_READ(&(pD->regs->usx_interrupt_mask_register));
    }

    return status;
}

/*
 * Function used to check PCS25G synchronization. Number of attemps
 * is described by %P_PCS25G_MAX_POLLING_ATTEMPS. Time beetween each
 * attemp is described by %P_PCS25G_POLLING_WAIT
 * @param[in] specific driver's pD
 * @return CDN_EOK if success
 * @return CDN_EIO if timeout was reached
 */
static uint32_t blockLockPolling(const CEDI_PrivateData* pD)
{
    uint8_t attemps = 0U;
    volatile uint32_t* regAddr = &(pD->regs->usx_status_register);
    uint32_t regVal, linkFaultIndicator;
    bool blockLock = false;
    uint32_t status = CDN_EOK;

    /* Wait for block-lock synchronization */
    do {
        regVal = CPS_REG_READ(regAddr);
        /* Synchronization was achieved when BlockLock is 1U */
        blockLock = (EMAC_REGS__USX_STATUS_REGISTER__BLOCK_LOCK__READ(regVal) == 1U);

        if (blockLock) {
            break;
        } else {
            CPS_DelayNs(CEDI_PCS25G_POLLING_WAIT_NS);
            attemps++;
        }

    } while (attemps < CEDI_PCS25G_MAX_POLLING_ATTEMPS);

    if (!blockLock) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s %d\n",
                "ERROR: Block lock synchronization was not achieved. Attempts =",CEDI_PCS25G_MAX_POLLING_ATTEMPS);
        status = CDN_EIO;
    }

    if (status == CDN_EOK) {
        /* Check if any Rx&Tx Faults */
        attemps = 0U;
        regAddr = &(pD->regs->network_status);

        do {
            regVal = CPS_REG_READ(regAddr);
            linkFaultIndicator = EMAC_REGS__NETWORK_STATUS__LINK_FAULT_INDICATION__READ(regVal);

            /* check if any fault */
            if (linkFaultIndicator == 0U) {
                break;
            } else {
                CPS_DelayNs(CEDI_PCS25G_POLLING_WAIT_NS);
                attemps++;
            }

        } while (attemps < CEDI_PCS25G_MAX_POLLING_ATTEMPS);

        if (attemps == CEDI_PCS25G_MAX_POLLING_ATTEMPS) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "ERROR: Remote fault errors!");
            status = CDN_EIO;
        }
    }

    return status;

}

uint32_t CEDI_SetPcs25gEnable(CEDI_PrivateData* pD, bool enable)
{
    volatile uint32_t* regAddr;
    uint32_t regVal;
    uint32_t status = CEDI_SetPcs25gEnableSF(pD);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->usx_control_register);
        regVal = CPS_REG_READ(regAddr);
        if (enable) {
            EMAC_REGS__USX_CONTROL_REGISTER__SIGNAL_OK__SET(regVal);
        } else {
            EMAC_REGS__USX_CONTROL_REGISTER__SIGNAL_OK__CLR(regVal);
        }

        CPS_REG_WRITE(regAddr, regVal);

        if (enable) {
            status = blockLockPolling(pD);
        }
    }
    return status;
}

uint32_t CEDI_GetPcs25gEnable(const CEDI_PrivateData* pD, bool* enable)
{
    uint32_t regVal;
    uint32_t status = CEDI_GetPcs25gEnableSF(pD, enable);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        regVal = CPS_REG_READ(&(pD->regs->usx_control_register));
        *enable = EMAC_REGS__USX_CONTROL_REGISTER__SIGNAL_OK__READ(regVal) != 0U;
    }
    return status;
}

uint32_t CEDI_Pcs25gSetup(CEDI_PrivateData* pD, const CEDI_Pcs25gCfg* cfg, bool enable)
{
    uint32_t status = CEDI_Pcs25gSetupSF(pD, cfg);
    uint32_t regVal;
    volatile uint32_t* regAddr;


    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {

        /* Write extra data into network_config register */
        regAddr = &(pD->regs->network_config);
        regVal = CPS_REG_READ(regAddr);
        EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__SET(regVal);
        CPS_REG_WRITE(regAddr, regVal);

        /* disable auto-negotiation */
        regAddr = &(pD->regs->pcs_control);
        regVal = CPS_REG_READ(regAddr);
        // Must not do a read-modify-write with soft reset bit set otherwise
        // will cause any writes to be ignored...
        EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__CLR(regVal);
        EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__CLR(regVal);
        CPS_REG_WRITE(regAddr, regVal);
    }

    if (CDN_EOK == status) {
        status = initUsxControlReg(pD, cfg);
    }

    if (CDN_EOK == status) {
        if (enable) {
            regAddr = &(pD->regs->usx_control_register);
            regVal = CPS_REG_READ(regAddr);

            EMAC_REGS__USX_CONTROL_REGISTER__SIGNAL_OK__SET(regVal);
            CPS_REG_WRITE(regAddr, regVal);

            status = blockLockPolling(pD);

        }
    }

    return status;
}


uint32_t CEDI_CheckPcs25gSync(const CEDI_PrivateData* pD)
{
    uint32_t status = CEDI_CheckPcs25gSyncSF(pD);

    if (status == CDN_EOK) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (status == CDN_EOK) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (status == CDN_EOK) {
        status = blockLockPolling(pD);
    }

    return status;
}




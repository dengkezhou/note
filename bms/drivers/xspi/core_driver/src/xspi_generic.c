/******************************************************************************
 *
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * xspi_generic.c
 * This file contains STIG and Direct mode implementation.
 *
 *****************************************************************************/

#include <stdint.h>
#include <string.h>

#include <cps.h>
#include <cdn_log.h>
#include <cdn_errno.h>

#include "xspi_if.h"
#include "xspi_structs_if.h"

#include "xspi_sanity.h"
#include "xspi_priv.h"

#include "xspi_generic.h"
#include "xspi_core.h"

/**
 * Send command in Direct mode
 * @param[in] privateData Pointer to driver private data object
 * @param[in] directCmd Pointer to direct mode command structure
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SendDirectCommand(XSPI_PrivateData * privateData, const XSPI_DirectCmd * directCmd)
{
    uint32_t result = CDN_EOK;
    XSPI_DirectSdmaTransInfo sdmaInfo;

    /* Check parameters */
    if (XSPI_SendDirectCommandSF(privateData, directCmd) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        sdmaInfo.direction = directCmd->direction;
        sdmaInfo.directSdmaBuff = directCmd->sysMemPtr;
        sdmaInfo.transferSize = directCmd->transferSize;
        sdmaInfo.transferAddr = directCmd->transferAddr;

        /* Invoke Slave DMA transaction */
        if (privateData->callbacks.sdmaCb.directSdmaTransactionHandler != NULL) {
            privateData->callbacks.sdmaCb.directSdmaTransactionHandler(privateData, sdmaInfo);
        } else {
            result = CDN_EINVAL;
        }
    }

    return result;
}

/**
 * Checks busy status of Direct command generator module
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_EBUSY when controller is busy
 */
uint32_t XSPI_IsDirectCmdEngBusy(XSPI_PrivateData * privateData)
{
    uint32_t result = CDN_EOK;
    uint32_t ctrl_status_reg;

    /* Check parameters */
    if (XSPI_IsDirectCmdEngBusySF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        ctrl_status_reg = CPS_REG_READ(&privateData->regs->ctrl_status);

        if (CPS_FLD_READ(XSPI__CTRL_STATUS, GCMD_ENG_BUSY, ctrl_status_reg) == 1U) {
            result = CDN_EBUSY;
        }
    }

    return result;
}

/**
 * Internal function
 * Function sets remap address value in direct mode
 */
static uint32_t DirectSetRemapAddr(XSPI_PrivateData * privateData, const XSPI_DirectModeConfig * directModeConfig)
{
    uint32_t result = CDN_EOK;
    uint32_t direct_access_rmp_reg = 0U;
    uint32_t direct_access_rmp_1_reg = 0U;

    /* Check if address remap is enabled */
    if (directModeConfig->remapAddrEn == true) {
        direct_access_rmp_reg = CPS_FLD_WRITE(XSPI__DIRECT_ACCESS_RMP, RMP_ADDR_VAL, direct_access_rmp_reg, DIR_REMAP_ADDR_GET_LOW_DWORD(directModeConfig->remapAddrVal));
        direct_access_rmp_1_reg = CPS_FLD_WRITE(XSPI__DIRECT_ACCESS_RMP_1, RMP_ADDR_VAL_1, direct_access_rmp_1_reg, DIR_REMAP_ADDR_GET_HIGH_DWORD(directModeConfig->remapAddrVal));

        /* Check controller revision */
        if (privateData->ctrlRev >= XSPI_CTRL_REV_R003) {
            CPS_REG_WRITE(&privateData->regs->direct_access_rmp_1, direct_access_rmp_1_reg);
        } else if (direct_access_rmp_1_reg != 0U) {
            /* Below R003 controller revision high dword of remap address value is reserved */
            result = CDN_ENOTSUP;
        } else {
            /* Provide 'else' after the last 'else-if' construct (MISRA2012-RULE-15_7) */
        }

        if (result == CDN_EOK) {
            CPS_REG_WRITE(&privateData->regs->direct_access_rmp, direct_access_rmp_reg);
        }
    }

    return result;
}

/**
 * Internal function
 * Function gets remap address config in direct mode
 */
static void DirectGetRemapAddr(XSPI_PrivateData * privateData, XSPI_DirectModeConfig * directModeConfig)
{
    uint32_t direct_access_cfg_reg = 0U;
    uint32_t direct_access_rmp_reg = 0U;
    uint32_t direct_access_rmp_1_reg = 0U;

    direct_access_cfg_reg = CPS_REG_READ(&privateData->regs->direct_access_cfg);
    direct_access_rmp_reg = CPS_REG_READ(&privateData->regs->direct_access_rmp);

    /* Set remap enabled */
    if (CPS_FLD_READ(XSPI__DIRECT_ACCESS_CFG, RMP_ADDR_EN, direct_access_cfg_reg) == 0U) {
        directModeConfig->remapAddrEn = false;
    } else {
        directModeConfig->remapAddrEn = true;
    }

    /* Get remap address value */
    directModeConfig->remapAddrVal = (uint64_t)0U;

    directModeConfig->remapAddrVal |= DIR_REMAP_ADDR_SET_LOW_DWORD(CPS_FLD_READ(XSPI__DIRECT_ACCESS_RMP, RMP_ADDR_VAL, direct_access_rmp_reg));

    /* Read high dword on R003 controller revision */
    if (privateData->ctrlRev >= XSPI_CTRL_REV_R003) {
        direct_access_rmp_1_reg = CPS_REG_READ(&privateData->regs->direct_access_rmp_1);
    }

    directModeConfig->remapAddrVal |= DIR_REMAP_ADDR_SET_HIGH_DWORD(CPS_FLD_READ(XSPI__DIRECT_ACCESS_RMP_1, RMP_ADDR_VAL_1, direct_access_rmp_1_reg));
}

/**
 * Sets direct work mode config
 * @param[in] privateData Pointer to driver private data object
 * @param[in] directModeConfig Pointer to direct mode config structure
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetDirectModeConfig(XSPI_PrivateData * privateData, const XSPI_DirectModeConfig * directModeConfig)
{
    uint32_t result = CDN_EOK;
    uint32_t direct_access_cfg_reg = 0U;

    /* Check parameters */
    if (XSPI_SetDirectModeConfigSF(privateData, directModeConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        direct_access_cfg_reg = CPS_FLD_WRITE(XSPI__DIRECT_ACCESS_CFG, DAC_ADDR_MASK, direct_access_cfg_reg, directModeConfig->dacAddrMask);
        direct_access_cfg_reg = CPS_FLD_WRITE(XSPI__DIRECT_ACCESS_CFG, RMP_ADDR_EN, direct_access_cfg_reg, ((directModeConfig->remapAddrEn == true) ? 1U : 0U));
        direct_access_cfg_reg = CPS_FLD_WRITE(XSPI__DIRECT_ACCESS_CFG, MODE_BIT_XIP_DIS, direct_access_cfg_reg, ((directModeConfig->disXipMb == true) ? 1U : 0U));
        direct_access_cfg_reg = CPS_FLD_WRITE(XSPI__DIRECT_ACCESS_CFG, MODE_BIT_XIP_EN, direct_access_cfg_reg, ((directModeConfig->enXipMb == true) ? 1U : 0U));
        direct_access_cfg_reg = CPS_FLD_WRITE(XSPI__DIRECT_ACCESS_CFG, DAC_BANK_NUM, direct_access_cfg_reg, directModeConfig->bankSelect);

        if (!privateData->xSpiIot) {
            direct_access_cfg_reg = CPS_FLD_WRITE(XSPI__DIRECT_ACCESS_CFG, AUTO_POLL_DIS, direct_access_cfg_reg, ((directModeConfig->disableAutoPoll == true) ? 1U : 0U));
            direct_access_cfg_reg = CPS_FLD_WRITE(XSPI__DIRECT_ACCESS_CFG, AUTO_WEL_DIS, direct_access_cfg_reg, ((directModeConfig->disableAutoWelInstr == true) ? 1U : 0U));
        }

        CPS_REG_WRITE(&privateData->regs->direct_access_cfg, direct_access_cfg_reg);

        /* Set remap address config */
        result = DirectSetRemapAddr(privateData, directModeConfig);
    }

    return result;
}

/**
 * Gets direct work mode config
 * @param[in] privateData Pointer to driver private data object
 * @param[out] directModeConfig Pointer to direct mode config structure
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetDirectModeConfig(XSPI_PrivateData * privateData, XSPI_DirectModeConfig * directModeConfig)
{
    uint32_t result = CDN_EOK;
    uint32_t direct_access_cfg_reg;

    /* Check parameters */
    if (XSPI_GetDirectModeConfigSF(privateData, directModeConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Read register */
        direct_access_cfg_reg = CPS_REG_READ(&privateData->regs->direct_access_cfg);

        directModeConfig->dacAddrMask = (uint16_t) CPS_FLD_READ(XSPI__DIRECT_ACCESS_CFG, DAC_ADDR_MASK, direct_access_cfg_reg);

        if (!privateData->xSpiIot) {
            if (CPS_FLD_READ(XSPI__DIRECT_ACCESS_CFG, AUTO_POLL_DIS, direct_access_cfg_reg) == 0U) {
                directModeConfig->disableAutoPoll = false;
            } else {
                directModeConfig->disableAutoPoll = true;
            }
            if (CPS_FLD_READ(XSPI__DIRECT_ACCESS_CFG, AUTO_WEL_DIS, direct_access_cfg_reg) == 0U) {
                directModeConfig->disableAutoWelInstr = false;
            } else {
                directModeConfig->disableAutoWelInstr = true;
            }
        }

        if (CPS_FLD_READ(XSPI__DIRECT_ACCESS_CFG, MODE_BIT_XIP_DIS, direct_access_cfg_reg) == 0U) {
            directModeConfig->disXipMb = false;
        } else {
            directModeConfig->disXipMb = true;
        }
        if (CPS_FLD_READ(XSPI__DIRECT_ACCESS_CFG, MODE_BIT_XIP_EN, direct_access_cfg_reg) == 0U) {
            directModeConfig->enXipMb = false;
        } else {
            directModeConfig->enXipMb = true;
        }

        directModeConfig->bankSelect = (uint8_t) CPS_FLD_READ(XSPI__DIRECT_ACCESS_CFG, DAC_BANK_NUM, direct_access_cfg_reg);

        /* Get remap address config */
        DirectGetRemapAddr(privateData, directModeConfig);
    }
    return result;
}

static uint32_t GetP1InstrTypeMap(XSPI_Profile10AutonomicInstrType p10InstrType, uint8_t * instrTypeVal, bool * isInstrLink)
{
    uint32_t result = CDN_EOK;

    switch (p10InstrType) {
        /* SPI NOR instructions */
    case XSPI_P10_INSTR_READ_ARRAY:
    case XSPI_P10_INSTR_READ_ARRAY_XIP:
    case XSPI_P10_INSTR_READ_MEMORY_REGISTER:
    case XSPI_P10_INSTR_READ_JEDEC_ID:
    case XSPI_P10_INSTR_READ_SFDP:
        /* SPI NAND instructions */
    case XSPI_P10_INSTR_SNA_GET_FEATURES:
    case XSPI_P10_INSTR_SNA_READ_ID:
    case XSPI_P10_INSTR_SNA_READ_CACHE:
            
        /* Instructios with type 1 and instr_link field not present (required DATA_SEQ) */
        *instrTypeVal = XSPI_STIG_INSTR_TYPE_1;
        *isInstrLink = false;
        break;
        
        
        /* SPI NOR instructions */
    case XSPI_P10_INSTR_WRITE_ARRAY:
    case XSPI_P10_INSTR_WRITE_MEMORY_REGISTER:
    case XSPI_P10_INSTR_SETUP_READ_BURST:
        
        /* SPI NAND instructions */
    case XSPI_P10_INSTR_SNA_SET_FEATURES:
    case XSPI_P10_INSTR_SNA_PROGRAM_LOAD:
    case XSPI_P10_INSTR_SNA_RAND_PROGRAM_LOAD:
        /* Instructios with type 0 and instr_link field is present (optional DATA_SEQ) */
        *instrTypeVal = XSPI_STIG_INSTR_TYPE_0;
        *isInstrLink = true;
        break;
        
        
        /* SPI NOR instructions */
    case XSPI_P10_INSTR_WRITE_ENABLE_LATCH:
    case XSPI_P10_INSTR_WRITE_DISABLE_LATCH:
    case XSPI_P10_INSTR_ERASE_SECTOR:
    case XSPI_P10_INSTR_CHIP_ERASE:
    case XSPI_P10_INSTR_PROGRAM_ERASE_SUSPEND:
    case XSPI_P10_INSTR_PROGRAM_ERASE_RESUME:
    case XSPI_P10_INSTR_CLEAR_FLAG_REGISTER:
    case XSPI_P10_INSTR_ENTER_DEEP_POWER_DOWN:
    case XSPI_P10_INSTR_EXIT_DEEP_POWER_DOWN:
    case XSPI_P10_INSTR_RESET_ENABLE:
    case XSPI_P10_INSTR_ENTER_DEF_PROT_MODE:
    case XSPI_P10_INSTR_ENABLE_SDR_OCTAL_MODE:
    case XSPI_P10_INSTR_GLOBAL_PROTECTION:
    case XSPI_P10_INSTR_GLOBAL_UNPROTECTION:
    case XSPI_P10_INSTR_PROTECT_SECTOR:
    case XSPI_P10_INSTR_UNPROTECT_SECTOR:
    case XSPI_P10_INSTR_ENTER_4BYTE_ADDR_MODE:
    case XSPI_P10_INSTR_EXIT_4BYTE_ADDR_MODE:
        
        /* SPI NAND instructions */
    case XSPI_P10_INSTR_SNA_READ_PAGE:
    case XSPI_P10_INSTR_SNA_LAST_READ_PAGE_CACHE:
    case XSPI_P10_INSTR_SNA_RAND_READ_PAGE_CACHE:
    case XSPI_P10_INSTR_SNA_PROGRAM_EXEC:
        /* Instructios with type 0 and instr_link field not present (no DATA_SEQ) */
        *instrTypeVal = XSPI_STIG_INSTR_TYPE_0;
        *isInstrLink = false;
        break;

    case XSPI_P10_INSTR_SOFT_RESET:
        /* Instructios with type 2 and instr_link field not present */
        *instrTypeVal = XSPI_STIG_INSTR_TYPE_2;
        *isInstrLink = false;
        break;
    default:
        /* Invalid Profile 1 instruction */
        result = CDN_EINVAL;
        break;
    }
    return result;
}

static void GetP2InstrTypeMap(XSPI_Profile20AutonomicInstrType p20InstrType, uint8_t *instrTypeVal, bool *isInstrLink)
{
    /* Check if Instruction link field is present */
    if ((p20InstrType == XSPI_P20_INSTR_CMD_CODE_SEQ) || (p20InstrType == XSPI_P20_INSTR_WRITE_ARRAY)) {
        *isInstrLink = true;
    } else {
        *isInstrLink = false;
    }
    /* Set Instruction type parameter */
    *instrTypeVal = (uint8_t) p20InstrType;
}

/* parasoft-begin-suppress MISRA2012-RULE-12_2-2 "Shifting operation should be checked, DRV-4036" */

static void StigInstrFillAddrBytes(uint64_t address, uint32_t * cmdReg)
{
    uint8_t addr[6] = {0}, i;
    uint64_t pAddr = address;
    uint32_t addr_h,addr_l, * ptr;
    ptr = (uint32_t *)(&pAddr) ;
    addr_l = *ptr;
    addr_h = *(ptr+1);

    const uint8_t addrPhaseNumBytes = 6;

    /* Extract address into individual bytes */
    for (i = 0; i < addrPhaseNumBytes; i++) {
        //addr[i] = (uint8_t) ((p2Addr >> (i * 8)) & 0xFFULL);
        if(i < 4){
            addr[i] = (uint8_t) ((addr_l >> (i * 8)) & 0xFF );
        }else{
            addr[i] = (uint8_t) ((addr_h >> ( (i-4) * 8)) & 0xFF);
        }
    }
    /*
    const uint8_t addrPhaseNumBytes = 6U;

    for (i = 0U; i < addrPhaseNumBytes; i++) {
        addr[i] = (uint8_t) ((address >> (i * 8U)) & 0xFFULL);
    }
    */
    /* Fill address bytes into corresponding register values */
    cmdReg[3] |= STIG_FLD_ADDR_5(addr);

    cmdReg[2] |= STIG_FLD_ADDR_4(addr);
    cmdReg[2] |= STIG_FLD_ADDR_3(addr);
    cmdReg[2] |= STIG_FLD_ADDR_2(addr);
    cmdReg[2] |= STIG_FLD_ADDR_1(addr);

    cmdReg[1] |= STIG_FLD_ADDR_0(addr);
}

/* Internal function */
static void StigInstrP2FillAddrBytes(uint64_t address, uint32_t * cmdReg)
{
    uint8_t addr[6] = {0}, i;
    uint64_t p2Addr = address;
    
    uint32_t addr_h,addr_l, * ptr;
    ptr = (uint32_t *)(&p2Addr) ;
    addr_l = *ptr;
    addr_h = *(ptr+1);

    const uint8_t addrPhaseNumBytes = 6;

    /* Extract address into individual bytes */
    for (i = 0; i < addrPhaseNumBytes; i++) {
        //addr[i] = (uint8_t) ((p2Addr >> (i * 8)) & 0xFFULL);
        if(i < 4){
            addr[i] = (uint8_t) ((addr_l >> (i * 8)) & 0xFF );
        }else{
            addr[i] = (uint8_t) ((addr_h >> ( (i-4) * 8)) & 0xFF);
        }
    }

    /* Fill address bytes into corresponding register values */
    cmdReg[3] |= STIG_FLD_ADDR_BIT_44(addr[5]);
    cmdReg[3] |= STIG_FLD_ADDR_BIT_43(addr[5]);
    cmdReg[3] |= STIG_FLD_ADDR_BIT_42(addr[5]);
    cmdReg[3] |= STIG_FLD_ADDR_BIT_41(addr[5]);
    cmdReg[3] |= STIG_FLD_ADDR_BIT_40(addr[5]);

    cmdReg[2] |= STIG_FLD_ADDR_4(addr);
    cmdReg[2] |= STIG_FLD_ADDR_3(addr);
    cmdReg[2] |= STIG_FLD_ADDR_2(addr);
    cmdReg[2] |= STIG_FLD_ADDR_1(addr);

    cmdReg[1] |= STIG_FLD_ADDR_0(addr);
}

static void StigWriteInstruction(XSPI_PrivateData * privateData, uint32_t cmd_reg[5])
{
    /* Fill the registers as per calculated values */
    CPS_REG_WRITE(&privateData->regs->cmd_reg4, cmd_reg[4]);
    CPS_REG_WRITE(&privateData->regs->cmd_reg3, cmd_reg[3]);
    CPS_REG_WRITE(&privateData->regs->cmd_reg2, cmd_reg[2]);
    CPS_REG_WRITE(&privateData->regs->cmd_reg1, cmd_reg[1]);

    /* Trigger the instruction */
    CPS_REG_WRITE(&privateData->regs->cmd_reg0, cmd_reg[0]);
}

static void StigInstrSetCommonParams(uint8_t bankSelect, bool crcEnable, uint32_t * cmd_reg)
{
    /* Set fields common for all instructions */
    cmd_reg[4] |= (crcEnable == true) ? STIG_FLD_CRC_EN(1U) : STIG_FLD_CRC_EN(0U);
    cmd_reg[4] |= STIG_FLD_BANK(bankSelect);
}

static void StigP1InstrFillBoolFields(XSPI_StigProfile10Layout config, uint32_t * cmd_reg, bool isInstrLink)
{
    /* Calculate value to be filled in cmd_reg4 register */ 
    if ((isInstrLink == true) && (config.dataNoOfBytes == 0U)) {
        cmd_reg[4] |= STIG_FLD_INSTR_LINK(1U);
    } else {
        cmd_reg[4] |= STIG_FLD_INSTR_LINK(0U);
    }

    /* Set ADDR_SHIFT field */
    if (config.addrShift) {
        cmd_reg[4] |= STIG_FLD_ADDR_SHIFT(1U);
    } else {
        cmd_reg[4] |= STIG_FLD_ADDR_SHIFT(0U);
    }
    
    /* XIP mode and command phase extension enable */
    cmd_reg[4] |= (config.xipEnable == true) ? STIG_FLD_XIP_EN(1U) : STIG_FLD_XIP_EN(0U);
    cmd_reg[4] |= (config.instrOpcodeExt.enable == true) ? STIG_FLD_OPCODE_EXT_EN(1U) : STIG_FLD_OPCODE_EXT_EN(0U);
    
    /* DATA[0] DATA[1] fields */
    if (config.dataNoOfBytes != 0U) {
        cmd_reg[1] |= STIG_FLD_DATA(config.data);
    }
}

/* Prepare and send Profile 1 instruction */
static uint32_t XSPI_SendP1Instr(XSPI_PrivateData *privateData, XSPI_StigProfile10Layout config, uint8_t bankSelect, bool crcEnable)
{
    uint32_t result = CDN_EOK;
    uint8_t instrTypeVal;
    bool isInstrLink;
    uint32_t cmd_reg[5] = {0};
    XSPI_SeqCommandPhase *cmdPhase;
    XSPI_SeqAddressPhase *addrPhase;
    XSPI_SeqCommandExtension *cmdExt;

    cmdPhase = &config.instrOpcodePhase;
    addrPhase = &config.instrAddrPhase;
    cmdExt = &config.instrOpcodeExt;

    /* Get Instruction type and instr_link fields for current instruction */ 
    result = GetP1InstrTypeMap(config.profile10InstrType, &instrTypeVal, &isInstrLink);
    
    if (result == CDN_EOK) {
        
        StigP1InstrFillBoolFields(config, cmd_reg, isInstrLink);
        
        cmd_reg[4] |= STIG_FLD_CRC_VARIANT(config.crcVariant);

        StigInstrSetCommonParams(bankSelect, crcEnable, cmd_reg);

        cmd_reg[4] |= STIG_FLD_OPCODE_EDGE_MODE(cmdPhase->edge);
        cmd_reg[4] |= STIG_FLD_OPCODE_NO_OF_IOS(cmdPhase->ios);

        cmd_reg[4] |= STIG_FLD_ADDR_EDGE_MODE(addrPhase->edge);
        cmd_reg[4] |= STIG_FLD_ADDR_NO_OF_IOS(addrPhase->ios);

        /* Calculate value to be filled in cmd_reg3 register */ 
        cmd_reg[3] |= STIG_FLD_ADDR_NO_OF_BYTES(addrPhase->count);
        cmd_reg[3] |= STIG_FLD_DATA_NO_OF_BYTES(config.dataNoOfBytes);
        cmd_reg[3] |= STIG_FLD_CMD(cmdPhase->value);
        cmd_reg[3] |= STIG_FLD_CMD_EXT(cmdExt->value);

        /* Set address bytes */
        StigInstrFillAddrBytes(config.address, cmd_reg);

        cmd_reg[1] |= STIG_FLD_INSTR_TYPE(instrTypeVal);
        
        cmd_reg[0] = 0U;

        /* Write STIG instruction */
        StigWriteInstruction(privateData, cmd_reg);
    }
    return result;
}

static void StigP2InstrFillBoolFields(XSPI_StigProfile20Layout config, uint32_t * cmd_reg, bool isInstrLink)
{
    /* Set TCMS_EN field */
    if (config.tCmsEn) {
        cmd_reg[4] |= STIG_FLD_TCMS_EN(1U);
    } else {
        cmd_reg[4] |= STIG_FLD_TCMS_EN(0U);
    }
    
    /* Calculate value to be filled in cmd_reg4 register */ 
    if ((isInstrLink == true) && (config.dataNoOfBytes == 0U)) {
        cmd_reg[4] |= STIG_FLD_INSTR_LINK(1U);
    } else {
        cmd_reg[4] |= STIG_FLD_INSTR_LINK(0U);
    }
    
    cmd_reg[4] |= (config.extCmdModEnable == true) ? STIG_FLD_EXT_CMD_MOD_EN(1U) : STIG_FLD_EXT_CMD_MOD_EN(0U);
    
    /* Calculate value to be filled in cmd_reg3 register */ 
    cmd_reg[3] |= STIG_FLD_DATA_NO_OF_BYTES(config.dataNoOfBytes);
    cmd_reg[3] |= (config.rw == XSPI_DATA_TRANS_DIR_READ) ? STIG_FLD_RW(1U) : STIG_FLD_RW(0U);
    cmd_reg[3] |= (config.target == XSPI_TARGET_SPACE_REGISTER) ? STIG_FLD_TARGET(1U) : STIG_FLD_TARGET(0U);
    cmd_reg[3] |= (config.burstType == XSPI_BURST_TYPE_LINEAR) ? STIG_FLD_BURST_TYPE(1U) : STIG_FLD_BURST_TYPE(0U);
}

/* Prepare and send Profile 2 instruction */
static uint32_t XSPI_SendP2Instr(XSPI_PrivateData *privateData, XSPI_StigProfile20Layout config, uint8_t bankSelect, bool crcEnable)
{
    uint32_t result = CDN_EOK;
    uint32_t cmd_reg[5] = {0};
    uint8_t instrTypeVal;
    bool isInstrLink;

    /* Get Instruction type and instr_link fields for current instruction */ 
    GetP2InstrTypeMap(config.profile20InstrType, &instrTypeVal, &isInstrLink);
    
    /* Set bool type fields */
    StigP2InstrFillBoolFields(config, cmd_reg, isInstrLink);

    /* Set common parameters */
    StigInstrSetCommonParams(bankSelect, crcEnable, cmd_reg);

    /* Set address bytes */
    StigInstrP2FillAddrBytes(config.address, cmd_reg);

    if (config.dataNoOfBytes != 0U) {
        cmd_reg[1] |= STIG_FLD_DATA(config.data);
    }
    cmd_reg[1] |= STIG_FLD_INSTR_TYPE(instrTypeVal);

    cmd_reg[0] = 0U;

    /* Write STIG instruction */
    StigWriteInstruction(privateData, cmd_reg);
    
    return result;
}

/* Prepare and send Generic instruction */
static void XSPI_SendGenericInstr(XSPI_PrivateData *privateData, XSPI_StigGenericCmdLayout config, uint8_t bankSelect, bool crcEnable, bool isLink)
{
    uint32_t cmd_reg[5] = {0};
    const uint8_t *bytes;

    bytes = config.bytes;
    /* Calculate value to be filled in cmd_reg4 register */ 
    cmd_reg[4] |= (isLink == true) ? STIG_FLD_INSTR_LINK(1U) : STIG_FLD_INSTR_LINK(0U);

    StigInstrSetCommonParams(bankSelect, crcEnable, cmd_reg);

    cmd_reg[4] |= STIG_FLD_OPCODE_EDGE_MODE(config.edgeMode);
    cmd_reg[4] |= STIG_FLD_OPCODE_NO_OF_IOS(config.noOfIos);

    /* Calculate value to be filled in cmd_reg3 register */ 
    cmd_reg[3] |= STIG_FLD_GEN_INSTR_NO_OF_BYTES(config.noOfBytes);
    cmd_reg[3] |= STIG_FLD_GEN_INSTR_BYTE_9(bytes);
    cmd_reg[3] |= STIG_FLD_GEN_INSTR_BYTE_8(bytes);
    cmd_reg[3] |= STIG_FLD_GEN_INSTR_BYTE_7(bytes);

    /* Calculate value to be filled in cmd_reg2 register */ 
    cmd_reg[2] |= STIG_FLD_GEN_INSTR_BYTE_6(bytes);
    cmd_reg[2] |= STIG_FLD_GEN_INSTR_BYTE_5(bytes);
    cmd_reg[2] |= STIG_FLD_GEN_INSTR_BYTE_4(bytes);
    cmd_reg[2] |= STIG_FLD_GEN_INSTR_BYTE_3(bytes);

    /* Calculate value to be filled in cmd_reg1 register */ 
    cmd_reg[1] |= STIG_FLD_GEN_INSTR_BYTE_2(bytes);
    cmd_reg[1] |= STIG_FLD_GEN_INSTR_BYTE_1(bytes);
    cmd_reg[1] |= STIG_FLD_GEN_INSTR_BYTE_0(bytes);
    cmd_reg[1] |= STIG_FLD_INSTR_TYPE(XSPI_STIG_INSTR_TYPE_GEN_CMD_SEQ);

    cmd_reg[0] = 0U;

    /* Write STIG instruction */
    StigWriteInstruction(privateData, cmd_reg);
}

static void StigDataInstrFillBoolParams(const XSPI_StigDataSeqLayout *config, uint32_t * cmd_reg)
{
    /* Set CRC_INV field */
    if (config->crcInversion) {
        cmd_reg[4] |= STIG_FLD_CRC_INV(1U);
    } else {
        cmd_reg[4] |= STIG_FLD_CRC_INV(0U);
    }
    
    /* CRC parameters */
    cmd_reg[4] |= (config->crcOe == true) ? STIG_FLD_CRC_OE(1U) : STIG_FLD_CRC_OE(0U);
    cmd_reg[4] |= (config->crcUalChunkEn == true) ? STIG_FLD_CRC_UAL_CHUNK_EN(1U) : STIG_FLD_CRC_UAL_CHUNK_EN(0U);
    cmd_reg[4] |= (config->crcUalChunkChk == true) ? STIG_FLD_CRC_UAL_CHUNK_CHK(1U) : STIG_FLD_CRC_UAL_CHUNK_CHK(0U);
    
    /* Data swap */
    cmd_reg[4] |= (config->dataSwap == true) ? STIG_FLD_DATA_SWAP(1U) : STIG_FLD_DATA_SWAP(0U);
    
    /* Transaction direction */
    cmd_reg[4] |= (config->dir == XSPI_DATA_TRANS_DIR_WRITE) ? STIG_FLD_TRANSFER_DIR(1U) : STIG_FLD_TRANSFER_DIR(0U);
    
    /* Crossing boundary read enable */
    cmd_reg[3] |= (config->hfReadBoundEnable == true) ? STIG_FLD_HF_READ_BOUND_EN(1U) : STIG_FLD_HF_READ_BOUND_EN(0U);
}

/* Prepare and send Data sequence instruction */
static uint32_t XSPI_SendDataInstr(XSPI_PrivateData *privateData, const XSPI_StigDataSeqLayout *config, uint8_t bankSelect, bool crcEnable)
{
    uint32_t result = CDN_EOK;
    uint32_t cmd_reg[5] = {0};

    if (config != NULL) {

        /* Fill bool parameters for data sequence */
        StigDataInstrFillBoolParams(config, cmd_reg);

        /* Calculate value to be filled in cmd_reg4 register */ 
        cmd_reg[4] |= STIG_FLD_CRC_CHUNK_SIZE(config->crcChunkSize);

        StigInstrSetCommonParams(bankSelect, crcEnable, cmd_reg);

        cmd_reg[4] |= STIG_FLD_DATA_EDGE_MODE(config->instrDataPhase.edge);
        cmd_reg[4] |= STIG_FLD_DATA_NO_OF_IOS(config->instrDataPhase.ios);

        /* Calculate value to be filled in cmd_reg3 register */ 
        cmd_reg[3] |= STIG_FLD_DATA_PER_ADDR(config->dataPerAddress);
        cmd_reg[3] |= STIG_FLD_NO_OF_DUMMY(config->noOfDummy);
        cmd_reg[3] |= (config->dataNoOfBytes & 0xFFFF0000U) >> 16U;

        /* Calculate value to be filled in cmd_reg2 register */ 
        cmd_reg[2] = (config->dataNoOfBytes & 0x0000FFFFU) << 16U;

        /* Calculate value to be filled in cmd_reg1 register */
        if (config->dir == XSPI_DATA_TRANS_DIR_READ) {
            cmd_reg[1] |= STIG_FLD_STATUS_SOURCE(config->rdMode);
            if (config->rdMode == XSPI_READ_DATA_EXTENDED_MODE) {
                /* Save Slave DMA buffer pointer */
                privateData->stigSdmaBuff = config->sysMemPtr;
            } else {
                privateData->stigSdmaBuff = 0U;
            }
        } else {
            privateData->stigSdmaBuff = config->sysMemPtr;
        }
        cmd_reg[1] |= STIG_FLD_INSTR_TYPE(XSPI_STIG_INSTR_TYPE_DATA_SEQ);

        /* Enable stig done notification */
        cmd_reg[0] = 1U;

        /* Write STIG instruction */
        StigWriteInstruction(privateData, cmd_reg);
    }

    return result;
}

/*
 * Sends STIG JEDEC RESET command
 * @param[in] privateData  Pointer to driver private data object
 * @param[in] bankSelect   Selected bank to which JEDEC RESET instruction should be sent
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP if controller version is below R003
 */
uint32_t XSPI_SendStigJedecReset(XSPI_PrivateData *privateData, uint8_t bankSelect)
{
    uint32_t result = CDN_EOK;
    uint32_t cmd_reg[5] = {0};

    /* Check parameters */
    if (XSPI_SendStigJedecResetSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Check controller version */
        if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {
            result = CDN_ENOTSUP;
        } else {
            /* Set target device */
            cmd_reg[4] |= STIG_FLD_BANK((uint8_t) bankSelect);

            /* Set instruction type to 2 (reset instruction) */
            cmd_reg[0] |= XSPI_STIG_INSTR_TYPE_2;
            cmd_reg[4] |= STIG_FLD_JEDEC_RST_VARIANT;

            /* Fill the registers as per calculated values */
            CPS_REG_WRITE(&privateData->regs->cmd_reg4, cmd_reg[4]);
            CPS_REG_WRITE(&privateData->regs->cmd_reg3, cmd_reg[3]);
            CPS_REG_WRITE(&privateData->regs->cmd_reg2, cmd_reg[2]);
            CPS_REG_WRITE(&privateData->regs->cmd_reg1, cmd_reg[1]);

            /* Trigger the instruction */
            CPS_REG_WRITE(&privateData->regs->cmd_reg0, cmd_reg[0]);
        }
    }

    return result;
}

/* parasoft-end-suppress MISRA2012-RULE-12_2-2 */

static uint32_t StigSpiNandHwCheck(const XSPI_PrivateData *privateData, const XSPI_StigCommand *stigCommand)
{
    uint8_t i;
    uint32_t result = CDN_EOK;
    
    /* Checks if current controller version supports SPI NAND instructions */
    if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {
        for (i = 0U; i < stigCommand->instrChainLength; i++) {

            switch (stigCommand->instructionChain[i].profile10Instr.profile10InstrType) {
                case XSPI_P10_INSTR_SNA_GET_FEATURES:
                case XSPI_P10_INSTR_SNA_PROGRAM_EXEC:
                case XSPI_P10_INSTR_SNA_PROGRAM_LOAD:
                case XSPI_P10_INSTR_SNA_RAND_PROGRAM_LOAD:
                case XSPI_P10_INSTR_SNA_READ_CACHE:
                case XSPI_P10_INSTR_SNA_READ_ID:
                case XSPI_P10_INSTR_SNA_READ_PAGE:
                case XSPI_P10_INSTR_SNA_LAST_READ_PAGE_CACHE:
                case XSPI_P10_INSTR_SNA_RAND_READ_PAGE_CACHE:
                case XSPI_P10_INSTR_SNA_SET_FEATURES:
                    result = CDN_ENOTSUP;
                    break;

                default:
                    result = CDN_EOK;
                    break;
            }
            
            /* Found some SPI NAND instruction on R002 hardware */
            if (result == CDN_ENOTSUP) {
                break;
            }
        }
    }
    
    return result;
}

static uint32_t StigIterateOverInstrChain(XSPI_PrivateData *privateData, const XSPI_StigCommand *stigCommand)
{
    uint8_t i;
    uint32_t result = CDN_EOK;
    uint8_t bankSelect = (uint8_t) stigCommand->commBankSelect;
    bool genSeqInstrLink = false;
    
    /* Iterate through instruction sequence array */
    for (i = 0U; i < stigCommand->instrChainLength; i++) {
        if (stigCommand->instructionChain[i].stigInstrType == XSPI_STIG_INSTR_TYPE_PROFILE_10) {
            
            /* Send P10 instruction */
            result = XSPI_SendP1Instr(privateData, (stigCommand->instructionChain[i].profile10Instr), bankSelect, stigCommand->commCrcEnable);
            
        } else if (stigCommand->instructionChain[i].stigInstrType == XSPI_STIG_INSTR_TYPE_PROFILE_20) {
            
            /* Send P20 instruction */
            result = XSPI_SendP2Instr(privateData, (stigCommand->instructionChain[i].profile20Instr), bankSelect, stigCommand->commCrcEnable);
            
        } else if (stigCommand->instructionChain[i].stigInstrType == XSPI_STIG_INSTR_TYPE_GENERIC_SEQ) {
            
            /* If this Generic instruction is the last in the chain with no data sequence, set instr_link field to 0 */
            if ((i == (stigCommand->instrChainLength - 1U)) && (stigCommand->dataSeqInstr == NULL)) {
                genSeqInstrLink = false;
            }
            XSPI_SendGenericInstr(privateData, (stigCommand->instructionChain[i].genCmdInstr), bankSelect, stigCommand->commCrcEnable, genSeqInstrLink);
        } else {
            result = CDN_EINVAL;
        }
    }
    
    return result;
}

/**
 * Sends STIG command for execution
 * @param[in] privateData Pointer to driver private data object
 * @param[in] stigCommand Pointer to STIG command
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SendStigCommand(XSPI_PrivateData *privateData, XSPI_StigCommand *stigCommand)
{
    uint32_t result = CDN_EOK;
    uint8_t bankSelect;

    /* Check parameters */
    if (XSPI_SendStigCommandSF(privateData, stigCommand) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        bankSelect = (uint8_t) stigCommand->commBankSelect;
        
        result = StigSpiNandHwCheck((const XSPI_PrivateData *)privateData, (const XSPI_StigCommand *)stigCommand);
        
        if (result == CDN_EOK) {
            result = StigIterateOverInstrChain(privateData, (const XSPI_StigCommand *)stigCommand);
        }

        /* Data sequence instuction must be sent last in the sequence */
        if (result == CDN_EOK) {
            result = XSPI_SendDataInstr(privateData, stigCommand->dataSeqInstr, bankSelect, stigCommand->commCrcEnable);
        }
    }

    return result;
}

/**
 * Gets last command status (in STIG work mode)
 * @param[in] privateData Pointer to driver private data object
 * @param[out] stigCommand Stig command containing status information
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetStigStatus(XSPI_PrivateData *privateData, XSPI_StigCommand *stigCommand)
{
    uint32_t result = CDN_EOK;
    XSPI_CommandStatusInfo *statusInfo;

    /* Check parameters */
    if (XSPI_GetStigStatusSF(privateData, stigCommand) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        statusInfo = &(stigCommand->statusInfo);

        /* Get last command status */
        XSPI_GetLastCommandStatus(privateData, statusInfo, false);

        /* Read data from status for short read */
        if (statusInfo->status == XSPI_COMMAND_STATUS_SUCCESS) {
            if ((stigCommand->dataSeqInstr != NULL) && (stigCommand->dataSeqInstr->rdMode == XSPI_READ_DATA_SHORT_MODE)) {
                if (stigCommand->dataSeqInstr->dataNoOfBytes == 2U) {
                    statusInfo->dataFromDevice[1] = (uint8_t) ((statusInfo->statusValue >> 16U) & 0xFFU);
                    statusInfo->dataFromDevice[0] = (uint8_t) ((statusInfo->statusValue >> 24U) & 0xFFU);
                } else {
                    statusInfo->dataFromDevice[0] = (uint8_t) ((statusInfo->statusValue >> 16U) & 0xFFU);
                }
            }
        }
    }

    return result;
}

/**********************************************************************
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          api-generator: 13.06.f48696b
 *          Do not edit it manually.
 **********************************************************************
 * Cadence Core driver for eXpanded Serial Peripheral Interface
 **********************************************************************/

#ifndef XSPI_PRIV_H
#define XSPI_PRIV_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */
/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure, DRV-4932" */



/** @defgroup ConfigInfo  Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
/** Controller magic number (FULL configuration) */
#define	XSPI_MAGIC_NUMBER_FULL_CONFIG 0x6522U

/** Controller magic number (IOT configuration) */
#define	XSPI_MAGIC_NUMBER_IOT_CONFIG 0x6523U

/** Instruction type 0 */
#define	XSPI_STIG_INSTR_TYPE_0 0U

/** Instruction type 1 */
#define	XSPI_STIG_INSTR_TYPE_1 1U

/** Instruction type 2 */
#define	XSPI_STIG_INSTR_TYPE_2 2U

/** Generic Instruction type */
#define	XSPI_STIG_INSTR_TYPE_GEN_CMD_SEQ 96U

/** Data Instruction type */
#define	XSPI_STIG_INSTR_TYPE_DATA_SEQ 127U

/**
 *  @}
 */


/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */


/**********************************************************************
 * Forward declarations
 **********************************************************************/
typedef struct XSPI_CdmaCommandDescriptor_s XSPI_CdmaCommandDescriptor;

/**********************************************************************
 * Structures and unions
 **********************************************************************/
/** XSPI Private data structure */
struct XSPI_PrivateData_s
{
    /** xSPI registers */
    volatile XSPI_Regs* regs;
    /** Base address of CDMA descriptors */
    uintptr_t cdmaCmdsDescBase;
    /** Max number of CDMA commands allocated in memory (in R004 applicable only for FULL/FULL_ASF configuration) */
    uint8_t cdmaCmdsMaxNum;
    /** Controller callbacks */
    XSPI_Callbacks callbacks;
    /** Controller supported features */
    XSPI_CtrlFeaturesInfo ctrlFeatures;
    /** Controller version info */
    XSPI_VersionInfo ctrlVersion;
    /** Controller revision */
    XSPI_ControllerRevision ctrlRev;
    /** Stig SDMA buffer pointer for extended read mode */
    uintptr_t stigSdmaBuff;
    /** Indicates if last command was ignored by controller */
    bool lastCommandIgnored;
    /** Base address of xSPI registers */
    volatile XSPI_Regs* legacyStatSeqReg6Addr;
    /** Denotes if IOT configuration detected */
    bool xSpiIot;
    /** Read-only number of threads */
    uint8_t maxThreadNum;
};

/** CDMA descriptor */
struct XSPI_CdmaCommandDescriptor_s
{
    /** Next descriptor pointer */
    uint64_t nextDescPtr;
    /** System memory pointer */
    uint64_t sysMemPtr;
    /** xSPI pointer (since R003, field is split into ROW and COLUMN addresses for SPI NAND devices) */
    uint64_t xSpiPtr;
    /** Reserved space */
    uint64_t reserved;
    /** Command type */
    uint16_t cmdType;
    /** Command flags */
    uint16_t cmdFlags;
    /** Command count */
    uint32_t cmdCounter;
    /** Command status */
    uint32_t status;
    /** Padding to fit size = 48B */
    uint32_t __padding;
};

/**
 *  @}
 */

/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif	/* XSPI_PRIV_H */

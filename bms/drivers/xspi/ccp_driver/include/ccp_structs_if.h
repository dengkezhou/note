/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure, DRV-4932" */
/**********************************************************************
 * Copyright (C) 2014-2020 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          api-generator: 13.05.b3ee589
 *          Do not edit it manually.
 **********************************************************************
 * Cadence Combo PHY Core Driver
 **********************************************************************/
#ifndef CCP_STRUCTS_IF_H
#define CCP_STRUCTS_IF_H

#include "cdn_stdtypes.h"
#include "ccp_if.h"

/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * Structures and unions
 **********************************************************************/
/** "The structure that contains the resource requirements for driver operation." */
struct CCP_SysReq_s
{
    /** "@details The number of bytes required for driver operation." */
    uint32_t privDataSize;
};

/** "Configuration parameters passed to probe and init." */
struct CCP_Config_s
{
    /** PHY Registry read access callback. */
    CCP_ReadPhyReg readPhyReg;
    /** PHY Registry write access callback. */
    CCP_WritePhyReg writePhyReg;
};

struct CCP_PrivateData_s
{
    CCP_Regs* regs;
    /** "Config info supplied to init." */
    CCP_Config cfg;
};

/** Controls the DQ related timing. */
struct CCP_PhyDqTimingReg_s
{
    uint8_t ioMaskAlwaysOn;
    uint8_t ioMaskEnd;
    uint8_t ioMaskStart;
    uint8_t dataClkperiodDelay;
    /** Defines the DQ pad dynamic termination select enable time. */
    uint8_t dataSelectTselStart;
    /** Adjusts the starting point of the DQ pad output enable window. */
    uint8_t dataSelectTselEnd;
    /** Defines the DQ pad dynamic termination select disable time. */
    uint8_t dataSelectOeStart;
    /** Adjusts the starting point of the DQ pad output enable window. */
    uint8_t dataSelectOeEnd;
};

/** Controls the DQS related timing. */
struct CCP_PhyDqsTimingReg_s
{
    /** Defines additional latency on the write DQS path. */
    uint8_t dqsClkPeriodDelay;
    /** Field to choose lpbk_dqs to capture data for reads. */
    uint8_t useExtLpbkDqs;
    /** Field choose lpbk_dqs to capture data for reads. */
    uint8_t useLpbkDqs;
    /** Use Phony DQS. */
    uint8_t usePhonyDqs;
    /** Field to choose phony DQS cmd. */
    uint8_t usePhonyDqsCmd;
    /** Phony DQS select. */
    uint8_t phonyDqsSel;
    /** Defines the DQ pad dynamic termination select enable time. */
    uint8_t dqsSelectTselStart;
    /** Defines the DQ pad dynamic termination select disable time. */
    uint8_t dqsSelectTselEnd;
    /** Adjusts the starting point of the DQS pad output enable window. */
    uint8_t dqsSelectOeStart;
    /** Adjusts the ending point of the DQS pad output enable window. */
    uint8_t dqsSelectOeEnd;
};

/**
 * Controls the gate and loopback control related timing.
 * All the reserved fields must be set to 0.
*/
struct CCP_PhyGateLpbkCtrlReg_s
{
    /** Defines the method of transfering the data from DQS domain flops to the clk_phy clock domain. */
    uint8_t syncMethod;
    /** DQS Phase bypass. */
    uint8_t swDqsPhaseBypass;
    /** Enables the software half cycle shift. */
    uint8_t enSwHalfCycle;
    /** Software half cycle shift effect. */
    uint8_t swHalfCycleShift;
    /** DLL Phase Detect Selector for DQS OE generation. */
    uint8_t paramPhaseDetectSelOe;
    /** Defines the read data delay. */
    uint8_t rdDelSel;
    /** Defines the read data delay for the empty signal generated based on the incoming DQS strobes. */
    uint8_t rdDelSelEmpty;
    /** Sets the cycle delay between the LFSR and loopback error check logic. */
    uint8_t lpbkErrCheckTiming;
    /** Selects data output type for phy_obs_reg_0[23:8]. */
    uint8_t lpbkFailMuxsel;
    /** Loopback control. */
    uint8_t loopbackControl;
    /** Controls the loopback read multiplexer. */
    uint8_t lpbk_internal;
    /** Controls internal write multiplexer. */
    uint8_t lpbkEn;
    /** This parameter cause the gate to be always on. */
    uint8_t gateCfgAlwaysOn;
    /** Extend the closing of the DQS gate */
    uint8_t gateCfgClose;
    /** Coarse adjust of gate open time. */
    uint8_t gateCfg;
};

/** This register holds the control for the Master DLL logic. */
struct CCP_PhyDllMasterCtrlReg_s
{
    /** This register holds the control for the Master DLL logic. */
    uint8_t paramDllBypassMode;
    /** Selects the number of delay elements to be inserted between the phase detect flip-flops. */
    uint8_t paramPhaseDetectSel;
    /** Holds the number of consecutive increment or decrement .indications */
    uint8_t paramDllLockNum;
    /** This value is the initial delay value for the DLL. */
    uint8_t paramDllStartPoint;
};

/** This register holds the control for the slave DLL logic. All reserved fields must be set to 0. */
struct CCP_PhyDllSlaveCtrlReg_s
{
    /** Controls the read command DQS delay */
    uint8_t readDqsCmdDelay;
    /** Controls the clk_wrdqs delay line. */
    uint8_t clkWrdqsDelay;
    /** Controls the clk_wr delay line. */
    uint8_t clkWrDelay;
    /** Controls the read DQS delay. */
    uint8_t readDqsDelay;
};

/** This register controls the DQS related timing. */
struct CCP_PhyIeTimingReg_s
{
    /** Forces the input enable(s) to be on always. */
    uint8_t ieAlwaysOn;
    /** Define the start position for the DQ input enable. */
    uint8_t dqIeStart;
    /** Define the stop position for the DQ input enable. */
    uint8_t dqIeStop;
    /** Define the start position for the DQS input enable. */
    uint8_t dqsIeStart;
    /** Define the stop position for the DQS input enable. */
    uint8_t dqsIeStop;
    /** Specifies the number of clocks of delay for the dfi_rddata_en signal. */
    uint8_t rddataEnIeDly;
};

/** This register holds the following observable points in the PHY. */
struct CCP_PhyObsReg0_s
{
    /** CMD Status signal to indicate that the logic gate was closed. */
    uint8_t dqsCmdOverflow;
    /** CMD Status signal to indicate that the logic gate had to be forced closed. */
    uint8_t dqsCmdUnderrun;
    /** Status signal to indicate that the logic gate was closed too late. */
    uint8_t dqsOverflow;
    /** Status signal to indicate that the logic gate had to be forced closed. */
    uint8_t dqsUnderrun;
    /** Loopback DQ  errors data. */
    uint16_t lpbkDqData;
    /** Loopback status. */
    uint8_t lpbkStatus;
};

/** This register holds the following observable points in the PHY. */
struct CCP_PhyDllObsReg0_s
{
    /** State of the cumulative dll_lock_inc register.  */
    uint8_t lockIncDbg;
    /** State of the cumulative dll_lock_dec register.  */
    uint8_t lockDecDbg;
    /** Reports the number of delay elements. */
    uint8_t dllLockValue;
    /** Number of master DLL consecutive inc/dec. */
    uint8_t dllUnlockCount;
    /** Indicates status of DLL. Defines the mode in which the DLL has achieved the lock. */
    uint8_t dllLockedMode;
    /** Indicates status of DLL - locked/unlocked. */
    uint8_t dllLock;
};

/** This register holds the following observable points in the PHY. */
struct CCP_PhyDllObsReg1_s
{
    /** Holds the encoded value for the clk_wr delay line for this slice. */
    uint8_t decoderOutWr;
    /** Holds the encoded value for the CMD read delay line for this slice. */
    uint8_t decoderOutRdCmd;
    /** Holds the encoded value for the read delay line for this slice. */
    uint8_t decoderOutRd;
};

/** This register holds the following observable points in the PHY. */
struct CCP_PhyDllObsReg2_s
{
    /** Holds the encoded value for the clk_wrdqs delay line for this slice. */
    uint8_t decoderOutWrdqs;
};

/** This register holds the following observable points in the PHY. */
struct CCP_PhyStaticToggReg_s
{
    /** Enables the toggling for the active part of the read_dqs delay line in idle state. */
    uint8_t readDqsToggEnable;
    /** Holds the encoded value for the CMD read delay line for this slice. */
    uint8_t staticToggEnable;
    /** Global control to enable the toggle signal during static activity. */
    uint8_t staticToggGlobalEnable;
    /** Clock divider to create toggle signal. */
    uint16_t staticTogClkDiv;
};

/** This struct holds the values of delay of each DQ bit on the write path. */
struct CCP_PhyWrDeskewReg_s
{
    /** Deskew delay for DQ bit 0. */
    uint8_t wrDq0DeskwDelay;
    /** Deskew delay for DQ bit 1. */
    uint8_t wrDq1DeskwDelay;
    /** Deskew delay for DQ bit 2. */
    uint8_t wrDq2DeskwDelay;
    /** Deskew delay for DQ bit 3. */
    uint8_t wrDq3DeskwDelay;
    /** Deskew delay for DQ bit 4. */
    uint8_t wrDq4DeskwDelay;
    /** Deskew delay for DQ bit 5. */
    uint8_t wrDq5DeskwDelay;
    /** Deskew delay for DQ bit 6. */
    uint8_t wrDq6DeskwDelay;
    /** Deskew delay for DQ bit 7. */
    uint8_t wrDq7DeskwDelay;
};

/** This struct holds the values of delay of each DQ bit on the read path. */
struct CCP_PhyRdDeskewReg_s
{
    /** Deskew delay for DQ bit 0. */
    uint8_t rdDq0DeskwDelay;
    /** Deskew delay for DQ bit 1. */
    uint8_t rdDq1DeskwDelay;
    /** Deskew delay for DQ bit 2. */
    uint8_t rdDq2DeskwDelay;
    /** Deskew delay for DQ bit 3. */
    uint8_t rdDq3DeskwDelay;
    /** Deskew delay for DQ bit 4. */
    uint8_t rdDq4DeskwDelay;
    /** Deskew delay for DQ bit 5. */
    uint8_t rdDq5DeskwDelay;
    /** Deskew delay for DQ bit 6. */
    uint8_t rdDq6DeskwDelay;
    /** Deskew delay for DQ bit 7. */
    uint8_t rdDq7DeskwDelay;
};

/**
 * This structs holds the values of delay of CMD bit on the write and read path path as well as the values of phase detect
 * block for CMD bit on the write path.
*/
struct CCP_PhyWrRdDeskewCmd_s
{
    /** Defines additional latency on the CMD signal. */
    uint8_t cmdClkperiodDelay;
    /** CMD SW DQ phase bypass */
    uint8_t cmdSwDqPhaseBypass;
    /** Enables the software half cycle shift. */
    uint8_t cmdEnSwHalfCycle;
    /** CMD SW half cycle shift */
    uint8_t cmdSwHalfCycleShift;
    /** DLL Phase Detect Selector for CMD generation to handle the clock domain crossing between the clock and clk_wr signal. */
    uint8_t cmdPhaseDetectSel;
};

/** This struct holds the values of phase detect block for each DQ DQ bit on the write path. */
struct CCP_PhyWrDeskewPdCtrl0Dq0_s
{
    /** DQ0 SW Phase Bypass. */
    uint8_t dq0SwDqPhaseBypass;
    /** DQ0 EN SW half cycle. */
    uint8_t dq0EnSwHalfCycle;
    /** DQ0 SW half cycle shift. */
    uint8_t dq0SwHalfCycleShift;
    /** DQ0 phase detect sel. */
    uint8_t dq0PhaseDetectSel;
};

/** This struct holds the available hardware features. */
struct CCP_PhyFeaturesReg_s
{
    /** Support for Automotive Safety Feature. */
    uint8_t asfSup;
    /** Support for PLL. */
    uint8_t pllSup;
    /** Support for JTAG muxes. */
    uint8_t jtagSup;
    /** Support for external LPBK_DQS io pad. */
    uint8_t extLpbkDqs;
    /** SFR interface type.0 - DFI, 1 - APB */
    uint8_t regIntf;
    /** Support for per-bit deskew. */
    uint8_t perBitDeskew;
    /** Support for clock ratio on DFI interface. 0 - 1:1, 1 - 1:2 */
    uint8_t dfiClockRatio;
    /** Support for aging in delay lines. */
    uint8_t aging;
    /** Number of taps in I/O delay lines. 0 - 256, 1 - 512. */
    uint8_t dllTapNum;
    /** Maximum number of banks supported by hardware. */
    uint8_t bankNum;
    /** Support for SD/eMMC. */
    uint8_t sdEmmc;
    /** Support for XSPI. */
    uint8_t xspi;
    /** Support for 16bit in ONFI SDR work mode. */
    uint8_t sdr16Bit;
    /** Support for ONFI4.1 - NAND Flash. */
    uint8_t onfi41;
    /** Support for ONFI4.0 - NAND Flash. */
    uint8_t onfi40;
};

/** This register handles the global control settings for the PHY. Please make sure all the reserved fields are set to 0. */
struct CCP_PhyCtrlMain_s
{
    /** The value that should be driven on the DQS pin while SDR operations are in progress. */
    uint8_t sdrDqsValue;
    /** The timing of assertion of phony DQS to the data slices. */
    uint8_t phonyDqsTiming;
    /** Defines additional latency on the control signals ALE/CLE/WE/RE/CE/WP. */
    uint8_t ctrlClkperiodDelay;
};

/** This register handles the global control settings for the termination selects for reads. Please make sure all the reserved fields are set to 0. */
struct CCP_PhyTselReg_s
{
    /** Termination select off value for the data. */
    uint8_t tselOffValueData;
    /** Termination select read value for the data. */
    uint8_t tselRdValueData;
    /** Termination select off value for the data strobe. */
    uint8_t tselOffValueDqs;
    /** Termination select read value for the data strobe */
    uint8_t tselRdValueDqs;
};

/**
 *  @}
 */

#endif	/* CCP_STRUCTS_IF_H */

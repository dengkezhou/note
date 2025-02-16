/* eip202_rd_format.h
 *
 * EIP-202 Ring Control Driver Library API Result Descriptor Internal interface
 */

/*****************************************************************************
* Copyright (c) 2011-2020 by Rambus, Inc. and/or its subsidiaries.
* All rights reserved. Unauthorized use (including, without limitation,
* distribution and copying) is strictly prohibited. All use requires,
* and is subject to, explicit written authorization and nondisclosure
* Rambus, Inc. and/or its subsidiaries
*
* For more information or support, please go to our online support system at
* https://sipsupport.rambus.com.
* In case you do not have an account for this system, please send an e-mail
* to sipsupport@rambus.com.
*****************************************************************************/

#ifndef EIP202_RD_FORMAT_H_
#define EIP202_RD_FORMAT_H_

#include <cae.h>

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

// Descriptor I/O Driver Library API implementation
#include "eip202_rdr.h"                // EIP202_ARM_CommandDescriptor_t


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"                // bool, uint32_t, uint8_t

// Driver Framework DMA Resource API
#include "dmares_types.h"              // DMAResource_Handle_t


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */

/*----------------------------------------------------------------------------
 * EIP202_RD_Make_ControlWord
 *
 * This helper function returns the Control Word that can be written to
 * the EIP-202 Prepared Descriptor.
 *
 * This function is re-entrant.
 *
 */
uint32_t
EIP202_RD_Make_ControlWord(
        const uint8_t ExpectedResultWordCount,
        const uint32_t PrepSegmentByteCount,
        const bool fFirstSegment,
        const bool fLastSegment);


/*----------------------------------------------------------------------------
 * EIP202_Prepared_Write
 *
 * This helper function writes the EIP-202 Logical Prepared Descriptor to the RDR
 *
 * This function is not re-entrant.
 *
 */
void
EIP202_Prepared_Write(cae_device *dev,
        DMAResource_Handle_t Handle,
        const unsigned int WordOffset,
        const EIP202_ARM_PreparedDescriptor_t * const Descr_p);


/*----------------------------------------------------------------------------
 * EIP202_ReadDescriptor
 *
 * This helper function reads the EIP-202 Result Descriptor from the RDR
 *
 * This function is not re-entrant.
 *
 */
void
EIP202_ReadDescriptor(cae_device *dev,
        EIP202_ARM_ResultDescriptor_t * const Descr_p,
        const DMAResource_Handle_t Handle,
        const unsigned int WordOffset,
        const unsigned int DescOffsetWordCount,
        bool * const fLastSegment,
        bool * const fFirstSegment);


/*----------------------------------------------------------------------------
 * EIP202_ClearDescriptor
 *
 * This helper function clears the EIP-202 Result Descriptor in the RDR
 *
 * This function is not re-entrant.
 *
 */
void
EIP202_ClearDescriptor(cae_device *dev,
        EIP202_ARM_ResultDescriptor_t * const Descr_p,
        const DMAResource_Handle_t Handle,
        const unsigned int WordOffset,
        const unsigned int DscrWordCount);


/*----------------------------------------------------------------------------
 * EIP202_RD_Read_ControlWord
 *
 * This helper function reads the EIP-202 Result Descriptor Control Word
 * and Result Token Data
 *
 * This function is not re-entrant.
 *
 */
void
EIP202_RD_Read_ControlWord(
        const uint32_t ControlWord,
        uint32_t * TokenData_pp,
        EIP202_RDR_Result_Control_t * const RDControl_p,
        EIP202_RDR_Result_Token_t * const ResToken_p);


/*----------------------------------------------------------------------------
 * EIP202_RD_Read_BypassData
 */
void
EIP202_RD_Read_BypassData(
        const uint32_t * BypassData_p,
        const uint8_t BypassWordCount,
        EIP202_RDR_BypassData_t * const BD_p);


#endif /* EIP202_RD_FORMAT_H_ */


/* end of file eip202_rd_format.h */

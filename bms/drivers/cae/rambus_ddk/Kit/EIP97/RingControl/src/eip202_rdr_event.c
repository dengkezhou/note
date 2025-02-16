/* eip202_rdr_event.c
 *
 * EIP-202 Ring Control Driver Library
 * CDR Event Management API implementation
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include <cae.h>

#include "eip202_rdr.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include "c_eip202_ring.h"

// EIP-202 Ring Control Driver Library Internal interfaces
#include "eip202_ring_internal.h"
#include "eip202_rdr_level0.h"         // EIP-202 Level 0 macros
#include "eip202_rdr_fsm.h"             // RDR State machine

// Driver Framework Basic Definitions API
#include "basic_defs.h"                // IDENTIFIER_NOT_USED, bool, uint32_t


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * EIP202_RDR_Status_Get
 */
EIP202_Ring_Error_t
EIP202_RDR_Status_Get(cae_device *dev,
        EIP202_Ring_IOArea_t * const IOArea_p,
        EIP202_RDR_Status_t * const Status_p)
{
    Device_Handle_t Device;
    EIP202_Ring_Error_t rv;
    volatile EIP202_RDR_True_IOArea_t * const TrueIOArea_p = RDRIOAREA(IOArea_p);

    EIP202_RING_CHECK_POINTER(IOArea_p);
    EIP202_RING_CHECK_POINTER(Status_p);

    Device = TrueIOArea_p->Device;

    EIP202_RDR_PREP_COUNT_RD(dev, Device, &Status_p->RDPrepWordCount);
    EIP202_RDR_PROC_COUNT_RD(dev, Device,
                             &Status_p->RDProcWordCount,
                             &Status_p->RDProcPktWordCount);

    EIP202_RDR_STAT_RD(dev, Device,
                       &Status_p->fDMAError,
                       &Status_p->fTresholdInt,
                       &Status_p->fError,
                       &Status_p->fOUFlowError,
                       &Status_p->fTimeoutInt,
                       &Status_p->fRDBufOverflowInt,
                       &Status_p->fRDOverflowInt,
                       &Status_p->RDFIFOWordCount);

    // Transit to a new state
    if(Status_p->fDMAError)
        rv = EIP202_RDR_State_Set((volatile EIP202_RDR_State_t*)&TrueIOArea_p->State,
                                 EIP202_RDR_STATE_FATAL_ERROR);
    else
        // Remain in the current state
        rv = EIP202_RDR_State_Set((volatile EIP202_RDR_State_t*)&TrueIOArea_p->State,
                                 (EIP202_RDR_State_t)TrueIOArea_p->State);
    if(rv != EIP202_RING_NO_ERROR)
        return EIP202_RING_ILLEGAL_IN_STATE;

    return EIP202_RING_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP202_RDR_Processed_FillLevel_High_INT_Enable
 */
EIP202_Ring_Error_t
EIP202_RDR_Processed_FillLevel_High_INT_Enable(cae_device *dev,
        EIP202_Ring_IOArea_t * const IOArea_p,
        const unsigned int ThresholdDscrCount,
        const unsigned int Timeout,
        const bool fIntPerPacket)
{
    Device_Handle_t Device;
    EIP202_Ring_Error_t rv;
    volatile EIP202_RDR_True_IOArea_t * const TrueIOArea_p = RDRIOAREA(IOArea_p);

    EIP202_RING_CHECK_POINTER(IOArea_p);

    if(EIP202_RING_RD_INTERRUPTS_PER_PACKET_FLAG == 0 && fIntPerPacket)
        return EIP202_RING_ARGUMENT_ERROR;

    Device = TrueIOArea_p->Device;

    if (fIntPerPacket)
    {
        EIP202_RDR_THRESH_WR(dev, Device,
                             (uint32_t)ThresholdDscrCount,
                             // Set packet processing mode,
                             // e.g. interrupts per packet i.s.o. descriptor
                             true,
                             (uint8_t)Timeout);
    }
    else
    {
        EIP202_RDR_THRESH_WR(dev, Device,
                             (uint32_t)ThresholdDscrCount *
                             TrueIOArea_p->DescOffsWordCount,
                             // Set packet processing mode,
                             // e.g. interrupts per packet i.s.o. descriptor
                             false,
                             (uint8_t)Timeout);
    }

#ifdef EIP202_CLUSTERED_WRITES_DISABLE
    // Prevent clustered write operations, break them with a read operation
    // Note: Reading the EIP202_RDR_RING_BASE_ADDR_LO register
    //       has no side effects!
    EIP202_RDR_Read32(dev, Device, EIP202_RDR_RING_BASE_ADDR_LO);
#endif

    // Remain in the current state
    rv = EIP202_RDR_State_Set((volatile EIP202_RDR_State_t*)&TrueIOArea_p->State,
                             (EIP202_RDR_State_t)TrueIOArea_p->State);
    if(rv != EIP202_RING_NO_ERROR)
        return EIP202_RING_ILLEGAL_IN_STATE;

    return EIP202_RING_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP202_RDR_Processed_FillLevel_High_INT_ClearAndDisable
 *
 */
EIP202_Ring_Error_t
EIP202_RDR_Processed_FillLevel_High_INT_ClearAndDisable(cae_device *dev,
        EIP202_Ring_IOArea_t * const IOArea_p,
        const bool fOvflIntOnly)
{
    Device_Handle_t Device;
    EIP202_Ring_Error_t rv;
    volatile EIP202_RDR_True_IOArea_t * const TrueIOArea_p = RDRIOAREA(IOArea_p);

    EIP202_RING_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    if(fOvflIntOnly)
    {
        // Clear Descriptor and Buffer overflow interrupts
        EIP202_RDR_STAT_CLEAR_DSCR_BUF_OFLO_IRQ_WR(dev, Device);
    }
    else
    {
        // Disable Processed Descriptor threshold interrupt,
        // Disable Timeout interrupt and stop timeout counter for
        // reducing power consumption
        EIP202_RDR_THRESH_WR(dev,
                           Device,
                           TrueIOArea_p->RingSizeWordCount,
                           0,  // Set descriptor processing mode
                           0); // Disable timeout

#ifdef EIP202_CLUSTERED_WRITES_DISABLE
        // Prevent clustered write operations, break them with a read operation
        // Note: Reading the EIP202_RDR_RING_BASE_ADDR_LO register
        //       has no side effects!
        EIP202_RDR_Read32(dev, Device, EIP202_RDR_RING_BASE_ADDR_LO);
#endif

        // Clear all RDR interrupts
        EIP202_RDR_STAT_CLEAR_ALL_IRQ_WR(dev, Device);

#ifdef EIP202_CLUSTERED_WRITES_DISABLE
        // Prevent clustered write operations, break them with a read operation
        // Note: Reading the EIP202_RDR_RING_BASE_ADDR_LO register
        //       has no side effects!
        EIP202_RDR_Read32(dev, Device, EIP202_RDR_RING_BASE_ADDR_LO);
#endif
    }

    // Remain in the current state
    rv = EIP202_RDR_State_Set((volatile EIP202_RDR_State_t*)&TrueIOArea_p->State,
                             (EIP202_RDR_State_t)TrueIOArea_p->State);
    if(rv != EIP202_RING_NO_ERROR)
        return EIP202_RING_ILLEGAL_IN_STATE;

    return EIP202_RING_NO_ERROR;
}


/* end of file eip202_rdr_event.c */



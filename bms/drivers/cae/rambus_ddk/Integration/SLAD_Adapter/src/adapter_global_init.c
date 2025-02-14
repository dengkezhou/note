/* adapter_global_init.c
 *
 * Global Control initialization module.
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

#include "adapter_global_init.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default Adapter configuration
#include "c_adapter_global.h"   // ADAPTER_GLOBAL_PRNG_SEED

// Global Control API: Packet I/O
#include "api_global_eip97.h"

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // uint8_t, uint32_t, bool

// Driver Framework C Library API
#include "clib.h"               // memcpy

// EIP-97 Driver Library Global Control API
#include "eip97_global_event.h" // Event Management
#include "eip97_global_init.h"  // Init/Uninit
#include "eip97_global_prng.h"  // PRNG Control

#include "device_types.h"       // Device_Handle_t
#include "device_mgmt.h"        // Device_find
#include "log.h"                // Log API


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */
static const uint32_t Global_PRNG_Key[8] = ADAPTER_GLOBAL_PRNG_SEED;

/*----------------------------------------------------------------------------
 * BoolToString()
 *
 * Convert boolean value to string.
 */
#if LOG_SEVERITY_MAX > LOG_SEVERITY_NO_OUTPUT
static const char *
BoolToString(
        const bool b)
{
    if (b)
        return "true";
    else
        return "false";
}
#endif

/*----------------------------------------------------------------------------
 * Adapter_Global_StatusReport()
 *
 * Obtain all available global status information from the EIP-97 driver
 * and report it.
 */
static void
Adapter_Global_StatusReport(cae_device *dev)
{
    GlobalControl97_Error_t rc;
    unsigned int i;

    LOG_INFO("\n\t\t Adapter_Global_StatusReport \n");

    LOG_CRIT("Global Status of the EIP-97\n");

    for (i=0; i < ADAPTER_GLOBAL_EIP97_NOF_PES; i++)
    {
        LOG_CRIT("Packet Engine %d Status\n", i);
        {
            GlobalControl97_DFE_Status_t DFE_Status;

            rc = GlobalControl97_DFE_Status_Get(dev, i, &DFE_Status);

            if (rc != GLOBAL_CONTROL_NO_ERROR)
            {
                continue;
            }

            LOG_CRIT("DFE Status: CD FIFO Words: %d, CDR ID: %d, DMA size: %d\n"
                     "AtDMA busy: %s, DataDMA busy: %s, DMA err: %s\n",
                     DFE_Status.CDFifoWord32Count,
                     DFE_Status.CDR_ID,
                     DFE_Status.DMASize,
                     BoolToString(DFE_Status.fAtDMABusy),
                     BoolToString(DFE_Status.fDataDMABusy),
                     BoolToString(DFE_Status.fDMAError));
        }

        {
            GlobalControl97_DSE_Status_t DSE_Status;

            rc = GlobalControl97_DSE_Status_Get(dev, i, &DSE_Status);

            if (rc != GLOBAL_CONTROL_NO_ERROR)
            {
                continue;
            }

            LOG_CRIT("DSE Status: RD FIFO Words: %d, RDR ID: %d, DMA size: %d\n"
                     "Data flush  busy: %s, DataDMA busy: %s, DMA err: %s\n",
                     DSE_Status.RDFifoWord32Count,
                     DSE_Status.RDR_ID,
                     DSE_Status.DMASize,
                     BoolToString(DSE_Status.fDataFlushBusy),
                     BoolToString(DSE_Status.fDataDMABusy),
                     BoolToString(DSE_Status.fDMAError));
        }

        {
            GlobalControl97_Token_Status_t Token_Status;
            rc = GlobalControl97_Token_Status_Get(dev, i, &Token_Status);

            if (rc != GLOBAL_CONTROL_NO_ERROR)
            {
                continue;
            }

            LOG_CRIT("Token Status: Active: %d, loc available: %s\n"
                     "res available: %s, read active: %s, ccache active: %s\n"
                     "cntx fetch: %s, res cntx: %s\n"
                     "processing held: %s, busy: %s\n",
                     Token_Status.ActiveTokenCount,
                     BoolToString(Token_Status.fTokenLocationAvailable),
                     BoolToString(Token_Status.fResultTokenAvailable),
                     BoolToString(Token_Status.fTokenReadActive),
                     BoolToString(Token_Status.fContextCacheActive),
                     BoolToString(Token_Status.fContextFetch),
                     BoolToString(Token_Status.fResultContext),
                     BoolToString(Token_Status.fProcessingHeld),
                     BoolToString(Token_Status.fBusy));
        }

        {
            GlobalControl97_Context_Status_t Context_Status;

            rc = GlobalControl97_Context_Status_Get(dev, i, &Context_Status);

            if (rc != GLOBAL_CONTROL_NO_ERROR)
            {
                continue;
            }

            LOG_CRIT("Context Status: Err mask: %04x, Available: %d\n"
                     "Active cntx: %s, next cntx: %s, result cntx: %s"
                     " Err recov: %s\n",
                     Context_Status.Error,
                     Context_Status.AvailableTokenCount,
                     BoolToString(Context_Status.fActiveContext),
                     BoolToString(Context_Status.fNextContext),
                     BoolToString(Context_Status.fResultContext),
                     BoolToString(Context_Status.fErrorRecovery));
        }

        {
            GlobalControl97_Interrupt_Status_t Interrupt_Status;

            rc = GlobalControl97_Interrupt_Status_Get(i, &Interrupt_Status);

            if (rc != GLOBAL_CONTROL_NO_ERROR)
            {
                continue;
            }

            LOG_CRIT("Interrupt Status: input DMA err: %s, output DMA err %s \n"
                     "pkt proc err: %s, pkt timeout: %s, f a t a l err: %s, "
                     "PE int out: %s\n"
                     "inp DMA enable: %s, outp DMA enable %s, "
                     "pkt proc enable: %s\n"
                     "pkt timeout enable: %s, f a t a l enable: %s,"
                     "PE int out enable: %s\n",
                     BoolToString(Interrupt_Status.fInputDMAError),
                     BoolToString(Interrupt_Status.fOutputDMAError),
                     BoolToString(Interrupt_Status.fPacketProcessingError),
                     BoolToString(Interrupt_Status.fPacketTimeout),
                     BoolToString(Interrupt_Status.fFatalError),
                     BoolToString(Interrupt_Status.fPeInterruptOut),
                     BoolToString(Interrupt_Status.fInputDMAErrorEnabled),
                     BoolToString(Interrupt_Status.fOutputDMAErrorEnabled),
                     BoolToString(Interrupt_Status.fPacketProcessingEnabled),
                     BoolToString(Interrupt_Status.fPacketTimeoutEnabled),
                     BoolToString(Interrupt_Status.fFatalErrorEnabled),
                     BoolToString(Interrupt_Status.fPeInterruptOutEnabled));
        }
        {
            GlobalControl97_Output_Transfer_Status_t OutXfer_Status;

            rc = GlobalControl97_OutXfer_Status_Get(dev, i, &OutXfer_Status);

            if (rc != GLOBAL_CONTROL_NO_ERROR)
            {
                continue;
            }

            LOG_CRIT("Output Transfer Status: availabe: %d, "
                     "min: %d, max: %d, size mask: %d\n",
                     OutXfer_Status.AvailableWord32Count,
                     OutXfer_Status.MinTransferWordCount,
                     OutXfer_Status.MaxTransferWordCount,
                     OutXfer_Status.TransferSizeMask);
        }
        {
            GlobalControl97_PRNG_Status_t PRNG_Status;

            rc = GlobalControl97_PRNG_Status_Get(dev, i, &PRNG_Status);

            if (rc == GLOBAL_CONTROL_ERROR_NOT_IMPLEMENTED)
            {
                LOG_CRIT("No PRNG present in EIP-96\n");
            }
            else if (rc == GLOBAL_CONTROL_NO_ERROR)
            {
                    LOG_CRIT("PRNG Status: busy: %s, res ready: %s\n",
                             BoolToString(PRNG_Status.fBusy),
                             BoolToString(PRNG_Status.fResultReady));
            }
        }
    }
}


/*----------------------------------------------------------------------------
 * Adapter_Global_Init()
 *
 */
bool
Adapter_Global_Init(cae_device *dev)
{
    GlobalControl97_Error_t rc;
    unsigned int i;

    LOG_INFO("\n\t\t Adapter_Global_Init \n");
    // Initialize the device
    rc = GlobalControl97_Init(dev, false);
    if (rc != GLOBAL_CONTROL_NO_ERROR)
    {
        LOG_CRIT("Adaptar_Global_Init: EIP97 initialization failed\n");
        return false; // error
    }
    // First read the device capabilities
    {
        GlobalControl97_Capabilities_t Capabilities;

        rc = GlobalControl97_Capabilities_Get(dev, &Capabilities);
        if ( rc != GLOBAL_CONTROL_NO_ERROR)
        {
            LOG_CRIT("GlobalControl97_Capabilities_Get returned error\n");
        }
        else
        {
            LOG_CRIT("Global EIP-97 capabilities: %s\n",
                     Capabilities.szTextDescription);
        }
    }
    // Enable the rings for the packet engines
    // This version enables ring #0 only on Packet Engine #0 only
    {
        GlobalControl97_Ring_PE_Map_t RingPEMap;

        ZEROINIT(RingPEMap);

        // Enable rings
        RingPEMap.RingPE_Mask = ADAPTER_GLOBAL_EIP97_RINGMASK;

        // Set rings priority
        RingPEMap.RingPrio_Mask = ADAPTER_GLOBAL_EIP97_PRIOMASK;

        for (i=0; i < ADAPTER_GLOBAL_EIP97_NOF_PES; i++)
        {
            rc = GlobalControl97_Configure(dev, i, &RingPEMap);
            if (rc != GLOBAL_CONTROL_NO_ERROR)
            {
                LOG_CRIT("Ring configuration failed for PE %d\n", i);
                GlobalControl97_UnInit(dev);
                return false; // error
            }
        }
    }

    {
        GlobalControl97_PRNG_Status_t PRNG_Status;
        // Check whether we have a PRNG.
        rc = GlobalControl97_PRNG_Status_Get(dev, 0, &PRNG_Status);

        if (rc != GLOBAL_CONTROL_NO_ERROR && rc != GLOBAL_CONTROL_ERROR_NOT_IMPLEMENTED)
        {
                return false;
        }
        if (rc != GLOBAL_CONTROL_ERROR_NOT_IMPLEMENTED)
        {
            for (i=0; i < ADAPTER_GLOBAL_EIP97_NOF_PES; i++)
            {
                GlobalControl97_PRNG_Reseed_t PRNG_Reseed;

                PRNG_Reseed.SeedLo = Global_PRNG_Key[0];
                PRNG_Reseed.SeedHi = Global_PRNG_Key[1];
                PRNG_Reseed.Key0Lo = Global_PRNG_Key[2];
                PRNG_Reseed.Key0Hi = Global_PRNG_Key[3];
                PRNG_Reseed.Key1Lo = Global_PRNG_Key[4];
                PRNG_Reseed.Key1Hi = Global_PRNG_Key[5];
                PRNG_Reseed.LFSRLo = Global_PRNG_Key[6];
                PRNG_Reseed.LFSRHi = Global_PRNG_Key[7];

                rc = GlobalControl97_PRNG_Reseed(dev, i, &PRNG_Reseed);

                if (rc != GLOBAL_CONTROL_NO_ERROR)
                {
                    LOG_CRIT("Could not reseed PRNG of PE#%d\n",i);
                    GlobalControl97_UnInit(dev);
                    return false; // error
                }
            }
        }
        else
        {
            LOG_CRIT("No PRNG in PEs, skip initialization\n");
        }
    }
    Adapter_Global_StatusReport(dev);

    return true; // success
}


/*----------------------------------------------------------------------------
 * Adapter_Global_UnInit()
 *
 */
void
Adapter_Global_UnInit(cae_device *dev)
{
    LOG_INFO("\n\t\t Adapter_Global_UnInit \n");

    Adapter_Global_StatusReport(dev);

    GlobalControl97_UnInit(dev);
}


/* end of file adapter_global_eip97.c */

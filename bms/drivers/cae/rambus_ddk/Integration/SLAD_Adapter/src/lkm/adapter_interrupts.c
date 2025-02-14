/* adapter_interrupts.c
 *
 * Adapter EIP-202 module responsible for interrupts.
 *
 */

/*****************************************************************************
* Copyright (c) 2008-2020 by Rambus, Inc. and/or its subsidiaries.
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

#include <cae.h>
#include <irq.h>

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "adapter_interrupts.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default Adapter configuration
#include "c_adapter_eip202.h"      // ADAPTER_*INTERRUPT*

// Driver Framework Basic Definitions API
#include "basic_defs.h"            // bool, IDENTIFIER_NOT_USED

// Driver Framework C-RunTime Library API
#include "clib.h"                  // ZEROINIT

// EIP-201 Advanced interrupt Controller (AIC)
#include "eip201.h"

// Logging API
#include "log.h"

// Driver Framework Device API
#include "device_types.h"          // Device_Handle_t
#include "device_mgmt.h"           // Device_Find, Device_GetReference
#include <linux/string.h>
#include <stdlib/stdio.h>

// Linux Kernel API
//#include <linux/interrupt.h>       // request_irq, free_irq,
                                   // DECLARE_TASKLET, tasklet_schedule,
                                   // IRQ_DISABLED
//#include <linux/irq.h>             // IRQ_TYPE_LEVEL_HIGH
//#include <linux/irqreturn.h>       // irqreturn_t

enum irqreturn {
	IRQ_NONE                = (0 << 0),
	IRQ_HANDLED             = (1 << 0),
	IRQ_WAKE_THREAD         = (1 << 1),
};

typedef enum irqreturn irqreturn_t;

#ifdef ADAPTER_EIP202_USE_UMDEVXS_IRQ
#include "umdevxs_interrupt.h"
#endif

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define ARRAY_ELEMCOUNT(_a)             (sizeof(_a) / sizeof(_a[0]))

#define IRQF_SHARED	0x00000080

#define ADAPTERINT_REQUEST_IRQ_FLAGS    (IRQF_SHARED)

/*----------------------------------------------------------------------------
 * Local variables
 */

#define ADAPTER_EIP202_ADD_AIC(_name,_idx, isirq)  \
    {NULL, _name, _idx, -1, {0, }, isirq}


static Adapter_AIC_t tmp_Adapter_AICTable[] = { ADAPTER_EIP202_AICS };

#define ADAPTER_EIP202_ADD_IRQ(_name,_phy,_aicname,_tasklet,_pol)    \
    {(1<<(_phy)),#_name,NULL,_aicname,NULL,0,NULL,_tasklet, \
                                              EIP201_CONFIG_##_pol}

static Adapter_Interrupt_t tmp_Adapter_IRQTable[] = { ADAPTER_EIP202_IRQS };

extern void cipher_callback(void *args);
extern void digest_callback(void *args);
extern PEC_Status_t PEC_ResultNotify_Request(cae_device *dev,
					     const unsigned int InterfaceId,
					     PEC_NotifyFunction_t CBFunc_p,
					     void *args,
					     const unsigned int ResultsCount);

/*----------------------------------------------------------------------------
 * AdapterINT_GetActiveIntNr
 *
 * Returns 0..31 depending on the lowest '1' bit.
 * Returns 32 when all bits are zero
 *
 * Using binary break-down algorithm.
 */
static inline int
AdapterINT_GetActiveIntNr(
        uint32_t Sources)
{
    unsigned int IntNr = 0;
    unsigned int R16, R8, R4, R2;

    if (Sources == 0)
        return 32;

    // if the lower 16 bits are empty, look at the upper 16 bits
    R16 = Sources & 0xFFFF;
    if (R16 == 0)
    {
        IntNr += 16;
        R16 = Sources >> 16;
    }

    // if the lower 8 bits are empty, look at the high 8 bits
    R8 = R16 & 0xFF;
    if (R8 == 0)
    {
        IntNr += 8;
        R8 = R16 >> 8;
    }
    R4 = R8 & 0xF;
    if (R4 == 0)
    {
        IntNr += 4;
        R4 = R8 >> 4;
    }

    R2 = R4 & 3;
    if (R2 == 0)
    {
        IntNr += 2;
        R2 = R4 >> 2;
    }

    // last two bits are trivial
    // 00 => cannot happen
    // 01 => +0
    // 10 => +1
    // 11 => +0
    if (R2 == 2)
        IntNr++;

    return IntNr;
}


/*----------------------------------------------------------------------------
 * AdapterINT_Report_InterruptCounters
 */
static void
AdapterINT_Report_InterruptCounters(cae_device *dev)
{
    int i;
    for (i=0; i<ARRAY_ELEMCOUNT(dev->Adapter_IRQTable); i++)
    {
        if ( (1<<i) & ADAPTER_EIP202_INTERRUPTS_TRACEFILTER)
        {
            LOG_CRIT("AIC %s interrupt source %s mask %08x counter %d\n",
                     dev->Adapter_IRQTable[i].AICName,
                     dev->Adapter_IRQTable[i].name,
                     dev->Adapter_IRQTable[i].SourceBitMask,
                     dev->Adapter_IRQTable[i].Counter);
        }
    }
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupt_Enable
 */
void
Adapter_Interrupt_Enable(cae_device *dev,
        const int nIRQ,
        const unsigned int Flags)
{
    IDENTIFIER_NOT_USED(Flags);
    LOG_INFO("\n\t\t %s \n", __func__);

    if (nIRQ < 0 || nIRQ >= ADAPTER_MAX_INTERRUPTS)
    {
            LOG_CRIT(
                    "Adapter_Interrupt_Enable: "
                    "Failed, IRQ %d not supported\n",
                    nIRQ);
    }
    else
    {
        EIP201_SourceMask_EnableSource(dev, dev->Adapter_IRQTable[nIRQ].AIC->Device,
                                       dev->Adapter_IRQTable[nIRQ].SourceBitMask);
        LOG_INFO("\n\t\t\tAdapter_Interrupt_Enable "
                 "IRQ %d %s %s mask=%08x\n",
                 nIRQ,
                 dev->Adapter_IRQTable[nIRQ].AICName,
                 dev->Adapter_IRQTable[nIRQ].name,
                 dev->Adapter_IRQTable[nIRQ].SourceBitMask);
   }

    LOG_INFO("\n\t\t %s done \n", __func__);
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupt_Disable
 */
void
Adapter_Interrupt_Disable(cae_device *dev,
        const int nIRQ,
        const unsigned int Flags)
{
    IDENTIFIER_NOT_USED(Flags);

    LOG_INFO("\n\t\t %s \n", __func__);

    if (nIRQ < 0 || nIRQ >= ADAPTER_MAX_INTERRUPTS)
    {
            LOG_CRIT(
                    "Adapter_Interrupt_Disable: "
                    "Failed, IRQ %d not supported\n",
                    nIRQ);
    }
    else
    {
        EIP201_SourceMask_DisableSource(dev, dev->Adapter_IRQTable[nIRQ].AIC->Device,
                                       dev->Adapter_IRQTable[nIRQ].SourceBitMask);
        LOG_INFO("\n\t\t\tAdapter_Interrupt_Disable "
                 "IRQ %d %s %s mask=%08x\n",
                 nIRQ,
                 dev->Adapter_IRQTable[nIRQ].AICName,
                 dev->Adapter_IRQTable[nIRQ].name,
                 dev->Adapter_IRQTable[nIRQ].SourceBitMask);
    }

    LOG_INFO("\n\t\t %s done \n", __func__);
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupt_SetHandler
 */
void
Adapter_Interrupt_SetHandler(cae_device *dev,
        const int nIRQ,
        Adapter_InterruptHandler_t HandlerFunction)
{
    if (nIRQ < 0 || nIRQ >= ADAPTER_MAX_INTERRUPTS)
        return;

    LOG_INFO(
            "Adapter_Interrupt_SetHandler: "
            "HandlerFnc=%p for IRQ %d\n",
            HandlerFunction,
            nIRQ);

    dev->Adapter_IRQTable[nIRQ].Handler = HandlerFunction;
}


/*----------------------------------------------------------------------------
 * AdapterINT_CommonTasklet
 *
 * This handler is scheduled in the top-halve interrupt handler when it
 * decodes one of the CDR or RDR interrupt sources.
 * The data parameter is the IRQ value (from adapter_interrupts.h) for that
 * specific interrupt source.
 */
static void
AdapterINT_CommonTasklet(cae_device *dev,
        unsigned long data)
{
    const unsigned int IntNr = (unsigned int)data;
    Adapter_InterruptHandler_t H;

    LOG_INFO("\n\t\t%s \n", __func__);

    LOG_INFO("Tasklet invoked intnr=%d\n",IntNr);

    // verify we have a handler
    H = dev->Adapter_IRQTable[IntNr].Handler;

    if (H)
    {
        // invoke the handler
        H(dev, IntNr, 0);
    }
    else
    {
        LOG_CRIT(
            "AdapterINT_CommonTasklet: "
            "Error, disabling IRQ %d with missing handler\n",
            IntNr);
        Adapter_Interrupt_Disable(dev, IntNr, 0);
    }

    LOG_INFO("\n\t\t%s done\n", __func__);
}


/*----------------------------------------------------------------------------
 * AdapterINT_AICHandler
 *
 * Handle all interrupts connected to the specified AIC.
 *
 * If this AIC is connected directly to a system IRQ line, this is
 * called directly from the Top Half Handler.
 *
 * If this AIC is connected via an IRQ line of another AIC, this is
 * called from the handler function of that interrupt.
 *
 * Return: 0 for success, -1 for failure.
 */
static int
AdapterINT_AICHandler(cae_device *dev, Adapter_AIC_t *AIC)
{
    EIP201_SourceBitmap_t Sources;
    int IntNr, irq, rc = 0;

    LOG_INFO("\n\t\t%s \n", __func__);

    if (AIC == NULL)
        return -1;

    if (AIC->Device == NULL)
    {
        LOG_INFO("%s: skipping spurious interrupt for AIC %s, IRQ %d\n",
                 __func__,
                 AIC->name,
                 AIC->irq);
        goto exit; // no error
    }

    Sources = EIP201_SourceStatus_ReadAllEnabled(dev, AIC->Device);
    if (Sources == 0)
    {
        rc = -1;
        goto exit; // error
    }

    EIP201_Acknowledge(dev, AIC->Device, Sources);

    LOG_INFO("%s: AIC %s, IRQ %d, sources=%x\n",
             __func__,
             AIC->name,
             AIC->irq,
             Sources);

    while (Sources)
    {
        IntNr = AdapterINT_GetActiveIntNr(Sources);

        /* Get number of first bit set */
        Sources &= ~(1<<IntNr);

        /* Clear this in sources */
        irq = AIC->BitIRQs[IntNr];

        LOG_INFO("%s: Handle IRQ %d for AIC %s\n", __func__, irq, AIC->name);

        if (irq < 0 || irq >= ADAPTER_MAX_INTERRUPTS)
        {
            LOG_CRIT("%s: %s IRQ not defined for bit %d, disabling source\n",
                     __func__,
                     AIC->name,
                     IntNr);
            EIP201_SourceMask_DisableSource(dev, AIC->Device, (1<<IntNr));
        }

        dev->Adapter_IRQTable[irq].Counter++;

        if ( (1<<irq) & ADAPTER_EIP202_INTERRUPTS_TRACEFILTER)
            LOG_CRIT("%s: encountered interrupt %d, bit %d for AIC %s\n",
                     __func__,
                     irq,
                     IntNr,
                     AIC->name);

        if(dev->Adapter_IRQTable[irq].fHaveTasklet)
        {
            LOG_INFO("%s: Start tasklet\n", __func__);
            /* IRQ is handled via tasklet */
            //tasklet_schedule(&dev->Adapter_IRQTable[irq].tasklet);
	    AdapterINT_CommonTasklet(dev, irq);
            Adapter_Interrupt_Disable(dev, irq, 0);
        }
        else
        {
            Adapter_InterruptHandler_t H = dev->Adapter_IRQTable[irq].Handler;
            LOG_INFO("%s: Run normal handler\n", __func__);
            /* Handler is called directly */
            if (H)
            {
                H(dev, irq, 0);
            }
            else
            {
                LOG_CRIT(
                    "%s : Error, disabling IRQ %d with missing handler\n",
                    __func__,
                    irq);

                Adapter_Interrupt_Disable(dev, irq, 0);
            }
        }
    } // while

exit:
    LOG_INFO("\n\t\t%s done\n", __func__);
    return rc;
}


/*----------------------------------------------------------------------------
 * AdapterINT_TopHalfHandler
 *
 * This is the interrupt handler function call by the kernel when our hooked
 * interrupt is active.
 *
 * Call the handler for the associated AIC.
 */
static int
AdapterINT_TopHalfHandler(
        int irq,
        void * dev_id)
{
    irqreturn_t Int_Rc = IRQ_NONE;
    cae_device *dev = (cae_device *)dev_id;

    LOG_INFO("\n\t\t%s \n", __func__);

    if (irq < 0 || irq >= MAX_OS_IRQS || dev->IRQ_AIC_Mapping[irq]==NULL)
    {
        LOG_CRIT("%s: No AIC defined for IRQ %d\n",__func__,irq);
        goto error;
    }

    if ( AdapterINT_AICHandler(dev, dev->IRQ_AIC_Mapping[irq]) < 0)
    {
        goto error;
    }

    Int_Rc = IRQ_HANDLED;

	/* re-open interrupt for crypto algorithm. */
	if (dev->ctx) {
		if (((cipher_ctx *)dev->ctx)->type == CAE_CRYPTO_ALGO)
			PEC_ResultNotify_Request(dev, INTERFACE_ID, cipher_callback, dev->ctx, 1);
		else if (((md_ctx *)dev->ctx)->type == CAE_HASH_ALGO)
			PEC_ResultNotify_Request(dev, INTERFACE_ID, digest_callback, dev->ctx, 1);
	}
error:
    LOG_INFO("\n\t\t%s done\n", __func__);

    IDENTIFIER_NOT_USED(dev_id);
    return Int_Rc;
}


/*----------------------------------------------------------------------------
 * AdapterINT_ChainedAIC
 *
 * Handler function for IRQ that services an entire AIC.
 */
static void
AdapterINT_ChainedAIC(void *c_dev, const int irq, const unsigned int flags)
{
	cae_device *dev = (cae_device *)c_dev;
	IDENTIFIER_NOT_USED(flags);
	AdapterINT_AICHandler(dev, dev->Adapter_IRQTable[irq].extra);
}


/*----------------------------------------------------------------------------
 * AdapterINT_SetInternalLinkage
 *
 * Create AIC References in dev->Adapter_IRQTable.
 * Fill in BitIRQs references in Adapter_AICTable.
 * Perform some consistency checks.
 *
 * Return 0 on success, -1 on failure.
 */
static int
AdapterINT_SetInternalLinkage(cae_device *dev)
{
    int i,j;
    int IntNr;

    for (i=0; i<ARRAY_ELEMCOUNT(dev->Adapter_IRQTable); i++)
    {
        dev->Adapter_IRQTable[i].AIC = NULL;
    }

    for (i=0; i<ARRAY_ELEMCOUNT(dev->Adapter_AICTable); i++)
    {
        for (j=0; j<32; j++)
        {
            dev->Adapter_AICTable[i].BitIRQs[j] = -1;
        }
        for (j=0; j<ARRAY_ELEMCOUNT(dev->Adapter_IRQTable); j++)
        {
            if (strcmp(dev->Adapter_AICTable[i].name, dev->Adapter_IRQTable[j].AICName)
                == 0)
            {
                if (dev->Adapter_IRQTable[j].AIC)
                {
                    LOG_CRIT("%s: AIC link set more than once\n",__func__);
                }
                dev->Adapter_IRQTable[j].AIC = dev->Adapter_AICTable + i;
                IntNr = AdapterINT_GetActiveIntNr(
                    dev->Adapter_IRQTable[j].SourceBitMask);
                if (IntNr < 0 || IntNr >= 32)
                {
                    LOG_CRIT("%s: IRQ %d source bit %d out of range\n",
                             __func__,j,IntNr);
                    return -1;
                }
                else if (dev->Adapter_AICTable[i].BitIRQs[IntNr] >= 0)
                {
                    LOG_CRIT(
                        "%s: AIC %s IRQ %d source bit %d already defined\n",
                        __func__,
                        dev->Adapter_AICTable[i].name,
                        j,
                        IntNr);
                    return -1;
                }
                else
                {
                    dev->Adapter_AICTable[i].BitIRQs[IntNr] = j;
                }
            }
        }
    }
    for (i=0; i<ARRAY_ELEMCOUNT(dev->Adapter_IRQTable); i++)
    {
        if (dev->Adapter_IRQTable[i].AIC == NULL)
        {
            LOG_CRIT("%s: AIC pointer of IRQ %d is null\n",__func__,i);
            return -1;
        }
    }

    return 0;
}


/*----------------------------------------------------------------------------
 * AdapterINT_AIC_Init
 *
 */
static bool
AdapterINT_AIC_Init(cae_device *dev)
{
    EIP201_Status_t res;
    unsigned int i;

    // Initialize all configured EIP-201 AIC devices
    for (i = 0; i < ARRAY_ELEMCOUNT(dev->Adapter_AICTable); i++)
    {
        LOG_INFO("%s: Initialize AIC %s\n",__func__,dev->Adapter_AICTable[i].name);

        dev->Adapter_AICTable[i].Device = Device_Find(dev, dev->Adapter_AICTable[i].name);
        if (dev->Adapter_AICTable[i].Device == NULL)
        {
            LOG_CRIT("%s: Device_Find() failed for %s\n",
                     __func__,
                     dev->Adapter_AICTable[i].name);
            return false; // error
        }

        res = EIP201_Initialize(dev, dev->Adapter_AICTable[i].Device, NULL, 0);
        if (res != EIP201_STATUS_SUCCESS)
        {
            LOG_CRIT("%s: EIP201_Initialize() failed, error %d\n", __func__, res);
            return false; // error
        }
    }

    return true; // success
}


/*----------------------------------------------------------------------------
 * AdapterINT_AIC_Enable
 *
 */
static void
AdapterINT_AIC_Enable(cae_device *dev)
{
    unsigned int i;
    for (i = 0; i < ARRAY_ELEMCOUNT(dev->Adapter_AICTable); i++)
        if (!dev->Adapter_AICTable[i].isIRQ)
            Adapter_Interrupt_Enable(dev, dev->Adapter_AICTable[i].irq_idx, 0);
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupts_Init
 *
 */
bool
Adapter_Interrupts_Init(cae_device *dev,
        const int nIRQ)
{
    int i;
    int IntNr = nIRQ;

    LOG_INFO("\n\t\t %s \n", __func__);

    memcpy(dev->Adapter_AICTable, tmp_Adapter_AICTable, sizeof(tmp_Adapter_AICTable));
    memcpy(dev->Adapter_IRQTable, tmp_Adapter_IRQTable, sizeof(tmp_Adapter_IRQTable));

    if (AdapterINT_SetInternalLinkage(dev) < 0)
    {
        LOG_CRIT("Interrupt AIC and IRQ tables are inconsistent\n");
        return false;
    }

    // Initialize the AIC devices
    if (!AdapterINT_AIC_Init(dev))
        return false;

    // Initialize the dev->Adapter_IRQTable and tasklets.
    for (i=0; i<ARRAY_ELEMCOUNT(dev->Adapter_IRQTable); i++)
    {
        dev->Adapter_IRQTable[i].Handler = NULL;
        dev->Adapter_IRQTable[i].extra = NULL;
        dev->Adapter_IRQTable[i].Counter = 0;
        //if (dev->Adapter_IRQTable[i].fHaveTasklet)
            //tasklet_init(&dev->Adapter_IRQTable[i].tasklet,
            //             AdapterINT_CommonTasklet,
            //             (long)i);
        EIP201_Config_Change(dev, dev->Adapter_IRQTable[i].AIC->Device,
                             dev->Adapter_IRQTable[i].SourceBitMask,
                             dev->Adapter_IRQTable[i].Config);
        // Clear any pending egde-sensitive interrupts.
        EIP201_Acknowledge(dev, dev->Adapter_IRQTable[i].AIC->Device,
                           dev->Adapter_IRQTable[i].SourceBitMask);
    }

    // Request the IRQs for each AIC or register to IRQ of other AIC.
    for (i=0; i<ARRAY_ELEMCOUNT(dev->Adapter_AICTable); i++)
    {
        if (dev->Adapter_AICTable[i].isIRQ)
        {
            int res;

            LOG_INFO("\n\t\t %s: Request IRQ for AIC %s\n",
                     __func__,dev->Adapter_AICTable[i].name);

#ifdef ADAPTER_EIP202_USE_UMDEVXS_IRQ
            res = UMDevXS_Interrupt_Request(AdapterINT_TopHalfHandler,
                                            dev->Adapter_AICTable[i].irq_idx);
            IntNr = res;
#else
            {
                //struct device * Device_p;
                // Get device reference for this resource
                //Device_p = Device_GetReference(dev, NULL, NULL);
		if (dev->id == CAE0) {
			res = request_irq(IntNr,
                                  AdapterINT_TopHalfHandler,
                                  "core0",
                                  dev);
		} else {
			res = request_irq(IntNr,
                                  AdapterINT_TopHalfHandler,
                                  "core1",
                                  dev);
		}
            }
#endif
            if (res < 0)
            {
                LOG_CRIT("%s: Request IRQ error %d\n", __func__, res);
                return false;
            }
            else
            {
                dev->Adapter_AICTable[i].irq = IntNr;
                dev->IRQ_AIC_Mapping[IntNr] = dev->Adapter_AICTable + i;
                LOG_INFO("%s: Successfully hooked IRQ %d\n", __func__, IntNr);
            }
        }
        else
        {
            IntNr = dev->Adapter_AICTable[i].irq_idx;
            LOG_INFO("%s: Hook up AIC %s to chained IRQ %d\n",
                     __func__,
                     dev->Adapter_AICTable[i].name,
                     IntNr);
            if (IntNr < 0 || IntNr >= ADAPTER_MAX_INTERRUPTS)
            {
                LOG_CRIT("%s: IRQ %d out of range\n", __func__,IntNr);
            }
            dev->Adapter_IRQTable[IntNr].extra =  dev->Adapter_AICTable + i;
            Adapter_Interrupt_SetHandler(dev, IntNr, AdapterINT_ChainedAIC);
        }
    }

    // Enable AIC
    AdapterINT_AIC_Enable(dev);

    LOG_INFO("\n\t\t %s done\n", __func__);
    dev->Adapter_IRQ_Initialized = true;

    return true;
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupts_UnInit
 */
void
Adapter_Interrupts_UnInit(cae_device *dev, const int nIRQ)
{
    unsigned int i;
    IDENTIFIER_NOT_USED(nIRQ);

    LOG_INFO("\n\t\t %s \n", __func__);
    if (!dev->Adapter_IRQ_Initialized)
        return;

    // disable all interrupts
    for (i = 0; i < ARRAY_ELEMCOUNT(dev->Adapter_AICTable); i++)
    {
        if (dev->Adapter_AICTable[i].Device)
        {
            EIP201_SourceMask_DisableSource(dev, dev->Adapter_AICTable[i].Device,
                                            EIP201_SOURCE_ALL);
            dev->Adapter_AICTable[i].Device = NULL;
        }

        if(dev->Adapter_AICTable[i].isIRQ && dev->Adapter_AICTable[i].irq > 0)
        {
#ifdef ADAPTER_EIP202_USE_UMDEVXS_IRQ
            UMDevXS_Interrupt_Request(NULL,dev->Adapter_AICTable[i].irq_idx);
#else
            // Get device reference for this resource
            //struct device * Device_p = Device_GetReference(dev, NULL, NULL);

            LOG_INFO("%s: Free IRQ %d for AIC %s\n",
                     __func__,
                     dev->Adapter_AICTable[i].irq,
                     dev->Adapter_AICTable[i].name);

            // unhook the interrupt
            //free_irq(dev->Adapter_AICTable[i].irq, Device_p);

            LOG_INFO("%s: Successfully freed IRQ %d for AIC %s\n",
                     __func__,
                     dev->Adapter_AICTable[i].irq,
                     dev->Adapter_AICTable[i].name);
#endif
        }
    }

    // Kill all tasklets
    //for (i = 0; i < ARRAY_ELEMCOUNT(dev->Adapter_IRQTable); i++)
    //    if (dev->Adapter_IRQTable[i].fHaveTasklet) {
            //tasklet_kill(&dev->Adapter_IRQTable[i].tasklet);
	//}

    AdapterINT_Report_InterruptCounters(dev);

    ZEROINIT(dev->IRQ_AIC_Mapping);

    dev->Adapter_IRQ_Initialized = false;

    LOG_INFO("\n\t\t %s done\n", __func__);
}


#ifdef ADAPTER_PEC_RPM_EIP202_DEVICE0_ID
/*----------------------------------------------------------------------------
 * Adapter_Interrupts_Resume
 */
int
Adapter_Interrupts_Resume(cae_device *dev)
{
    LOG_INFO("\n\t\t %s \n", __func__);

    if (!dev->Adapter_IRQ_Initialized)
    {
        LOG_CRIT("%s: failed, not initialized\n", __func__);
        return -1;
    }

    // Resume AIC devices
    if (!AdapterINT_AIC_Init(dev))
        return -2; // error

    // Re-enable AIC interrupts
    AdapterINT_AIC_Enable(dev);

    LOG_INFO("\n\t\t %s done\n", __func__);

    return 0; // success
}
#endif


/* end of file adapter_interrupts.c */

/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2006 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Abstract : Encoder Wrapper Layer for 6280/7280/8270 without interrupts
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: ewl_x280_polling.c,v $
--  $Revision: 1.1 $
--
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    1. Include headers
------------------------------------------------------------------------------*/

#include "basetype.h"
#include "ewl.h"
#include "ewl_x280_common.h"
#include <common.h>


#ifndef EWL_NO_HW_TIMEOUT
#define EWL_WAIT_HW_TIMEOUT 2   /* HW IRQ timeout in seconds */
#endif

extern volatile u32 asic_status;

void HandleSIGIO(hx280ewl_t * enc)
{
    enc->sigio_needed = 0;  /* no need for SIGIO when polling */
    return;
}

/*******************************************************************************
 Function name   : EWLReserveHw
 Description     : Reserve HW resource for currently running codec
*******************************************************************************/
i32 EWLReserveHw(const void *inst)
{
    hx280ewl_t *enc = (hx280ewl_t *) inst;

    assert(enc != NULL);

    PTRACE("EWLReserveHw: PID %d trying to reserve ...\n", getpid());

    /* Check invalid parameters */
    if(inst == NULL)
        return EWL_ERROR;
    EWLWriteReg(inst, 0x38, 0);

    return EWL_OK;
}

/*******************************************************************************
 Function name   : EWLWaitHwRdy
 Description     : Wait for the encoder semaphore
 Return type     : i32 
 Argument        : void
*******************************************************************************/
//i32 EWLWaitHwRdy(const void *inst)
i32 EWLWaitHwRdy(const void *inst, u32 *slicesReady)
{
    hx280ewl_t *enc = (hx280ewl_t *) inst;
    volatile u32 irq_stats;

    i32 ret = EWL_HW_WAIT_TIMEOUT;
    u32 timeout = 1000;

    assert(enc != NULL);

    PTRACE("EWLWaitHwRdy\n");
    (void) enc;

    irq_stats = enc->pRegBase[1];

    PTRACE("IRQ stat %08x\n", irq_stats);

    if((irq_stats & ASIC_STATUS_ALL))
    {
        irq_stats &= (~(ASIC_IRQ_LINE));

        EWLWriteReg(inst, 0x04, irq_stats); /* clear IRQ */
        ret = EWL_OK;
    }
    else if(timeout)
    {
		int loop = 1;
        do
        {
            irq_stats = enc->pRegBase[1];
            if((irq_stats & ASIC_STATUS_ALL))
            {
                ret = EWL_HW_WAIT_OK;
                loop = 0;   /* end the polling loop */

                irq_stats &= (~ASIC_IRQ_LINE);
                EWLWriteReg(inst, 0x04, irq_stats); /* clear IRQ */
            }
        }
        while(loop);
    }

    asic_status = irq_stats;

    return ret;
}

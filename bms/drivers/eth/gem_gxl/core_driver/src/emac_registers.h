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
 * emac_registers.h
 * This file is used to include correct version of register headers (vm/non-vm).
 * 
 * Based on a compilation flag CEDI_USE_VM_HEADERS, 
 * right header is automatically included.
 *****************************************************************************/
#ifndef EMAC_REGISTERS_H
    #define EMAC_REGISTERS_H

    #ifdef CEDI_USE_VM_HEADERS
        #include "emac_regs_vm.h"
    #else
        #include "emac_regs_non_vm.h"
    #endif

#endif	/* EMAC_REGISTERS_H */

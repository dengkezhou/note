/* cs_driver_ext.h
 *
 * Top-level Product Configuration Settings specific for FPGA.
 */

/*****************************************************************************
* Copyright (c) 2010-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_CS_DRIVER_EXT_H
#define INCLUDE_GUARD_CS_DRIVER_EXT_H

// Enable Board control and reset.
//#define ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
//#define ADAPTER_GLOBAL_FPGA_HW_RESET_ENABLE
//#define ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE

// Driver license for the module registration with the Linux kernel
#define DRIVER_LICENSE  "Proprietary"

// FPGA DMA buffer alignment is 8 bytes
//#define DRIVER_DMA_ALIGNMENT_BYTE_COUNT     8

// Disable usage of the EIP-202 Ring Arbiter
#define DRIVER_EIP202_RA_DISABLE


/****************************************************************************
 * Adapter Global configuration parameters
 */

// FPGA board specific parameters
//#define ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
//#define ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
//#define ADAPTER_GLOBAL_FPGA_HW_RESET_ENABLE


#endif /* Include Guard */


/* end of file cs_driver_ext.h */

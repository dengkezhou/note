/* cs_hwpal_ext.h
 *
 * Security-IP-97 (FPGA) PCI chip specific configuration parameters
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

#ifndef CS_HWPAL_EXT_H_
#define CS_HWPAL_EXT_H_


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// For obtaining the IRQ number
#ifdef DRIVER_INTERRUPTS
#define HWPAL_INTERRUPTS
#endif

#define HWPAL_MAGIC_PCICONFIGSPACE  0xFF434647      // 43 46 47 = C F G

#define HWPAL_REMAP_ADDRESSES   ;

#define HWPAL_DEVICE_TO_FIND       "PCI.0" // PCI Bar 0

#define HWPAL_DEVICE_ADD_PCI    HWPAL_DEVICE_ADD("PCI_CONFIG_SPACE", 0,  \
                                  HWPAL_MAGIC_PCICONFIGSPACE,            \
                                  HWPAL_MAGIC_PCICONFIGSPACE + 1024,     \
                                  7)

// definition of static resources inside the PCI device
// Refer to the data sheet of device for the correct values
//                       Name         DevNr  Start    Last  Flags (see below)
#define HWPAL_DEVICES \
        HWPAL_DEVICE_ADD_PCI, \
        HWPAL_DEVICE_ADD("EIP97_GLOBAL",  0, 0,        0x3ffff,  7),  \
        HWPAL_DEVICE_ADD("EIP202_CDR0",   0, 0x0000,   0x0fff,   7),  \
        HWPAL_DEVICE_ADD("EIP202_RDR0",   0, 0x0000,   0x0fff,   7),  \
        HWPAL_DEVICE_ADD("EIP202_CDR1",   0, 0x1000,   0x1fff,   7),  \
        HWPAL_DEVICE_ADD("EIP202_RDR1",   0, 0x1000,   0x1fff,   7),  \
        HWPAL_DEVICE_ADD("EIP202_CDR2",   0, 0x2000,   0x2fff,   7),  \
        HWPAL_DEVICE_ADD("EIP202_RDR2",   0, 0x2000,   0x2fff,   7),  \
        HWPAL_DEVICE_ADD("EIP202_CDR3",   0, 0x3000,   0x3fff,   7),  \
        HWPAL_DEVICE_ADD("EIP202_RDR3",   0, 0x3000,   0x3fff,   7),  \
        HWPAL_DEVICE_ADD("EIP201_GLOBAL", 0, 0xf800,   0xf8ff,   7),  \
        HWPAL_DEVICE_ADD("EIP201_RING0",  0, 0xe000,   0xe0ff,   7),  \
        HWPAL_DEVICE_ADD("EIP201_RING1",  0, 0xd000,   0xd0ff,   7),  \
        HWPAL_DEVICE_ADD("EIP201_RING2",  0, 0xc000,   0xc0ff,   7),  \
        HWPAL_DEVICE_ADD("EIP201_RING3",  0, 0xb000,   0xb0ff,   7)

// Flags:
//   bit0 = Trace reads (requires HWPAL_TRACE_DEVICE_READ)
//   bit1 = Trace writes (requires HWPAL_TRACE_DEVICE_WRITE)
//   bit2 = Swap word endianess (requires HWPAL_DEVICE_ENABLE_SWAP)

#ifndef ARCH_ARM64
#define HWPAL_USE_MSI
#endif


#endif /* CS_HWPAL_EXT_H_ */


/* end of file cs_hwpal_ext.h */

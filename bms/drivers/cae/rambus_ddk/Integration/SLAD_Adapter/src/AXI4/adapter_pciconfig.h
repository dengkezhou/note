/* adapter_pciconfig.h
 *
 * This header file describes the PCI Configuration registers.
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

#ifndef INCLUDE_GUARD_ADAPTER_PCICONFIG_H
#define INCLUDE_GUARD_ADAPTER_PCICONFIG_H

// offset definitions for the interesting registers
#define PCICONFIG_REG_ID          0x00
#define PCICONFIG_REG_STATCMD     0x04
//#define PCICONFIG_REG_CLASSREV    0x08
#define PCICONFIG_REG_CONFIG      0x0C
//#define PCICONFIG_REG_BASEADDR_LO 0x10
//#define PCICONFIG_REG_BASEADDR_HI 0x14
//#define PCICONFIG_REG_SUBSYSTEM   0x2C
//#define PCICONFIG_REG_INTCFG      0x3C


/*----------------------------------------------------------------------------
 * PCICONFIG_REG_ID helper macros
 */
#define PCICONFIG_ID_EXTRACT_DEVICE(_regvalue) \
        (_regvalue >> 16) & 0xFFFF

#define PCICONFIG_ID_EXTRACT_VENDOR(_regvalue) \
        (_regvalue & 0xFFFF)


/*----------------------------------------------------------------------------
 * PCICONFIG_REG_STATCMD helper macros
 */
#define PCICONFIG_STATCMD_MEMORYACCESS_ENABLE  BIT_1
#define PCICONFIG_STATCMD_BUSMASTER_ENABLE     BIT_2
#define PCICONFIG_STATCMD_PARITYERR_ENABLE     BIT_6
#define PCICONFIG_STATCMD_SYSTEMERR_ENABLE     BIT_8


/*----------------------------------------------------------------------------
 * PCICONFIG_REG_CONFIG helper macros
 */
#define PCICONFIG_CONFIG_UPDATE_CACHELINESIZE(_Value, _CacheLineSize) \
        (_Value & ~0xFF) | (0xFF & (_CacheLineSize))

#define PCICONFIG_CONFIG_UPDATE_MASTERLATENCYTIMER(_Value,_MasterLatencyTimer)\
        (_Value & ~0xFF00) | (0xFF00 & ((_MasterLatencyTimer) << 8))

#endif /* Include Guard */

/* end of file adapter_pciconfig.h */

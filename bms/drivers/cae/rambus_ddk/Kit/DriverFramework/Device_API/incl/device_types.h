/* device_types.h
 *
 * Driver Framework, Device API, Type Definitions
 *
 * The document "Driver Framework Porting Guide" contains the detailed
 * specification of this API. The information contained in this header file
 * is for reference only.
 */

/*****************************************************************************
* Copyright (c) 2007-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_DEVICE_TYPES_H
#define INCLUDE_GUARD_DEVICE_TYPES_H

/*----------------------------------------------------------------------------
 * Device_Handle_t
 *
 * This handle represents a device, typically one hardware block instance.
 *
 * The Device API can access the static device resources (registers and RAM
 * inside the device) using offsets inside the device. This abstracts memory
 * map knowledge and simplifies device instantiation.
 *
 * Each device has its own configuration, including the endianness swapping
 * need for the words transferred. Endianness swapping can thus be performed
 * on the fly and transparent to the caller.
 *
 * The details of the handle are implementation specific and must not be
 * relied on, with one exception: NULL is guaranteed to be a non-existing
 * handle.
 */

typedef void * Device_Handle_t;


/*----------------------------------------------------------------------------
 * Device_Reference_t
 *
 * This is an implementation-specific reference for the device. It can
 * be passed from the implementation of the Device API to other modules
 * for use, for example, with OS services that require such a reference.
 *
 * The details of the handle are implementation specific and must not be
 * relied on, with one exception: NULL is guaranteed to be a non-existing
 * handle.
 */
typedef void * Device_Reference_t;


/*----------------------------------------------------------------------------
 * Device_Data_t
 *
 * This is an implementation-specific reference for the device. It can
 * be passed from the implementation of the Device API to other modules
 * for use, for example, with OS services that require such a reference.
 */
typedef struct
{
    // Physical address of the device mapped in memory
    void * PhysAddr;

} Device_Data_t;


// Device properties structure
typedef struct
{
    // Device name
    char * Name_p;

    // Device offset range inside system memory map
    unsigned int StartByteOffset;
    unsigned int LastByteOffset;

    // Implementation specific device flags
    char Flags;

} Device_Properties_t;


#endif /* Include Guard */


/* end of file device_types.h */

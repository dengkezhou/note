/* device_rw.h
 *
 * Driver Framework, Device API, Read/Write functions
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

#ifndef INCLUDE_GUARD_DEVICE_RW_H
#define INCLUDE_GUARD_DEVICE_RW_H

// Driver Framework Basic Defs API
#include "basic_defs.h"     // uint32_t, inline

// Driver Framework Device API
#include "device_types.h"   // Device_Handle_t


/*----------------------------------------------------------------------------
 * Device_Read32
 *
 * This function can be used to read one static 32bit resource inside a device
 * (typically a register or memory location). Since reading registers can have
 * side effects, the implementation must guarantee that the resource will be
 * read only once and no neighboring resources will be accessed.
 *
 * If required (decided based on internal configuration), on the fly endianness
 * swapping of the value read will be performed before it is returned to the
 * caller.
 *
 * Device (input)
 *     Handle for the device instance as returned by Device_Find.
 *
 * ByteOffset (input)
 *     The byte offset within the device for the resource to read.
 *
 * Return Value
 *     The value read.
 *
 * When the Device or Offset parameters are invalid, the implementation will
 * return an unspecified value.
 */

/*----------------------------------------------------------------------------
 * Device_Write32
 *
 * This function can be used to write one static 32bit resource inside a
 * device (typically a register or memory location). Since writing registers
 * can have side effects, the implementation must guarantee that the resource
 * will be written exactly once and no neighboring resources will be
 * accessed.
 *
 * If required (decided based on internal configuration), on the fly endianness
 * swapping of the value to be written will be performed.
 *
 * Device (input)
 *     Handle for the device instance as returned by Device_Find.
 *
 * ByteOffset (input)
 *     The byte offset within the device for the resource to write.
 *
 * Value (input)
 *     The 32bit value to write.
 *
 * Return Value
 *     None
 *
 * The write can only be successful when the Device and ByteOffset parameters
 * are valid.
 */

/*----------------------------------------------------------------------------
 * Device_Read32Array
 *
 * This function perform the same task as Device_Read32 for an array of
 * consecutive 32bit words, allowing the implementation to use a more optimal
 * burst-read (if available).
 *
 * See Device_Read32 for pre-conditions and a more detailed description.
 *
 * Device (input)
 *     Handle for the device instance as returned by Device_Find.
 *
 * StartByteOffset (input)
 *     Byte offset of the first resource to read.
 *     This value is incremented by 4 for each following resource.
 *
 * MemoryDst_p (output)
 *     Pointer to the memory where the retrieved words will be stored.
 *
 * Count (input)
 *     The number of 32bit words to transfer.
 *
 * Return Value
 *     None.
 */

/*----------------------------------------------------------------------------
 * Device_Write32Array
 *
 * This function perform the same task as Device_Write32 for an array of
 * consecutive 32bit words, allowing the implementation to use a more optimal
 * burst-write (if available).
 *
 * See Device_Write32 for pre-conditions and a more detailed description.
 *
 * Device (input)
 *     Handle for the device instance as returned by Device_Find.
 *
 * StartByteOffset (input)
 *     Byte offset of the first resource to write.
 *     This value is incremented by 4 for each following resource.
 *
 * MemorySrc_p (input)
 *     Pointer to the memory where the values to be written are located.
 *
 * Count (input)
 *     The number of 32bit words to transfer.
 *
 * Return Value
 *     None.
 */

#endif /* Include Guard */

/* end of file device_rw.h */

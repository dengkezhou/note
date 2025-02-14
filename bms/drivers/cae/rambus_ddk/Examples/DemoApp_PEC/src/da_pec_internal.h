/* da_internal.h
 *
 * Internal functions for Demo Application.
 */

/*****************************************************************************
* Copyright (c) 2016-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef DA_INTERNAL_H_
#define DA_INTERNAL_H_

#include <common.h>
#include <malloc.h>
#include <linux/mtd/compat.h>

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
#include "c_da_pec.h"             // configuration switches
#include "api_pec.h"
#include "api_pec_sg.h"
#include "api_dmabuf.h"

#include "sa_builder.h"


#ifdef DA_PEC_USERMODE
#include <stdlib.h>
#include <unistd.h>  // usleep

#define da_pec_malloc(s) malloc(s)
#define da_pec_free(s)   free(s)
#define da_pec_usleep(s) usleep(s)

#else

//#include <linux/init.h>
//#include <linux/module.h>
//#include <linux/kernel.h>       // printk
//#include <linux/slab.h>
//#include <asm/delay.h>          // udelay

#define da_pec_malloc(s) kmalloc(s, GFP_KERNEL)
#define da_pec_free(s)   kfree(s)
#define da_pec_usleep(s) udelay(s)


#endif

/****************************************************************
* Definitions and macros.
*****************************************************************/


// Number of DDK_PEC_IF_ID
#if defined DDK_PEC_IF_ID && !defined DA_PEC_COMBINED_DRIVER
#define INTERFACE_ID        DDK_PEC_IF_ID
#else
// PEC API interface ID not specified, defaulting to ID 0
#define INTERFACE_ID        0
#endif // DDK_PEC_IF_ID NOT DA_PEC_COMBINED_DRIVER


// Standard IOToken API
#include "iotoken.h"

#if defined(DA_PEC_IOTOKEN_EXT_SRV_ICEOCE)

// Extended IOToken API
#include "iotoken_ext_srv_iceoce.h"

// EIP-207 Firmware API
#include "firmware_eip207_api_cmd.h"

#elif defined(DA_PEC_IOTOKEN_EXT_SRV_ICE)

// Extended IOToken API
#include "iotoken_ext_srv_ice.h"

// EIP-207 Firmware API
#include "firmware_eip207_api_cmd.h"

#elif !defined(DA_PEC_EIP197)
#include "iotoken_ext_97.h"

#else
#error "Unknown IOToken engine configuration"
#endif

#if defined(DA_PEC_IOTOKEN_EXT_SRV_ICEOCE) || \
    defined(DA_PEC_IOTOKEN_EXT_SRV_ICE)
#define DA_PEC_IOTOKEN_EXT     // Enable extended IOToken API implementation
#endif



/*----------------------------------------------------------------------------
 * da_pec_pe_get_one
 *
 * Attempt to receive a single packet from the result descriptor ring.
 * Try this a configurable number of times. When a packet is received,
 * check its status and perform header post-processing.
 *
 * OutTokenDscr_p (output)
 *     Pointer to the Output Token descriptor that will be updated.
 *
 * OutTokenData_p (output)
 *     Pointer to the Output Token buffer where the token will be stored.
 *
 * RD_p (output)
 *     Pointer to the result descriptor that will be updated.
 *
 * Return
 *     0  : no packet received (timeout), IO error
 *            or packet processing error.
 *     >0 : number of packets received.
 */

/*----------------------------------------------------------------------------
 * da_pec_iotoken_create
 */
bool
da_pec_iotoken_create(
        IOToken_Input_Dscr_t * const Dscr_p,
        void * const Ext_p,
        uint32_t * Data_p,
        PEC_CommandDescriptor_t * const PEC_CmdDscr);


/*----------------------------------------------------------------------------
 * da_pec_invalidate_rec
 *
 * Invalidate specified transform record from the cache.
 *
 * Rec_p (input)
 *     DMABuf handle of record .
 *
 * Return
 *     true  : the invalidate succeeded
 *     false : the invalidate failed
 */
bool
da_pec_invalidate_rec(
        const DMABuf_Handle_t Rec_p);

/*----------------------------------------------------------------------------
 * da_pec_hmac_precompute
 *
 * Precompute the inner and outer digest parameters required by the SA Builder
 * for the HMAC operation.
 *
 * AuthAlgo (Input)
 *     One of the HMAC algorithms supported by the SA Builder.
 *
 * AuthKey_p (input)
 *     HMAC key.
 *
 * AuthKeyByteCount (input)
 *     Size of the HMAC key in bytes.
 *
 * Inner_p (output)
 *     Computed inner digest.
 *
 * Outer_p (output)
 *     Computed outer digest
 *
 * Return
 *     true  : Success
 *     false : failure
 */

/*----------------------------------------------------------------------------
 * da_pec_basic_hash
 * Compute a basic hash of a message.
 *
 * HashAlgo (input)
 *     Hash algorithm
 *
 * Input_p (input)
 *     Message data to be hashed.
 *
 * InputByteCount (input)
 *     Number of bytes in the message to be hashed.
 *
 * Output_p (output)
 *     Resulting hash of the message.
 *
 * OutputByteCount (input)
 *     Expedcted number of bytes of the hash.
 *
 * Finalize (input)
 *     If true, finalize the message (appending padding and message length)
 *     before computing the hash of the message.
 *     If false, do not finalize, just run the hash compression function on
 *     the data block supplied and return the contents of the intermediate
 *     digest. This is required for precomputing the HMAC inner and outer
 *     digest parameters for the SA builder.
 *
 * Return
 *     true  : Success
 *     false : failure
 */

/*----------------------------------------------------------------------------
 * da_pec_aes_block_encrypt
 *
 * Encrypt a single AES block.
 */

/*----------------------------------------------------------------------------
 * da_pec_basic_crypt_hash
 *
 */

/*----------------------------------------------------------------------------
 * da_pec_gcm
 *
 */

/*----------------------------------------------------------------------------
 * da_pec_ipsec_esp
 *
 */

/*----------------------------------------------------------------------------
 * da_pec_basic_sha3
 *
 */
bool
da_pec_basic_sha3(
        const bool fVerbose);


/*----------------------------------------------------------------------------
 * da_pec_basic_wireless
 *
 */
bool
da_pec_basic_wireless(
        const bool fVerbose);


/*----------------------------------------------------------------------------
 * da_pec_basic_multihash
 *
 */

#endif /* DA_INTERNAL_H_ */


/* end of file da_internal.h */

/* token_builder.h
 *
 * Token Builder API.
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


#ifndef TOKEN_BUILDER_H_
#define TOKEN_BUILDER_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "sa_builder_params.h"

// Driver Framework Basic Definitions API
#include "basic_defs.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
typedef enum
{
    TKB_STATUS_OK,
    TKB_INVALID_PARAMETER,
    TKB_BAD_PACKET,
    TKB_BAD_PROTOCOL,
    TKB_BAD_FIELD_SIZE,
    TKB_BAD_CRYPTO,
    TKB_ERROR,
} TokenBuilder_Status_t;

/* The Token Context Record is an opaque data structure that holds
   per-SA information needed by the Token Builder. Its contents are
   never used outside the Token Builder. The application refers to it
   via a void pointer and the application shall call
   TokenBuilder_GetContextSIze() to determine its size and allocate a
   sufficiently large buffer for it.

   The Token Context Record does not in any way refer to the
   SABuilder_SA_Params_t record from which it is derived and the
   latter may safely be discarded after the call to
   TokenBuilder_BuildContext().

   The Token Context Record is produced by TokenBuilder_BuildContext()
   and will be used by TokenBuilder_BuildToken(). The application has
   to make sure that this data structure is not modified and remains
   allocated as long as it is used. After its last use in a call to
   TokenBuilder_BuildToken(), it may safely be discarded.

   The Packet Token is a data structure used by some types of packet
   engine and is required to process the packet correctly. It must be
   generated separately for every single packet processed.

   The Packet Token is an opaque data structure as far as the application is
   concerned.. The application refers to it via a void pointer and the
   application shall call TokenBuilder_GettSIze() to determine its
   size and allocate a sufficiently large buffer for it..

   A Packet Token has a 32-bit header word, which is returned separately from
   the main Packet Token data structure.

   The Packet Token must remain allocated until it has been used by
   the hardware to process that packet.
*/

/* Per-packet flags */

/* For a basic hash operation, possibly spanning multiple packets,
 * indicate that this packet is the final one of the hash message
*/
#define TKB_PACKET_FLAG_HASHFINAL BIT_0

/* For a basic hash operation, possibly spanning multiple packets,
 * indicate that this packet is the first one of the hash message
*/
#define TKB_PACKET_FLAG_HASHFIRST BIT_1

/* For a basic hash operation, when the message consists of a single
 * packet, set both TKB_PACKET_FLAG_HASHFIRST and
 * TKB_PACKET_FLAG_HASHFINAL. For protocols such as IPsec, that always
 * hash per packet, those flags are not used and should not be set.
*/

/* Specify that the ARC4 state must be loaded */
#define TKB_PACKET_FLAG_ARC4_LOAD BIT_2

/* Specify that the ARC4 state must be saved */
#define TKB_PACKET_FLAG_ARC4_SAVE BIT_3

/* Specify that the initial ARC4 state must be derived from the key.
   Use this for the first packet encrypted or decrypted by each key, unless
   the state was loaded by SA Builder.*/
#define TKB_PARCKET_FLAG_ARC4_INIT BIT_4
#define TKB_PACKET_FLAG_ARC4_INIT BIT_4

/* Specify that the counter (for counter mode) must be reinitialized */
#define TKB_PACKET_FLAG_CTR_INIT BIT_5

/* Specify that hash must be appended to output packet */
#define TKB_PACKET_FLAG_HASHAPPEND BIT_6

/* Specify for AES-XTS (stateful) that the initial IV must be computed from
   Key2. */
#define TKB_PACKET_FLAG_XTS_INIT BIT_7


/* Structure to represent optional per-packet parameters */
typedef struct
{
    uint32_t PacketFlags; /* Per packet flags. Zero if none apply, bitwise
                              or of TKB_PACKET_FLAG_* constants. */
    uint32_t BypassByteCount; /* The number of bytes of the packet
                                that must be bypassed (copied
                                unmodified) */
    uint8_t PadByte;   /* A single-byte value that can be specified
                          per packet.
                          - Next Header for outbound IPsec.
                          - Record Type for outbound SSL/TLS
                          - Number of valid bits in last byte for SNOW/ZUC
                          - Pad alignment minus 1 for outbound basic
                            hash-encrypt.
                       */
    uint8_t *IV_p;      /* Only applies when IvSrc is SAB_IV_SRC_TOKEN */

    uint32_t AdditionalValue; /* Required for protocol-specific applications
                                 - Pad alignment for outbound IPSec/SSL/TLS
                                 - Number of pad bytes for inbound SSL/TLS
                                   (unless single-pass operation is enabled).
                                 - Rollover counter for outbound SRTP
                                 - SRTCP index for outbound SRTCP
                                 - AAD length for basic crypto/hash.
                                 - Count value for wireless algorithms
                                 - J value for AES-XTS */
    uint8_t *AAD_p;     /* Addtional authentication data, for basic crypto and
                           hash operations and also for combined
                           crypto-authentication algorithsms such as GCM.
                           If this is NULL, any additional authentication
                           data is at the start of the packet instead.
                         */
} TokenBuilder_Params_t;


/*----------------------------------------------------------------------------
 * TokenBuilder_GetContextSize
 *
 * Determine the size of the token context record in 32-bit words, which may
 * depend on the SA parameters.
 *
 * SAParams_p (input)
 *   Points to the SA parameters data structure
 * TokenContextWord32Count_p (output)
 *   Required size of the Token Context Record in 32-bit words.
 *
 * Return:
 * TKB_STATUS_OK if successful.
 * TKB_INVALID_PARAMETER if any of the pointer parameters is NULL or if
 *                      the contents of the input data structures are invalid.
 */
TokenBuilder_Status_t
TokenBuilder_GetContextSize(
    const SABuilder_Params_t * const SAParams_p,
    unsigned int * const TokenContextWord32Count_p);


/*----------------------------------------------------------------------------
 * TokenBuilder_BuildContext
 *
 * Create a Token Context Record.
 *
 * SAParams_p (input)
 *   Points to the SA parameters data structure. It is important that
 *   SABuilder_GetSIze() and SABuilder_BuildSA() have already been called
 *   for this SA.
 * TokenContext_p (output)
 *   Buffer to hold the Token Context Record. It must point to a valid
 *   storage buffer that is large enough to hold the Token
 *   Context. Before calling this function, the application must call
 *   TokeBuilder_GetContextSize() with the same SA parameters and
 *   allocate a buffer of that size.
 *
 * Return:
 * TKB_STATUS_OK if successful.
 * TKB_INVALID_PARAMETER if any of the pointer parameters is NULL or if
 *                      the contents of the SA parameters are invalid.
 */
TokenBuilder_Status_t
TokenBuilder_BuildContext(
    const SABuilder_Params_t * const SAParams_p,
    void * const TokenContext_p);


/*----------------------------------------------------------------------------
 * TokenBuilder_GetSize
 *
 * Determine the size of a packet token.
 *
 * TokenContext_p (input)
 *   Points to the Token Context Record.
 * TokenWord32Count_p (output)
 *   Expected size of the packet token in 32-bit words, depending on the
 *   contents of the Token Context Record. For some protocols, the
 *   actual token size depends on the packet contents as well, but in
 *   this case the maximum token size for that context is returned.
 *
 * Return:
 * TKB_STATUS_OK if successful.
 * TKB_INVALID_PARAMETER if any of the pointer parameters is NULL or if
 *                      the contents of the input data structures are invalid.
 */
TokenBuilder_Status_t
TokenBuilder_GetSize(
    const void * const TokenContext_p,
    unsigned int * const TokenWord32Count_p);


/*----------------------------------------------------------------------------
 * TokenBuilder_BuildToken
 *
 * Create a packet token, which is required by the packet engine to
 * process the packet correctly.
 *
 * TokenContext_p (input)
 *   Pointer to an initialized token context record, as
 *   produced by TokenBuilder_BuildContext().
 * Packet_p (input)
 *   Pointer to the packet to be processed.
 * PacketByteCount (input)
 *   Size of the packet in bytes (including any  bypass).
 * TKBParams_p (input)
 *   Additional per-packet parameters of the packet. Not all are defined for
 *   all protocols.
 * Token_p (output)
 *   Buffer to store the token. It must point to a valid storage
 *   buffer large enough to hold the packet token. Before calling this
 *   function, the application must call TokenBuilder_GetSize() with the
 *   same token context and allocate a buffer of that size.
 * TokenWord32Count_p (output)
 *   Actual size of the packet token in 32-bit words, which may be less
 *   than the size returned by TokebBuilder_GetSize().
 * TokenHeaderWord_p (output)
 *   Token Header Word. The Reuse Context field (bits 21..20) is always
 *   set to 1 1 (Force update before reload), which ensures correct
 *   operation. For performance reasons, the application could modify this
 *   field as follows, after calling this function and before submitting the
 *   token to the packet engine:
 *   - If the token is generated for a packet operation using the same SA
 *     as the previous operation on the same packet engine, change the field to
 *     0 1 (clear bit 21).
 *   - Else change the field to 0 0 (clear both bits 21 and 20).
 *
 * Return:
 * TKB_STATUS_OK if successful.
 * TKB_INVALID_PARAMETER if any of the pointer parameters is NULL or if
 *                      the contents of the token context are invalid.
 * TKB_BAD_PACKET if the packet has an invalid header or its size is out of
 *                range or its size is wrongly aligned for a block cipher.
 */
TokenBuilder_Status_t
TokenBuilder_BuildToken(void *ctx,
    const void * const TokenContext_p,
    const uint8_t *const Packet_p,
    const uint32_t PacketByteCount,
    const TokenBuilder_Params_t * const TKBParams_p,
    void * const Token_p,
    uint32_t * const TokenWord32Count_p,
    uint32_t * const TokenHeaderWord_p);


#endif /* TOKEN_BUILDER_H_ */


/* end of file token_builder.h */

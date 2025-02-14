/**
 * @file      pufs_hmac.h
 * @brief     PUFsecurity HMAC API interface
 * @copyright 2020 PUFsecurity
 */
/* THIS SOFTWARE IS SUPPLIED BY PUFSECURITY ''AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. TO THE FULLEST
 * EXTENT ALLOWED BY LAW, PUFSECURITY'S TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES,
 * IF ANY, THAT YOU HAVE PAID DIRECTLY TO PUFSECURITY FOR THIS SOFTWARE.
 */

#ifndef __PUFS_HMAC_H__
#define __PUFS_HMAC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "pufs_common.h"
#include "pufs_ka.h"
#include "pufs_dma.h"

/*****************************************************************************
 * Type definitions
 ****************************************************************************/
typedef struct pufs_hmac_context pufs_hmac_ctx;
typedef pufs_hmac_ctx pufs_hash_ctx;

/*****************************************************************************
 * Enumerations
 ****************************************************************************/
/**
 * @brief Cryptographic hash algorithms
 */
typedef enum {
    SHA_224,                ///< SHA224
    SHA_256,                ///< SHA256
    HASH_DEFAULT = SHA_256, ///< Default to SHA256
    SHA_384,                ///< SHA384
    SHA_512,                ///< SHA512
    SHA_512_224,            ///< SHA512/224
    SHA_512_256,            ///< SHA512/256
    SM3,                    ///< SM3
    N_HASH_T,               // keep in the last one
} pufs_hash_t;

/*****************************************************************************
 * API functions
 ****************************************************************************/
/**
 * @brief Initialize hmac/hash module
 *
 * @param[in] hmac_offset  hmac offset of memory map
 */
pufs_status_t pufs_hmac_module_init(uint32_t hmac_offset);
/**
 * @brief Obtain a pointer to HMAC internal context
 *
 * @return A pointer to HMAC internal context, or NULL if error
 */
pufs_hmac_ctx* pufs_hmac_ctx_new(void);
#define pufs_hash_ctx_new() pufs_hmac_ctx_new()
/**
 * @brief Free a pointer to HMAC internal context
 *
 * @param[in] hmac_ctx  A pointer to HMAC context.
 */
void pufs_hmac_ctx_free(pufs_hmac_ctx* hmac_ctx);
#define pufs_hash_ctx_free(hmac_ctx) pufs_hmac_ctx_free(hmac_ctx)
/**
 * @brief Initialize hash calculator
 *
 * @param[in] hmac_ctx  HMAC context.
 * @param[in] hash      Hash algorithm.
 * @return              SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_hash_init(pufs_hash_ctx* hash_ctx, pufs_hash_t hash);
/**
 * @brief Input data into hash calculator
 *
 * @param[in] hmac_ctx  HMAC context.
 * @param[in] msg       Message.
 * @param[in] msglen    Message length in bytes.
 * @return              SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_hash_update(pufs_hash_ctx* hash_ctx,
                               const uint8_t* msg,
                               uint32_t msglen);
/**
 * @brief Input SGDMA descriptors into hash calculator
 *
 * @param[in] hmac_ctx  HMAC context.
 * @param[in] descs     SGDMA descriptors
 * @param[in] descs_len the length of SGDMA descriptors
 * @param[in] last      set true if there is no more incoming descriptors
 * @return              SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_hash_sg_append(pufs_hash_ctx* hash_ctx,
                                  pufs_dma_sg_desc_st *descs,
                                  uint32_t descs_len,
                                  bool last);
/**
 * @brief In SGDMA mode, xtract message digest from hash calculator
 *
 * @param[in]  hmac_ctx  HMAC context.
 * @param[out] md        Message digest.
 * @return               SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_hash_sg_done(pufs_hash_ctx *hash_ctx,
                                pufs_dgst_st* md);
/**
 * @brief Extract message digest from hash calculator
 *
 * @param[in]  hmac_ctx  HMAC context.
 * @param[out] md        Message digest.
 * @return               SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_hash_final(pufs_hash_ctx* hash_ctx, pufs_dgst_st* md);
/**
 * @brief Calculate hash value of a message.
 *
 * @param[out] md      Message digest.
 * @param[in]  msg     Message.
 * @param[in]  msglen  Message length in bytes.
 * @param[in]  hash    Hash algorithm.
 * @return             SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_hash(pufs_dgst_st* md,
                        const uint8_t* msg,
                        uint32_t msglen,
                        pufs_hash_t hash);
/**
 * @brief Initialize HMAC calculator
 *
 * @param[in] hmac_ctx  HMAC context.
 * @param[in] hash      Hash algorithm.
 * @param[in] keytype   Key type.
 * @param[in] keyaddr   Key address.
 * @param[in] keybits   Key length in bits.
 * @return              SUCCESS on success, otherwise an error code.
 *
 * @note \em keyaddr may be a \ref pufs_rt_slot_t element, a \ref pufs_ka_slot_t
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_hmac_init(hmac_ctx, hash, keytype, keyaddr, keybits) \
    _pufs_hmac_init(hmac_ctx, hash, keytype, (size_t)keyaddr, keybits)
/**
 * @brief HMAC calculator initializer with keyaddr type casting
 *
 * @warning DO NOT call this function directly. Use pufs_hmac_init() instead.
 */
pufs_status_t _pufs_hmac_init(pufs_hmac_ctx* hmac_ctx,
                              pufs_hash_t hash,
                              pufs_key_type_t keytype,
                              size_t keyaddr,
                              uint32_t keybits);
/**
 * @brief Input data into HMAC calculator
 *
 * @param[in] hmac_ctx  HMAC context.
 * @param[in] msg     Message.
 * @param[in] msglen  Message length in bytes.
 * @return            SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_hmac_update(pufs_hmac_ctx* hmac_ctx,
                               const uint8_t* msg,
                               uint32_t msglen);
/**
 * @brief Input SGDMA descriptors into HMAC calculator
 *
 * @param[in] hmac_ctx  HMAC context.
 * @param[in] descs     SGDMA descriptors
 * @param[in] descs_len the length of SGDMA descriptors
 * @param[in] last      set true if there is no more incoming descriptors.
 * @return              SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_hmac_sg_append(pufs_hmac_ctx *hmac_ctx,
                                  pufs_dma_sg_desc_st *descs,
                                  uint32_t descs_len,
                                  bool last);
/**
 * @brief In SGDMA mode, xtract message digest from hash calculator
 *
 * @param[in]  hmac_ctx  HMAC context.
 * @param[out] md        Message digest.
 * @return               SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_hmac_sg_done(pufs_hmac_ctx *hmac_ctx,
                                pufs_dgst_st *md);
/**
 * @brief Extract message digest from HMAC calculator
 *
 * @param[in]  hmac_ctx  HMAC context.
 * @param[out] md        Message digest.
 * @return               SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_hmac_final(pufs_hmac_ctx* hmac_ctx, pufs_dgst_st* md);
/**
 * @brief Calculate HMAC hash value of a message with a key.
 *
 * @param[out] md       Message digest.
 * @param[in]  msg      Message.
 * @param[in]  msglen   Message length in bytes.
 * @param[in]  hash     Hash algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @return              SUCCESS on success, otherwise an error code.
 *
 * @note \em keyaddr may be a \ref pufs_rt_slot_t element, a \ref pufs_ka_slot_t
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_hmac(md, msg, msglen, hash, keytype, keyaddr, keybits)\
    _pufs_hmac(md, msg, msglen, hash, keytype, (size_t)keyaddr, keybits)
/**
 * @brief HMAC calculator with keyaddr type casting
 *
 * @warning DO NOT call this function directly. Use pufs_hmac() instead.
 */
pufs_status_t _pufs_hmac(pufs_dgst_st* md,
                         const uint8_t* msg,
                         uint32_t msglen,
                         pufs_hash_t hash,
                         pufs_key_type_t keytype,
                         size_t keyaddr,
                         uint32_t keybits);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_HMAC_H__ */
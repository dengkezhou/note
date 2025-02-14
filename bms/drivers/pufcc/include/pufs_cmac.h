/**
 * @file      pufs_cmac.h
 * @brief     PUFsecurity CMAC API interface
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

#ifndef __PUFS_CMAC_H__
#define __PUFS_CMAC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "pufs_common.h"
#include "pufs_ka.h"
#include "pufs_dma.h"

/*****************************************************************************
 * Type definitions
 ****************************************************************************/
typedef struct pufs_cmac_context pufs_cmac_ctx;

/*****************************************************************************
 * API functions
 ****************************************************************************/
/**
 * @brief Initialize cmac module
 *
 * @param[in] cmac_offset  cmac offset of memory map
 */
pufs_status_t pufs_cmac_module_init(uint32_t cmac_offset);
/**
 * @brief Obtain a pointer to CMAC internal context
 *
 * @return A pointer to CMAC internal context, or NULL if error
 */
pufs_cmac_ctx* pufs_cmac_ctx_new(void);
/**
 * @brief Free a pointer to CMAC internal context
 *
 * @param[in] cmac_ctx  A pointer to CMAC context.
 */
void pufs_cmac_ctx_free(pufs_cmac_ctx* cmac_ctx);
/**
 * @brief Initialize CMAC calculator
 *
 * @param[in] cmac_ctx  CMAC context to be initialized.
 * @param[in] cipher    Block cipher algorithm.
 * @param[in] keytype   Key type.
 * @param[in] keyaddr   Key address.
 * @param[in] keybits   Key length in bits.
 * @return              SUCCESS on success, otherwise an error code.
 *
 * @note \em keyaddr may be a \ref pufs_rt_slot_t element, a \ref pufs_ka_slot_t
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_cmac_init(cmac_ctx, cipher, keytype, keyaddr, keybits) \
    _pufs_cmac_init(cmac_ctx, cipher, keytype, (size_t)keyaddr, keybits)
/**
 * @brief CMAC calculator initializer with keyaddr type casting
 *
 * @warning DO NOT call this function directly. Use pufs_cmac_init() instead.
 */
pufs_status_t _pufs_cmac_init(pufs_cmac_ctx* cmac_ctx,
                              pufs_cipher_t cipher,
                              pufs_key_type_t keytype,
                              size_t keyaddr,
                              uint32_t keybits);
/**
 * @brief Input data into CMAC calculator
 *
 * @param[in] cmac_ctx  CMAC context.
 * @param[in] msg       Message.
 * @param[in] msglen    Message length in bytes.
 * @return              SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_cmac_update(pufs_cmac_ctx* cmac_ctx,
                               const uint8_t* msg,
                               uint32_t msglen);
/**
 * @brief Input SGDMA descriptors into CMAC calculator
 *
 * @param[in] cmac_ctx  CMAC context.
 * @param[in] descs     SGDMA descriptors
 * @param[in] descs_len the length of SGDMA descriptors
 * @param[in] last      set true if there is no more incoming descriptors
 * @return              SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_cmac_sg_append(pufs_cmac_ctx *cmac_ctx,
                                  pufs_dma_sg_desc_st *descs,
                                  uint32_t descs_len,
                                  bool last);
/**
 * @brief In SGDMA mode, extract message digest from CMAC calculator
 *
 * @param[in] cmac_ctx  CMAC context.
 * @param[out] md       Message digest.
 * @return              SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_cmac_sg_done(pufs_cmac_ctx *cmac_ctx, pufs_dgst_st *md);
/**
 * @brief Extract message digest from CMAC calculator
 *
 * @param[in] cmac_ctx  CMAC context.
 * @param[out] md       Message digest.
 * @return              SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_cmac_final(pufs_cmac_ctx *cmac_ctx, pufs_dgst_st *md);
/**
 * @brief Calculate CMAC hash value of a message with a key.
 *
 * @param[out] md       Message digest.
 * @param[in]  msg      Message.
 * @param[in]  msglen   Message length in bytes.
 * @param[in]  cipher   Block cipher algorithm.
 * @param[in]  keytype  Key type.
 * @param[in]  keyaddr  Key address.
 * @param[in]  keybits  Key length in bits.
 * @return              SUCCESS on success, otherwise an error code.
 *
 * @note \em keyaddr may be a \ref pufs_rt_slot_t element, a \ref pufs_ka_slot_t
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_cmac(md, msg, msglen, cipher, keytype, keyaddr, keybits) \
    _pufs_cmac(md, msg, msglen, cipher, keytype, (size_t)keyaddr, keybits)
/**
 * @brief CMAC calculator with keyaddr type casting
 *
 * @warning DO NOT call this function directly. Use pufs_cmac() instead.
 */
pufs_status_t _pufs_cmac(pufs_dgst_st* md,
                         const uint8_t* msg,
                         uint32_t msglen,
                         pufs_cipher_t cipher,
                         pufs_key_type_t keytype,
                         size_t keyaddr,
                         uint32_t keybits);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_CMAC_H__ */

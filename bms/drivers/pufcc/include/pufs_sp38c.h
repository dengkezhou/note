/**
 * @file      pufs_sp38c.h
 * @brief     PUFsecurity SP38C API interface
 * @copyright 2021 PUFsecurity
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

#ifndef __PUFS_SP38C_H__
#define __PUFS_SP38C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pufs_common.h"
#include "pufs_dma.h"
#include "pufs_ka.h"

/*****************************************************************************
 * Type definitions
 ****************************************************************************/
typedef struct pufs_sp38c_context pufs_sp38c_ctx;

typedef enum {
    CCM_AAD,
    CCM_PLAINTEXT,
} pufs_ccm_data_t;

/*****************************************************************************
 * API functions
 ****************************************************************************/
/**
 * @brief Initialize sp38c module
 *
 * @param[in] sp38c_offset  sp38c offset of memory map
 */
pufs_status_t pufs_sp38c_module_init(uintptr_t sp38c_offset);
/**
 * @brief Obtain a pointer to SP38C internal context
 *
 * @return A pointer to SP38C internal context, or NULL if error
 */
pufs_sp38c_ctx* pufs_sp38c_ctx_new(void);
/**
 * @brief Free a pointer to SP38C internal context
 *
 * @param[in] sp38c_ctx  A pointer to SP38C context.
 */
void pufs_sp38c_ctx_free(pufs_sp38c_ctx* sp38c_ctx);
/**
 * @brief Initialize CCM encryptor
 *
 * @param[in] sp38c_ctx  SP38C context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] nonce      Nonce.
 * @param[in] noncelen   Nonce length in bytes.
 * @param[in] aadlen     AAD length in bytes.
 * @param[in] inlen      Payload length in bytes.
 * @param[in] taglen     Tag length in bytes.
 * @return               SUCCESS on success, otherwise an error code.
 *
 * @note \em keyaddr may be a \ref pufs_rt_slot_t element, a \ref pufs_ka_slot_t
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_ccm_init(sp38c_ctx, cipher, keytype, keyaddr, keybits, nonce, noncelen, aadlen, inlen, taglen)\
    _pufs_enc_ccm_init(sp38c_ctx, cipher, keytype, (size_t)keyaddr, keybits, nonce, noncelen, aadlen, inlen, taglen)
/**
 * @brief CCM encryptor initializer with keyaddr type casting
 *
 * @warning DO NOT call this function directly. Use pufs_enc_ccm_init() instead.
 */
pufs_status_t _pufs_enc_ccm_init(pufs_sp38c_ctx* sp38c_ctx,
                                 pufs_cipher_t cipher,
                                 pufs_key_type_t keytype,
                                 size_t keyaddr,
                                 uint32_t keybits,
                                 const uint8_t* nonce,
                                 uint32_t noncelen,
                                 uint64_t aadlen,
                                 uint64_t inlen,
                                 uint32_t taglen);
/**
 * @brief Input data into CCM encryptor
 *
 * @param[in]  sp38c_ctx  SP38C context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return                SUCCESS on success, otherwise an error code.
 *
 * @note Input data may be either AAD or plaintext. Set \rm out to NULL when
 *       input AAD. Complete AAD data must be passed first before the plaintext.
 */
pufs_status_t pufs_enc_ccm_update(pufs_sp38c_ctx* sp38c_ctx,
                                  uint8_t* out,
                                  uint32_t* outlen,
                                  const uint8_t* in,
                                  uint32_t inlen);
/**
 * @brief Input SGDMA descriptors into CCM encryptor
 *
 * @param[in]  sp38c_ctx  SP38C context.
 * @param[in]  data_type  The input data type of descriptors.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors.
 * @return                SUCCESS on success, otherwise an error code.
 *
 * @note Input data may be either AAD or plaintext.
 *       The data length of each descriptor should be 16 * N bytes except the last one.
 *       For example, the length of descriptor could be 32 + 32 + 7.
 *       However, 5 + 5 + 5 is not allowed.
 */
pufs_status_t pufs_enc_ccm_sg_append(pufs_sp38c_ctx *sp38c_ctx,
                                     pufs_ccm_data_t data_type,
                                     pufs_dma_sg_desc_st *descs,
                                     uint32_t descs_len,
                                     bool last);
/**
 * @brief In SGDMA mode, finalize CCM encryptor
 *
 * @param[in]  sp38c_ctx  SP38C context.
 * @param[out] tag        Output Tag.
 * @return                SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_enc_ccm_sg_done(pufs_sp38c_ctx *sp38c_ctx, uint8_t *tag);
/**
 * @brief Finalize CCM encryptor
 *
 * @param[in]  sp38c_ctx  SP38C context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[out] tag        Output tag.
 * @return                SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_enc_ccm_final(pufs_sp38c_ctx* sp38c_ctx,
                                 uint8_t* out,
                                 uint32_t* outlen,
                                 uint8_t* tag);
/**
 * @brief Encryption using CCM mode.
 *
 * @param[out] out       Output data.
 * @param[out] outlen    Output data length in bytes.
 * @param[in]  in        Input data.
 * @param[in]  inlen     Input data length in bytes.
 * @param[in]  cipher    Block cipher algorithm.
 * @param[in]  keytype   Key type.
 * @param[in]  keyaddr   Key address.
 * @param[in]  keybits   Key length in bits.
 * @param[in]  nonce     Nonce.
 * @param[in]  noncelen  Nonce length in bytes.
 * @param[in]  aad       Additional authentication data.
 * @param[in]  aadlen    Additional authentication data length in bytes.
 * @param[out] tag       Output tag.
 * @param[in]  taglen    Specified output tag length in bytes.
 * @return               SUCCESS on success, otherwise an error code.
 *
 * @note \em keyaddr may be a \ref pufs_rt_slot_t element, a \ref pufs_ka_slot_t
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_enc_ccm(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     nonce, noncelen, aad, aadlen, tag, taglen)\
    _pufs_enc_ccm(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, nonce, noncelen, aad, aadlen, tag, taglen)
/**
 * @brief Encryption using CCM mode with keyaddr type casting.
 *
 * @warning DO NOT call this function directly. Use pufs_enc_ccm() instead.
 */
pufs_status_t _pufs_enc_ccm(uint8_t* out,
                            uint32_t* outlen,
                            const uint8_t* in,
                            uint32_t inlen,
                            pufs_cipher_t cipher,
                            pufs_key_type_t keytype,
                            size_t keyaddr,
                            uint32_t keybits,
                            const uint8_t* nonce,
                            uint32_t noncelen,
                            const uint8_t* aad,
                            uint32_t aadlen,
                            uint8_t* tag,
                            uint32_t taglen);
/**
 * @brief Initialize CCM decryptor
 *
 * @param[in] sp38c_ctx  SP38C context to be initialized.
 * @param[in] cipher     Block cipher algorithm.
 * @param[in] keytype    Key type.
 * @param[in] keyaddr    Key address.
 * @param[in] keybits    Key length in bits.
 * @param[in] nonce      Nonce.
 * @param[in] noncelen   Nonce length in bytes.
 * @param[in] aadlen     AAD length in bytes.
 * @param[in] inlen      Payload length in bytes.
 * @param[in] taglen     Tag length in bytes.
 * @return               SUCCESS on success, otherwise an error code.
 *
 * @note \em keyaddr may be a \ref pufs_rt_slot_t element, a \ref pufs_ka_slot_t
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_ccm_init(sp38c_ctx, cipher, keytype, keyaddr, keybits, nonce, noncelen, aadlen, inlen, taglen)\
    _pufs_dec_ccm_init(sp38c_ctx, cipher, keytype, (size_t)keyaddr, keybits, nonce, noncelen, aadlen, inlen, taglen)
/**
 * @brief CCM decryptor initializer with keyaddr type casting
 *
 * @warning DO NOT call this function directly. Use pufs_dec_ccm_init() instead.
 */
pufs_status_t _pufs_dec_ccm_init(pufs_sp38c_ctx* sp38c_ctx,
                                 pufs_cipher_t cipher,
                                 pufs_key_type_t keytype,
                                 size_t keyaddr,
                                 uint32_t keybits,
                                 const uint8_t* nonce,
                                 uint32_t noncelen,
                                 uint64_t aadlen,
                                 uint64_t inlen,
                                 uint32_t taglen);
/**
 * @brief Input data into CCM decryptor
 *
 * @param[in]  sp38c_ctx  SP38C context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  in         Input data.
 * @param[in]  inlen      Input data length in bytes.
 * @return                SUCCESS on success, otherwise an error code.
 *
 * @note Input data may be either AAD or plaintext. Set \rm out to NULL when
 *       input AAD. Complete AAD data must be passed first before the plaintext.
 */
pufs_status_t pufs_dec_ccm_update(pufs_sp38c_ctx* sp38c_ctx,
                                  uint8_t* out,
                                  uint32_t* outlen,
                                  const uint8_t* in,
                                  uint32_t inlen);
/**
 * @brief Input SGDMA descriptors into CCM decryptor
 *
 * @param[in]  sp38c_ctx  SP38C context.
 * @param[in]  data_type  The input data type of descriptors.
 * @param[in]  descs      SGDMA descriptors.
 * @param[in]  descs_len  The length of SGDMA descriptor array.
 * @param[in]  last       set true if there is no more incoming descriptors.
 * @return                SUCCESS on success, otherwise an error code.
 *
 * @note Input data may be either AAD or plaintext. 
 *       Complete AAD data must be passed first before the plaintext.
 *       The data length of each descriptor should be 16 * N bytes except the last one.
 *       For example, the length of descriptor could be 32 + 32 + 7.
 *       However, 5 + 5 + 5 is not allowed.
 */
pufs_status_t pufs_dec_ccm_sg_append(pufs_sp38c_ctx *sp38c_ctx,
                                     pufs_ccm_data_t data_type,
                                     pufs_dma_sg_desc_st *descs,
                                     uint32_t descs_len,
                                     bool last);
/**
 * @brief In SGDMA mode, finalize CCM decryptor
 *
 * @param[in]  sp38c_ctx  SP38C context.
 * @param[out] tag        Input Tag.
 * @return                SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_dec_ccm_sg_done(pufs_sp38c_ctx *sp38c_ctx, const uint8_t *tag);
/**
 * @brief Finalize CCM decryptor with tag output
 *
 * @param[in]  sp38c_ctx  SP38C context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[out] tag        Output tag.
 * @return                SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_dec_ccm_final_tag(pufs_sp38c_ctx *sp38c_ctx,
                                     uint8_t *out,
                                     uint32_t *outlen,
                                     uint8_t *tag);
/**
 * @brief Finalize CCM decryptor with tag checking
 *
 * @param[in]  sp38c_ctx  SP38C context.
 * @param[out] out        Output data.
 * @param[out] outlen     Output data length in bytes.
 * @param[in]  tag        Input tag.
 * @return                SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_dec_ccm_final(pufs_sp38c_ctx* sp38c_ctx,
                                 uint8_t* out,
                                 uint32_t* outlen,
                                 const uint8_t* tag);
/**
 * @brief Decryption using CCM mode.
 *
 * @param[out] out       Output data.
 * @param[out] outlen    Output data length in bytes.
 * @param[in]  in        Input data.
 * @param[in]  inlen     Input data length in bytes.
 * @param[in]  cipher    Block cipher algorithm.
 * @param[in]  keytype   Key type.
 * @param[in]  keyaddr   Key address.
 * @param[in]  keybits   Key length in bits.
 * @param[in]  nonce     Nonce.
 * @param[in]  noncelen  Nonce length in bytes.
 * @param[in]  aad       Additional authentication data.
 * @param[in]  aadlen    Additional authentication data length in bytes.
 * @param[in]  tag       Input tag.
 * @param[in]  taglen    Specified input tag length in bytes.
 * @return               SUCCESS on success, otherwise an error code.
 *
 * @note \em keyaddr may be a \ref pufs_rt_slot_t element, a \ref pufs_ka_slot_t
 *       element, or a memory address according to the \em keytype setting.
 * @warning Set \ref PUFKEY or \ref SHARESEC as \em keytype is not allowed.
 */
#define pufs_dec_ccm(out, outlen, in, inlen, cipher, keytype, keyaddr, keybits,\
                     nonce, noncelen, aad, aadlen, tag, taglen)\
    _pufs_dec_ccm(out, outlen, in, inlen, cipher, keytype, (size_t)keyaddr,\
                  keybits, nonce, noncelen, aad, aadlen, tag, taglen)
/**
 * @brief Decryption using CCM mode with keyaddr type casting.
 *
 * @warning DO NOT call this function directly. Use pufs_dec_ccm() instead.
 */
pufs_status_t _pufs_dec_ccm(uint8_t* out,
                            uint32_t* outlen,
                            const uint8_t* in,
                            uint32_t inlen,
                            pufs_cipher_t cipher,
                            pufs_key_type_t keytype,
                            size_t keyaddr,
                            uint32_t keybits,
                            const uint8_t* nonce,
                            int noncelen,
                            const uint8_t* aad,
                            int aadlen,
                            const uint8_t* tag,
                            int taglen);

/**
 * @brief A helper function to format the AAD info which is concatenated with the associated data.
 *        Please see A.2.2 Formatting of the Associated Data for more detail.
 *        Check `pufs_aes_ccm_enc_sg_test` and `pufs_aes_ccm_dec_sg_test` test functions to know how to use it.
 * 
 * @param[out] buf    output buffer for aad header
 * @param[in]  aadlen the length of original aad data
 * @warning    User MUST call this function to format AAD if user use SGDMA descriptors as input.
 */
uint32_t pufs_ccm_formatting_aad_header(uint8_t *buf, uint64_t aadlen);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_SP38C_H__ */

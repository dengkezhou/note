/**
 * @file      pufs_ka.h
 * @brief     PUFsecurity KA API interface
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

#ifndef __PUFS_KA_H__
#define __PUFS_KA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "pufs_common.h"

/*****************************************************************************
 * Enumerations
 ****************************************************************************/
/**
 * @brief Key types
 */
typedef enum {
    SWKEY = 0,    ///< Software key input from outside.
    OTPKEY = 1,   ///< Key stored in OTP. See OTPKEY_## in \ref pufs_rt_slot_t.
    PUFKEY = 2,   ///< Key stored in PUF. See PUFSLOT_## in \ref pufs_rt_slot_t.
    RANDKEY = 3,  ///< Key is generated by RNG.
    SHARESEC = 4, ///< Shared secret. See SHARESEC_## in \ref pufs_ka_slot_t.
    SSKEY = 5,    ///< Session/secret key. See SK###_## in \ref pufs_ka_slot_t.
    PRKEY,        ///< Private key. See PRK_## in \ref pufs_ka_slot_t.
} pufs_key_type_t;
/**
 * @brief Key array (KA) slots
 */
typedef enum {
    // session key slots
    SK128_0,     ///< 128-bit session key slot 0
    SK128_1,     ///< 128-bit session key slot 1
    SK128_2,     ///< 128-bit session key slot 2
    SK128_3,     ///< 128-bit session key slot 3
    SK128_4,     ///< 128-bit session key slot 4
    SK128_5,     ///< 128-bit session key slot 5
    SK128_6,     ///< 128-bit session key slot 6
    SK128_7,     ///< 128-bit session key slot 7
    SK256_0,     ///< 256-bit session key slot 0
    SK256_1,     ///< 256-bit session key slot 1
    SK256_2,     ///< 256-bit session key slot 2
    SK256_3,     ///< 256-bit session key slot 3
    SK512_0,     ///< 512-bit session key slot 0
    SK512_1,     ///< 512-bit session key slot 1
    // private key slots
    PRK_0,       ///< private key slot 0
    PRK_1,       ///< private key slot 1
    PRK_2,       ///< private key slot 2
    /// shared secret slot 0.
    SHARESEC_0,  ///< shared secret slot 0
    N_KA_SLOT_T, ///< keep in the last one
} pufs_ka_slot_t;
/**
 * @brief Key wrapping algorithms.
 */
typedef enum {
    AES_CBC_CS2, ///< AES-CBC-CS2
    AES_KW,      ///< AES_KW
    AES_KWP,     ///< AES_KWP
    AES_KW_INV,  ///< AES_KW with inserve cipher
    AES_KWP_INV, ///< AES_KWP with inverse cipher
    N_KEYWRAP_T, // keep in the last one
} pufs_key_wrap_t;

/*****************************************************************************
 * API functions
 ****************************************************************************/
/**
 * @brief Initialize KA module
 *
 * @param[in] ka_offset  ka offset of memory map
 */
pufs_status_t pufs_ka_module_init(uint32_t ka_offset);
/**
 * @brief Initialize KWP module
 *
 * @param[in] kwp_offset  kwp offset of memory map
 */
pufs_status_t pufs_kwp_module_init(uint32_t kwp_offset);
/**
 * @brief Import a plaintext key into Key Array.
 *
 * @param[in] keytype  Key type.
 * @param[in] slot     Key slot.
 * @param[in] key      Key.
 * @param[in] keybits  Key length in bits.
 * @return             SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_import_plaintext_key(pufs_key_type_t keytype,
                                        pufs_ka_slot_t slot,
                                        const uint8_t* key,
                                        uint32_t keybits);
/**
 * @brief Export a plaintext key from Key Array.
 *
 * @param[in] keytype  Key type.
 * @param[in] slot     Key slot.
 * @param[in] key      Key.
 * @param[in] keybits  Key length in bits.
 * @return             SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_export_plaintext_key(pufs_key_type_t keytype,
                                        pufs_ka_slot_t slot,
                                        uint8_t* key,
                                        uint32_t keybits);
/**
 * @brief Import an encrypted key into Key Array.
 *
 * @param[in] keytype  Key type.
 * @param[in] slot     Key slot.
 * @param[in] key      Wrapped key.
 * @param[in] keybits  Plaintext key length in bits.
 * @param[in] kekslot  KEK key slot.
 * @param[in] kekbits  KEK key length in bits.
 * @param[in] keywrap  Key wrapping algorithm.
 * @param[in] iv       Initial vector. iv can be NULL.
 * @return             SUCCESS on success, otherwise an error code.
 *
 * TODO: Add explanation on when iv should be NULL.
 */
pufs_status_t pufs_import_wrapped_key(pufs_key_type_t keytype,
                                       pufs_ka_slot_t slot,
                                       const uint8_t* key,
                                       uint32_t keybits,
                                       pufs_ka_slot_t kekslot,
                                       uint32_t kekbits,
                                       pufs_key_wrap_t keywrap,
                                       const uint8_t* iv);
/**
 * @brief Export an encrypted secret/session key or private key from Key Array.
 *
 * @param[in]  keytype  Key type.
 * @param[in]  slot     Key slot.
 * @param[out] key      Wrapped key.
 * @param[in]  keybits  Plaintext key length in bits.
 * @param[in]  kekslot  KEK key slot.
 * @param[in]  kekbits  KEK key length in bits.
 * @param[in]  keywrap  Key wrapping algorithm.
 * @param[in]  iv       Initial vector. iv can be NULL.
 * @return              SUCCESS on success, otherwise an error code.
 *
 * TODO: Add explanation on when iv should be NULL.
 */
pufs_status_t pufs_export_wrapped_key(pufs_key_type_t keytype,
                                       pufs_ka_slot_t slot,
                                       uint8_t* key,
                                       uint32_t keybits,
                                       pufs_ka_slot_t kekslot,
                                       uint32_t kekbits,
                                       pufs_key_wrap_t keywrap,
                                       const uint8_t* iv);
/**
 * @brief Free a slot in Key Array.
 *
 * @param[in] keytype  Key type.
 * @param[in] slot     Key slot.
 * @param[in] keybits  Plaintext key length in bits.
 *
 * @return SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_clear_key(pufs_key_type_t keytype,
                             pufs_ka_slot_t slot,
                             uint32_t keybits);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_KA_H__ */

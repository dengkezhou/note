/**
 * @file      pufs_crypto_internal.h
 * @brief     PUFsecurity Crypto Internal
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

#ifndef __PUFS_CRYPTO_INTERNAL_H__
#define __PUFS_CRYPTO_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "pufs_crypto.h"
#include "pufs_common.h"
#include "pufs_crypto_regs.h"

/*****************************************************************************
 * Macros
 ****************************************************************************/

#define CRYPTO_VERSION 0x5046A0A1

#define CRYPTO_IO_CTX_SIZE  144
#define CRYPTO_IO_CTX_NUM     8

#define crypto_write_regs(member, index, value) \
    _crypto_write_regs(offsetof(struct pufs_crypto_regs, member), index, value);

/*****************************************************************************
 * Variables
 ****************************************************************************/

extern struct pufs_crypto_regs *crypto_regs;

/*****************************************************************************
 * Internal Functions
 ****************************************************************************/

void _crypto_write_regs(uint32_t offset, uint32_t index, uint32_t value);

/**
 * @brief Write a software key to crypto engine
 *
 * @param[in] key
 * @param[in] length key length
 */
pufs_status_t crypto_write_sw_key(uint8_t *key, size_t length);

/**
 * @brief Write an initialize vector to crypto engine
 *
 * @param[in] iv
 * @param[in] length iv length
 */
pufs_status_t crypto_write_iv(uint8_t *iv, size_t length);

/**
 * @brief Read the vector from crypto engine
 *
 * @param[in] out    output buffer
 * @param[in] length iv length
 */
pufs_status_t crypto_read_iv(uint8_t *out, size_t length);

/**
 * @brief Write a dgst to crypto engine
 *
 * @param[in] dgst
 * @param[in] length dgst length
 */
pufs_status_t crypto_write_dgst(uint8_t *dgst, size_t length);

/**
 * @brief Read the dgst from crypto engine
 *
 * @param[in] out output buffer
 * @param[in] length length of output buffer
 */
void crypto_read_dgest(uint8_t *out, size_t length);

pufs_status_t crypto_check_ccm_algo(pufs_cipher_t cipher, uint32_t keybits);

pufs_status_t crypto_check_cmac_algo(pufs_cipher_t cipher, uint32_t keybits);

pufs_status_t crypto_check_sp38a_algo(pufs_cipher_t cipher, uint32_t keybits);

pufs_status_t crypto_check_sp38d_algo(pufs_cipher_t cipher, uint32_t keybits);

pufs_status_t crypto_check_sp38e_algo(pufs_cipher_t cipher, uint32_t keybits);

pufs_status_t crypto_check_chacha_algo(uint32_t keybits);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /*__PUFS_CRYPTO_INTERNAL_H__*/
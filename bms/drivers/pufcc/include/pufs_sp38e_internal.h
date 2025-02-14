/**
 * @file      pufs_sp38e_internal.h
 * @brief     PUFsecurity SP38E internal interface
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

#ifndef __PUFS_SP38E_INTERNAL_H__
#define __PUFS_SP38E_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pufs_sp38e.h"
#include "pufs_sp38e_regs.h"
#include "pufs_crypto_internal.h"

/*****************************************************************************
 * Macros
 ****************************************************************************/

#define SP38E_VERSION 0x33384500

/*****************************************************************************
 * Variables
 ****************************************************************************/

extern struct pufs_sp38e_regs *sp38e_regs;

/*****************************************************************************
 * Enumerations
 ****************************************************************************/
/**
 * enum type for GCM context protection
 */
typedef enum {
    SP38E_AVAILABLE,
    SP38E_TWEAK,
    SP38E_XTS,
} sp38e_op;

/*****************************************************************************
 * Structures
 ****************************************************************************/
/**
 * structure for context of block cipher XTS mode (128-bit block size)
 *
 * This structure keeps necessary information to trigger SP38E HW, including
 *  1. operation (AVAILABLE, TWEAK, XTS): op
 *  2. encryption or decryption: encrypt
 *  3. block cipher algotithm: cipher
 *  4. 2 key information for AES-XTS: {key, keybits, keyslot, keytype}[12]
 *     4.a key1 for plaintext encryption, might be read by sgdma
 *     4.b key2 for tweak generation, which is usually done without sgdma, for now?
 *  5. tweak: i
 *  6. minimum byte length of the last input data: minlen
 *  7. buffer for incomplete-block input: buff, buflen
 *  8. sequence number of the 128-bit block inside the data unit: j
 */
struct pufs_sp38e_context
{
    uint8_t buff[2 * BC_BLOCK_SIZE];
    uint8_t key2[SW_KEY_MAXLEN];
    uint32_t buflen;
    uint32_t keybits;
    uint32_t minlen;
    uint32_t keyslot1;
    uint32_t keyslot2;
    uint32_t j;
    pufs_key_type_t keytype1;
    pufs_key_type_t keytype2;
    bool encrypt;
    bool start;
    sp38e_op op;
    pufs_cipher_t cipher;
    uint8_t i[BC_BLOCK_SIZE];
    uint8_t dgst[DGST_INT_STATE_LEN];
    uint8_t key1[SW_KEY_MAXLEN]; // move here for sgdma
};

/*****************************************************************************
 * Internal functions
 ****************************************************************************/
/**
 * @brief SP38E GDLE preparation
 *
 * @param[in] sp38e_ctx  SP38E context.
 * @return               SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_gdle_xts_prepare(pufs_sp38e_ctx* sp38e_ctx);
/**
 * @brief SP38E GDLE post-processing
 *
 * @param[in] sp38e_ctx  SP38E context.
 * @return               SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_gdle_xts_postproc(pufs_sp38e_ctx* sp38e_ctx);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_SP38E_INTERNAL_H__ */

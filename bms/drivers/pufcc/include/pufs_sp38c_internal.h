/**
 * @file      pufs_sp38c_internal.h
 * @brief     PUFsecurity SP38C internal interface
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

#ifndef __PUFS_SP38C_INTERNAL_H__
#define __PUFS_SP38C_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pufs_sp38c.h"
#include "pufs_sp38c_regs.h"
#include "pufs_crypto_internal.h"

/*****************************************************************************
 * Macros
 ****************************************************************************/

#define SP38C_VERSION 0x33384301
#define DMA_KEY_CFG_0_CCM 0xB

/*****************************************************************************
 * Enumerations
 ****************************************************************************/
/**
 * enum type for CCM input
 */
typedef enum {
    SP38C_NONE,
    SP38C_AAD,
    SP38C_TEXT,
} sp38c_stage;
/**
 * enum type for CCM context protection
 */
typedef enum {
    SP38C_AVAILABLE,
    SP38C_CCM,
} sp38c_op;

/*****************************************************************************
 * Structures
 ****************************************************************************/
/**
 * structure for context of block cipher CCM mode (128-bit block size)
 *
 * This structure keeps necessary information to trigger SP38C HW, including
 *  1. operation (AVAILABLE, CCM): op
 *  2. encryption or decryption: encrypt
 *  3. block cipher algotithm: cipher
 *  4. key information for AES: key, keybits, keyslot, keytype
 *  5. counter blocks: i, ctri
 *  6. minimum byte length of the last input data: minlen
 *  7. buffer for incomplete-block input: buff, buflen
 *  8. intermediate CBC-MAC value: cbcmac
 *  9. byte lengths: aadlen, inlen, taglen
 *
 *  NOTE: Bool member(e.g. encrypt) should NOT be placed in front of `ctri`,
 *        or `ctri`(uint8[]) might start with non-word-aligned address, which
 *        might cause problems for the dma module.
 */
struct pufs_sp38c_context
{
    uint64_t aadlen;
    uint64_t inlen;
    uint64_t currentlen; // for block_number
    uint8_t buff[BC_BLOCK_SIZE];
    uint32_t qlen;
    uint32_t buflen;
    uint32_t keybits;
    uint32_t minlen;
    uint32_t keyslot;
    uint32_t taglen;
    pufs_key_type_t keytype;
    bool encrypt;
    bool ctr_start;
    bool cbcmac_start;
    sp38c_op op;
    sp38c_stage stage;
    pufs_cipher_t cipher;
    uint8_t ctri[IV_MAXLEN];
    uint8_t cbcmac[DGST_INT_STATE_LEN];  // only first-16 bytes are used
    uint8_t key[SW_KEY_MAXLEN];
};

/*****************************************************************************
 * Variables
 ****************************************************************************/

extern struct pufs_sp38c_regs *sp38c_regs;

/*****************************************************************************
 * Internal functions
 ****************************************************************************/
/**
 * @brief SP38C GDLE preparation
 *
 * @param[in] sp38c_ctx  SP38C context.
 * @param[in] out        The pointer to the output for register setting.
 * @param[in] inlen      The input text length in bytes.
 * @return               SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_gdle_ccm_prepare(pufs_sp38c_ctx* sp38c_ctx,
                                    const uint8_t* out,
                                    uint32_t inlen);
/**
 * @brief SP38C GDLE post-processing
 *
 * @param[in] sp38c_ctx  SP38C context.
 * @return               SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_gdle_ccm_postproc(pufs_sp38c_ctx* sp38c_ctx);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_SP38C_INTERNAL_H__ */

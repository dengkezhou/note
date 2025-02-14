/**
 * @file      pufs_crypto.c
 * @brief     PUFsecurity Crypto Engine API
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

//#include <stdio.h>
#include <string.h>

#include "pufs_reg_ctrl.h"
#include "pufs_internal.h"
#include "pufs_dma_internal.h"
#include "pufs_crypto_internal.h"

struct pufs_crypto_regs *crypto_regs = NULL;

/*****************************************************************************
 * Static functions
 ****************************************************************************/

// note: due to the 32bit bus, the length of src MUST be a multiple of 4
static void write_data(uint32_t *dst, uint8_t *src, size_t length)
{
    uint32_t *src32 = (uint32_t *)src;
    length = length / 4;

    for (size_t i = 0; i < length; ++i)
        *(dst + i) = be2le(*(src32 + i));

}

// Assume it is always valid to read (length / byte_per_word) + 1 words from src address.
static void read_data(uint8_t *dst, uint32_t *src, size_t length)
{
    uint32_t *dst32 = (uint32_t *)dst;
    uint32_t word_nums = 0, rest = 0, last_word;
    word_nums = length / 4;
    rest = length % 4;

    for (uint32_t i = 0; i < word_nums; i++)
        dst32[i] = be2le(src[i]);

    if (rest != 0)
    {
        last_word = be2le(src[word_nums]);
        memcpy(dst + (word_nums * 4), &last_word, rest);
    }
}

static pufs_status_t crypto_check_algo_support(uint32_t mask, pufs_cipher_t cipher, uint32_t keybits)
{
    uint32_t feature = crypto_regs->feature;

    if ((feature & mask) == 0)
        return E_UNSUPPORT;

    switch (cipher)
    {
    case AES:
        if ((feature & CRYPTO_FEATURE_AES_MASK) == 0)
            return E_UNSUPPORT;
        switch (keybits)
        {
        case 128:
            if ((feature & CRYPTO_FEATURE_AES_K128_MASK) == 0)
                return E_UNSUPPORT;
            break;
        case 192:
            if ((feature & CRYPTO_FEATURE_AES_K192_MASK) == 0)
                return E_UNSUPPORT;
            break;
        case 256:
            if ((feature & CRYPTO_FEATURE_AES_K256_MASK) == 0)
                return E_UNSUPPORT;
            break;
        default:
            return E_INVALID;
        }
        break;
    case SM4:
        if ((feature & CRYPTO_FEATURE_SM4_MASK) == 0)
            return E_UNSUPPORT;
        if (keybits != 128)
            return E_INVALID;
        break;
    case CHACHA:
        if (keybits != 128 && keybits != 256)
            return E_INVALID;
        break;
    default:
        return E_INVALID;
    }

    return SUCCESS;
}

pufs_status_t pufs_crypto_module_init(uintptr_t crypto_offset)
{
    crypto_regs = (struct pufs_crypto_regs *)(pufs_context.base_addr + crypto_offset);
    return version_check(CRYPTO_VERSION, crypto_regs->version);
}

void _crypto_write_regs(uint32_t offset, uint32_t index, uint32_t value)
{
    *((uint32_t *)(((uintptr_t)crypto_regs) + offset + index)) = value;
}

pufs_status_t crypto_write_sw_key(uint8_t *key, size_t length)
{
    if (length > SW_KEY_MAXLEN)
        return E_INVALID;
    
    write_data((uint32_t *)crypto_regs->sw_key, key, length);
    return SUCCESS;
}

pufs_status_t crypto_write_iv(uint8_t *iv, size_t length)
{
    if (length > IV_MAXLEN)
        return E_INVALID;
    
    write_data((uint32_t *)crypto_regs->iv, iv, length);
    return SUCCESS;
}

pufs_status_t crypto_read_iv(uint8_t *out, size_t length)
{
    length = length < IV_MAXLEN ? length : IV_MAXLEN;
    read_data(out, (void *)crypto_regs->iv_out, length);
    return SUCCESS;
}

pufs_status_t crypto_write_dgst(uint8_t *dgst, size_t length)
{
    if (length > DGST_INT_STATE_LEN)
        return E_INVALID;
    
    write_data((uint32_t *)crypto_regs->dgst_in, dgst, length);
    return SUCCESS;
}

// note: due to the 32bit bus, the length of src MUST be a multiple of 4
void crypto_read_dgest(uint8_t *out, size_t length)
{
    length = length < DGST_INT_STATE_LEN ? length : DGST_INT_STATE_LEN;
    read_data(out, (void *)crypto_regs->dgst_out, length);
}

pufs_status_t crypto_check_ccm_algo(pufs_cipher_t cipher, uint32_t keybits)
{
    return crypto_check_algo_support(CRYPTO_FEATURE_CCM_MASK, cipher, keybits);
}

pufs_status_t crypto_check_cmac_algo(pufs_cipher_t cipher, uint32_t keybits)
{
    return crypto_check_algo_support(CRYPTO_FEATURE_CMAC_MASK, cipher, keybits);
}

pufs_status_t crypto_check_sp38a_algo(pufs_cipher_t cipher, uint32_t keybits)
{
    return crypto_check_algo_support(CRYPTO_FEATURE_SP38A_MASK, cipher, keybits);
}

pufs_status_t crypto_check_sp38d_algo(pufs_cipher_t cipher, uint32_t keybits)
{
    return crypto_check_algo_support(CRYPTO_FEATURE_GCM_MASK, cipher, keybits);
}

pufs_status_t crypto_check_sp38e_algo(pufs_cipher_t cipher, uint32_t keybits)
{
    return crypto_check_algo_support(CRYPTO_FEATURE_XTS_MASK, cipher, keybits);
}

pufs_status_t crypto_check_chacha_algo(uint32_t keybits)
{
    return crypto_check_algo_support(CRYPTO_FEATURE_CHACHA_MASK, CHACHA, keybits);
}
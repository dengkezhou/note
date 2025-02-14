/**
 * @file      pufs_kwp_test.c
 * @brief     PUFsecurity KWP API test cases
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "pufs_common.h"
#include "pufs_pal.h"
#include "pufs_log.h"
#include "pufs_ka.h"
#include "pufs_rt.h"
#include "pufs_kdf.h"
#include "pufs_hmac.h"
#include "pufs_test_common.h"
#include "pufs_tv_aeskw.h"
#include "pufs_tv_aeskwp.h"
#include "pufs_memory_map.h"

/*****************************************************************************
 * Static functions
 ****************************************************************************/
static pufs_status_t pufs_export_key_rules(pufs_key_type_t kektype,
                                           pufs_key_type_t keytype)
{
    switch (kektype)
    {
    case PUFKEY:
        switch (keytype)
        {
        case SSKEY:
        case RANDKEY:
        case OTPKEY:
        case PUFKEY:
            return SUCCESS;
        default:
            return E_DENY;
        }
        break;
    case RANDKEY:
        switch (keytype)
        {
        case SSKEY:
        case RANDKEY:
            return SUCCESS;
        default:
            return E_DENY;
        }
        break;
    default:
        break;
    }
    return E_DENY;
}

pufs_status_t init_ka_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_crypto_test()) == SUCCESS &&
        (check = pufs_hmac_module_init(HMAC_HASH_ADDR_OFFSET)) == SUCCESS)
        check = pufs_kdf_module_init(KDF_ADDR_OFFSET);
    return check;
}

/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_key_export_test(void)
{
    const void* import_key = "98a8e2613bab4e0793a6fbe5b74a8043b8bbe619";
    uint8_t export_key[24];
    pufs_ka_slot_t keys[] = { SK128_0, SK128_1, SK128_2, SK128_3 };
    pufs_key_type_t keytypes[] = { SSKEY, RANDKEY, OTPKEY, PUFKEY };
    pufs_status_t check = SUCCESS;

    if (((check = pufs_import_plaintext_key(SSKEY, SK128_0, import_key, 128)) != SUCCESS) ||
        ((check = pufs_key_expansion(SSKEY, SK128_1, 128, PRF_HMAC, SHA_256, false, NULL, 0, 4, keytypes[1], 0, 128, NULL, 0)) != SUCCESS) ||
        ((check = pufs_key_expansion(SSKEY, SK128_2, 128, PRF_HMAC, SHA_256, false, NULL, 0, 4, keytypes[2], OTPKEY_0, 128, NULL, 0)) != SUCCESS) ||
        ((check = pufs_key_expansion(SSKEY, SK128_3, 128, PRF_HMAC, SHA_256, false, NULL, 0, 4, keytypes[3], PUFSLOT_1, 256, NULL, 0)) != SUCCESS))
    {
        LOG_ERROR("%s", "\t[FAILED] Key generation for different origin failed.");
        return check;
    }

    for (uint32_t i=0; i<4; i++)
        for (uint32_t j=0; j<4; j++)
        {
            check = pufs_export_wrapped_key(
                SSKEY, keys[j], export_key, 128, keys[i], 128, AES_KWP, NULL);
            if (check != pufs_export_key_rules(keytypes[i], keytypes[j]))
            {
                LOG_ERROR("KEK: %lu, Key: %lu -> Got status %s",
                        i, j, pufs_strstatus(check));
                return E_VERFAIL;
            }
        }

    pufs_clear_key(SSKEY, SK128_0, 128);
    pufs_clear_key(SSKEY, SK128_1, 128);
    pufs_clear_key(SSKEY, SK128_2, 128);
    pufs_clear_key(SSKEY, SK128_3, 128);
    return SUCCESS;
}

static pufs_status_t pufs_aes_key_wrapping_test(const uint32_t ntests,
                                       const struct kw_test_pattern *tp,
                                       pufs_key_wrap_t kwptype)
{
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    for (uint32_t i=0; i<ntests; i++)
    {
        if (tp[i].ptlen == 0)
            continue;

        pufs_dgst_st md1, md2;
        uint32_t kekbits = tp[i].keybits;
        uint32_t keybits = B2b(tp[i].ptlen);
        pufs_ka_slot_t kekslot = (kekbits > 128) ? SK256_2 : SK128_4;
        pufs_ka_slot_t keyslot = (keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen);

        if (((check = pufs_key_expansion(SSKEY, kekslot, kekbits, PRF_HMAC, SHA_256, false, NULL, 0, 4, PUFKEY, PUFSLOT_1, 256, NULL, 0)) != SUCCESS) ||
            ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].pt, keybits)) != SUCCESS) ||
            ((check = pufs_export_wrapped_key(SSKEY, keyslot, out, keybits, kekslot, kekbits, kwptype, NULL)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, keybits)) != SUCCESS) ||
            ((check = pufs_import_wrapped_key(SSKEY, keyslot, out, keybits, kekslot, kekbits, kwptype, NULL)) != SUCCESS) ||
            ((check = pufs_hmac(&md1, NULL, 0, SHA_256, SSKEY, keyslot, keybits)) != SUCCESS) ||
            ((check = pufs_hmac(&md2, NULL, 0, SHA_256, SWKEY, tp[i].pt, keybits)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, keybits)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, kekslot, kekbits)) != SUCCESS) ||
            ((check = (md1.dlen != md2.dlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(md1.dgst, md2.dgst, md1.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    free(out);
    return check;
}

pufs_status_t pufs_aes_kw_test(void)
{
    return pufs_aes_key_wrapping_test(sizeof(aes_wrap_tp) / sizeof(struct kw_test_pattern), aes_wrap_tp, AES_KW);
}

pufs_status_t pufs_aes_kw_inv_test(void)
{
    return pufs_aes_key_wrapping_test(sizeof(aes_wrap_tp) / sizeof(struct kw_test_pattern), aes_wrap_tp, AES_KW_INV);
}

pufs_status_t pufs_aes_kwp_test(void)
{
    return pufs_aes_key_wrapping_test(sizeof(aes_wrap_pad_tp) / sizeof(struct kw_test_pattern), aes_wrap_pad_tp, AES_KWP);
}

pufs_status_t pufs_aes_kwp_inv_test(void)
{
    return pufs_aes_key_wrapping_test(sizeof(aes_wrap_pad_tp) / sizeof(struct kw_test_pattern), aes_wrap_pad_tp, AES_KWP_INV);
}

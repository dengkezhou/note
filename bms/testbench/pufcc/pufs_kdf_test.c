/**
 * @file      pufs_kdf_test.c
 * @brief     PUFsecurity KDF API test cases
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
#include <string.h>
#include <malloc.h>

#include "pufs_test_common.h"
#include "pufs_log.h"
#include "pufs_kdf.h"
#include "pufs_tv_hkdfext.h"
#include "pufs_tv_hkdfexp.h"
#include "pufs_tv_ckdfexp.h"
#include "pufs_tv_skdfexp.h"
#include "pufs_tv_pbkdf.h"
#include "pufs_memory_map.h"

/*****************************************************************************
 * Static functions
 ****************************************************************************/
static pufs_status_t kdf2_test(const uint32_t ntests,
                      const struct kdf2_test_pattern *tp,
                      pufs_prf_family_t prf)
{
    pufs_status_t check = SUCCESS;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md1, md2;
        uint32_t kdkbits = B2b(tp[i].kilen);
        pufs_ka_slot_t keyslot = (tp[i].outlen > 32) ? SK512_0 : (tp[i].outlen > 16) ? SK256_0 : SK128_0;
        pufs_ka_slot_t kdkslot = (kdkbits > 256) ? SK512_1 : (kdkbits > 128) ? SK256_2 : SK128_4;
        if (((check = pufs_import_plaintext_key(SSKEY, kdkslot, tp[i].ki, kdkbits)) != SUCCESS) ||
            ((check = pufs_key_expansion(SSKEY, keyslot, B2b(tp[i].outlen), prf, tp[i].hash, tp[i].feedback, tp[i].iv, tp[i].ctrpos, tp[i].ctrlen, SSKEY, kdkslot, kdkbits, tp[i].info, tp[i].infolen)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, kdkslot, kdkbits)) != SUCCESS) ||
            ((check = pufs_hmac(&md1, NULL, 0, SHA_256, SSKEY, keyslot, B2b(tp[i].outlen))) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, B2b(tp[i].outlen))) != SUCCESS) ||
            ((check = pufs_hmac(&md2, NULL, 0, SHA_256, SWKEY, tp[i].ko, B2b(tp[i].outlen))) != SUCCESS) ||
            ((check = (md1.dlen != md2.dlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(md1.dgst, md2.dgst, md1.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
       }
    }
    return check;
}

static pufs_status_t kdf2_swkey_test(const uint32_t ntests,
                            const struct kdf2_test_pattern *tp,
                            pufs_prf_family_t prf)
{
    pufs_status_t check = SUCCESS;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md1, md2;
        pufs_ka_slot_t keyslot = (tp[i].outlen > 32) ? SK512_0 : (tp[i].outlen > 16) ? SK256_0 : SK128_0;
        if (((check = pufs_key_expansion(SSKEY, keyslot, B2b(tp[i].outlen), prf, tp[i].hash, tp[i].feedback, tp[i].iv, tp[i].ctrpos, tp[i].ctrlen, SWKEY, tp[i].ki, B2b(tp[i].kilen), tp[i].info, tp[i].infolen)) != SUCCESS) ||
            ((check = pufs_hmac(&md1, NULL, 0, SHA_256, SSKEY, keyslot, B2b(tp[i].outlen))) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, B2b(tp[i].outlen))) != SUCCESS) ||
            ((check = pufs_hmac(&md2, NULL, 0, SHA_256, SWKEY, tp[i].ko, B2b(tp[i].outlen))) != SUCCESS) ||
            ((check = (md1.dlen != md2.dlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(md1.dgst, md2.dgst, md1.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}

pufs_status_t init_kdf_test(void)
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
pufs_status_t pufs_ckdf2_test(void)
{
    return kdf2_test((sizeof(ckdf2_tp) / sizeof(struct kdf2_test_pattern)), ckdf2_tp,
              PRF_CMAC);
}

pufs_status_t pufs_ckdf2_swkey_test(void)
{
    return kdf2_swkey_test((sizeof(ckdf2_tp) / sizeof(struct kdf2_test_pattern)),
                    ckdf2_tp, PRF_CMAC);
}

pufs_status_t pufs_hkdf2_test(void)
{
    return kdf2_test((sizeof(hkdf2_tp) / sizeof(struct kdf2_test_pattern)), hkdf2_tp,
              PRF_HMAC);
}

pufs_status_t pufs_hkdf2_swkey_test(void)
{
    return kdf2_swkey_test((sizeof(hkdf2_tp) / sizeof(struct kdf2_test_pattern)),
                    hkdf2_tp, PRF_HMAC);
}

pufs_status_t pufs_skdf2_swkey_test(void)
{
    return kdf2_swkey_test((sizeof(skdf2_tp) / sizeof(struct kdf2_test_pattern)),
                    skdf2_tp, PRF_HASH);
}

pufs_status_t pufs_hkdf1_test(void)
{
    const uint32_t ntests = sizeof(hkdf1_tp) / sizeof(struct hkdf1_test_pattern);
    const struct hkdf1_test_pattern* tp = hkdf1_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md1, md2;
        pufs_ka_slot_t keyslot = (B2b(tp[i].ikmlen) > 256) ? SK512_0 : (B2b(tp[i].ikmlen) > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].ikm, B2b(tp[i].ikmlen))) != SUCCESS) ||
            ((check = pufs_kdf(SSKEY, SK512_1, 512, PRF_HMAC, tp[i].hash, false, NULL, 0, 1, SSKEY, keyslot, B2b(tp[i].ikmlen), tp[i].salt, tp[i].saltlen, NULL, 0)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, B2b(tp[i].ikmlen))) != SUCCESS) ||
            ((check = pufs_hmac(&md1, NULL, 0, tp[i].hash, SSKEY, SK512_1, 512)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, SK512_1, 512)) != SUCCESS) ||
            ((check = pufs_key_expansion(SSKEY, SK512_0, 512, PRF_HMAC, tp[i].hash, false, NULL, 0, 1, SWKEY, tp[i].prk, 256, NULL, 0)) != SUCCESS) ||
            ((check = pufs_hmac(&md2, NULL, 0, tp[i].hash, SSKEY, SK512_0, 512)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, SK512_0, 512)) != SUCCESS) ||
            ((check = (md1.dlen != md2.dlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(md1.dgst, md2.dgst, md1.dlen)) != SUCCESS))
        {
            pufs_clear_key(SSKEY, keyslot, B2b(tp[i].ikmlen));
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}

pufs_status_t pufs_hkdf1_swkey_test(void)
{
    const uint32_t ntests = sizeof(hkdf1_tp) / sizeof(struct hkdf1_test_pattern);
    const struct hkdf1_test_pattern* tp = hkdf1_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md1, md2;
        if (((check = pufs_kdf(SSKEY, SK512_0, 512, PRF_HMAC, tp[i].hash, false, NULL, 0, 1, SWKEY, tp[i].ikm, B2b(tp[i].ikmlen), tp[i].salt, tp[i].saltlen, NULL, 0)) != SUCCESS) ||
            ((check = pufs_hmac(&md1, NULL, 0, tp[i].hash, SSKEY, SK512_0, 512)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, SK512_0, 512)) != SUCCESS) ||
            ((check = pufs_key_expansion(SSKEY, SK512_0, 512, PRF_HMAC, tp[i].hash, false, NULL, 0, 1, SWKEY, tp[i].prk, 256, NULL, 0)) != SUCCESS) ||
            ((check = pufs_hmac(&md2, NULL, 0, tp[i].hash, SSKEY, SK512_0, 512)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, SK512_0, 512)) != SUCCESS) ||
            ((check = (md1.dlen != md2.dlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(md1.dgst, md2.dgst, md1.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}

pufs_status_t pufs_pbkdf_test(void)
{
    const uint32_t ntests = sizeof(pbkdf_tp) / sizeof(struct pbkdf_test_pattern);
    const struct pbkdf_test_pattern* tp = pbkdf_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md1, md2;
        uint32_t kbits = B2b(tp[i].keylen);
        uint32_t saltbits = B2b(tp[i].saltlen);
        pufs_ka_slot_t keyslot = (kbits > 256) ? SK512_0 : (kbits > 128) ? SK256_0 : SK128_0;
        pufs_ka_slot_t saltslot = (saltbits > 256) ? SK512_1 : (saltbits > 128) ? SK256_2 : SK128_4;
        if (((check = pufs_import_plaintext_key(SSKEY, saltslot, tp[i].salt, saltbits)) != SUCCESS) ||
            ((check = pufs_pbkdf(SSKEY, keyslot, kbits, PRF_HMAC, tp[i].hash, tp[i].iter, SSKEY, saltslot, saltbits, tp[i].pass, tp[i].passlen)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, saltslot, saltbits)) != SUCCESS) ||
            ((check = pufs_hmac(&md1, NULL, 0, tp[i].hash, SSKEY, keyslot, kbits)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, kbits)) != SUCCESS) ||
            ((check = pufs_hmac(&md2, NULL, 0, tp[i].hash, SWKEY, tp[i].key, kbits)) != SUCCESS) ||
            ((check = (md1.dlen != md2.dlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(md1.dgst, md2.dgst, md1.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}

pufs_status_t pufs_pbkdf_swkey_test(void)
{
    const uint32_t ntests = sizeof(pbkdf_tp) / sizeof(struct pbkdf_test_pattern);
    const struct pbkdf_test_pattern* tp = pbkdf_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md1, md2;
        uint32_t kbits = B2b(tp[i].keylen);
        pufs_ka_slot_t keyslot = (kbits > 256) ? SK512_0 : (kbits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_pbkdf(SSKEY, keyslot, kbits, PRF_HMAC, tp[i].hash, tp[i].iter, SWKEY, tp[i].salt, B2b(tp[i].saltlen), tp[i].pass, tp[i].passlen)) != SUCCESS) ||
            ((check = pufs_hmac(&md1, NULL, 0, tp[i].hash, SSKEY, keyslot, kbits)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, kbits)) != SUCCESS) ||
            ((check = pufs_hmac(&md2, NULL, 0, tp[i].hash, SWKEY, tp[i].key, kbits)) != SUCCESS) ||
            ((check = (md1.dlen != md2.dlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(md1.dgst, md2.dgst, md1.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}

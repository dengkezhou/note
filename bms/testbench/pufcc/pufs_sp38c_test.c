/**
 * @file      pufs_sp38c_test.c
 * @brief     PUFsecurity SP38C API test cases
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "pufs_pal.h"
#include "pufs_log.h"
#include "pufs_test_common.h"
#include "pufs_sp38c.h"
#include "pufs_tv_aesccm.h"
#include "pufs_memory_map.h"

#define CCM_DESC_MAX_LEN     4
#define CCM_AAD_BUFF_LEN    64

pufs_status_t init_sp38c_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_crypto_test()) == SUCCESS)
        check = pufs_sp38c_module_init(SP38C_ADDR_OFFSET);
    return check;
}

/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_aes_ccm_enc_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL, *tag = NULL;
    pufs_sp38c_ctx *sp38c_ctx = pufs_sp38c_ctx_new();
    if (sp38c_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen == 0 ? 1 : tp[i].ctlen);
        tag = malloc(tp[i].taglen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_ccm_init(sp38c_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].nonce, tp[i].noncelen, tp[i].aadlen, tp[i].ptlen, tp[i].taglen)) != SUCCESS) ||
            ((check = pufs_enc_ccm_update(sp38c_ctx, NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS) ||
            ((check = pufs_enc_ccm_update(sp38c_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_ccm_final(sp38c_ctx, out + outlen, &toutlen, tag)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tag, tp[i].tag, tp[i].taglen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
        free(tag);
    }
    pufs_sp38c_ctx_free(sp38c_ctx);
    return check;
}

pufs_status_t pufs_aes_ccm_enc_sg_test(void)
{
    pufs_status_t check = SUCCESS;
    pufs_dma_sg_desc_st descs[CCM_DESC_MAX_LEN];
    uint32_t index = 0, descs_len = 0, aad_aligned_len;
    uint8_t tag[BC_BLOCK_SIZE];
    void *pt_in = NULL, *out = NULL, *aad_in = NULL;

    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    
    pufs_sp38c_ctx *sp38c_ctx = pufs_sp38c_ctx_new();
    if (sp38c_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        if ((check = pufs_enc_ccm_init(sp38c_ctx,
                              tp[i].cipher, SSKEY, keyslot, tp[i].keybits,
                              tp[i].nonce, tp[i].noncelen,
                              tp[i].aadlen, tp[i].ptlen, tp[i].taglen)) != SUCCESS)
            goto done;

        // concatenate the generated AAD header and AAD
        aad_in = malloc(CCM_AAD_BUFF_LEN);
        memset(aad_in, 0x0, CCM_AAD_BUFF_LEN);
        index = pufs_ccm_formatting_aad_header((uint8_t *)aad_in, tp[i].aadlen);        
        memcpy((uint8_t*)aad_in + index, tp[i].aad, tp[i].aadlen);

        // the new length of AAD is AAD header + original tp[i].aadlen
        aad_aligned_len = ((tp[i].aadlen + index + (BC_BLOCK_SIZE - 1)) / BC_BLOCK_SIZE) * BC_BLOCK_SIZE;

        form_sg_descs(descs, &descs_len, CCM_DESC_MAX_LEN, NULL, aad_in, aad_aligned_len, 0, false);
        if (tp[i].aadlen > 0 && ((check = pufs_enc_ccm_sg_append(sp38c_ctx, CCM_AAD, descs, descs_len, true)) != SUCCESS))
            goto done;

        out = malloc(tp[i].ctlen == 0 ? 1 : tp[i].ctlen);
        pt_in = malloc(tp[i].ptlen);
        memcpy(pt_in, tp[i].pt, tp[i].ptlen);

        form_sg_descs(descs, &descs_len,  CCM_DESC_MAX_LEN, out, pt_in, tp[i].ptlen, 0, true);
        if (tp[i].ptlen > 0 && ((check = pufs_enc_ccm_sg_append(sp38c_ctx, CCM_PLAINTEXT, descs, descs_len, true)) != SUCCESS))
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_enc_ccm_sg_done(sp38c_ctx, tag)) != SUCCESS)
            goto done;

        if ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) == SUCCESS) 
            check = pufs_test_memcmp(tag, tp[i].tag, tp[i].taglen);
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(aad_in);
        free(pt_in);
        free(out);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38c_ctx_free(sp38c_ctx);
    return check;
}

pufs_status_t pufs_aes_ccm_enc_test(void)
{
    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL, *tag = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen == 0 ? 1 : tp[i].ctlen);
        tag = malloc(BC_BLOCK_SIZE);
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_ccm(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].nonce, tp[i].noncelen, tp[i].aad, tp[i].aadlen, tag, tp[i].taglen)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tag, tp[i].tag, tp[i].taglen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
        free(tag);
    }
    return check;
}

pufs_status_t pufs_aes_ccm_enc_swkey_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL, *tag = NULL;
    pufs_sp38c_ctx* sp38c_ctx = pufs_sp38c_ctx_new();
    if (sp38c_ctx == NULL)
    {
        LOG_INFO("\t[FAILED] %s\n", "{ ERROR MESSAGE HERE! }");
        return E_ERROR;
    }

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen == 0 ? 1 : tp[i].ctlen);
        tag = malloc(BC_BLOCK_SIZE);
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        if (((check = pufs_enc_ccm_init(sp38c_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].nonce, tp[i].noncelen, tp[i].aadlen, tp[i].ptlen, tp[i].taglen)) != SUCCESS) ||
            ((check = pufs_enc_ccm_update(sp38c_ctx, NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS) ||
            ((check = pufs_enc_ccm_update(sp38c_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_ccm_final(sp38c_ctx, out + outlen, &toutlen, tag)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tag, tp[i].tag, tp[i].taglen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
        free(tag);
    }
    pufs_sp38c_ctx_free(sp38c_ctx);
    return check;
}

pufs_status_t pufs_aes_ccm_enc_swkey_test(void)
{
    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL, *tag = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen == 0 ? 1 : tp[i].ctlen);
        tag = malloc(BC_BLOCK_SIZE);
        if (((check = pufs_enc_ccm(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].nonce, tp[i].noncelen, tp[i].aad, tp[i].aadlen, tag, tp[i].taglen)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tag, tp[i].tag, tp[i].taglen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
        free(tag);
    }
    return check;
}

pufs_status_t pufs_aes_ccm_enc_multi_ctx_test(void)
{
    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    pufs_status_t check = SUCCESS;

    pufs_sp38c_ctx** sp38c_ctxs = (pufs_sp38c_ctx**)malloc(ntests * sizeof(pufs_sp38c_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    uint8_t** tags = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38c_ctxs[i] = pufs_sp38c_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(51)) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((tags[i] = malloc(16)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_enc_ccm_init(sp38c_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].nonce, tp[i].noncelen, tp[i].aadlen, tp[i].ptlen, tp[i].taglen)) != SUCCESS)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_enc_ccm_update(sp38c_ctxs[i], NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_ccm_update(sp38c_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_ccm_final(sp38c_ctxs[i], outs[i] + outlens[i], &toutlen, tags[i])) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ctlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tags[i], tp[i].tag, tp[i].taglen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38c_ctx_free(sp38c_ctxs[i]);
    free(sp38c_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    for (uint32_t i=0; i<ntests; i++)
        free(tags[i]);
    free(tags);
    return check;
}

pufs_status_t pufs_aes_ccm_dec_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38c_ctx* sp38c_ctx = pufs_sp38c_ctx_new();
    if (sp38c_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {  
        out = malloc(tp[i].ptlen == 0 ? 1 : tp[i].ptlen);
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_ccm_init(sp38c_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].nonce, tp[i].noncelen, tp[i].aadlen, tp[i].ctlen, tp[i].taglen)) != SUCCESS) ||
            ((check = pufs_dec_ccm_update(sp38c_ctx, NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS) ||
            ((check = pufs_dec_ccm_update(sp38c_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_ccm_final(sp38c_ctx, out + outlen, &toutlen, tp[i].tag)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38c_ctx_free(sp38c_ctx);
    return check;
}

pufs_status_t pufs_aes_ccm_dec_sg_test(void)
{
    pufs_status_t check = SUCCESS;
    pufs_dma_sg_desc_st descs[CCM_DESC_MAX_LEN];
    uint32_t index = 0, descs_len = 0, aad_aligned_len;
    void *ct_in = NULL, *out = NULL, *aad_in = NULL;

    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;

    pufs_sp38c_ctx *sp38c_ctx = pufs_sp38c_ctx_new();
    if (sp38c_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        if ((check = pufs_dec_ccm_init(sp38c_ctx,
                              tp[i].cipher, SSKEY, keyslot, tp[i].keybits,
                              tp[i].nonce, tp[i].noncelen,
                              tp[i].aadlen, tp[i].ptlen, tp[i].taglen)) != SUCCESS)
            goto done;

        // concatenate the generated AAD header and AAD
        aad_in = malloc(CCM_AAD_BUFF_LEN);
        memset(aad_in, 0x0, CCM_AAD_BUFF_LEN);
        index = pufs_ccm_formatting_aad_header((uint8_t *)aad_in, tp[i].aadlen);
        memcpy((uint8_t*)aad_in + index, tp[i].aad, tp[i].aadlen);

        // the new length of AAD is AAD header + original tp[i].aadlen
        aad_aligned_len = ((tp[i].aadlen + index + (BC_BLOCK_SIZE - 1)) / BC_BLOCK_SIZE) * BC_BLOCK_SIZE;

        form_sg_descs(descs, &descs_len, CCM_DESC_MAX_LEN, NULL, aad_in, aad_aligned_len, 0, false);
        if (tp[i].aadlen > 0 && ((check = pufs_dec_ccm_sg_append(sp38c_ctx, CCM_AAD, descs, descs_len, true)) != SUCCESS))
            goto done;

        out = malloc(tp[i].ptlen);
        ct_in = malloc(tp[i].ctlen);
        memcpy(ct_in, tp[i].ct, tp[i].ctlen);

        form_sg_descs(descs, &descs_len, CCM_DESC_MAX_LEN, out, ct_in, tp[i].ctlen, 0, true);
        if (tp[i].ptlen > 0 && ((check = pufs_dec_ccm_sg_append(sp38c_ctx, CCM_PLAINTEXT, descs, descs_len, true)) != SUCCESS))
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_dec_ccm_sg_done(sp38c_ctx, tp[i].tag)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen);
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(aad_in);
        free(ct_in);
        free(out);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38c_ctx_free(sp38c_ctx);
    return check;
}

pufs_status_t pufs_aes_ccm_dec_test(void)
{
    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen == 0 ? 1 : tp[i].ptlen);
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_ccm(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].nonce, tp[i].noncelen, tp[i].aad, tp[i].aadlen, tp[i].tag, tp[i].taglen)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
    }
    return check;
}

pufs_status_t pufs_aes_ccm_dec_swkey_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38c_ctx* sp38c_ctx = pufs_sp38c_ctx_new();
    if (sp38c_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen == 0 ? 1 : tp[i].ptlen);
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        if (((check = pufs_dec_ccm_init(sp38c_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].nonce, tp[i].noncelen, tp[i].aadlen, tp[i].ctlen, tp[i].taglen)) != SUCCESS) ||
            ((check = pufs_dec_ccm_update(sp38c_ctx, NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS) ||
            ((check = pufs_dec_ccm_update(sp38c_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_ccm_final(sp38c_ctx, out + outlen, &toutlen, tp[i].tag)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38c_ctx_free(sp38c_ctx);
    return check;
}

pufs_status_t pufs_aes_ccm_dec_swkey_test(void)
{
    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen == 0 ? 1 : tp[i].ptlen);
        if (((check = pufs_dec_ccm(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].nonce, tp[i].noncelen, tp[i].aad, tp[i].aadlen, tp[i].tag, tp[i].taglen)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
    }
    return check;
}

pufs_status_t pufs_aes_ccm_dec_multi_ctx_test(void)
{
    const uint32_t ntests = sizeof(aes_ccm_tp) / sizeof(struct ccm_test_pattern);
    const struct ccm_test_pattern* tp = aes_ccm_tp;
    pufs_status_t check = SUCCESS;

    pufs_sp38c_ctx** sp38c_ctxs = (pufs_sp38c_ctx**)malloc(ntests * sizeof(pufs_sp38c_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38c_ctxs[i] = pufs_sp38c_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(51)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if (pufs_dec_ccm_init(sp38c_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].nonce, tp[i].noncelen, tp[i].aadlen, tp[i].ctlen, tp[i].taglen) != SUCCESS)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if (pufs_dec_ccm_update(sp38c_ctxs[i], NULL, NULL, tp[i].aad, tp[i].aadlen) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if (pufs_dec_ccm_update(sp38c_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].ct, tp[i].ctlen) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if (pufs_dec_ccm_final(sp38c_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].tag) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ptlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].pt, tp[i].ptlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38c_ctx_free(sp38c_ctxs[i]);
    free(sp38c_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

/**
 * @file      pufs_sm2_test.c
 * @brief     PUFsecurity SM2 API test cases
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

#include "pufs_test_common.h"
#include "pufs_log.h"
#include "pufs_sm2.h"
#include "pufs_tv_sm2_enc.h"
#include "pufs_tv_sm2_kex.h"
#include "pufs_tv_sm2_sign.h"
// Use init_pkc_test()
/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_sm2_dec_test(void)
{
    const uint32_t ntests = sizeof(sm2_enc_tp) / sizeof(struct sm2_enc_test_pattern);
    const struct sm2_enc_test_pattern* tp = sm2_enc_tp;
    pufs_status_t check = SUCCESS;

    uint8_t* out = NULL;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        uint32_t outlen;
        if (((check = pufs_import_plaintext_key(PRKEY, PRK_0, tp[i].prk, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
            ((check = pufs_sm2_dec(out, &outlen, tp[i].ct, tp[i].ctlen, PRK_0, SM2_C1C3C2)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_0, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
            ((check = (outlen == tp[i].ptlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].pt, out, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
        }
        free(out);
        if (check != SUCCESS)
            break;
    }
    return check;
}
pufs_status_t pufs_sm2_enc_test(void)
{
    const uint32_t ntests = sizeof(sm2_enc_tp) / sizeof(struct sm2_enc_test_pattern);
    const struct sm2_enc_test_pattern* tp = sm2_enc_tp;
    pufs_status_t check = SUCCESS;

    uint8_t* out = NULL;
    uint8_t* pt = NULL;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ec_point_st puk;
        uint32_t outlen, ptlen;
        out = malloc(tp[i].ctlen);
        pt  = malloc(tp[i].ptlen);
        puk.qlen = ecc_param[tp[i].name].len;
        memcpy(puk.x, tp[i].pukx, puk.qlen);
        memcpy(puk.y, tp[i].puky, puk.qlen);
        if (((check = pufs_sm2_enc(out, &outlen, tp[i].pt, tp[i].ptlen, puk, SM2_C1C3C2, NULL)) != SUCCESS) ||
            ((check = pufs_import_plaintext_key(PRKEY, PRK_0, tp[i].prk, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
            ((check = pufs_sm2_dec(pt, &ptlen, out, outlen, PRK_0, SM2_C1C3C2)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_0, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
            ((check = (ptlen == tp[i].ptlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].pt, pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
        }
        free(out);
        free(pt);
        if (check != SUCCESS)
            break;
    }
    return check;
}
pufs_status_t pufs_sm2_kex_test(void)
{
    const uint32_t ntests = sizeof(sm2_kex_tp) / sizeof(struct sm2_kex_test_pattern);
    const struct sm2_kex_test_pattern* tp = sm2_kex_tp;
    pufs_status_t check = SUCCESS;

    uint8_t* out = NULL;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].keylen);
        pufs_ec_point_st pukr, tpukr;
        pufs_dgst_st s2, s3;
        pukr.qlen = tpukr.qlen = ecc_param[tp[i].name].len;
        memcpy(pukr.x, tp[i].pukrx, pukr.qlen);
        memcpy(pukr.y, tp[i].pukry, pukr.qlen);
        memcpy(tpukr.x, tp[i].tpukrx, tpukr.qlen);
        memcpy(tpukr.y, tp[i].tpukry, tpukr.qlen);
        if (((check = pufs_import_plaintext_key(PRKEY, PRK_0, tp[i].prkl, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
            ((check = pufs_import_plaintext_key(PRKEY, PRK_1, tp[i].tprkl, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
            ((check = pufs_sm2_kex(&s2, &s3, out, B2b(tp[i].keylen), tp[i].idl, tp[i].idllen, tp[i].idr, tp[i].idrlen, PRK_0, PRK_1, &pukr, &tpukr, tp[i].init)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_0, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_1, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].check3, s3.dgst, s3.dlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].key, out, tp[i].keylen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
        }
        free(out);
        if (check != SUCCESS)
            break;
    }
    return check;
}
pufs_status_t pufs_sm2_verify_test(void)
{
    const uint32_t ntests = sizeof(sm2_sign_tp) / sizeof(struct sm2_sign_test_pattern);
    const struct sm2_sign_test_pattern* tp = sm2_sign_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ec_point_st puk;
        pufs_ecdsa_sig_st sig;
        puk.qlen = sig.qlen = ecc_param[tp[i].name].len;
        memcpy(puk.x, tp[i].pukx, puk.qlen);
        memcpy(puk.y, tp[i].puky, puk.qlen);
        memcpy(sig.r, tp[i].r, sig.qlen);
        memcpy(sig.s, tp[i].s, sig.qlen);
        if ((check = pufs_sm2_verify(sig, tp[i].msg, tp[i].msglen, tp[i].id, tp[i].idlen, puk)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
pufs_status_t pufs_sm2_sign_test(void)
{
    const uint32_t ntests = sizeof(sm2_sign_tp) / sizeof(struct sm2_sign_test_pattern);
    const struct sm2_sign_test_pattern* tp = sm2_sign_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ec_point_st puk;
        pufs_ecdsa_sig_st sig;
        puk.qlen = ecc_param[tp[i].name].len;
        memcpy(puk.x, tp[i].pukx, puk.qlen);
        memcpy(puk.y, tp[i].puky, puk.qlen);
        if (((check = pufs_import_plaintext_key(PRKEY, PRK_0, tp[i].prk, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
            ((check = pufs_sm2_sign(&sig, tp[i].msg, tp[i].msglen, tp[i].id, tp[i].idlen, PRK_0, NULL)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_0, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
            ((check = pufs_sm2_verify(sig, tp[i].msg, tp[i].msglen, tp[i].id, tp[i].idlen, puk)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}

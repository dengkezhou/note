/**
 * @file      pufs_ecp_test.c
 * @brief     PUFsecurity ECP API test cases
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
#include <stdbool.h>
#include <malloc.h>

#include "pufs_common.h"
#include "pufs_log.h"
#include "pufs_ecp.h"
#include "pufs_ecp_test.h"
#include "pufs_kdf.h"
#include "pufs_hmac.h"
#include "pufs_test_common.h"
#include "pufs_tv_ecpuk.h"
#include "pufs_tv_ecpkv.h"
#include "pufs_tv_ecccdh.h"
#include "pufs_tv_ecdsav.h"
#include "pufs_tv_ecdsas.h"
#include "pufs_tv_rsaexp.h"
#include "pufs_tv_rsax931.h"
#include "pufs_tv_rsap1v15.h"
#include "pufs_tv_rsapss.h"

// Use init_pkc_test()
/*****************************************************************************
 * Test functions
 ****************************************************************************/
/**
 * RSA verify test function
 */
pufs_status_t pufs_rsa_verify_test(void)
{
    const uint32_t ntests = sizeof(rsa_exp_tp) / sizeof(struct rsa_exp_test_pattern);
    const struct rsa_exp_test_pattern* tp = rsa_exp_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_rsa_verify(tp[i].s, tp[i].rsatype, tp[i].n, tp[i].e, tp[i].m)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * RSA sign test function
 */
pufs_status_t pufs_rsa_sign_test(void)
{
    const uint32_t ntests = sizeof(rsa_exp_tp) / sizeof(struct rsa_exp_test_pattern);
    const struct rsa_exp_test_pattern* tp = rsa_exp_tp;
    pufs_status_t check = SUCCESS;

    uint8_t out[512];
    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t len = 0;
        switch (tp[i].rsatype)
        {
        case RSA1024:
            len = 128;
            break;
        case RSA2048:
            len = 256;
            break;
        case RSA3072:
            len = 384;
            break;
        case RSA4096:
            len = 512;
            break;
        default:
            return E_INVALID;
        }
        memset(out, 0x0, 512);
        if ((check = pufs_rsa_sign(out, tp[i].rsatype, tp[i].n, tp[i].e, tp[i].d, tp[i].m, NULL)) != SUCCESS ||
            (check = pufs_test_memcmp(tp[i].s, out, len)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * RSA X9.31 verify test function
 */
pufs_status_t pufs_rsa_x931_verify_test(void)
{
    const uint32_t ntests = sizeof(rsa_x931_tp) / sizeof(struct rsa_x931_test_pattern);
    const struct rsa_x931_test_pattern* tp = rsa_x931_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_rsa_x931_verify(tp[i].s, tp[i].rsatype, tp[i].n, tp[i].e, tp[i].m, tp[i].mlen)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * RSA X9.31 sign test function
 */
pufs_status_t pufs_rsa_x931_sign_test(void)
{
    const uint32_t ntests = sizeof(rsa_x931_tp) / sizeof(struct rsa_x931_test_pattern);
    const struct rsa_x931_test_pattern* tp = rsa_x931_tp;
    pufs_status_t check = SUCCESS;

    uint8_t out[512];
    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t len = 0;
        switch (tp[i].rsatype)
        {
        case RSA1024:
            len = 128;
            break;
        case RSA2048:
            len = 256;
            break;
        case RSA3072:
            len = 384;
            break;
        case RSA4096:
            len = 512;
            break;
        default:
            return E_INVALID;
        }
        memset(out, 0x0, 512);
        if ((check = pufs_rsa_x931_sign(out, tp[i].rsatype, tp[i].n, tp[i].e, tp[i].d, tp[i].hash, tp[i].m, tp[i].mlen, NULL)) != SUCCESS ||
            (check = pufs_test_memcmp(tp[i].s, out, len)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * RSA PSS verify test function
 */
pufs_status_t pufs_rsa_pss_verify_test(void)
{
    const uint32_t ntests = sizeof(rsa_pss_tp) / sizeof(struct rsa_pss_test_pattern);
    const struct rsa_pss_test_pattern* tp = rsa_pss_tp;
    pufs_status_t check;

    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_rsa_pss_verify(tp[i].s, tp[i].rsatype, tp[i].n, tp[i].e, tp[i].hash, tp[i].m, tp[i].mlen)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * RSA PSS sign test function
 */
pufs_status_t pufs_rsa_pss_sign_test(void)
{
    const uint32_t ntests = sizeof(rsa_pss_tp) / sizeof(struct rsa_pss_test_pattern);
    const struct rsa_pss_test_pattern* tp = rsa_pss_tp;
    pufs_status_t check;

    uint8_t out[512];
    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t len = 0;
        switch (tp[i].rsatype)
        {
        case RSA1024:
            len = 128;
            break;
        case RSA2048:
            len = 256;
            break;
        case RSA3072:
            len = 384;
            break;
        case RSA4096:
            len = 512;
            break;
        default:
            return E_INVALID;
        }
        memset(out, 0x0, 512);
        if ((check = pufs_rsa_pss_sign(out, tp[i].rsatype, tp[i].n, tp[i].e, tp[i].d, tp[i].hash, tp[i].m, tp[i].mlen, tp[i].salt, tp[i].saltlen, NULL)) != SUCCESS ||
            (check = pufs_test_memcmp(tp[i].s, out, len)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}

/**
 * RSA PKCS#1 v1.5 verify test function
 */
pufs_status_t pufs_rsa_p1v15_verify_test(void)
{
    const uint32_t ntests = sizeof(rsa_p1v15_tp) / sizeof(struct rsa_p1v15_test_pattern);
    const struct rsa_p1v15_test_pattern* tp = rsa_p1v15_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_rsa_p1v15_verify(tp[i].s, tp[i].rsatype, tp[i].n, tp[i].e, tp[i].m, tp[i].mlen)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * RSA PKCS#1 v1.5 sign test function
 */
pufs_status_t pufs_rsa_p1v15_sign_test(void)
{
    const uint32_t ntests = sizeof(rsa_p1v15_tp) / sizeof(struct rsa_p1v15_test_pattern);
    const struct rsa_p1v15_test_pattern* tp = rsa_p1v15_tp;
    pufs_status_t check = SUCCESS;

    uint8_t out[512];
    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t len = 0;
        switch (tp[i].rsatype)
        {
        case RSA1024:
            len = 128;
            break;
        case RSA2048:
            len = 256;
            break;
        case RSA3072:
            len = 384;
            break;
        case RSA4096:
            len = 512;
            break;
        default:
            return E_ERROR;
        }
        memset(out, 0x0, 512);
        if ((check = pufs_rsa_p1v15_sign(out, tp[i].rsatype, tp[i].n, tp[i].e, tp[i].d, tp[i].hash, tp[i].m, tp[i].mlen, NULL)) != SUCCESS ||
            (check = pufs_test_memcmp(tp[i].s, out, len)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * ECP public key generation test function
 */
pufs_status_t pufs_ecp_ecpuk_test(void)
{
    const uint32_t ntests = sizeof(ecpuk_tp) / sizeof(struct ecpuk_test_pattern);
    const struct ecpuk_test_pattern* tp = ecpuk_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ec_point_st puk;
        if (((check = pufs_import_plaintext_key(PRKEY, PRK_0, tp[i].prk, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = pufs_ecp_set_curve_byname(tp[i].name)) != SUCCESS) ||
            ((check = pufs_ecp_gen_puk(&puk, PRKEY, PRK_0)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_0, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(puk.x, tp[i].Qx, puk.qlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * ECP public key validation test function
 */
pufs_status_t pufs_ecp_ecpkv_test(void)
{
    const uint32_t ntests = sizeof(ecpkv_tp) / sizeof(struct ecpkv_test_pattern);
    const struct ecpkv_test_pattern* tp = ecpkv_tp;
    pufs_status_t check = SUCCESS;

    pufs_ec_point_st puk;
    for (uint32_t i=0; i<ntests; i++)
    {
        puk.qlen = ecc_param[tp[i].name].len;
        memcpy(puk.x, tp[i].Qx, puk.qlen);
        memcpy(puk.y, tp[i].Qy, puk.qlen);
        if ((check = pufs_ecp_set_curve_byname(tp[i].name)) != SUCCESS)
            goto cleanup;

        check = pufs_ecp_validate_puk(puk, true);
        if (check != SUCCESS && check != E_VERFAIL)
            goto cleanup;

        if ((tp[i].valid == true && check == SUCCESS) ||
            (tp[i].valid == false && check == E_VERFAIL))
            check = SUCCESS;
        else
            check = E_VERFAIL;

cleanup:
        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * ECP ECC CDH test function
 */
pufs_status_t pufs_ecp_ecccdh_2e2s_test(void)
{
    const uint32_t ntests = sizeof(ecccdh_tp) / sizeof(struct ecccdh_test_pattern);
    const struct ecccdh_test_pattern* tp = ecccdh_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_ecp_set_curve_byname(tp[i].name)) != SUCCESS)
            goto cleanup;

        pufs_dgst_st md1, md2;
        uint8_t info[256], salt[64], kek[32], iv[16];
        pufs_ec_point_st puk0, puk1, puk2;
        pufs_rand(info, 64);
        pufs_rand(salt, 16);
        pufs_rand(kek, 8);
        pufs_rand(iv, 4);
        // ECC CDH -> KDF -> export
        if (((check = pufs_ecp_gen_eprk(PRK_0)) != SUCCESS) ||
            ((check = pufs_ecp_gen_eprk(PRK_1)) != SUCCESS) ||
            ((check = pufs_ecp_gen_eprk(PRK_2)) != SUCCESS) ||
            ((check = pufs_ecp_gen_puk(&puk0, PRKEY, PRK_0)) != SUCCESS) ||
            ((check = pufs_ecp_gen_puk(&puk1, PRKEY, PRK_1)) != SUCCESS) ||
            ((check = pufs_ecp_gen_puk(&puk2, PRKEY, PRK_2)) != SUCCESS) ||
            ((check = pufs_ecp_ecccdh_2e2s(puk1, puk2, PRK_0, PRKEY, PRK_1, NULL)) != SUCCESS) ||
            ((check = pufs_kdf(SSKEY, SK512_0, 512, PRF_HMAC, SHA_256, false, NULL, 0, 4, SHARESEC, SHARESEC_0, 0, salt, 64, info, 256)) != SUCCESS) ||
            ((check = pufs_hmac(&md1, NULL, 0, SHA_256, SSKEY, SK512_0, 512)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, SK512_0, 512)) != SUCCESS) ||
            ((check = pufs_ecp_ecccdh_2e2s(puk0, puk1, PRK_1, PRKEY, PRK_2, NULL)) != SUCCESS) ||
            ((check = pufs_kdf(SSKEY, SK512_1, 512, PRF_HMAC, SHA_256, false, NULL, 0, 4, SHARESEC, SHARESEC_0, 0, salt, 64, info, 256)) != SUCCESS) ||
            ((check = pufs_hmac(&md2, NULL, 0, SHA_256, SSKEY, SK512_1, 512)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, SK512_1, 512)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_0, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_1, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_2, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = (md1.dlen == md2.dlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(md1.dgst, md2.dgst, md1.dlen)) != SUCCESS))
            goto cleanup;

cleanup:
        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * ECP ECC CDH 2e test function
 */
pufs_status_t pufs_ecp_ecccdh_2e_test(void)
{
    const uint32_t ntests = sizeof(ecccdh_tp) / sizeof(struct ecccdh_test_pattern);
    const struct ecccdh_test_pattern* tp = ecccdh_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_ecp_set_curve_byname(tp[i].name)) != SUCCESS)
            goto cleanup;

        pufs_dgst_st md1, md2;
        uint8_t info[256], salt[64], kek[32], iv[16];
        pufs_ec_point_st puk0, puk1;
        pufs_rand(info, 64);
        pufs_rand(salt, 16);
        pufs_rand(kek, 8);
        pufs_rand(iv, 4);
        // ECC CDH -> KDF -> export
        if (((check = pufs_ecp_gen_eprk(PRK_0)) != SUCCESS) ||
            ((check = pufs_ecp_gen_eprk(PRK_1)) != SUCCESS) ||
            ((check = pufs_ecp_gen_puk(&puk0, PRKEY, PRK_0)) != SUCCESS) ||
            ((check = pufs_ecp_gen_puk(&puk1, PRKEY, PRK_1)) != SUCCESS) ||
            ((check = pufs_ecp_ecccdh_2e(puk1, PRK_0, NULL)) != SUCCESS) ||
            ((check = pufs_kdf(SSKEY, SK512_0, 512, PRF_HMAC, SHA_256, false, NULL, 0, 4, SHARESEC, SHARESEC_0, 0, salt, 64, info, 256)) != SUCCESS) ||
            ((check = pufs_hmac(&md1, NULL, 0, SHA_256, SSKEY, SK512_0, 512)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, SK512_0, 512)) != SUCCESS) ||
            ((check = pufs_ecp_ecccdh_2e(puk0, PRK_1, NULL)) != SUCCESS) ||
            ((check = pufs_kdf(SSKEY, SK512_1, 512, PRF_HMAC, SHA_256, false, NULL, 0, 4, SHARESEC, SHARESEC_0, 0, salt, 64, info, 256)) != SUCCESS) ||
            ((check = pufs_hmac(&md2, NULL, 0, SHA_256, SSKEY, SK512_1, 512)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, SK512_1, 512) != SUCCESS)) ||
            ((check = pufs_clear_key(PRKEY, PRK_0, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_1, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = (md1.dlen == md2.dlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(md1.dgst, md2.dgst, md1.dlen)) != SUCCESS))
            goto cleanup;
cleanup:
        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * ECP ECC CDH OSS test function
 */
pufs_status_t pufs_ecp_ecccdh_oss_test(void)
{
    const uint32_t ntests = sizeof(ecccdh_tp) / sizeof(struct ecccdh_test_pattern);
    const struct ecccdh_test_pattern* tp = ecccdh_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_ecp_set_curve_byname(tp[i].name)) != SUCCESS)
            goto cleanup;

        uint8_t out[72];
        pufs_ec_point_st puk;
        uint32_t fbits = ecc_param[tp[i].name].fbits;
        puk.qlen = ecc_param[tp[i].name].len;
        memcpy(puk.x, tp[i].Qx, puk.qlen);
        memcpy(puk.y, tp[i].Qy, puk.qlen);
        if (((check = pufs_import_plaintext_key(PRKEY, PRK_0, tp[i].prk, fbits)) != SUCCESS) ||
            ((check = pufs_ecp_ecccdh_2e(puk, PRK_0, out)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_0, fbits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].Z, puk.qlen)) != SUCCESS))
            goto cleanup;

cleanup:
        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * ECP ECDSA verification test function
 */
pufs_status_t pufs_ecp_ecdsa_verify_test(void)
{
    const uint32_t ntests = sizeof(ecdsav_tp) / sizeof(struct ecdsav_test_pattern);
    const struct ecdsav_test_pattern* tp = ecdsav_tp;
    pufs_status_t check = SUCCESS;

    pufs_dgst_st md;
    pufs_ec_point_st puk;
    pufs_ecdsa_sig_st sig;
    for (uint32_t i=0; i<ntests; i++)
    {
        md.dlen = ecc_param[tp[i].name].len;
        if (md.dlen > 64)
            md.dlen = 64;
        memcpy(md.dgst, tp[i].md, md.dlen);
        puk.qlen = ecc_param[tp[i].name].len;
        memcpy(puk.x, tp[i].Qx, puk.qlen);
        memcpy(puk.y, tp[i].Qy, puk.qlen);
        sig.qlen = ecc_param[tp[i].name].len;
        memcpy(sig.r, tp[i].r, sig.qlen);
        memcpy(sig.s, tp[i].s, sig.qlen);
        if ((check = pufs_ecp_set_curve_byname(tp[i].name)) != SUCCESS)
            goto cleanup;

        check = pufs_ecp_ecdsa_verify_dgst(sig, md, puk);
        if (check != SUCCESS && check != E_VERFAIL)
            goto cleanup;

        if ((tp[i].valid == true && check == SUCCESS) ||
            (tp[i].valid == false && check == E_VERFAIL))
            check = SUCCESS;
        else
            check = E_VERFAIL;

cleanup:
        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * ECP ECDSA verification with OTP key test function
 */
pufs_status_t pufs_ecp_ecdsa_verify_otpkey_test(void)
{
    const uint32_t ntests = sizeof(ecdsav_tp) / sizeof(struct ecdsav_test_pattern);
    const struct ecdsav_test_pattern* tp = ecdsav_tp;
    pufs_status_t check = SUCCESS;

    pufs_dgst_st md;
    pufs_ecdsa_sig_st sig;
    pufs_rt_slot_t keyidx = OTPKEY_0;
    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t keywlen = (ecc_param[tp[i].name].len + 3) / 4;
        if (keywlen > 8)
            return E_INVALID;        

        md.dlen = ecc_param[tp[i].name].len;
        if (md.dlen > 64)
            md.dlen = 64;
        memcpy(md.dgst, tp[i].md, md.dlen);
        sig.qlen = ecc_param[tp[i].name].len;
        memcpy(sig.r, tp[i].r, sig.qlen);
        memcpy(sig.s, tp[i].s, sig.qlen);
        if (((check = pufs_ecp_set_curve_byname(tp[i].name)) != SUCCESS) ||
            ((check = pufs_program_key2otp(keyidx, tp[i].Qx, 8 * ecc_param[tp[i].name].len)) != SUCCESS) ||
            ((check = pufs_program_key2otp(keyidx + keywlen, tp[i].Qy, 8 *ecc_param[tp[i].name].len)) != SUCCESS))
            goto cleanup;

        check = pufs_ecp_ecdsa_verify_dgst_otpkey(sig, md, keyidx);
        if ((check != SUCCESS) && (check != E_VERFAIL))
            goto cleanup;

       if ((tp[i].valid == true && check == SUCCESS) ||
            (tp[i].valid == false && check == E_VERFAIL))
            check = SUCCESS;
        else
            check = E_VERFAIL;

cleanup:
        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        keyidx += 2 * keywlen;
    }
    return check;
}
/**
 * ECP ECDSA sign with specific k test function
 */
pufs_status_t pufs_ecp_ecdsa_sign_k_test(void)
{
    const uint32_t ntests = sizeof(ecdsas_tp) / sizeof(struct ecdsas_test_pattern);
    const struct ecdsas_test_pattern* tp __attribute__((unused)) = ecdsas_tp;
    pufs_status_t check = SUCCESS;

    pufs_dgst_st md;
    pufs_ecdsa_sig_st sig;
    for (uint32_t i=0; i<ntests; i++)
    {
        md.dlen = ecc_param[tp[i].name].len;
        if (md.dlen > 64)
            md.dlen = 64;
        memcpy(md.dgst, tp[i].md, md.dlen);
        if (((check = pufs_import_plaintext_key(PRKEY, PRK_0, tp[i].prk, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = pufs_ecp_set_curve_byname(tp[i].name)) != SUCCESS) ||
            ((check = pufs_ecp_ecdsa_sign_dgst(&sig, md, PRKEY, PRK_0, tp[i].k)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_0, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(sig.r, tp[i].r, sig.qlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(sig.s, tp[i].s, sig.qlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}
/**
 * ECP ECDSA sign then verify test function
 */
pufs_status_t pufs_ecp_ecdsa_sign_verify_test(void)
{
    const uint32_t ntests = sizeof(ecdsas_tp) / sizeof(struct ecdsas_test_pattern);
    const struct ecdsas_test_pattern* tp = ecdsas_tp;
    pufs_status_t check = SUCCESS;

    pufs_dgst_st md;
    pufs_ec_point_st puk;
    pufs_ecdsa_sig_st sig;
    for (uint32_t i=0; i<ntests; i++)
    {
        md.dlen = ecc_param[tp[i].name].len;
        if (md.dlen > 64)
            md.dlen = 64;
        memcpy(md.dgst, tp[i].md, md.dlen);
        if (((check = pufs_ecp_set_curve_byname(tp[i].name)) != SUCCESS) ||
            ((check = pufs_import_plaintext_key(PRKEY, PRK_0, tp[i].prk, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = pufs_ecp_gen_puk(&puk, PRKEY, PRK_0)) != SUCCESS) ||
            ((check = pufs_ecp_ecdsa_sign_dgst(&sig, md, PRKEY, PRK_0, NULL)) != SUCCESS) ||
            ((check = pufs_clear_key(PRKEY, PRK_0, ecc_param[tp[i].name].fbits)) != SUCCESS) ||
            ((check = pufs_ecp_ecdsa_verify_dgst(sig, md, puk)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
    }
    return check;
}

pufs_status_t pufs_ecp_eprk_gen_test(void)
{
    pufs_status_t check = SUCCESS;
    pufs_ec_point_st puk;

    // Iterate through all possible curve and do eprk_gen
    for (pufs_ec_name_t curve = NISTB163; curve < N_ECNAME_T;curve++)
    {
        if (curve == SM2)   continue; // SM2 has no eprk_gen mprogm

        if (((check = pufs_ecp_set_curve_byname(curve))) ||
            ((check = pufs_ecp_gen_eprk(PRK_0))) != SUCCESS ||
            ((check = pufs_ecp_gen_puk(&puk, PRKEY, PRK_0))) != SUCCESS ||
            ((check = pufs_clear_key(PRKEY, PRK_0, ecc_param[curve].fbits)) != SUCCESS))
        {
            LOG_ERROR("Case %lu Failed.", (uint32_t)curve);
            return check;
        }
    }
    return check;
}

pufs_status_t pufs_ecp_sprk_gen_test(void)
{
    pufs_status_t check = SUCCESS;
    pufs_ec_point_st puk;
    pufs_ka_slot_t prvslot = PRK_0;
    pufs_rt_slot_t pufslot = PUFSLOT_1;
    const char *salt = "pufsecurity salt";
    const char *info = "pufsecurity info";
    
    pufs_ecp_set_curve_byname(NISTB163);
    if ((check = pufs_ecp_gen_sprk(prvslot, pufslot, (uint8_t *)salt, 16, (uint8_t *)info, 16, HASH_DEFAULT)) == SUCCESS)
        check = pufs_ecp_gen_puk(&puk, PRKEY, PRK_0);

    return check;
}

pufs_status_t pufs_ecp_ecdsa_verify_msg_test(void)
{
    const struct ecdsas_test_pattern* tp = &ecdsas_tp[0];
    pufs_status_t check = SUCCESS;
    pufs_ec_point_st puk;
    pufs_ecdsa_sig_st sig;
    pufs_dgst_st md;

#define VERIFY_IMG_SIZE (1024U * 48U)

    if (((check = pufs_hash(&md, (uint8_t *)0x14000000, VERIFY_IMG_SIZE, SHA_512)) != SUCCESS) ||
        ((check = pufs_ecp_set_curve_byname(tp->name)) != SUCCESS) ||
        ((check = pufs_import_plaintext_key(PRKEY, PRK_0, tp->prk, ecc_param[tp->name].fbits)) != SUCCESS) ||
        ((check = pufs_ecp_gen_puk(&puk, PRKEY, PRK_0)) != SUCCESS) ||
        ((check = pufs_ecp_ecdsa_sign_dgst(&sig, md, PRKEY, PRK_0, NULL)) != SUCCESS) ||
        ((check = pufs_clear_key(PRKEY, PRK_0, ecc_param[tp->name].fbits)) != SUCCESS) ||
        ((check = pufs_ecp_ecdsa_verify_dgst(sig, md, puk)) != SUCCESS))
    {
        LOG_ERROR("Sign and verify failed");
        return check;
    }
    uint64_t t;
    t = get_timer(0);
    pufs_hash(&md, (uint8_t *)0x14000000, VERIFY_IMG_SIZE, SHA_256);
    t = get_timer(t);
    printf("SHA_256 Time: %ldms\n", t);

    t = get_timer(0);
    pufs_hash(&md, (uint8_t *)0x14000000, VERIFY_IMG_SIZE, SHA_512);
    t = get_timer(t);
    printf("SHA_512 Time: %ldms\n", t);

    t = get_timer(0);
    if ((check = pufs_ecp_ecdsa_verify_msg(sig, (uint8_t *)0x14000000, VERIFY_IMG_SIZE, SHA_512, puk) != SUCCESS))
    {
        LOG_ERROR("Msg verify failed");
        return check;
    }
    t = get_timer(t);
    printf("Hash&ECDSA Verify Time: %ldms\n", t);

    return check;
}

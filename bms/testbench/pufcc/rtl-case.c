#include "rtl-case.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "pufs_test_common.h"
#include "pufs_memory_map.h"
#include "pufs_pal.h"
#include "pufs_log.h"
#include "pufs_chacha.h"
#include "pufs_chacha_test.h"
#include "pufs_sp38a.h"
#include "pufs_sp38a_test.h"
#include "pufs_sp38c.h"
#include "pufs_sp38d.h"
#include "pufs_sp38e.h"
#include "pufs_sp90a.h"
#include "pufs_cmac.h"
#include "pufs_cmac_test.h"
#include "pufs_dma.h"
#include "pufs_dma_test.h"
#include "pufs_ecp.h"
#include "pufs_ecp_test.h"
#include "pufs_kdf.h"
#include "pufs_hmac.h"
#include "pufs_hmac_test.h"
#include "pufs_ka.h"
#include "pufs_rt.h"
#include "pufs_rt_internal.h"
#include "pufs_rt_test.h"
#include "pufs_sm2.h"
#include "pufs_tv_chacha20.h"
#include "pufs_tv_chacha20-poly1305.h"
#include "pufs_tv_cmac.h"
#include "pufs_tv_ecpuk.h"
#include "pufs_tv_ecpkv.h"
#include "pufs_tv_ecccdh.h"
#include "pufs_tv_ecdsav.h"
#include "pufs_tv_ecdsas.h"
#include "pufs_tv_rsaexp.h"
#include "pufs_tv_rsax931.h"
#include "pufs_tv_rsap1v15.h"
#include "pufs_tv_rsapss.h"
#include "pufs_tv_sha2.h"
#include "pufs_tv_sm3.h"
#include "pufs_tv_hmac.h"
#include "pufs_tv_hkdfext.h"
#include "pufs_tv_hkdfexp.h"
#include "pufs_tv_ckdfexp.h"
#include "pufs_tv_skdfexp.h"
#include "pufs_tv_pbkdf.h"
#include "pufs_tv_sm2_enc.h"
#include "pufs_tv_sm2_kex.h"
#include "pufs_tv_sm2_sign.h"
#include "pufs_tv_aesecb.h"
#include "pufs_tv_aescfb.h"
#include "pufs_tv_aesofb.h"
#include "pufs_tv_aescbc.h"
#include "pufs_tv_aesctr.h"
#include "pufs_tv_sm4ecb.h"
#include "pufs_tv_sm4cfb.h"
#include "pufs_tv_sm4ofb.h"
#include "pufs_tv_sm4cbc.h"
#include "pufs_tv_sm4ctr.h"
#include "pufs_tv_aesccm.h"
#include "pufs_tv_aesgcm.h"
#include "pufs_tv_aesxts.h"
#include "pufs_tv_drbgctr.h"


bool rtl_enc_dec_chacha20_poly1305_test(void){
    pufs_status_t status;

    status = pufs_chacha20_poly1305_enc_test();
    if(status != SUCCESS){
        printf("Test Pufsecurity ChaCha20-Poly1305 CRYPTO encryption Failed.\n");
    }

    status = pufs_chacha20_poly1305_dec_test();
    if(status != SUCCESS){
        printf("Test Pufsecurity ChaCha20-Poly1305 CRYPTO decryption Failed.\n");
    }

    printf("Test Pufsecurity ChaCha20-Poly1305 CRYPTO Pass.\n");
    return true;
}
bool rtl_enc_dec_chacha_test(void){
    pufs_status_t status;

    status = pufs_chacha_enc_test();
    if(status != SUCCESS){
        printf("Test Pufsecurity ChaCha CRYPTO encryption Failed.\n");
    }

    status = pufs_chacha_dec_test();
    if(status != SUCCESS){
        printf("Test Pufsecurity ChaCha CRYPTO decryption Failed.\n");
    }

    printf("Test Pufsecurity ChaCha CRYPTO Pass.\n");
    return true;
}
bool rtl_hash_aes_cmac_test(void)
{
    pufs_status_t check = SUCCESS;
    const struct cmac_test_pattern* tp = cmac_tp;
    uint32_t i=0;
    
    pufs_dgst_st md;
    pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
    if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_cmac(&md, tp[i].msg, tp[i].msglen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS))
    {
        LOG_ERROR("Case%lu Failed.",  i);
        printf("Test Pufsecurity CMAC-AES Failed.\n");
        return false;
    }
    printf("Test Pufsecurity CMAC-AES Pass.\n");
    return true;
}
bool rtl_dma_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t *buff = malloc(16);
    if ((check = pufs_dump_rand_dma(buff, 16, false)) != SUCCESS)
    {
        LOG_ERROR("Failed to read dma %s", false ? "entropy" : "random");
        free(buff);
        printf("Test Pufsecurity DMA-Rand Failed.\n");
        return false;
    }

    check = E_VERFAIL;
    for (uint32_t i = 0; i < 16; i++)
    {
        if ((buff[i] != 0x0) && (buff[i] != 0xFF))
            check = SUCCESS;
    }
    
    free(buff);
    if(check != SUCCESS){
        printf("Test Pufsecurity DMA-Rand Failed.\n");
        return false;
    }

    printf("Test Pufsecurity DMA-Rand Pass.\n");
    return true;
}
bool rtl_sgdma_test(void)
{
    pufs_status_t check = SUCCESS;
    uint32_t desc_len = 0, msg_len;
    // FIXME: msg must be 32bytes until issue on AXI FIFO is resolved
    const char *msg = "this_is_test_for_dma_and_is_32B.";
    pufs_dma_sg_desc_st descs[2], fix_write_desc;
    void *in = NULL, *out = NULL;

    msg_len = strlen(msg);
    out = malloc(msg_len);
    in = malloc(msg_len);
    memcpy(in, msg, msg_len);

    form_sg_descs(descs, &desc_len, 2, out, in, msg_len, 32, true);
    descs[0].attr.fix_read_addr = true;
    descs[0].read_addr = PUFS_TEST_FIFO_ADDRESS;

    if ((check = pufs_dma_read_write_sg(&descs[0])) != SUCCESS)
        goto cleanup;
    
    fix_write_desc.length = msg_len;
    fix_write_desc.read_addr = PUFS_TEST_READ_ADDRESS;
    fix_write_desc.write_addr =  PUFS_TEST_FIFO_ADDRESS;
    fix_write_desc.attr.fix_write_addr = true;
    fix_write_desc.attr.fix_read_addr = false;
    fix_write_desc.attr.read_protect = 0;
    fix_write_desc.attr.write_protect = 0;

    check = pufs_dma_read_write_sg(&fix_write_desc);

cleanup:
    free(in);
    free(out);
    if(check == SUCCESS){
        printf("Test Pufsecurity SGDMA Pass.\n");
        return true;
    }else{
        printf("Test Pufsecurity SGDMA Failed.\n");
        return false;
    }
}
bool rtl_sign_valid_rsa_test(void)
{
    const struct rsa_exp_test_pattern* tp = rsa_exp_tp;
    pufs_status_t check = SUCCESS;
    uint32_t i=0;
    uint8_t out[512];
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
        printf("Test Pufsecurity RSA Sign Failed.\n");
        return false;
    }

    if ((check = pufs_rsa_verify(tp[i].s, tp[i].rsatype, tp[i].n, tp[i].e, tp[i].m)) != SUCCESS)
    {
        printf("Test Pufsecurity RSA Valid Failed.\n");
        return false;
    }

    printf("Test Pufsecurity RSA Sign&Valid Pass.\n");
    return true;
}
bool rtl_rsa_key_test(void)
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
    if(check != SUCCESS){
        printf("Test Pufsecurity RSA Key Failed.\n");
        return false;
    }

    check = pufs_ecp_validate_puk(puk, true);
    if(check != SUCCESS){
        printf("Test Pufsecurity RSA Key validate Failed.\n");
        return false;
    }

    printf("Test Pufsecurity RSA Key Pass.\n");
    return true;
}
bool rtl_rsa_ephemeral_key_test(void)
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
            printf("Test Pufsecurity RSA RSA Key-Ephemeral Failed.\n");
            return false;
        }
    }

    check = pufs_ecp_validate_puk(puk, true);
    if(check != SUCCESS){
        printf("Test Pufsecurity RSA RSA Key-Ephemeral validate Failed.\n");
        return false;
    }

    printf("Test Pufsecurity RSA Key-Ephemeral Pass.\n");
    return true;
}
bool rtl_sign_valid_ecdsa_dgst_test(void)
{
    const struct ecdsas_test_pattern* tp = ecdsas_tp;
    pufs_status_t check = SUCCESS;
    uint32_t i = 0;

    pufs_dgst_st md;
    pufs_ec_point_st puk;
    pufs_ecdsa_sig_st sig;

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
        printf("Test Pufsecurity ECDSA(dgst) Sign&Valid Failed.\n");
        return false;
    }
    
    printf("Test Pufsecurity ECDSA(dgst) Sign&Valid Pass\n");
    return true;

}
bool rtl_sign_valid_ecdsa_dgst_otpkey_test(void)
{
    const struct ecdsav_test_pattern* tp = ecdsav_tp;
    pufs_status_t check = SUCCESS;
    uint32_t i = 0;
    pufs_dgst_st md;
    pufs_ecdsa_sig_st sig;
    pufs_rt_slot_t keyidx = OTPKEY_0;

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
        printf("Test Pufsecurity ECDSA(OTP-KEY) Sign&Valid Failed.\n");
        return false;
    }
    
    printf("Test Pufsecurity ECDSA(OTP-KEY) Sign&Valid Pass.\n");
    return true;
}
bool rtl_hash_sm3_test(void)
{
    pufs_status_t check = SUCCESS;
    const struct hash_test_pattern* tp = sm3_tp;
    uint32_t i = 0;
    pufs_dgst_st md;

    if ((check = pufs_hash(&md, tp[i].msg, tp[i].msglen, tp[i].hash)) != SUCCESS ||
        (check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS)
    {
        printf("Test Pufsecurity SM3 Hash Failed.\n");
        return false;
    }

    printf("Test Pufsecurity SM3 Hash Pass.\n");
    return true;
}
bool rtl_hash_sha_test(void)
{
    pufs_status_t check = SUCCESS;
    const struct hash_test_pattern* tp = sha2_tp;
    uint32_t i = 10;
    pufs_dgst_st md;

    if ((check = pufs_hash(&md, tp[i].msg, tp[i].msglen, tp[i].hash)) != SUCCESS ||
        (check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS)
    {
        printf("Test Pufsecurity SHA-512-256 Hash Failed.\n");
        return false;
    }

    printf("Test Pufsecurity SHA-512-256 Hash Pass.\n");
    return true;
}
bool rtl_kdf_shared_secret_test(void)
{
    const struct hkdf1_test_pattern* tp = hkdf1_tp;
    pufs_status_t check = SUCCESS;
    uint32_t i=0;

    pufs_dgst_st md1, md2;
    pufs_ka_slot_t keyslot = (B2b(tp[i].ikmlen) > 256) ? SK512_0 : (B2b(tp[i].ikmlen) > 128) ? SK256_0 : SK128_0;
    if (((check = pufs_import_plaintext_key(SHARESEC, keyslot, tp[i].ikm, B2b(tp[i].ikmlen))) != SUCCESS) ||
        ((check = pufs_kdf(SHARESEC, SK512_1, 512, PRF_HMAC, tp[i].hash, false, NULL, 0, 1, SHARESEC, keyslot, B2b(tp[i].ikmlen), tp[i].salt, tp[i].saltlen, NULL, 0)) != SUCCESS) ||
        ((check = pufs_clear_key(SHARESEC, keyslot, B2b(tp[i].ikmlen))) != SUCCESS) ||
        ((check = pufs_hmac(&md1, NULL, 0, tp[i].hash, SHARESEC, SK512_1, 512)) != SUCCESS) ||
        ((check = pufs_clear_key(SHARESEC, SK512_1, 512)) != SUCCESS) ||
        ((check = pufs_key_expansion(SHARESEC, SK512_0, 512, PRF_HMAC, tp[i].hash, false, NULL, 0, 1, SWKEY, tp[i].prk, 256, NULL, 0)) != SUCCESS) ||
        ((check = pufs_hmac(&md2, NULL, 0, tp[i].hash, SHARESEC, SK512_0, 512)) != SUCCESS) ||
        ((check = pufs_clear_key(SHARESEC, SK512_0, 512)) != SUCCESS) ||
        ((check = (md1.dlen != md2.dlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_test_memcmp(md1.dgst, md2.dgst, md1.dlen)) != SUCCESS))
    {
        pufs_clear_key(SHARESEC, keyslot, B2b(tp[i].ikmlen));
        printf("Test Pufsecurity KDF(shared secret) Failed.\n");
        return false;
    }

    printf("Test Pufsecurity KDF(shared secret) Pass.\n");
    return true;
    
}
bool rtl_otp_test(void)
{
    pufs_status_t check;
    uint32_t r[32], w[32];
    int ret;
    memset(w, PUFRT_VALUE8(0xaa), 32);

    
    if ((check = pufs_program_otp((const uint8_t*)w, 32, 0)) != SUCCESS)
        return false;
    if ((check = pufs_read_otp((uint8_t*)r, 32, 0)) != SUCCESS)
        return false;

    ret = memcmp(r,w,32);
    if(ret){
        printf("Test Pufsecurity OTP Read&Write Failed.\n");
        return false;
    }

    memset(w, PUFRT_VALUE8(0xbb), 32);
    if ((check = pufs_program_otp((const uint8_t*)w, 32, 0)) != SUCCESS)
        return false;
    if ((check = pufs_read_otp((uint8_t*)r, 32, 0)) != SUCCESS)
        return false;

    ret = memcmp(r,w,32);
    if(ret){
        printf("Test Pufsecurity OTP Read&Write Failed.\n");
        return false;
    }

    printf("Test Pufsecurity OTP Read&Write Pass.\n");
    return true;
}
bool rtl_aes_ecb_test(void)
{
    const struct bc_test_pattern* tp = aes_ecb_tp;
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    uint32_t outlen;
    uint32_t i=5;
    pufs_ka_slot_t keyslot;

    out = malloc(tp[i].ctlen);
    keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
    if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_enc_ecb(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
        ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
    {
        printf("Test Pufsecurity AES(ECB) CRYPTO enc Failed.\n");
        free(out);
        return false;
    }
    free(out);

    keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
    out = malloc(tp[i].ptlen);
    if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_dec_ecb(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
        ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
    {
        printf("Test Pufsecurity AES(ECB) CRYPTO dec Failed.\n");
        free(out);
        return false;
    }
    free(out);
    
    printf("Test Pufsecurity AES(ECB) CRYPTO Pass.\n");
    return true;

}
bool rtl_sm4_ecb_test(void)
{
    const struct bc_test_pattern* tp = sm4_ecb_tp;
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    uint32_t outlen;
    uint32_t i=0;
    pufs_ka_slot_t keyslot;

    out = malloc(tp[i].ctlen);
    keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
    if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_enc_ecb(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
        ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
    {
        printf("Test Pufsecurity SM4(ECB) CRYPTO dec Failed.\n");
        free(out);
        return false;
    }
    free(out);

    keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
    out = malloc(tp[i].ptlen);
    if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_dec_ecb(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
        ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
        ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
    {
        printf("Test Pufsecurity SM4(ECB) CRYPTO dec Failed.\n");
        free(out);
        return false;
    }
    free(out);
    
    printf("Test Pufsecurity SM4(ECB) CRYPTO Pass.\n");
    return true;
    
}
bool rtl_drbg_test(void)
{
    const struct drbg_test_pattern* tp = drbg_tp;
    pufs_status_t check = SUCCESS;
    uint32_t i=0;
    pufs_drbg_enable_testmode();


    uint8_t out[64];
    bool df = (tp[i].nonce != NULL);

    // instantiate
    pufs_drbg_testmode_entropy(tp[i].e_inst, tp[i].e_instlen);
    if ((check = pufs_drbg_instantiate(AES_CTR_DRBG, tp[i].security, df, tp[i].nonce, tp[i].noncelen, tp[i].pstr, tp[i].pstrlen)) != SUCCESS)
        goto uninst;

    // reseed
    if (tp[i].e_reseed != NULL)
    {
        pufs_drbg_testmode_entropy(tp[i].e_reseed, tp[i].e_reseedlen);
        if ((check = pufs_drbg_reseed(df, tp[i].adin_reseed, tp[i].adin_reseedlen)) != SUCCESS)
            goto uninst;
    }

    bool pr;
    // 1st generate
    pr = (tp[i].e_gen1 != NULL);
    if (pr)
        pufs_drbg_testmode_entropy(tp[i].e_gen1, tp[i].e_gen1len);
    if ((check = pufs_drbg_generate(out, B2b(tp[i].outlen), pr, df, tp[i].adin_gen1, tp[i].adin_gen1len, true)) != SUCCESS)
        goto uninst;

    // 2nd generate
    pr = (tp[i].e_gen2 != NULL);
    if (pr)
        pufs_drbg_testmode_entropy(tp[i].e_gen2, tp[i].e_gen2len);
    if ((check = pufs_drbg_generate(out, B2b(tp[i].outlen), pr, df, tp[i].adin_gen2, tp[i].adin_gen2len, true)) != SUCCESS)
        goto uninst;

    if (memcmp(out, tp[i].out, tp[i].outlen) != 0)
        check = E_VERFAIL;
uninst:
    if (check != SUCCESS){
        printf("Test Pufsecurity DRBG Failed.\n");
        return false;
    }
        
    pufs_status_t uinst_check = SUCCESS;
    if ((uinst_check = pufs_drbg_uninstantiate()) != SUCCESS){
        LOG_ERROR("Case%lu, %s", i, "Fail to uninstantiate drbg");
        printf("Test Pufsecurity DRBG Failed.\n");
        return false;
    }

    printf("Test Pufsecurity DRBG Pass.\n");
    return true;
    
}
bool rtl_enc_dec_sm2_test(void)
{
    const struct sm2_enc_test_pattern* tp = sm2_enc_tp;
    pufs_status_t check = SUCCESS;

    uint8_t* out = NULL;
    uint8_t* pt = NULL;
    uint32_t i=0;

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
        free(out);
        free(pt);
        printf("Test Pufsecurity SM2 CRYPTO enc Failed.\n");
        return false;
    }
    free(out);
    free(pt);


    out = malloc(tp[i].ptlen);
    if (((check = pufs_import_plaintext_key(PRKEY, PRK_0, tp[i].prk, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
        ((check = pufs_sm2_dec(out, &outlen, tp[i].ct, tp[i].ctlen, PRK_0, SM2_C1C3C2)) != SUCCESS) ||
        ((check = pufs_clear_key(PRKEY, PRK_0, B2b(ecc_param[tp[i].name].len))) != SUCCESS) ||
        ((check = (outlen == tp[i].ptlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
        ((check = pufs_test_memcmp(tp[i].pt, out, tp[i].ptlen)) != SUCCESS))
    {
        LOG_ERROR("Case%lu Failed.",  i);
        free(out);
        printf("Test Pufsecurity SM2 CRYPTO dec Failed.\n");
        return false;
    }
    free(out);

    printf("Test Pufsecurity SM2 CRYPTO Pass.\n");
    return true;
}
bool rtl_sign_valid_sm2_test(void)
{
    const struct sm2_sign_test_pattern* tp = sm2_sign_tp;
    pufs_status_t check = SUCCESS;
    uint32_t i = 0;

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
        printf("Test Pufsecurity SM2 Sign Failed.\n");
        return false;
    }


    puk.qlen = sig.qlen = ecc_param[tp[i].name].len;
    memcpy(puk.x, tp[i].pukx, puk.qlen);
    memcpy(puk.y, tp[i].puky, puk.qlen);
    memcpy(sig.r, tp[i].r, sig.qlen);
    memcpy(sig.s, tp[i].s, sig.qlen);
    if ((check = pufs_sm2_verify(sig, tp[i].msg, tp[i].msglen, tp[i].id, tp[i].idlen, puk)) != SUCCESS)
    {
        LOG_ERROR("Case%lu Failed.",  i);
        printf("Test Pufsecurity SM2 Valid Failed.\n");
        return false;
    }


    printf("Test Pufsecurity SM2 Sign&Valid Pass.\n");
    return true;
}
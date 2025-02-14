#ifndef __PUFS_RTL_TEST_CASE__H
#include <stdio.h>
#include <stdbool.h>

/*RTL Test Cases*/
bool rtl_enc_dec_chacha20_poly1305_test(void);
bool rtl_enc_dec_chacha_test(void);
bool rtl_hash_aes_cmac_test(void);
bool rtl_dma_test(void);
bool rtl_sgdma_test(void);
bool rtl_sign_valid_rsa_test(void);
bool rtl_rsa_key_test(void);
bool rtl_rsa_ephemeral_key_test(void);
bool rtl_sign_valid_ecdsa_dgst_test(void);
bool rtl_sign_valid_ecdsa_dgst_otpkey_test(void);
bool rtl_hash_sm3_test(void);
bool rtl_hash_sha_test(void);
bool rtl_kdf_shared_secret_test(void);
bool rtl_otp_test(void);
bool rtl_aes_ecb_test(void);
bool rtl_sm4_ecb_test(void);
bool rtl_drbg_test(void);
bool rtl_enc_dec_sm2_test(void);
bool rtl_sign_valid_sm2_test(void);

#endif // !__PUFS_RTL_TEST_CASE__H
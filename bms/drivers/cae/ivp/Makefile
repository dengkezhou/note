
ARCHIVE := drv_cae.a

ifdef CONFIG_E906
CUSTOM_CFLAGS += -Wno-shift-count-overflow
CUSTOM_CFLAGS += -fno-var-tracking-assignments
endif

srcs-y += \
	test_ipsec_esp_in_aes_ctr_sha1_transport.c \
	test_ipsec_esp_out_aes_ctr_sha1_transport_esn.c \
	test_ipsec_esp_in_aes_ctr_sha1_transport_esn.c \
	test_ipsec_esp_out_aes_ctr_sha1_transport.c \
	test_ipsec_esp_out_aes_ctr_sha2_transport.c \
	test_ipsec_esp_out_aes_cbc_sha1_transport.c \
	test_ipsec_esp_in_aes_ctr_sha2_transport.c \
	test_ipsec_esp_in_aes_cbc_sha1_transport.c \
	intc_hia.c \
	eip97_reg_test.c \
	test_aes_ecb_nist_dec.c \
	test_hmac_sha384_fips.c \
	test_hmac_sha1.c \
	test_tdes_ecb_nist_dec.c \
	test_crc32_chained.c \
	test_sha384_fips.c \
	test_aes_ctr_nist.c \
	test_sha256.c \
	test_tdes_ecb_length.c \
	test_hmac_sha224.c \
	test_bypass.c \
	test_hmac_sha256.c \
	test_hmac_sha256_fips.c \
	test_aes_cbc_nist.c \
	test_hmac_sha1_fips.c \
	test_sha1_save_hash.c \
	test_sha224_fips.c \
	test_md5.c \
	test_sha1_fips.c \
	test_crc32.c \
	test_aes_ctr_nist_dec.c \
	test_hmac_md5_rfc.c \
	test_sha512_fips.c \
	test_md5_rfc.c \
	test_hmac_sha224_fips.c \
	test_hmac_sha512_fips.c \
	test_aes_cbc_nist_dec.c \
	test_tdes_ecb_nist.c \
	test_hmac_md5.c \
	test_aes_ecb_nist.c \
	test_des_cbc_length.c \
	test_sha1.c \
	test_sha256_fips.c \
	test_des_ecb_length.c \
	test_sha224.c \
	test_macsec_in_default.c \
	test_macsec_out_default.c \
	ivp_speed.c \
	fpga_ivp_speed.c \
	aes_128_gcm_speed.c


#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <getopt.h>
#include <cae.h>
#include "data.h"

#define MAX_STR_LEN 48

static int crypto_scan_flag = 0;
static int hash_scan_flag = 0;
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
static int crypto_hash_scan_flag = 0;
static int hash_crypto_scan_flag = 0;
#endif

extern void cae_ivp_test(cae_id id, char *name, int ivp_speed_test, int enc);
extern int cae_speed_test(cae_id id, cipher crypto_type, int speed_enc, int ivp);

int crypto_enum_to_string(cipher crypto_type, unsigned char *str_crypto_type)
{
	int ret = 0;
	switch (crypto_type) {
	case CIPHER_DES_ECB:
		strcpy((char *)str_crypto_type, "des-ecb");
		break;
	case CIPHER_DES_CBC:
		strcpy((char *)str_crypto_type, "des-cbc");
		break;
	case CIPHER_3DES_ECB:
		strcpy((char *)str_crypto_type, "des-ede3-ecb");
		break;
	case CIPHER_3DES_CBC:
		strcpy((char *)str_crypto_type, "des-ede3-cbc");
		break;
	case CIPHER_AES_128_ECB:
		strcpy((char *)str_crypto_type, "aes-128-ecb");
		break;
	case CIPHER_AES_128_CBC:
		strcpy((char *)str_crypto_type, "aes-128-cbc");
		break;
	case CIPHER_AES_128_OFB128:
		strcpy((char *)str_crypto_type, "aes-128-ofb");
		break;
	case CIPHER_AES_128_CFB:
		strcpy((char *)str_crypto_type, "aes-128-cfb");
		break;
	case CIPHER_AES_128_CTR:
		strcpy((char *)str_crypto_type, "aes-128-ctr");
		break;
	case CIPHER_AES_128_ICM:
		strcpy((char *)str_crypto_type, "aes-128-icm");
		break;
	case CIPHER_AES_128_CCM:
		strcpy((char *)str_crypto_type, "aes-128-ccm");
		break;
	case CIPHER_AES_128_GCM:
		strcpy((char *)str_crypto_type, "aes-128-gcm");
		break;
	case CIPHER_AES_192_ECB:
		strcpy((char *)str_crypto_type, "aes-192-ecb");
		break;
	case CIPHER_AES_192_CBC:
		strcpy((char *)str_crypto_type, "aes-192-cbc");
		break;
	case CIPHER_AES_192_OFB128:
		strcpy((char *)str_crypto_type, "aes-192-ofb");
		break;
	case CIPHER_AES_192_CFB:
		strcpy((char *)str_crypto_type, "aes-192-cfb");
		break;
	case CIPHER_AES_192_CTR:
		strcpy((char *)str_crypto_type, "aes-192-ctr");
		break;
	case CIPHER_AES_192_ICM:
		strcpy((char *)str_crypto_type, "aes-192-icm");
		break;
	case CIPHER_AES_192_CCM:
		strcpy((char *)str_crypto_type, "aes-192-ccm");
		break;
	case CIPHER_AES_192_GCM:
		strcpy((char *)str_crypto_type, "aes-192-gcm");
		break;
	case CIPHER_AES_256_ECB:
		strcpy((char *)str_crypto_type, "aes-256-ecb");
		break;
	case CIPHER_AES_256_CBC:
		strcpy((char *)str_crypto_type, "aes-256-cbc");
		break;
	case CIPHER_AES_256_OFB128:
		strcpy((char *)str_crypto_type, "aes-256-ofb");
		break;
	case CIPHER_AES_256_CFB:
		strcpy((char *)str_crypto_type, "aes-256-cfb");
		break;
	case CIPHER_AES_256_CTR:
		strcpy((char *)str_crypto_type, "aes-256-ctr");
		break;
	case CIPHER_AES_256_ICM:
		strcpy((char *)str_crypto_type, "aes-256-icm");
		break;
	case CIPHER_AES_256_CCM:
		strcpy((char *)str_crypto_type, "aes-256-ccm");
		break;
	case CIPHER_AES_256_GCM:
		strcpy((char *)str_crypto_type, "aes-256-gcm");
		break;
	default:
		ret = -1;
		break;
	}
	return ret;
}

static int hash_enum_to_string(md hash_type, unsigned char *str_hash_type)
{
	int ret = 0;
	switch (hash_type) {
	case HASH_MD5:
		strcpy((char *)str_hash_type, "md5");
		break;
	case HASH_SHA1:
		strcpy((char *)str_hash_type, "sha1");
		break;
	case HASH_SHA2_224:
		strcpy((char *)str_hash_type, "sha224");
		break;
	case HASH_SHA2_256:
		strcpy((char *)str_hash_type, "sha256");
		break;
	case HASH_SHA2_384:
		strcpy((char *)str_hash_type, "sha384");
		break;
	case HASH_SHA2_512:
		strcpy((char *)str_hash_type, "sha512");
		break;
	case HASH_HMAC_MD5:
		strcpy((char *)str_hash_type, "md5-hmac");
		break;
	case HASH_HMAC_SHA1:
		strcpy((char *)str_hash_type, "sha1-hmac");
		break;
	case HASH_HMAC_SHA2_224:
		strcpy((char *)str_hash_type, "sha224-hmac");
		break;
	case HASH_HMAC_SHA2_256:
		strcpy((char *)str_hash_type, "sha256-hmac");
		break;
	case HASH_HMAC_SHA2_384:
		strcpy((char *)str_hash_type, "sha384-hmac");
		break;
	case HASH_HMAC_SHA2_512:
		strcpy((char *)str_hash_type, "sha512-hmac");
		break;
	case HASH_AES_128_XCBC_MAC_96:
		strcpy((char *)str_hash_type, "aes-128-xcbc-mac-96");
		break;
	case HASH_AES_192_XCBC_MAC_96:
		strcpy((char *)str_hash_type, "aes-192-xcbc-mac-96");
		break;
	case HASH_AES_256_XCBC_MAC_96:
		strcpy((char *)str_hash_type, "aes-256-xcbc-mac-96");
		break;
	case HASH_AES_128_XCBC_MAC_PRF:
		strcpy((char *)str_hash_type, "aes-128-xcbc-mac-prf");
		break;
	case HASH_AES_192_XCBC_MAC_PRF:
		strcpy((char *)str_hash_type, "aes-192-xcbc-mac-prf");
		break;
	case HASH_AES_256_XCBC_MAC_PRF:
		strcpy((char *)str_hash_type, "aes-256-xcbc-mac-prf");
		break;
	case HASH_GHASH:
		strcpy((char *)str_hash_type, "ghash");
		break;
	case HASH_CRC32:
		strcpy((char *)str_hash_type, "crc32");
		break;
	case HASH_SSLMAC_SHA1:
		strcpy((char *)str_hash_type, "sha1-ssl-mac");
		break;
	case HASH_AES_128_CMAC:
		strcpy((char *)str_hash_type, "aes-128-cmac");
		break;
	case HASH_AES_192_CMAC:
		strcpy((char *)str_hash_type, "aes-192-cmac");
		break;
	case HASH_AES_256_CMAC:
		strcpy((char *)str_hash_type, "aes-256-cmac");
		break;
	case HASH_AES_128_CBC_MAC:
		strcpy((char *)str_hash_type, "aes-128-cbc-mac");
		break;
	case HASH_AES_192_CBC_MAC:
		strcpy((char *)str_hash_type, "aes-192-cbc-mac");
		break;
	case HASH_AES_256_CBC_MAC:
		strcpy((char *)str_hash_type, "aes-256-cbc-mac");
		break;
	default:
		ret = -1;
		break;
	}
	return ret;
}

static int comfirm_crypto_params(unsigned char **in, unsigned char **key,
				 unsigned char **iv, unsigned char **nonce,
				 unsigned char **aad, unsigned char **out,
				 unsigned char *str_crypto_type)
{
	int ret = -1;
	int i = 0;
	for (i = 0; i < sizeof(crypto_data) / sizeof(struct crypto); i++) {
		if (!strcmp(crypto_data[i].name,
			    (const char *)str_crypto_type)) {
			ret = 0;
			break;
		}
	}
	if (ret == 0) {
		*in = crypto_data[i].in;
		*key = crypto_data[i].key;
		*iv = crypto_data[i].iv;
		*nonce = crypto_data[i].nonce;
		*aad = crypto_data[i].aad;
		*out = crypto_data[i].out;
	}
	return 0;
}

static int confirm_hash_params(unsigned char **in, unsigned char **key,
			       unsigned char **out,
			       unsigned char *str_hash_type)
{
	int ret = -1;
	int i = 0;
	for (i = 0; i < sizeof(hash_data) / sizeof(struct hash); i++) {
		if (!strcmp(hash_data[i].name, (const char *)str_hash_type)) {
			ret = 0;
			break;
		}
	}
	if (ret == 0) {
		*in = hash_data[i].in;
		*key = hash_data[i].key;
		*out = hash_data[i].out;
	}
	return 0;
}

static int confirm_misc_params(unsigned char **in, misc_params *misc_paras,
			       unsigned char **out,
			       unsigned char *str_crypto_type,
			       unsigned char *str_hash_type, int enc,
			       int hash_first)
{
	int ret = -1;
	int i = 0;
	struct combined *data = NULL;
	int len = 0;

	if (hash_first) {
		if (enc) {
			data = hash_enc_data;
			len = sizeof(hash_enc_data) / sizeof(struct combined);
		} else {
			data = hash_dec_data;
			len = sizeof(hash_dec_data) / sizeof(struct combined);
		}
	} else {
		if (enc) {
			data = enc_hash_data;
			len = sizeof(enc_hash_data) / sizeof(struct combined);
		} else {
			data = dec_hash_data;
			len = sizeof(dec_hash_data) / sizeof(struct combined);
		}
	}

	for (i = 0; i < len; i++) {
		if (!strcmp(data[i].crypto_name,
			    (const char *)str_crypto_type)) {
			if (!strcmp(data[i].hash_name,
				    (const char *)str_hash_type)) {
				ret = 0;
				break;
			}
		}
	}
	if (ret == 0) {
		*in = data[i].in;
		misc_paras->crypto_key = data[i].crypto_key;
		misc_paras->iv = data[i].iv;
		misc_paras->nonce = data[i].nonce;
		misc_paras->aad = data[i].aad;
		misc_paras->hash_key = data[i].hash_key;
		*out = data[i].out;
	}
	return ret;
}

static int cipher_test(cae_id id, cipher crypto_type)
{
	int ret = -1;
	cipher_ctx *ctx = NULL;
	unsigned char out_0[200] = { 0 };
	unsigned char out_1[200] = { 0 };
	int out_0_len = 0;
	int out_1_len = 0;
	int total_len = 0;
	unsigned char *in = NULL;
	unsigned char *key = NULL;
	unsigned char *iv = NULL;
	unsigned char *nonce = NULL;
	unsigned char *aad = NULL;
	unsigned char *encrypted_out = NULL;
	unsigned char str_crypto_type[30] = { 0 };
	cae_device *dev = NULL;
	bool blocked = CAE_UPDATE_BLOCK;

	dev = itcs_cae_init(id);
	if (!dev) {
		printf("cae%d init failed!\n", id);
		return -1;
	}

	if (crypto_enum_to_string(crypto_type, str_crypto_type) == -1)
		goto cleanup;
	printf("cipher type: %s\n", str_crypto_type);
	if (comfirm_crypto_params(&in, &key, &iv, &nonce, &aad, &encrypted_out,
				  str_crypto_type) == -1)
		goto cleanup;

	ctx = itcs_cipher_ctx_new(dev);
	if (!ctx)
		goto exit;
	if (itcs_cipher_ctx_set_padding(ctx, PADDING_PKCS7) != 1)
		goto cleanup;
	if (itcs_cipher_init(ctx, crypto_type, key, iv, ENCRYPT) != 1)
		goto cleanup;

	if (itcs_cipher_update(ctx, out_0, &out_0_len, in, strlen((char *)in),
			       blocked) != 1)
		goto cleanup;
	if (itcs_cipher_final(ctx, out_1, &out_1_len) != 1)
		goto cleanup;
	memcpy(out_0 + out_0_len, out_1, out_1_len);
	total_len = out_0_len + out_1_len;
	if (total_len <= 0 || memcmp(encrypted_out, out_0, total_len))
		goto cleanup;

	memset(out_0, 0, out_0_len);
	memset(out_1, 0, out_1_len);
	if (itcs_cipher_init(ctx, crypto_type, key, iv, DECRYPT) != 1)
		goto cleanup;
	if (itcs_cipher_update(ctx, out_0, &out_0_len, encrypted_out, total_len,
			       blocked) != 1)
		goto cleanup;
	if (itcs_cipher_final(ctx, out_1, &out_1_len) != 1)
		goto cleanup;
	memcpy(out_0 + out_0_len, out_1, out_1_len);
	total_len = out_0_len + out_1_len;
	if (total_len <= 0 || memcmp(out_0, in, total_len))
		goto cleanup;

	printf("Test Crypto %s enc and dec Pass\n", str_crypto_type);
	ret = 0;
cleanup:
	itcs_cipher_ctx_free(ctx);
exit:
	itcs_cae_exit(dev);
	return ret;
}

static int digest_test(cae_id id, md hash_type)
{
	int ret = -1;
	md_ctx *ctx = NULL;
	unsigned char md[64] = { 0 };
	unsigned int len = 0;
	unsigned char *in = NULL;
	unsigned char *key = NULL;
	unsigned char *hashed_out = NULL;
	unsigned char str_hash_type[30] = { 0 };
	cae_device *dev = NULL;
	bool blocked = CAE_UPDATE_BLOCK;

	dev = itcs_cae_init(id);
	if (!dev) {
		printf("cae%d init failed!\n", id);
		return -1;
	}

	if (hash_enum_to_string(hash_type, str_hash_type) == -1)
		goto cleanup;
	printf("hash type: %s\n", str_hash_type);
	if (confirm_hash_params(&in, &key, &hashed_out, str_hash_type) == -1)
		goto cleanup;

	ctx = itcs_md_ctx_new(dev);
	if (!ctx)
		goto exit;
	if (itcs_digest_init(ctx, hash_type, key) != 1)
		goto cleanup;
	if (itcs_digest_update(ctx, in, strlen((char *)in), blocked) != 1)
		goto cleanup;
	if (itcs_digest_final(ctx, md, &len) != 1)
		goto cleanup;
	printf("digest len: %d\n", len);
	if (len > 0 && !memcmp(hashed_out, md, len)) {
		printf("Test Hash %s Pass\n", str_hash_type);
		ret = 0;
	} else {
		printf("Test Hash %s failed\n", str_hash_type);
		ret = -1;
	}
cleanup:
	itcs_md_ctx_free(ctx);
exit:
	itcs_cae_exit(dev);
	return ret;
}

static int misc_test(cae_id id, cipher crypto_type, md hash_type, int enc,
		     int hash_first, protocol proto_type)
{
	int ret = -1;
	misc_ctx *ctx = NULL;
	misc_params misc_paras;
	unsigned char out[64] = { 0 };
	unsigned int len = 0;
	unsigned char *misc_crypto_in = NULL;
	unsigned char str_crypto_type[30];
	unsigned char str_hash_type[30];
	unsigned char *expected_out = NULL;
	cae_device *dev = NULL;

	dev = itcs_cae_init(id);
	if (!dev) {
		printf("cae%d init failed!\n", id);
		return -1;
	}

	if (crypto_enum_to_string(crypto_type, str_crypto_type) == -1)
		goto cleanup;
	if (hash_enum_to_string(hash_type, str_hash_type) == -1)
		goto cleanup;

	misc_paras.crypto_type = crypto_type;
	misc_paras.hash_type = hash_type;
	if (confirm_misc_params(&misc_crypto_in, &misc_paras, &expected_out,
				str_crypto_type, str_hash_type, enc,
				hash_first) == -1)
		goto cleanup;

	ctx = itcs_misc_ctx_new(dev);
	if (!ctx)
		goto exit;

	misc_paras.enc = enc;
	misc_paras.proto_type = proto_type;
	misc_paras.hash_first = hash_first;
	if (itcs_misc_init(ctx, &misc_paras) != 1)
		goto cleanup;

	if (itcs_misc_ctx_set_padding(ctx, PADDING_PKCS7) != 1)
		goto cleanup;
	if (itcs_misc_update(ctx, misc_crypto_in,
			     strlen((char *)misc_crypto_in)) != 1)
		goto cleanup;
	if (itcs_misc_final(ctx, out, &len) != 1)
		goto cleanup;
	if (len <= 0 && memcmp(expected_out, out, len))
		goto cleanup;

	ret = 0;
cleanup:
	itcs_misc_ctx_free(ctx);
exit:
	itcs_cae_exit(dev);
	return ret;
}

static int parallel_test(cipher crypto_type)
{
	int ret = -1;
	cipher_ctx *ctx_0 = NULL;
	cipher_ctx *ctx_1 = NULL;
	unsigned char out_0[200] = { 0 };
	unsigned char out_1[200] = { 0 };
	int out_0_len = 0;
	int out_1_len = 0;
	int total_0_len = 0;
	unsigned char out_2[200] = { 0 };
	unsigned char out_3[200] = { 0 };
	int out_2_len = 0;
	int out_3_len = 0;
	int total_1_len = 0;
	unsigned char *in = NULL;
	unsigned char *key = NULL;
	unsigned char *iv = NULL;
	unsigned char *nonce = NULL;
	unsigned char *aad = NULL;
	unsigned char *encrypted_out = NULL;
	unsigned char str_crypto_type[30] = { 0 };
	cae_id id_0 = CAE0;
	cae_id id_1 = CAE1;
	cae_device *dev_0 = NULL;
	cae_device *dev_1 = NULL;
	bool blocked = CAE_UPDATE_NONBLOCK;

	dev_0 = itcs_cae_init(id_0);
	if (!dev_0) {
		printf("cae%d init failed!\n", id_0);
		goto exit_0;
	}
	dev_1 = itcs_cae_init(id_1);
	if (!dev_1) {
		printf("cae%d init failed!\n", id_1);
		goto exit_1;
	}

	if (crypto_enum_to_string(crypto_type, str_crypto_type) == -1)
		goto exit_2;
	printf("cipher type: %s\n", str_crypto_type);
	if (comfirm_crypto_params(&in, &key, &iv, &nonce, &aad, &encrypted_out,
				  str_crypto_type) == -1)
		goto exit_2;

	ctx_0 = itcs_cipher_ctx_new(dev_0);
	if (!ctx_0)
		goto exit_2;
	ctx_1 = itcs_cipher_ctx_new(dev_1);
	if (!ctx_1)
		goto exit_3;
	if (itcs_cipher_ctx_set_padding(ctx_0, PADDING_PKCS7) != 1)
		goto cleanup;
	if (itcs_cipher_ctx_set_padding(ctx_1, PADDING_PKCS7) != 1)
		goto cleanup;

	if (itcs_cipher_init(ctx_0, crypto_type, key, iv, ENCRYPT) != 1)
		goto cleanup;
	if (itcs_cipher_init(ctx_1, crypto_type, key, iv, ENCRYPT) != 1)
		goto cleanup;

	if (itcs_cipher_update(ctx_0, out_0, &out_0_len, in, strlen((char *)in),
			       blocked) != 1)
		goto cleanup;
	if (itcs_cipher_update(ctx_1, out_2, &out_2_len, in, strlen((char *)in),
			       blocked) != 1)
		goto cleanup;

	if (itcs_cipher_final(ctx_0, out_1, &out_1_len) != 1)
		goto cleanup;
	if (itcs_cipher_final(ctx_1, out_3, &out_3_len) != 1)
		goto cleanup;
	memcpy(out_0 + out_0_len, out_1, out_1_len);
	memcpy(out_2 + out_2_len, out_3, out_3_len);
	total_0_len = out_0_len + out_1_len;
	total_1_len = out_2_len + out_3_len;
	printf("cae%d enc len: %d\n", id_0, total_0_len);
	printf("cae%d enc len: %d\n", id_1, total_1_len);
	if ((total_0_len <= 0 || memcmp(encrypted_out, out_0, total_0_len)) ||
	    (total_1_len <= 0 || memcmp(encrypted_out, out_2, total_1_len)))
		goto cleanup;

	memset(out_0, 0, out_0_len);
	memset(out_1, 0, out_1_len);
	memset(out_2, 0, out_2_len);
	memset(out_3, 0, out_3_len);
	if (itcs_cipher_init(ctx_0, crypto_type, key, iv, DECRYPT) != 1)
		goto cleanup;
	if (itcs_cipher_init(ctx_1, crypto_type, key, iv, DECRYPT) != 1)
		goto cleanup;

	if (itcs_cipher_update(ctx_0, out_0, &out_0_len, encrypted_out,
			       total_0_len, blocked) != 1)
		goto cleanup;
	if (itcs_cipher_update(ctx_1, out_2, &out_2_len, encrypted_out,
			       total_1_len, blocked) != 1)
		goto cleanup;

	if (itcs_cipher_final(ctx_0, out_1, &out_1_len) != 1)
		goto cleanup;
	if (itcs_cipher_final(ctx_1, out_3, &out_3_len) != 1)
		goto cleanup;
	memcpy(out_0 + out_0_len, out_1, out_1_len);
	memcpy(out_2 + out_2_len, out_3, out_3_len);
	total_0_len = out_0_len + out_1_len;
	total_1_len = out_2_len + out_3_len;
	printf("cae%d dec len: %d\n", id_0, total_0_len);
	printf("cae%d dec len: %d\n", id_1, total_1_len);
	if ((total_0_len <= 0 || memcmp(out_0, in, total_0_len)) ||
	    (total_1_len <= 0 || memcmp(out_2, in, total_1_len)))
		goto cleanup;

	printf("Test dual core %s enc and dec Pass\n", str_crypto_type);
	ret = 0;
cleanup:
	itcs_cipher_ctx_free(ctx_1);
exit_3:
	itcs_cipher_ctx_free(ctx_0);
exit_2:
	itcs_cae_exit(dev_1);
exit_1:
	itcs_cae_exit(dev_0);
exit_0:
	return ret;
}

static cipher crypto_scan_param_proc(char *params)
{
	cipher cipher_type = CIPHER_NULL;

	if (!strcmp(params, "des-ecb"))
		cipher_type = CIPHER_DES_ECB;
	else if (!strcmp(params, "des-cbc"))
		cipher_type = CIPHER_DES_CBC;
	else if (!strcmp(params, "3des-ecb"))
		cipher_type = CIPHER_3DES_ECB;
	else if (!strcmp(params, "3des-cbc"))
		cipher_type = CIPHER_3DES_CBC;
	else if (!strcmp(params, "aes-128-ecb"))
		cipher_type = CIPHER_AES_128_ECB;
	else if (!strcmp(params, "aes-128-cbc"))
		cipher_type = CIPHER_AES_128_CBC;
	else if (!strcmp(params, "aes-128-ofb128"))
		cipher_type = CIPHER_AES_128_OFB128;
	else if (!strcmp(params, "aes-128-cfb"))
		cipher_type = CIPHER_AES_128_CFB;
	else if (!strcmp(params, "aes-128-ctr"))
		cipher_type = CIPHER_AES_128_CTR;
	else if (!strcmp(params, "aes-128-icm"))
		cipher_type = CIPHER_AES_128_ICM;
	else if (!strcmp(params, "aes-128-ccm"))
		cipher_type = CIPHER_AES_128_CCM;
	else if (!strcmp(params, "aes-128-gcm"))
		cipher_type = CIPHER_AES_128_GCM;
	else if (!strcmp(params, "aes-192-ecb"))
		cipher_type = CIPHER_AES_192_ECB;
	else if (!strcmp(params, "aes-192-cbc"))
		cipher_type = CIPHER_AES_192_CBC;
	else if (!strcmp(params, "aes-192-ofb128"))
		cipher_type = CIPHER_AES_192_OFB128;
	else if (!strcmp(params, "aes-192-cfb"))
		cipher_type = CIPHER_AES_192_CFB;
	else if (!strcmp(params, "aes-192-ctr"))
		cipher_type = CIPHER_AES_192_CTR;
	else if (!strcmp(params, "aes-192-icm"))
		cipher_type = CIPHER_AES_192_ICM;
	else if (!strcmp(params, "aes-192-ccm"))
		cipher_type = CIPHER_AES_192_CCM;
	else if (!strcmp(params, "aes-192-gcm"))
		cipher_type = CIPHER_AES_192_GCM;
	else if (!strcmp(params, "aes-256-ecb"))
		cipher_type = CIPHER_AES_256_ECB;
	else if (!strcmp(params, "aes-256-cbc"))
		cipher_type = CIPHER_AES_256_CBC;
	else if (!strcmp(params, "aes-256-ofb128"))
		cipher_type = CIPHER_AES_256_OFB128;
	else if (!strcmp(params, "aes-256-cfb"))
		cipher_type = CIPHER_AES_256_CFB;
	else if (!strcmp(params, "aes-256-ctr"))
		cipher_type = CIPHER_AES_256_CTR;
	else if (!strcmp(params, "aes-256-icm"))
		cipher_type = CIPHER_AES_256_ICM;
	else if (!strcmp(params, "aes-256-ccm"))
		cipher_type = CIPHER_AES_256_CCM;
	else if (!strcmp(params, "aes-256-gcm"))
		cipher_type = CIPHER_AES_256_GCM;
	return cipher_type;
}

static int crypto_scan_test(cae_id id, char *params)
{
	int i;
	int des_3des_cnt = 4;
	int aes_cnt = 24;
	cipher des_3des_type[] = { CIPHER_DES_ECB, CIPHER_DES_CBC,
				   CIPHER_3DES_ECB, CIPHER_3DES_CBC };
	cipher aes_type[] = { CIPHER_AES_128_ECB,    CIPHER_AES_128_CBC,
			      CIPHER_AES_128_CTR,    CIPHER_AES_128_ICM,
			      CIPHER_AES_128_OFB128, CIPHER_AES_128_CFB,
			      CIPHER_AES_128_CCM,    CIPHER_AES_128_GCM,
			      CIPHER_AES_192_ECB,    CIPHER_AES_192_CBC,
			      CIPHER_AES_192_CTR,    CIPHER_AES_192_ICM,
			      CIPHER_AES_192_OFB128, CIPHER_AES_192_CFB,
			      CIPHER_AES_192_CCM,    CIPHER_AES_192_GCM,
			      CIPHER_AES_256_ECB,    CIPHER_AES_256_CBC,
			      CIPHER_AES_256_CTR,    CIPHER_AES_256_ICM,
			      CIPHER_AES_256_OFB128, CIPHER_AES_256_CFB,
			      CIPHER_AES_256_CCM,    CIPHER_AES_256_GCM };

	if (!strcmp(params, "all")) {
		for (i = 0; i < des_3des_cnt; i++) {
			if (cipher_test(id, des_3des_type[i]) == -1)
				return -1;
		}
		for (i = 0; i < aes_cnt; i++) {
			if (cipher_test(id, aes_type[i]) == -1)
				return -1;
		}
		printf("Test Crypto enc and dec Ergodic Pass\n");
	} else {
		if (cipher_test(id, crypto_scan_param_proc(params)) == -1) {
			printf("crypto test error!\n");
			return -1;
		}
	}

	return 0;
}

static md hash_scan_param_proc(char *params)
{
	md hash_type = HASH_NULL;

	if (!strcmp(params, "md5"))
		hash_type = HASH_MD5;
	else if (!strcmp(params, "sha1"))
		hash_type = HASH_SHA1;
	else if (!strcmp(params, "sha2-224"))
		hash_type = HASH_SHA2_224;
	else if (!strcmp(params, "sha2-256"))
		hash_type = HASH_SHA2_256;
	else if (!strcmp(params, "sha2-384"))
		hash_type = HASH_SHA2_384;
	else if (!strcmp(params, "sha2-512"))
		hash_type = HASH_SHA2_512;
	else if (!strcmp(params, "md5-hmac"))
		hash_type = HASH_HMAC_MD5;
	else if (!strcmp(params, "sha1-hmac"))
		hash_type = HASH_HMAC_SHA1;
	else if (!strcmp(params, "sha2-224-hmac"))
		hash_type = HASH_HMAC_SHA2_224;
	else if (!strcmp(params, "sha2-256-hmac"))
		hash_type = HASH_HMAC_SHA2_256;
	else if (!strcmp(params, "sha2-384-hmac"))
		hash_type = HASH_HMAC_SHA2_384;
	else if (!strcmp(params, "sha2-512-hmac"))
		hash_type = HASH_HMAC_SHA2_512;
	else if (!strcmp(params, "aes-128-xcbc-mac-96"))
		hash_type = HASH_AES_128_XCBC_MAC_96;
	else if (!strcmp(params, "aes-192-xcbc-mac-96"))
		hash_type = HASH_AES_192_XCBC_MAC_96;
	else if (!strcmp(params, "aes-256-xcbc-mac-96"))
		hash_type = HASH_AES_256_XCBC_MAC_96;
	else if (!strcmp(params, "aes-128-xcbc-mac-prf"))
		hash_type = HASH_AES_128_XCBC_MAC_PRF;
	else if (!strcmp(params, "aes-192-xcbc-mac-prf"))
		hash_type = HASH_AES_192_XCBC_MAC_PRF;
	else if (!strcmp(params, "aes-256-xcbc-mac-prf"))
		hash_type = HASH_AES_256_XCBC_MAC_PRF;
	else if (!strcmp(params, "ghash"))
		hash_type = HASH_GHASH;
	else if (!strcmp(params, "crc32"))
		hash_type = HASH_CRC32;
	else if (!strcmp(params, "sha1-sslmac"))
		hash_type = HASH_SSLMAC_SHA1;
	else if (!strcmp(params, "aes-128-cmac"))
		hash_type = HASH_AES_128_CMAC;
	else if (!strcmp(params, "aes-192-cmac"))
		hash_type = HASH_AES_192_CMAC;
	else if (!strcmp(params, "aes-256-cmac"))
		hash_type = HASH_AES_256_CMAC;
	else if (!strcmp(params, "aes-128-cbc-mac"))
		hash_type = HASH_AES_128_CBC_MAC;
	else if (!strcmp(params, "aes-192-cbc-mac"))
		hash_type = HASH_AES_192_CBC_MAC;
	else if (!strcmp(params, "aes-256-cbc-mac"))
		hash_type = HASH_AES_256_CBC_MAC;
	return hash_type;
}

static int hash_scan_test(cae_id id, char *params)
{
	int i;
	int cnt = 27;
	md hash_type[] = { HASH_MD5,
			   HASH_SHA1,
			   HASH_SHA2_224,
			   HASH_SHA2_256,
			   HASH_SHA2_384,
			   HASH_SHA2_512,
			   HASH_HMAC_MD5,
			   HASH_HMAC_SHA1,
			   HASH_HMAC_SHA2_224,
			   HASH_HMAC_SHA2_256,
			   HASH_HMAC_SHA2_384,
			   HASH_HMAC_SHA2_512,
			   HASH_AES_128_XCBC_MAC_96,
			   HASH_AES_192_XCBC_MAC_96,
			   HASH_AES_256_XCBC_MAC_96,
			   HASH_AES_128_XCBC_MAC_PRF,
			   HASH_AES_192_XCBC_MAC_PRF,
			   HASH_AES_256_XCBC_MAC_PRF,
			   HASH_GHASH,
			   HASH_CRC32,
			   HASH_SSLMAC_SHA1,
			   HASH_AES_128_CMAC,
			   HASH_AES_192_CMAC,
			   HASH_AES_256_CMAC,
			   HASH_AES_128_CBC_MAC,
			   HASH_AES_192_CBC_MAC,
			   HASH_AES_256_CBC_MAC };

	if (!strcmp(params, "all")) {
		for (i = 0; i < cnt; i++) {
			if (digest_test(id, hash_type[i]) == -1) {
				printf("digest test error!\n");
				return -1;
			}
		}
		printf("Test Hash Ergodic Pass\n");
	} else {
		if (digest_test(id, hash_scan_param_proc(params)) == -1) {
			printf("digest test error!\n");
			return -1;
		}
	}
	return 0;
}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
static int combined_scan_test(cae_id id, int hash_first)
{
	int i, j, k;
	int enc = 0;
	int crypto_cnt = 22;
	int hash_cnt = 25;
	cipher crypto_type[] = {
		CIPHER_DES_ECB,	       CIPHER_DES_CBC,	   CIPHER_3DES_ECB,
		CIPHER_3DES_CBC,       CIPHER_AES_128_ECB, CIPHER_AES_128_CBC,
		CIPHER_AES_128_OFB128, CIPHER_AES_128_CFB, CIPHER_AES_128_CTR,
		CIPHER_AES_128_ICM,    CIPHER_AES_192_ECB, CIPHER_AES_192_CBC,
		CIPHER_AES_192_OFB128, CIPHER_AES_192_CFB, CIPHER_AES_192_CTR,
		CIPHER_AES_192_ICM,    CIPHER_AES_256_ECB, CIPHER_AES_256_CBC,
		CIPHER_AES_256_OFB128, CIPHER_AES_256_CFB, CIPHER_AES_256_CTR,
		CIPHER_AES_256_ICM
	};
	md hash_type[] = { HASH_MD5,
			   HASH_SHA1,
			   HASH_SHA2_224,
			   HASH_SHA2_256,
			   HASH_SHA2_384,
			   HASH_SHA2_512,
			   HASH_HMAC_MD5,
			   HASH_HMAC_SHA1,
			   HASH_HMAC_SHA2_224,
			   HASH_HMAC_SHA2_256,
			   HASH_HMAC_SHA2_384,
			   HASH_HMAC_SHA2_512,
			   HASH_AES_128_XCBC_MAC_96,
			   HASH_AES_192_XCBC_MAC_96,
			   HASH_AES_256_XCBC_MAC_96,
			   HASH_AES_128_XCBC_MAC_PRF,
			   HASH_AES_192_XCBC_MAC_PRF,
			   HASH_AES_256_XCBC_MAC_PRF,
			   HASH_CRC32,
			   HASH_AES_128_CMAC,
			   HASH_AES_192_CMAC,
			   HASH_AES_256_CMAC,
			   HASH_AES_128_CBC_MAC,
			   HASH_AES_192_CBC_MAC,
			   HASH_AES_256_CBC_MAC };
	int crypto_cnt_1 = 4;
	int hash_cnt_1 = 1;
	cipher crypto_type_1[] = { CIPHER_DES_ECB, CIPHER_DES_CBC,
				   CIPHER_3DES_ECB, CIPHER_3DES_CBC };
	md hash_type_1[] = { HASH_SSLMAC_SHA1 };
	int crypto_cnt_2 = 3;
	int hash_cnt_2 = 1;
	cipher crypto_type_2[] = { CIPHER_AES_128_CTR, CIPHER_AES_192_CTR,
				   CIPHER_AES_256_CTR };
	md hash_type_2[] = { HASH_GHASH };

	for (k = 0; k < 2; k++) {
		enc = !enc;
		for (i = 0; i < crypto_cnt; i++) {
			for (j = 0; j < hash_cnt; j++) {
				if (misc_test(id, crypto_type[i], hash_type[j],
					      enc, hash_first,
					      PROTO_NULL) == -1)
					return -1;
			}
		}
		for (i = 0; i < crypto_cnt_1; i++) {
			for (j = 0; j < hash_cnt_1; j++) {
				if (misc_test(id, crypto_type_1[i],
					      hash_type_1[j], enc, hash_first,
					      PROTO_NULL) == -1)
					return -1;
			}
		}
		for (i = 0; i < crypto_cnt_2; i++) {
			for (j = 0; j < hash_cnt_2; j++) {
				if (misc_test(id, crypto_type_2[i],
					      hash_type_2[j], enc, hash_first,
					      PROTO_NULL) == -1)
					return -1;
			}
		}
	}
	return 0;
}

static int crypto_hash_scan_test(cae_id id)
{
	int ret;
	ret = combined_scan_test(id, 0);
	if (ret == 0)
		printf("Test Crypto-Hash enc-hash and dec-hash Ergodic Pass\n");
	return ret;
}

static int hash_crypto_scan_test(cae_id id)
{
	int ret;
	ret = combined_scan_test(id, 1);
	if (ret == 0)
		printf("Test Hash-Crypto hash-enc and hash-dec Ergodic Pass\n");
	return ret;
}
#endif

static int ipsec_single_test(cae_id id)
{
	if (misc_test(id, CIPHER_AES_256_CTR, HASH_HMAC_SHA2_512, 0, 1,
		      PROTO_IPSEC) == -1)
		return -1;

	printf("Test IPSEC aes-256-ctr-sha2-512-hmac Pass\n");
	return 0;
}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
static int ipsec_scan_test(cae_id id)
{
	int i, j;
	int crypto_cnt = 8;
	int hash_cnt = 12;
	cipher crypto_type[] = { CIPHER_DES_CBC,     CIPHER_3DES_CBC,
				 CIPHER_AES_128_CBC, CIPHER_AES_128_CTR,
				 CIPHER_AES_192_CBC, CIPHER_AES_192_CTR,
				 CIPHER_AES_256_CBC, CIPHER_AES_256_CTR };
	md hash_type[] = { HASH_HMAC_MD5,
			   HASH_HMAC_SHA1,
			   HASH_HMAC_SHA2_224,
			   HASH_HMAC_SHA2_256,
			   HASH_HMAC_SHA2_384,
			   HASH_HMAC_SHA2_512,
			   HASH_AES_128_XCBC_MAC_96,
			   HASH_AES_192_XCBC_MAC_96,
			   HASH_AES_256_XCBC_MAC_96,
			   HASH_AES_128_XCBC_MAC_PRF,
			   HASH_AES_192_XCBC_MAC_PRF,
			   HASH_AES_256_XCBC_MAC_PRF };
	int crypto_cnt_1 = 3;
	int hash_cnt_1 = 1;
	cipher crypto_type_1[] = { CIPHER_AES_128_CTR, CIPHER_AES_192_CTR,
				   CIPHER_AES_256_CTR };
	md hash_type_1[] = { HASH_GHASH };
	for (i = 0; i < crypto_cnt; i++) {
		for (j = 0; j < hash_cnt; j++) {
			if (misc_test(id, crypto_type[i], hash_type[j], 0, 1,
				      PROTO_IPSEC) == -1)
				return -1;
		}
	}
	for (i = 0; i < crypto_cnt_1; i++) {
		for (j = 0; j < hash_cnt_1; j++) {
			if (misc_test(id, crypto_type_1[i], hash_type_1[j], 0,
				      1, PROTO_IPSEC) == -1)
				return -1;
		}
	}
	printf("Test IPSEC Ergodic Pass\n");
	return 0;
}
#endif

static int ssl_single_test(cae_id id)
{
	if (misc_test(id, CIPHER_3DES_CBC, HASH_SSLMAC_SHA1, 0, 1, PROTO_SSL) ==
	    -1)
		return -1;

	printf("Test SSL/TLS/DTLS triple-des-cbc-sha1-ssl-mac Pass\n");
	return 0;
}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
static int ssl_scan_test(cae_id id)
{
	int i, j;
	int crypto_cnt = 4;
	int hash_cnt = 7;
	cipher crypto_type[] = { CIPHER_DES_CBC, CIPHER_3DES_CBC,
				 CIPHER_AES_128_CBC, CIPHER_AES_256_CBC };
	md hash_type[] = { HASH_HMAC_MD5,      HASH_HMAC_SHA1,
			   HASH_HMAC_SHA2_224, HASH_HMAC_SHA2_256,
			   HASH_HMAC_SHA2_384, HASH_HMAC_SHA2_512,
			   HASH_SSLMAC_SHA1 };
	int crypto_cnt_1 = 2;
	int hash_cnt_1 = 1;
	cipher crypto_type_1[] = { CIPHER_AES_128_CTR, CIPHER_AES_256_CTR };
	md hash_type_1[] = { HASH_GHASH };

	for (i = 0; i < crypto_cnt; i++) {
		for (j = 0; j < hash_cnt; j++) {
			if (misc_test(id, crypto_type[i], hash_type[j], 0, 1,
				      PROTO_SSL) == -1)
				return -1;
		}
	}
	for (i = 0; i < crypto_cnt_1; i++) {
		for (j = 0; j < hash_cnt_1; j++) {
			if (misc_test(id, crypto_type_1[i], hash_type_1[j], 0,
				      1, PROTO_SSL) == -1)
				return -1;
		}
	}
	printf("Test SSL/TLS/DTLS Ergodic Pass\n");
	return 0;
}
#endif

static int macsec_single_test(cae_id id)
{
	if (misc_test(id, CIPHER_AES_128_CTR, HASH_GHASH, 0, 1, PROTO_MACSEC) ==
	    -1)
		return -1;

	printf("Test MACSEC aes-128-ctr-ghash Pass\n");
	return 0;
}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
static int macsec_scan_test(cae_id id)
{
	int i, j;
	int hash_cnt = 1;
	int crypto_cnt = 3;
	cipher crypto_type[] = { CIPHER_AES_128_CTR, CIPHER_AES_192_CTR,
				 CIPHER_AES_256_CTR };
	md hash_type[] = { HASH_GHASH };
	for (i = 0; i < crypto_cnt; i++) {
		for (j = 0; j < hash_cnt; j++) {
			if (misc_test(id, crypto_type[i], hash_type[j], 0, 1,
				      PROTO_MACSEC) == -1)
				return -1;
		}
	}
	printf("Test MACSEC Ergodic Pass\n");
	return 0;
}
#endif

static int srtp_single_test(cae_id id)
{
	if (misc_test(id, CIPHER_AES_192_ICM, HASH_HMAC_SHA1, 0, 1,
		      PROTO_SRTP) == -1)
		return -1;

	printf("Test SRTP aes-192-icm-sha1-hmac Pass\n");
	return 0;
}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
static int srtp_scan_test(cae_id id)
{
	int i, j;
	int crypto_cnt = 3;
	int hash_cnt = 1;
	cipher crypto_type[] = { CIPHER_AES_128_ICM, CIPHER_AES_192_ICM,
				 CIPHER_AES_256_ICM };
	md hash_type[] = { HASH_HMAC_SHA1 };
	for (i = 0; i < crypto_cnt; i++) {
		for (j = 0; j < hash_cnt; j++) {
			if (misc_test(id, crypto_type[i], hash_type[j], 0, 1,
				      PROTO_SRTP) == -1)
				return -1;
		}
	}
	printf("Test SRTP Ergodic Pass\n");
	return 0;
}
#endif

static int pseudo_test(cae_id id)
{
	return 0;
}

static void cae_show_usage(void)
{
	printf("Usage: cae [OPTION]...\n\n");
	printf("--id\t\tcae core id\n");
	printf("--help\t\tcommand help\n");
	printf("--pseudo\t\tpseudo random number test case\n");
	printf("--3des ecb\t\t3des-ecb test case\n");
	printf("--3des cbc\t\t3des-cbc test case\n");
	printf("--aes-256 ecb\t\taes-256-ecb test case\n");
	printf("--aes-256 cbc\t\taes-256-cbc test case\n");
	printf("--aes-256 ofb128\t\taes-256-ofb128 test case\n");
	printf("--aes-256 cfb\t\taes-256-cfb test case\n");
	printf("--aes-256 ctr\t\taes-256-ctr test case\n");
	printf("--aes-256 icm\t\taes-256-icm test case\n");
	printf("--aes-256 ccm\t\taes-256-ccm test case\n");
	printf("--aes-256 gcm\t\taes-256-gcm test case\n");
	printf("--crypto\t\tcrypto combined test case\n");
	printf("--md5 basic\t\tmd5 basic test case\n");
	printf("--sha-1 basic\t\tsha-1 basic test case\n");
	printf("--sha-2 basic\t\tsha-2 basic test case\n");
	printf("--aes-xcbc-mac-96\t\taes-xcbc-mac-96 test case\n");
	printf("--ghash\t\tghash test case\n");
	printf("--crc-32\t\tcrc-32 test case\n");
	printf("--hash\t\thash combined test case\n");
	printf("--des ecb --md5 hmac\t\tdes-ecb + md5-hmac test case\n");
	printf("--3des cbc --sha-1 ssl-mac\t\t3des-cbc + sha-1-ssl-mac test case\n");
	printf("--aes cbc --sha-1 ssl-mac\t\taes-cbc + sha-1-ssl-mac test case\n");
	printf("--aes ofb --sha-2 hmac\t\taes-ofb + sha-2-hmac test case\n");
	printf("--aes cfb --aes-xcbc-mac\t\taes-cfb + aes-xcbc-mac test case\n");
	printf("--aes ctr --crc-32\t\taes-ctr + crc-32 test case\n");
	printf("--aes ctr --ghash\t\taes-ctr + ghash test case\n");
	printf("--crypto-hash\t\tcrypto + hash combined test case\n");
	printf("--hash-crypto\t\thash + crypto combined test case\n");
	printf("--ipsec combined\t\tipsec combined test case\n");
	printf("--ssl combined\t\tssl/tls/dtls combined test case\n");
	printf("--macsec combined\t\tmacsec combined test case\n");
	printf("--srtp combined\t\tsrtp combined test case\n");
	printf("--ipsec single\t\tipsec single test case\n");
	printf("--ssl single\t\tssl/tls/dtls single test case\n");
	printf("--macsec single\t\tmacsec single test case\n");
	printf("--srtp single\t\tsrtp single test case\n");
	printf("--dual\t\tdual core test case\n");
}

#if 0
int cae_find_clock_grp(void)
{
	unsigned long i, j, k, l, m;

	for (i = 1600000000; i <= 1600000000; i = i + 100000000) {
		itcs_pll_set_clock(CPU, "apll", i, false);
		udelay(5);
		for (j = 1500000000; j <= 1500000000; j = j + 100000000) {
			itcs_pll_set_clock(CPU, "dpll", j, false);
			udelay(5);
			for (m = 450000000; m <= 750000000; m = m + 50000000) {
				itcs_module_set_clock(CPU, "cae", "dpll", m, false);
				udelay(5);
				for (l = 104000000; l <= 104000000; l = l + 5000000) {
					//itcs_module_set_clock(CPU, "apb", "dpll", l, false);
					itcs_module_set_clock(CPU, "apb", NULL, l, false);
					udelay(5);
					for (k = 100000000; k <= 375000000; k = k + 1000000) {
						itcs_module_set_clock(CPU, "bus2", "dpll", k, false);
						udelay(5);
						printf("----apll: %ld, dpll: %ld, cae: %ld, bus2: %ld, apb: %ld----\n",
						       i, j, m, k, l);
						printf("----real, apll: %ld, dpll: %ld, cae: %ld, bus2: %ld, apb: %ld----\n",
						       itcs_pll_get_clock(CPU, "apll"), itcs_pll_get_clock(CPU, "dpll"),
						       itcs_module_get_clock(CPU, "cae"),
						       itcs_module_get_clock(CPU, "bus2"), itcs_module_get_clock(CPU, "apb"));


						//if (cipher_test(0, CIPHER_AES_256_CBC) == -1)
						//	return -1;
						//if (cipher_test(0, CIPHER_3DES_CBC) == -1)
						//	return -1;

						//if (digest_test(0, HASH_MD5) == -1)
						//	return -1;
						//if (digest_test(0, HASH_SHA1) == -1)
						//	return -1;
						//if (digest_test(0, HASH_SHA2_512) == -1)
						//	return -1;

						//if (parallel_test(CIPHER_AES_128_CBC) == -1)
						//	return -1;

						cae_ivp_test(0, "dual_core_aes_128_gcm", 1, 1);

						cae_ivp_test(0, "all", 0, 0);
						cae_ivp_test(1, "all", 0, 0);
						printf("\n");
						//while (1);
					}
				}
			}
		}
	}
	return 0;
}
#endif

int cae_main(int argc, char *argv[])
{
	int option_index = 0;
	int c;
	int ret = 0;
	cae_id id = CAE0;
	const char short_options[] = "";
	const struct option long_options[] = { { "pseudo", 0, 0, '0' },
					       { "des", 1, 0, '1' },
					       { "3des", 1, 0, '2' },
					       { "aes-256", 1, 0, '3' },
					       { "crypto", 1, 0, '4' },
					       { "md5", 1, 0, '5' },
					       { "sha1", 1, 0, '6' },
					       { "sha2-512", 1, 0, '7' },
					       { "aes-128-xcbc-mac-96", 0, 0,
						 '8' },
					       { "ghash", 0, 0, '9' },
					       { "crc-32", 0, 0, 'a' },
					       { "hash", 1, 0, 'b' },
					       { "crypto-hash", 0, 0, 'c' },
					       { "hash-crypto", 0, 0, 'd' },
					       { "ipsec", 1, 0, 'e' },
					       { "ssl", 1, 0, 'f' },
					       { "macsec", 1, 0, 'g' },
					       { "srtp", 1, 0, 'i' },
					       { "help", 0, 0, 'h' },
					       { "id", 1, 0, 'j' },
					       { "dual", 0, 0, 'k' },
					       { "ivp", 1, 0, 'l' },
					       { "speed", 1, 0, 'm' },
					       { "ivp_speed", 1, 0, 'n' },
					       { "fpga_ivp_speed", 0, 0, 'o' },
					       { 0, 0, 0, 0 } };
	cipher crypto_type = CIPHER_NULL;
	md hash_type = HASH_NULL;
	int pseudo_flag = 0;
	int ipsec_flag = 0;
	int ssl_flag = 0;
	int macsec_flag = 0;
	int srtp_flag = 0;
	int proto_single = 0;
	int hash_first = 0;
	int dual_core = 0;
	int ivp_test = 0;
	char ivp_name[MAX_STR_LEN] = { 0 };
	int speed_test = 0;
	int speed_enc = 0;
	int ivp_speed_test = 0;
	int fpga_ivp_speed_test = 0;
	char scan_params[MAX_STR_LEN] = { 0 };

#if 0
	return cae_find_clock_grp();
#endif

#ifdef CONFIG_COMPILE_ASIC
	itcs_module_set_clock(CPU, "cae", "dpll", 750000000, false);
#endif

	while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
		switch (c) {
		/* pseudo. */
		case '0':
			pseudo_flag = 1;
			break;
		/* des cipher. */
		case '1':
			if (!strcmp(optarg, "ecb")) {
				crypto_type = CIPHER_DES_ECB;
				if (optind == 7)
					hash_first = 1;
			}
			break;
		/* 3des cipher. */
		case '2':
			if (!strcmp(optarg, "ecb")) {
				crypto_type = CIPHER_3DES_ECB;
				if (optind == 7)
					hash_first = 1;
			} else if (!strcmp(optarg, "cbc")) {
				crypto_type = CIPHER_3DES_CBC;
				if (optind == 7)
					hash_first = 1;
			}
			break;
		/* aes-256 cipher. */
		case '3':
			if (!strcmp(optarg, "ecb"))
				crypto_type = CIPHER_AES_256_ECB;
			else if (!strcmp(optarg, "cbc"))
				crypto_type = CIPHER_AES_256_CBC;
			else if (!strcmp(optarg, "ofb"))
				crypto_type = CIPHER_AES_256_OFB128;
			else if (!strcmp(optarg, "cfb"))
				crypto_type = CIPHER_AES_256_CFB;
			else if (!strcmp(optarg, "ctr"))
				crypto_type = CIPHER_AES_256_CTR;
			else if (!strcmp(optarg, "icm"))
				crypto_type = CIPHER_AES_256_ICM;
			else if (!strcmp(optarg, "ccm"))
				crypto_type = CIPHER_AES_256_CCM;
			else if (!strcmp(optarg, "gcm"))
				crypto_type = CIPHER_AES_256_GCM;
			break;
		/* crypto combined. */
		case '4':
			strcpy(scan_params, optarg);
			crypto_scan_flag = 1;
			break;
		/* md5 hash. */
		case '5':
			if (!strcmp(optarg, "basic"))
				hash_type = HASH_MD5;
			else if (!strcmp(optarg, "hmac"))
				hash_type = HASH_HMAC_MD5;
			break;
		/* sha1 hash. */
		case '6':
			if (!strcmp(optarg, "basic"))
				hash_type = HASH_SHA1;
			else if (!strcmp(optarg, "ssl-mac"))
				hash_type = HASH_SSLMAC_SHA1;
			break;
		/* sha2-512 hash. */
		case '7':
			if (!strcmp(optarg, "basic"))
				hash_type = HASH_SHA2_512;
			else if (!strcmp(optarg, "hmac"))
				hash_type = HASH_HMAC_SHA2_512;
			break;
		/* aes-xcbc-mac hash. */
		case '8':
			hash_type = HASH_AES_128_XCBC_MAC_96;
			break;
		/* ghash hash. */
		case '9':
			hash_type = HASH_GHASH;
			break;
		/* crc-32 hash. */
		case 'a':
			hash_type = HASH_CRC32;
			break;
		/* hash combined. */
		case 'b':
			strcpy(scan_params, optarg);
			hash_scan_flag = 1;
			break;
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		/* crypto-hash combined. */
		case 'c':
			crypto_hash_scan_flag = 1;
			break;
		case 'd':
			hash_crypto_scan_flag = 1;
			break;
#endif
		/* ipsec. */
		case 'e':
			if (!strcmp(optarg, "single"))
				proto_single = 1;
			else if (!strcmp(optarg, "combined"))
				proto_single = 0;
			ipsec_flag = 1;
			break;
		/* ssl/tls/dtls. */
		case 'f':
			if (!strcmp(optarg, "single"))
				proto_single = 1;
			else if (!strcmp(optarg, "combined"))
				proto_single = 0;
			ssl_flag = 1;
			break;
		/* macsec. */
		case 'g':
			if (!strcmp(optarg, "single"))
				proto_single = 1;
			else if (!strcmp(optarg, "combined"))
				proto_single = 0;
			macsec_flag = 1;
			break;
		/* srtp. */
		case 'i':
			if (!strcmp(optarg, "single"))
				proto_single = 1;
			else if (!strcmp(optarg, "combined"))
				proto_single = 0;
			srtp_flag = 1;
			break;
		/* cae id. */
		case 'j':
			if (!strcmp(optarg, "0"))
				id = CAE0;
			else if (!strcmp(optarg, "1"))
				id = CAE1;
			break;
		/* dual core. */
		case 'k':
			dual_core = 1;
			break;
		case 'l':
			ivp_test = 1;
			strcpy(ivp_name, optarg);
			break;
		case 'm':
			speed_test = 1;
			if (!strcmp(optarg, "enc"))
				speed_enc = 1;
			else if (!strcmp(optarg, "dec"))
				speed_enc = 0;
			break;
		case 'n':
			ivp_speed_test = 1;
			strcpy(ivp_name, optarg);
			break;
		case 'o':
			fpga_ivp_speed_test = 1;
			break;
		case 'h':
		default:
			cae_show_usage();
			ret = -1;
			goto err;
		}
	}

	if (speed_test) {
		if (ivp_speed_test)
			cae_ivp_test(id, ivp_name, ivp_speed_test, speed_enc);
		else
			cae_speed_test(id, crypto_scan_param_proc(scan_params),
				       speed_enc, fpga_ivp_speed_test);
		ret = 0;
		goto err;
	}

	if (ivp_test) {
		cae_ivp_test(id, ivp_name, ivp_speed_test, speed_enc);
		ret = 0;
		goto err;
	}

	if (dual_core) {
		parallel_test(crypto_scan_param_proc(scan_params));
	} else if (pseudo_flag) {
		ret = pseudo_test(id);
	} else if (crypto_scan_flag) {
		ret = crypto_scan_test(id, scan_params);
	} else if (hash_scan_flag) {
		ret = hash_scan_test(id, scan_params);
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	} else if (crypto_hash_scan_flag) {
		ret = crypto_hash_scan_test(id);
	} else if (hash_crypto_scan_flag) {
		ret = hash_crypto_scan_test(id);
#endif
	} else if (ipsec_flag) {
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		if (proto_single)
			ret = ipsec_single_test(id);
		else
			ret = ipsec_scan_test(id);
#elif defined(CONFIG_COMPILE_RTL)
		if (proto_single)
			ret = ipsec_single_test(id);
#endif
	} else if (ssl_flag) {
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		if (proto_single)
			ret = ssl_single_test(id);
		else
			ret = ssl_scan_test(id);
#elif defined(CONFIG_COMPILE_RTL)
		if (proto_single)
			ret = ssl_single_test(id);
#endif
	} else if (macsec_flag) {
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		if (proto_single)
			ret = macsec_single_test(id);
		else
			ret = macsec_scan_test(id);
#elif defined(CONFIG_COMPILE_RTL)
		if (proto_single)
			ret = macsec_single_test(id);
#endif
	} else if (srtp_flag) {
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		if (proto_single)
			ret = srtp_single_test(id);
		else
			ret = srtp_scan_test(id);
#elif defined(CONFIG_COMPILE_RTL)
		if (proto_single)
			ret = srtp_single_test(id);
#endif
	} else if (crypto_type && hash_type) {
		if ((crypto_type == CIPHER_DES_ECB &&
		     hash_type == HASH_HMAC_MD5) ||
		    (hash_type == HASH_SSLMAC_SHA1 &&
		     crypto_type == CIPHER_3DES_CBC)) {
			ret = misc_test(id, crypto_type, hash_type, hash_first,
					1, PROTO_NULL);
			ret = misc_test(id, crypto_type, hash_type, hash_first,
					0, PROTO_NULL);
		} else {
			ret = misc_test(id, crypto_type, hash_type, hash_first,
					1, PROTO_NULL);
		}
	} else if (crypto_type) {
		ret = cipher_test(id, crypto_type);
	} else if (hash_type) {
		ret = digest_test(id, hash_type);
	}

	if (optind == 1) {
		cae_show_usage();
		ret = -1;
		goto err;
	}
err:
	optind = 1;
	return ret;
}

int cae_rtl(int id)
{
	printf("invoking id: %d\n", id);
	return 0;
}

void cae_init(void)
{
	register_testbench("cae", cae_main, cae_rtl);
}

testbench_init(cae_init);

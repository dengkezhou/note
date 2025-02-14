#include <common.h>
#include <cae.h>
#include "cipher.h"
#include "digest.h"
#include "misc.h"

#include "c_da_pec.h"
#include "da_pec_internal.h"

#include "api_pec.h"
#include "adapter_dmabuf.h"

extern void LKM_probe(cae_device *dev, unsigned long base_addr);
extern int Driver97_Init(cae_device *dev);
extern void Driver97_Exit(cae_device *dev);
extern PEC_Status_t PEC_Init(cae_device *dev, const unsigned int InterfaceId,
			     const PEC_InitBlock_t *const InitBlock_p);
extern PEC_Status_t PEC_UnInit(cae_device *dev, const unsigned int InterfaceId);

#if defined(CONFIG_DRV_CAE_IVP)
extern void test_ipsec_esp_in_aes_ctr_sha1_transport(void);
extern void test_ipsec_esp_out_aes_ctr_sha1_transport_esn(void);
extern void test_ipsec_esp_in_aes_ctr_sha1_transport_esn(void);
extern void test_ipsec_esp_out_aes_ctr_sha1_transport(void);
extern void test_ipsec_esp_out_aes_ctr_sha2_transport(void);
extern void test_ipsec_esp_out_aes_cbc_sha1_transport(void);
extern void test_ipsec_esp_in_aes_ctr_sha2_transport(void);
extern void test_ipsec_esp_in_aes_cbc_sha1_transport(void);
extern void intc_hia(void);
extern void eip97_reg_test(void);
extern void test_aes_ecb_nist_dec(void);
extern void test_hmac_sha384_fips(void);
extern void test_hmac_sha1(void);
extern void test_tdes_ecb_nist_dec(void);
extern void test_crc32_chained(void);
extern void test_sha384_fips(void);
extern void test_aes_ctr_nist(void);
extern void test_sha256(void);
extern void test_tdes_ecb_length(void);
extern void test_hmac_sha224(void);
extern void test_bypass(void);
extern void test_hmac_sha256(void);
extern void test_hmac_sha256_fips(void);
extern void test_aes_cbc_nist(void);
extern void test_hmac_sha1_fips(void);
extern void test_sha1_save_hash(void);
extern void test_sha224_fips(void);
extern void test_md5(void);
extern void test_sha1_fips(void);
extern void test_crc32(void);
extern void test_aes_ctr_nist_dec(void);
extern void test_hmac_md5_rfc(void);
extern void test_sha512_fips(void);
extern void test_md5_rfc(void);
extern void test_hmac_sha224_fips(void);
extern void test_hmac_sha512_fips(void);
extern void test_aes_cbc_nist_dec(void);
extern void test_tdes_ecb_nist(void);
extern void test_hmac_md5(void);
extern void test_aes_ecb_nist(void);
extern void test_des_cbc_length(void);
extern void test_sha1(void);
extern void test_sha256_fips(void);
extern void test_des_ecb_length(void);
extern void test_sha224(void);
extern void test_macsec_in_default(void);
extern void test_macsec_out_default(void);
extern void cae_ivp_speed_test(int id, char *name, int enc);

volatile unsigned int ivp_cae_base_addr = 0;
#endif

static volatile unsigned int cae_inited = 0;

int itcs_cipher_ctx_set_padding(cipher_ctx *ctx, int pad)
{
	return cipher_set_padding(ctx, pad);
}

int itcs_cipher_init(cipher_ctx *ctx, const cipher type, unsigned char *key,
		     unsigned char *iv, int enc)
{
	return cipher_init(ctx, type, key, iv, enc);
}

cipher_ctx *itcs_cipher_ctx_new(cae_device *dev)
{
	cipher_ctx *ctx;
	ctx = cipher_alloc_resources();
	if (ctx == NULL)
		return NULL;
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	memset(ctx, 0x0, sizeof(cipher_ctx));
#endif
	ctx->id = dev->id;
	ctx->dev = dev;
	dev->ctx = ctx;
	ctx->type = CAE_CRYPTO_ALGO;
	ctx->first_pkt = 1;
	ctx->final_pkt = 0;
	ctx->allocated = 0;
	return ctx;
}

int itcs_cipher_update(cipher_ctx *ctx, unsigned char *out, int *out_len,
		       const unsigned char *in, int in_len, bool blocked)
{
	return cipher_update(ctx, out, out_len, in, in_len, blocked);
}

int itcs_cipher_final(cipher_ctx *ctx, unsigned char *out, int *out_len)
{
	return cipher_final(ctx, out, out_len);
}

void itcs_cipher_ctx_free(cipher_ctx *ctx)
{
	cipher_free_resources(ctx);
}

int itcs_digest_init(md_ctx *ctx, const md type, unsigned char *key)
{
	return digest_init(ctx, type, key);
}

md_ctx *itcs_md_ctx_new(cae_device *dev)
{
	md_ctx *ctx;
	ctx = md_alloc_resources();
	if (ctx == NULL)
		return NULL;
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	memset(ctx, 0x0, sizeof(md_ctx));
#endif
	ctx->id = dev->id;
	ctx->dev = dev;
	ctx->first_pkt = 1;
	ctx->multi_part_packet_flag = 1;
	dev->ctx = ctx;
	ctx->type = CAE_HASH_ALGO;
	ctx->hash_final_pkt = 0;
	return ctx;
}

int itcs_digest_update(md_ctx *ctx, const void *in, unsigned long len,
		       bool blocked)
{
	return digest_update(ctx, in, len, blocked);
}

int itcs_digest_final(md_ctx *ctx, unsigned char *md, unsigned int *len)
{
	return digest_final(ctx, md, len);
}

void itcs_md_ctx_free(md_ctx *ctx)
{
	md_free_resources(ctx);
}

int itcs_misc_ctx_set_padding(misc_ctx *ctx, int pad)
{
	return misc_set_padding(ctx, pad);
}

int itcs_misc_init(misc_ctx *ctx, misc_params *misc_paras)
{
	return misc_init(ctx, misc_paras);
}

misc_ctx *itcs_misc_ctx_new(cae_device *dev)
{
	misc_ctx *ctx;
	ctx = misc_alloc_resources();
	if (ctx == NULL)
		return NULL;
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	memset(ctx, 0x0, sizeof(misc_ctx));
#endif
	ctx->id = dev->id;
	ctx->dev = dev;
	return ctx;
}

int itcs_misc_update(misc_ctx *ctx, const void *in, unsigned long in_len)
{
	return misc_update(ctx, in, in_len);
}

int itcs_misc_final(misc_ctx *ctx, unsigned char *md, unsigned int *len)
{
	return misc_final(ctx, md, len);
}

void itcs_misc_ctx_free(misc_ctx *ctx)
{
	misc_free_resources(ctx);
}

int cae_lowlevel_init(cae_device *dev)
{
	PEC_Status_t Status;

	Driver97_Init(dev);

	Log_FormattedMessage("DA_PEC loaded\n");
#ifdef DA_PEC_GATHER
	Log_FormattedMessage("DA_PEC: Gather is enabled\n");
#endif

	{
		PEC_InitBlock_t InitBlock = { 0, 0 };
		unsigned int LoopCounter = DA_PEC_PKT_GET_RETRY_COUNT;

		Log_FormattedMessage(
			"DA_PEC: Initializing PEC for interface ID %d\n",
			INTERFACE_ID);
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		while (LoopCounter > 0) {
			Status = PEC_Init(dev, INTERFACE_ID, &InitBlock);
			if (Status == PEC_STATUS_OK)
				break;
			else if (Status != PEC_STATUS_OK &&
				 Status != PEC_STATUS_BUSY) {
				Log_FormattedMessage(
					"DA_PEC: PEC could not be initialized, error=%d\n",
					Status);
				return -1;
			} else {
				// Wait for DA_PEC_PKT_GET_TIMEOUT_MS milliseconds
				da_pec_usleep(DA_PEC_PKT_GET_TIMEOUT_MS * 1000);
				LoopCounter--;
			}
		} // while
#elif defined(CONFIG_COMPILE_RTL)
		while (1) {
			Status = PEC_Init(dev, INTERFACE_ID, &InitBlock);
			if (Status == PEC_STATUS_OK)
				break;
			else if (Status != PEC_STATUS_OK &&
				 Status != PEC_STATUS_BUSY) {
				Log_FormattedMessage(
					"DA_PEC: PEC could not be initialized, error=%d\n",
					Status);
				return -1;
			}
		}
#endif
		// Check for timeout
		if (LoopCounter == 0) {
			Log_FormattedMessage(
				"DA_PEC: PEC could not be initialized, timeout\n");
			return -1;
		}
	}

	{
		PEC_Capabilities_t Capabilities;
		//Log_FormattedMessage("DA_PEC: Retrieving PEC capabilities\n");
		Status = PEC_Capabilities_Get(&Capabilities);
		if (Status != PEC_STATUS_OK) {
			LOG_CRIT(
				"DA_PEC: PEC capabilities could not be obtained, error=%d\n",
				Status);
			return -1;
		}
		//Log_FormattedMessage("DA_PEC: PEC capabilities: %s\n",
		//		     Capabilities.szTextDescription);
	}
	return 0;
}

cae_device *itcs_cae_init(cae_id id)
{
	cae_device *dev = NULL;

	dev = (cae_device *)malloc(sizeof(cae_device));
	if (!dev)
		return NULL;
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	memset(dev, 0, sizeof(cae_device));
#endif
	dev->AdapterPEC_InitLock = 1;
	dev->Adapter_Ring_EIP202_DMA_Alignment_ByteCount =
		ADAPTER_DMABUF_ALIGNMENT_INVALID;

	if (!cae_inited) {
		itcs_module_enable(CPU, "cae");
		cae_inited = 1;
	}
	if (id == CAE0) {
		/* set cae base address. */
		LKM_probe(dev, ITCS_C_CAE0_BASE);
		/* set irq number for global irq. */
		dev->irq = C_CAE4_IRQn;
		dev->id = CAE0;
	} else if (id == CAE1) {
		/* set cae base address. */
		LKM_probe(dev, ITCS_C_CAE1_BASE);
		/* set irq number for global irq. */
		dev->irq = C_CAE9_IRQn;
		dev->id = CAE1;
	} else {
		printf("unsupported cae core %d!\n", id);
		goto err;
	}
	if (cae_lowlevel_init(dev) == -1)
		printf("cae%d lowlevel init failed!\n", id);

	printf("cae core %d inited\n", id);

	return dev;
err:
	free(dev);
	return NULL;
}

void itcs_cae_exit(cae_device *dev)
{
	PEC_UnInit(dev, INTERFACE_ID);
	Driver97_Exit(dev);
	if (dev) {
		free(dev);
		dev = NULL;
	}
}

void cae_ivp_test(cae_id id, char *name, int ivp_speed_test, int enc)
{
#if defined(CONFIG_DRV_CAE_IVP)
	int all_flag = 0;

	itcs_module_enable(CPU, "cae");
	if (id == CAE0) {
		ivp_cae_base_addr = ITCS_C_CAE0_BASE;
	} else if (id == CAE1) {
		ivp_cae_base_addr = ITCS_C_CAE1_BASE;
	} else {
		printf("ivp: unsupported cae id %d\n", id);
		return;
	}

	if (ivp_speed_test) {
		cae_ivp_speed_test(id, name, enc);
		itcs_module_reset(CPU, "cae");
		return;
	}

	printf("cae%d starts ivp test\n", id);
	if (!strcmp(name, "all"))
		all_flag = 1;
	if (!strcmp(name, "test_ipsec_esp_in_aes_ctr_sha1_transport") ||
	    all_flag == 1) {
		test_ipsec_esp_in_aes_ctr_sha1_transport();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_ipsec_esp_out_aes_ctr_sha1_transport_esn") ||
	    all_flag == 1) {
		test_ipsec_esp_out_aes_ctr_sha1_transport_esn();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_ipsec_esp_in_aes_ctr_sha1_transport_esn") ||
	    all_flag == 1) {
		test_ipsec_esp_in_aes_ctr_sha1_transport_esn();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_ipsec_esp_out_aes_ctr_sha1_transport") ||
	    all_flag == 1) {
		test_ipsec_esp_out_aes_ctr_sha1_transport();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_ipsec_esp_out_aes_ctr_sha2_transport") ||
	    all_flag == 1) {
		test_ipsec_esp_out_aes_ctr_sha2_transport();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_ipsec_esp_out_aes_cbc_sha1_transport") ||
	    all_flag == 1) {
		test_ipsec_esp_out_aes_cbc_sha1_transport();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_ipsec_esp_in_aes_ctr_sha2_transport") ||
	    all_flag == 1) {
		test_ipsec_esp_in_aes_ctr_sha2_transport();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_ipsec_esp_in_aes_cbc_sha1_transport") ||
	    all_flag == 1) {
		test_ipsec_esp_in_aes_cbc_sha1_transport();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "intc_hia") || all_flag == 1) {
		intc_hia();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "eip97_reg_test") || all_flag == 1) {
		eip97_reg_test();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_aes_ecb_nist_dec") || all_flag == 1) {
		test_aes_ecb_nist_dec();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_hmac_sha384_fips") || all_flag == 1) {
		test_hmac_sha384_fips();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_hmac_sha1") || all_flag == 1) {
		test_hmac_sha1();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_tdes_ecb_nist_dec") || all_flag == 1) {
		test_tdes_ecb_nist_dec();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_crc32_chained") || all_flag == 1) {
		test_crc32_chained();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_sha384_fips") || all_flag == 1) {
		test_sha384_fips();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_aes_ctr_nist") || all_flag == 1) {
		test_aes_ctr_nist();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_sha256") || all_flag == 1) {
		test_sha256();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_tdes_ecb_length") || all_flag == 1) {
		test_tdes_ecb_length();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_hmac_sha224") || all_flag == 1) {
		test_hmac_sha224();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_bypass") || all_flag == 1) {
		test_bypass();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_hmac_sha256") || all_flag == 1) {
		test_hmac_sha256();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_hmac_sha256_fips") || all_flag == 1) {
		test_hmac_sha256_fips();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_aes_cbc_nist") || all_flag == 1) {
		test_aes_cbc_nist();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_hmac_sha1_fips") || all_flag == 1) {
		test_hmac_sha1_fips();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_sha1_save_hash") || all_flag == 1) {
		test_sha1_save_hash();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_sha224_fips") || all_flag == 1) {
		test_sha224_fips();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_md5") || all_flag == 1) {
		test_md5();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_sha1_fips") || all_flag == 1) {
		test_sha1_fips();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_crc32") || all_flag == 1) {
		test_crc32();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_aes_ctr_nist_dec") || all_flag == 1) {
		test_aes_ctr_nist_dec();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_hmac_md5_rfc") || all_flag == 1) {
		test_hmac_md5_rfc();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_sha512_fips") || all_flag == 1) {
		test_sha512_fips();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_md5_rfc") || all_flag == 1) {
		test_md5_rfc();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_hmac_sha224_fips") || all_flag == 1) {
		test_hmac_sha224_fips();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_hmac_sha512_fips") || all_flag == 1) {
		test_hmac_sha512_fips();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_aes_cbc_nist_dec") || all_flag == 1) {
		test_aes_cbc_nist_dec();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_tdes_ecb_nist") || all_flag == 1) {
		test_tdes_ecb_nist();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_hmac_md5") || all_flag == 1) {
		test_hmac_md5();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_aes_ecb_nist") || all_flag == 1) {
		test_aes_ecb_nist();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_des_cbc_length") || all_flag == 1) {
		test_des_cbc_length();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_sha1") || all_flag == 1) {
		test_sha1();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_sha256_fips") || all_flag == 1) {
		test_sha256_fips();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_des_ecb_length") || all_flag == 1) {
		test_des_ecb_length();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_sha224") || all_flag == 1) {
		test_sha224();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_macsec_in_default") || all_flag == 1) {
		test_macsec_in_default();
		itcs_module_reset(CPU, "cae");
	}
	if (!strcmp(name, "test_macsec_out_default") || all_flag == 1) {
		test_macsec_out_default();
		itcs_module_reset(CPU, "cae");
	}
#endif
}

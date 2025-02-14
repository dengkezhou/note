#ifndef __CAE_H__
#define __CAE_H__

#include <asm/io.h>
#include <stdbool.h>
#include <malloc.h>

#define CAE_DDK_INFO_DUMP 0

#include "cs_driver_ext.h"
#include "c_da_pec.h"
#include "da_pec_internal.h"
#include "api_pec_sg.h"
#include "api_dmabuf.h"
#include "clib.h"
#include "sa_builder.h"
#include "sa_builder_basic.h"
#include "token_builder.h"
#include "device_types.h"
#include "device_internal.h"
#include "dmares_types.h"
#include "dmares_record.h"
#include "eip97_global_types.h"
#include "adapter_lock.h"
#include "adapter_interrupts.h"
#include "eip202_ring_types.h"

/* cipher. */
#define MAX_CRYPTO_BLOCK_SIZE 32
#define MAX_CRYPTO_KEY_LEN 32
#define MAX_IV_LEN 16

#define PADDING_NONE 0
#define PADDING_PKCS7 1
#define PADDING_ISO7816_4 2
#define PADDING_ANSI923 3
#define PADDING_ISO10126 4
#define PADDING_ZERO 5

#define ENCRYPT 1
#define DECRYPT 0
#define CAE_UPDATE_BLOCK 1
#define CAE_UPDATE_NONBLOCK 0

/* digest. */
#define MAX_DIGEST_BLOCK_SIZE 256 //64
#define MAX_DIGEST_KEY_LEN 64
#define HMAC_PRE_COMPUTE_LEN 128

#define MAX_OS_IRQS 256
#define ADAPTER_MAX_AICS 2
// Define maximum number of supported interrupts
#define ADAPTER_MAX_INTERRUPTS 28

// LKM PCI implementation administration data
typedef struct {
	// declarations native to Linux kernel
	//struct pci_dev * PCI_Device_p;

	// virtual address returned by ioremap()
	uint32_t __iomem *MappedBaseAddr_p;

	// physical address passed to ioremap()
	phys_addr_t PhysBaseAddr;

	// PCI device driver data
	//struct pci_driver PCI_Driver;

	// PCI aperture identifier (Bar ID)
	int ResId;

	// PCI aperture size in bytes
	phys_addr_t ResByteCount;

	// true - MSI is used, false otherwise
	bool fUseMSI;

	bool fRetainMap;

	// Initialization flag, true - initialized, otherwise - false
	bool fInitialized;

} LKM_Admin_t;

typedef struct {
	int ReadIndex;
	int WriteIndex;
	uint32_t *Nrs_p;
} HWPAL_FreeList_t;

// Data structure for each Advanced interrupt controller
typedef struct {
	Device_Handle_t Device;
	char *name; // Device name (can be found with Device_Find().
	int irq_idx; // if isIRQ, then index of device interrupt.
		// If !isIRQ. then driver IRQ number to which AIC is connected.
	int irq; // System IRQ number
	int BitIRQs[32]; // Mapping from source bits to internal driver IRQ numbers.
	bool isIRQ; // true if AIC has dedicated system IRQ line, false is it
		// is cascaded from another AIC.
} Adapter_AIC_t;

typedef struct {
	void *User_p;
	DMABuf_Handle_t SrcPkt_Handle;
	DMABuf_Handle_t DstPkt_Handle;
	DMABuf_Handle_t Token_Handle;
	unsigned int Bypass_WordCount;
} Adapter_SideChannelRecord_t;

typedef struct {
	int Size;
	int ReadIndex;
	int WriteIndex;
	Adapter_SideChannelRecord_t Records[1 + ADAPTER_PEC_MAX_PACKETS +
					    ADAPTER_PEC_MAX_LOGICDESCR];
} AdapterPEC_SideChannelFIFO_t;

typedef enum {
	EIP201_CONFIG_ACTIVE_LOW = 0,
	EIP201_CONFIG_ACTIVE_HIGH,
	EIP201_CONFIG_FALLING_EDGE,
	EIP201_CONFIG_RISING_EDGE
} EIP201_Config_t;

// Data structure per interrupt
typedef struct {
	uint32_t SourceBitMask;
	char *name;
	Adapter_AIC_t *AIC;
	char *AICName;
	//struct tasklet_struct tasklet;
	Adapter_InterruptHandler_t Handler;
	uint32_t Counter;
	void *extra;
	bool fHaveTasklet;
	EIP201_Config_t Config;
} Adapter_Interrupt_t;

typedef struct {
	volatile PEC_NotifyFunction_t ResultNotifyCB_p;
	void *result_notify_args;
	volatile unsigned int ResultsCount;

	volatile PEC_NotifyFunction_t CommandNotifyCB_p;
	volatile unsigned int CommandsCount;
	void *command_notify_args;

} PEC_Notify_t;

// CDR settings
typedef struct {
	// Additional Token Pointer Descriptor Mode
	// When true the token data can be stored in a separate from the descriptor
	// DMA buffer
	bool fATP;

	// When true then the tokens consisting out of 1 or 2 32-bit words
	// can be passed to the PE directly via the command descriptor
	bool fATPtoToken;

	// Other ARM settings
	EIP202_ARM_Ring_Settings_t Params;

} EIP202_CDR_Settings_t;

// RDR settings
typedef struct {
	// Other ARM settings
	EIP202_ARM_Ring_Settings_t Params;

} EIP202_RDR_Settings_t;

// Logical Command Descriptor
typedef struct {
	// control fields for the command descriptor
	// EIP202_CDR_Write_ControlWord() helper function
	// can be used for obtaining this word
	uint32_t ControlWord;

	// Token header word
	uint32_t TokenHeader;

	// This parameter is copied through from command to result descriptor
	// unless EIP202_RING_ANTI_DMA_RACE_CONDITION_CDS configuration parameter
	// is defined in c_eip202_ring.h
	uint32_t ApplicationId;

	// Source packet data length, in bytes
	unsigned int SrcPacketByteCount;

	// Source packet data, has to be provided by the caller:
	// Physical address that can be used by Device DMA
	EIP202_DeviceAddress_t SrcPacketAddr;

	// Context Data DMA buffer, has to be allocated and filled in by the caller
	// Physical address that can be used by Device DMA
	EIP202_DeviceAddress_t TokenDataAddr;

	// Context Data DMA buffer, has to be allocated and filled in by the caller
	// Physical address that can be used by Device DMA
	EIP202_DeviceAddress_t ContextDataAddr;

	// Input Token buffer with fixed size
	uint32_t *Token_p;

} EIP202_ARM_CommandDescriptor_t;

// Logical Prepared Descriptor
typedef struct {
	// Control word for the prepared descriptor
	// EIP202_RDR_Write_Prepared_ControlWord() helper function
	// can be used for obtaining this word
	uint32_t PrepControlWord;

	// Destination packet data buffer, has to be provided by the caller:
	// Physical address that can be used by Device DMA
	EIP202_DeviceAddress_t DstPacketAddr;

} EIP202_ARM_PreparedDescriptor_t;

// Logical Result Descriptor
typedef struct {
	// control fields for the command descriptor
	// EIP202_RDR_Read_Processed_ControlWord() helper function
	// can be used for obtaining this word
	uint32_t ProcControlWord;

	// Destination packet (segment) data, has to be provided by the caller:
	// Physical address that can be used by Device DMA
	EIP202_DeviceAddress_t DstPacketAddr;

	// control fields for the command descriptor
	// EIP202_RDR_Read_Processed_ControlWord() helper function
	// can be used for obtaining this word

	// Output Token buffer with fixed size
	uint32_t *Token_p;

} EIP202_ARM_ResultDescriptor_t;

typedef struct {
	int id;
	LKM_Admin_t LKM_Admin;
	int irq;
	bool Adapter_IsInitialized;
#ifdef ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
	Device_Handle_t Adapter_Device_BOARDCTRL;
#endif
	int Device_IRQ;
	// All supported devices
	Device_Admin_t *HWPALLib_Devices_p[HWPAL_DEVICE_COUNT];
	// Global administration data
	Device_Global_Admin_t HWPALLib_Device_Global;
	int HandlesCount; // remainder are valid only when this is != 0
	int ChunksCount;
	uint32_t *Handles_p;
	DMAResource_Record_t **RecordChunkPtrs_p;
	HWPAL_FreeList_t FreeHandles;
	HWPAL_FreeList_t FreeRecords;
	void *HWPAL_Lock_p;
	EIP97_Global_IOArea_t Global_IOArea;
	bool Global_IsInitialized;
	bool Global_PRNG_Present;
	bool Adapter_IRQ_Initialized;
	Adapter_AIC_t *IRQ_AIC_Mapping[MAX_OS_IRQS];
	volatile bool PEC_IsInitialized[ADAPTER_PEC_DEVICE_COUNT];
	int AdapterPEC_InitLock;
	Adapter_Lock_CS_t AdapterPEC_InitCS;
	Adapter_Lock_t AdapterPEC_PutLock[ADAPTER_PEC_DEVICE_COUNT];
	Adapter_Lock_CS_t AdapterPEC_PutCS[ADAPTER_PEC_DEVICE_COUNT];
	Adapter_Lock_t AdapterPEC_GetLock[ADAPTER_PEC_DEVICE_COUNT];
	Adapter_Lock_CS_t AdapterPEC_GetCS[ADAPTER_PEC_DEVICE_COUNT];
	AdapterPEC_SideChannelFIFO_t
		Adapter_SideChannelFIFO[ADAPTER_PEC_DEVICE_COUNT];
	Adapter_AIC_t Adapter_AICTable[ADAPTER_MAX_AICS];
	Adapter_Interrupt_t Adapter_IRQTable[ADAPTER_MAX_INTERRUPTS];
	PEC_Notify_t PEC_Notify[ADAPTER_PEC_DEVICE_COUNT];

	EIP202_CDR_Settings_t CDR_Settings;
	EIP202_RDR_Settings_t RDR_Settings;
#ifdef ADAPTER_EIP202_INTERRUPTS_ENABLE
	unsigned int EIP202_Interrupts[ADAPTER_EIP202_DEVICE_COUNT];
#endif
	EIP202_Ring_IOArea_t CDR_IOArea[ADAPTER_EIP202_DEVICE_COUNT];
	EIP202_Ring_IOArea_t RDR_IOArea[ADAPTER_EIP202_DEVICE_COUNT];
	DMAResource_Handle_t CDR_Handle[ADAPTER_EIP202_DEVICE_COUNT];
	DMAResource_Handle_t RDR_Handle[ADAPTER_EIP202_DEVICE_COUNT];
	EIP202_ARM_CommandDescriptor_t
		EIP202_CDR_Entries[ADAPTER_EIP202_DEVICE_COUNT]
				  [ADAPTER_EIP202_MAX_LOGICDESCR];
	EIP202_ARM_PreparedDescriptor_t
		EIP202_RDR_Prepared[ADAPTER_EIP202_DEVICE_COUNT]
				   [ADAPTER_EIP202_MAX_LOGICDESCR];
	EIP202_ARM_ResultDescriptor_t
		EIP202_RDR_Entries[ADAPTER_EIP202_DEVICE_COUNT]
				  [ADAPTER_EIP202_MAX_LOGICDESCR];
	bool Adapter_Ring_EIP202_Configured;
	uint8_t Adapter_Ring_EIP202_HDW;
	uint8_t Adapter_Ring_EIP202_CFSize;
	uint8_t Adapter_Ring_EIP202_RFSize;
	int Adapter_Ring_EIP202_DMA_Alignment_ByteCount;
	void *ctx;
} cae_device;

typedef enum {
	CAE_ALGO_NULL,
	CAE_CRYPTO_ALGO,
	CAE_HASH_ALGO,
	CAE_MISC_ALGO
} algo_type;

typedef enum { CAE0, CAE1 } cae_id;

typedef enum {
	IPSEC_IP_MODE_NULL,
	IPSEC_IP_MODE_IPV4,
	IPSEC_IP_MODE_IPV6
} ipsec_ip_mode;

typedef enum {
	IPSEC_WORK_MODE_NULL,
	IPSEC_WORK_MODE_TUNNEL,
	IPSEC_WORK_MODE_TRANSPORT
} ipsec_work_mode;

typedef enum {
	IPSEC_PROTO_NULL,
	IPSEC_PROTO_ESP,
	IPSEC_PROTO_AH
} ipsec_protocol;

typedef enum {
	SSL_VERSION_NULL,
	SSL_VERSION_3_0,
	TLS_VERSION_1_0,
	TLS_VERSION_1_1,
	TLS_VERSION_1_2,
	TLS_VERSION_1_3,
	DTLS_VERSION_1_0,
	DTLS_VERSION_1_2
} ssl_version;

typedef enum {
	PROTO_NULL,
	PROTO_IPSEC,
	PROTO_SSL,
	PROTO_MACSEC,
	PROTO_SRTP
} protocol;

/* cipher. */
typedef enum {
	CIPHER_NULL,
	CIPHER_DES_ECB,
	CIPHER_DES_CBC,
	CIPHER_3DES_ECB,
	CIPHER_3DES_CBC,
	CIPHER_AES_128_ECB,
	CIPHER_AES_128_CBC,
	CIPHER_AES_128_OFB128,
	CIPHER_AES_128_CFB,
	CIPHER_AES_128_CTR,
	CIPHER_AES_128_ICM,
	CIPHER_AES_128_CCM,
	CIPHER_AES_128_GCM,
	CIPHER_AES_192_ECB,
	CIPHER_AES_192_CBC,
	CIPHER_AES_192_OFB128,
	CIPHER_AES_192_CFB,
	CIPHER_AES_192_CTR,
	CIPHER_AES_192_ICM,
	CIPHER_AES_192_CCM,
	CIPHER_AES_192_GCM,
	CIPHER_AES_256_ECB,
	CIPHER_AES_256_CBC,
	CIPHER_AES_256_OFB128,
	CIPHER_AES_256_CFB,
	CIPHER_AES_256_CTR,
	CIPHER_AES_256_ICM,
	CIPHER_AES_256_CCM,
	CIPHER_AES_256_GCM
} cipher;

typedef struct {
	cae_id id;
	int pad;
	unsigned char key[MAX_CRYPTO_KEY_LEN];
	unsigned char iv[MAX_IV_LEN];
	unsigned char *nonce;
	unsigned char *aad;
	unsigned int key_len;
	unsigned int iv_len;
	int enc;
	unsigned char remain[MAX_CRYPTO_BLOCK_SIZE];
	int remain_len;
	int blk_size;
	int crypto_algo;
	int crypto_mode;
	DMABuf_Handle_t SAHandle;
	DMABuf_Handle_t TokenHandle;
	DMABuf_HostAddress_t TokenHostAddress;
	void *TCRData;
	SABuilder_Params_t params;
	SABuilder_Params_Basic_t ProtocolParams;
	DMABuf_HostAddress_t SAHostAddress;
	PEC_ResultDescriptor_t cipher_res;
	volatile int rdr_done;
	volatile unsigned int first_pkt;
	volatile unsigned int final_pkt;
	/* pad next packet in interrupt. */
	DMABuf_HostAddress_t InPktHostAddress;
	DMABuf_HostAddress_t OutPktHostAddress;
	DMABuf_Handle_t InPktHandle;
	DMABuf_Handle_t OutPktHandle;
	IOToken_Input_Dscr_t InTokenDscr;
	uint32_t InputToken[IOTOKEN_IN_WORD_COUNT];
	uint32_t OutputToken[IOTOKEN_OUT_WORD_COUNT];
	IOToken_Output_Dscr_t OutTokenDscr;
	PEC_CommandDescriptor_t Cmd;
	TokenBuilder_Params_t TokenParams;
	unsigned int TokenWords;
	unsigned int TokenHeaderWord;
	const unsigned char *in;
	int in_len;
	unsigned char *out;
	int *out_len;
	unsigned int left_update_blks;
	int in_seek;
	unsigned int final_left_cnt;
	algo_type type;
	bool blocked;
	bool allocated;
	/* for dual core. */
	cae_device *dev;
} cipher_ctx;

/* message digest. */
typedef enum {
	HASH_NULL,
	HASH_MD5,
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
	HASH_AES_256_CBC_MAC
} md;

typedef struct {
	cae_id id;
	int auth_algo;
	int blk_size;
	unsigned char *key;
	unsigned char remain[MAX_DIGEST_BLOCK_SIZE];
	int remain_len;
	int digest_len;
	volatile int multi_part_packet_flag;
	volatile unsigned int first_pkt;
	SABuilder_Params_t params;
	SABuilder_Params_Basic_t BasicParams;
	DMABuf_Handle_t SAHandle;
	DMABuf_Handle_t TokenHandle;
	DMABuf_HostAddress_t TokenHostAddress;
	void *TCRData;
	DMABuf_HostAddress_t InPktHostAddress;
	DMABuf_HostAddress_t OutPktHostAddress;
	DMABuf_Handle_t InPktHandle;
	DMABuf_Handle_t OutPktHandle;
	uint8_t InnerDigest[HMAC_PRE_COMPUTE_LEN];
	uint8_t OuterDigest[HMAC_PRE_COMPUTE_LEN];
	DMABuf_HostAddress_t SAHostAddress;
	PEC_CommandDescriptor_t Cmd;
	PEC_ResultDescriptor_t hash_res;
	volatile int rdr_done;
	volatile unsigned int hash_final_pkt;
	/* pad next packet in interrupt. */
	unsigned int TokenWords;
	unsigned int TokenHeaderWord;
	TokenBuilder_Params_t TokenParams;
	IOToken_Input_Dscr_t InTokenDscr;
	uint32_t InputToken[IOTOKEN_IN_WORD_COUNT];
	const unsigned char *in;
	int in_len;
	unsigned int left_update_blks;
	int in_seek;
	unsigned int final_left_cnt;
	algo_type type;
	bool blocked;
	/* for dual core. */
	cae_device *dev;
} md_ctx;

/* misc(cipher + digest). */
typedef struct {
	cae_id id;
	cipher_ctx cipher;
	md_ctx digest;
	protocol proto_type;
	ssl_version ssl_ver;
	ipsec_protocol ipsec_proto;
	ipsec_work_mode ipsec_wm;
	ipsec_ip_mode ipsec_im;
	int hash_first;
	cae_device *dev;
} misc_ctx;

typedef struct {
	cipher crypto_type;
	md hash_type;
	unsigned char *crypto_key;
	unsigned char *iv;
	unsigned char *nonce;
	unsigned char *aad;
	int enc;
	unsigned char *hash_key;
	protocol proto_type;
	ssl_version ssl_ver;
	ipsec_protocol ipsec_proto;
	ipsec_work_mode ipsec_wm;
	ipsec_ip_mode ipsec_im;
	int hash_first;
} misc_params;

/* cipher api. */
cipher_ctx *itcs_cipher_ctx_new(cae_device *dev);
int itcs_cipher_init(cipher_ctx *ctx, const cipher type, unsigned char *key,
		     unsigned char *iv, int enc);
int itcs_cipher_ctx_set_padding(cipher_ctx *ctx, int pad);
int itcs_cipher_update(cipher_ctx *ctx, unsigned char *out, int *out_len,
		       const unsigned char *in, int in_len, bool blocked);
int itcs_cipher_final(cipher_ctx *ctx, unsigned char *out, int *out_len);
void itcs_cipher_ctx_free(cipher_ctx *ctx);

/* digest api. */
md_ctx *itcs_md_ctx_new(cae_device *dev);
int itcs_digest_init(md_ctx *ctx, const md type, unsigned char *key);
int itcs_digest_update(md_ctx *ctx, const void *in, unsigned long len,
		       bool blocked);
int itcs_digest_final(md_ctx *ctx, unsigned char *md, unsigned int *len);
void itcs_md_ctx_free(md_ctx *ctx);

/* misc(cipher + digest) api. */
misc_ctx *itcs_misc_ctx_new(cae_device *dev);
int itcs_misc_init(misc_ctx *ctx, misc_params *misc_paras);
int itcs_misc_ctx_set_padding(misc_ctx *ctx, int pad);
int itcs_misc_update(misc_ctx *ctx, const void *in, unsigned long in_len);
int itcs_misc_final(misc_ctx *ctx, unsigned char *md, unsigned int *len);
void itcs_misc_ctx_free(misc_ctx *ctx);

cae_device *itcs_cae_init(cae_id id);
void itcs_cae_exit(cae_device *dev);

#endif

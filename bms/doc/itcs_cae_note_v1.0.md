# CAE相关接口说明

## 头文件

```c
#include <cae.h>
```

## 接口说明

* cae初始化

```c
void itcs_cae_init(void);
```

* cae去初始化

```c
void itcs_cae_deinit(void);
```

* cipher context创建

```c
cipher_ctx *itcs_cipher_ctx_new(void);
```

返回值列表: 

| 返回值 | 返回值说明 |
| ------ | ---------- |
| !NULL  | 成功       |
| NULL   | 失败       |

* cipher初始化
```c
int itcs_cipher_init(cipher_ctx *ctx, const cipher type,
		                const unsigned char *key, const unsigned char *iv, int enc);
```

参数/返回值列表: 

|参数名|参数说明|
|--|--|
|ctx|cipher context|
|type|加解密算法类型，[见下](#cipher_type)|
|key|加解密密钥|
|iv|偏移量|
|enc|加密/解密，可填ENCRYPT或DECRYPT|

|返回值|返回值说明|
|--|--|
|1|成功|
|0|失败|

加解密算法类型:  
<a id="cipher_type"></a>

| 加解密算法类型        | 加解密算法说明              |
| --------------------- | --------------------------- |
| CIPHER_NULL           | 不指向任何算法              |
| CIPHER_AES_128_ECB    | 算法类型aes 128，模式ecb    |
| CIPHER_AES_128_CBC    | 算法类型aes 128，模式cbc    |
| CIPHER_AES_128_OFB128 | 算法类型aes 128，模式ofb128 |
| CIPHER_AES_128_CFB    | 算法类型aes 128，模式cfb    |
| CIPHER_AES_128_CTR    | 算法类型aes 128，模式ctr    |
| CIPHER_AES_128_ICM    | 算法类型aes 128，模式icm    |
| CIPHER_AES_128_CCM    | 算法类型aes 128，模式ccm    |
| CIPHER_AES_128_GCM    | 算法类型aes 128，模式gcm    |
| CIPHER_AES_192_ECB    | 算法类型aes 192，模式ecb    |
| CIPHER_AES_192_CBC    | 算法类型aes 192，模式cbc    |
| CIPHER_AES_192_OFB128 | 算法类型aes 192，模式ofb128 |
| CIPHER_AES_192_CFB    | 算法类型aes 192，模式cfb    |
| CIPHER_AES_192_CTR    | 算法类型aes 192，模式ctr    |
| CIPHER_AES_192_ICM    | 算法类型aes 192，模式icm    |
| CIPHER_AES_192_CCM    | 算法类型aes 192，模式ccm    |
| CIPHER_AES_192_GCM    | 算法类型aes 192，模式gcm    |
| CIPHER_AES_256_ECB    | 算法类型aes 256，模式ecb    |
| CIPHER_AES_256_CBC    | 算法类型aes 256，模式cbc    |
| CIPHER_AES_256_OFB128 | 算法类型aes 256，模式ofb128 |
| CIPHER_AES_256_CFB    | 算法类型aes 256，模式cfb    |
| CIPHER_AES_256_CTR    | 算法类型aes 256，模式ctr    |
| CIPHER_AES_256_ICM    | 算法类型aes 256，模式icm    |
| CIPHER_AES_256_CCM    | 算法类型aes 256，模式ccm    |
| CIPHER_AES_256_GCM    | 算法类型aes 256，模式gcm    |
| CIPHER_DES_ECB        | 算法类型des，模式ecb        |
| CIPHER_DES_CBC        | 算法类型des，模式cbc        |
| CIPHER_3DES_ECB       | 算法类型3des，模式ecb       |
| CIPHER_3DES_CBC       | 算法类型3des，模式cbc       |

* cipher context padding设置

```c
int itcs_cipher_ctx_set_padding(cipher_ctx *ctx, int pad);
```

参数/返回值列表:  

|参数名|参数说明|
|--|--|
|ctx|cipher context|
|pad|填充模式，[见下](#pad_mode)|

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 1      | 成功       |
| 0      | 失败       |

填充模式:
<a id="pad_mode"></a>

| 模式              | 模式说明      |
| ----------------- | ------------- |
| PADDING_NONE      | 不填充        |
| PADDING_PKCS7     | PKCS7填充     |
| PADDING_ISO7816_4 | ISO7816_4填充 |
| PADDING_ANSI923   | ANSI923填充   |
| PADDING_ISO10126  | ISO10126填充  |
| PADDING_ZERO      | 全填充为0     |

* 获得加解密结果

```c
int itcs_cipher_update(cipher_ctx *ctx, unsigned char *out,
		                      int *out_len, const unsigned char *in, int in_len, bool blocked);
```

参数/返回值列表:

|参数名|参数说明|
|--|--|
|ctx|cipher context|
|out| 加解密后的内容       |
|out_len|加解密后的内容的长度|
|in|要加解密的内容|
|in_len|要加解密的内容的长度|
|blocked|1为阻塞，0为非阻塞|

|返回值|返回值说明|
|--|--|
|1|成功|
|0|失败|

* 完成padding部分的加解密

```c
int itcs_cipher_final(cipher_ctx *ctx, unsigned char *out, int *out_len);
```

参数/返回值列表:  

|参数名|参数说明|
|--|--|
|ctx|cipher context|
|out|剩余部分加解密后的内容|
|out_len|剩余部分加解密后的内容的长度|

|返回值|返回值说明|
|--|--|
|1|成功|
|0|失败|

* 释放cipher context

```c
void itcs_cipher_ctx_free(cipher_ctx *ctx);
```
参数列表:  

| 参数名 | 参数说明       |
| ------ | -------------- |
| ctx    | cipher context |

* message digest context创建

```c
md_ctx *itcs_md_ctx_new(void);
```

返回值列表:  
|返回值|返回值说明|
|--|--|
|!NULL|成功|
|NULL|失败|

* 摘要初始化

```c
int itcs_digest_init(md_ctx *ctx, const md type, const unsigned char *key);
```

参数/返回值列表:  

| 参数名 | 参数说明                      |
| ------ | ----------------------------- |
| ctx    | message digest context        |
| type   | 摘要算法类型，[见下](md_type) |
| key    | 密钥                          |

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 1      | 成功       |
| 0      | 失败       |

摘要算法类型：

<a id="md_type"></a>

| 摘要算法类型              | 摘要算法说明         |
| ------------------------- | -------------------- |
| HASH_NULL                 | 不指向任何摘要算法   |
| HASH_MD5                  | basic md5            |
| HASH_SHA1                 | basic sha1           |
| HASH_SHA2_224             | basic sha2-224       |
| HASH_SHA2_256             | basic sha2-256       |
| HASH_SHA2_384             | basic sha2-384       |
| HASH_SHA2_512             | basic sha2-512       |
| HASH_SSLMAC_SHA1          | ssl-mac sha1         |
| HASH_HMAC_MD5             | hmac md5             |
| HASH_HMAC_SHA1            | hmac sha1            |
| HASH_HMAC_SHA2_224        | hmac sha2-224        |
| HASH_HMAC_SHA2_256        | hmac sha2-256        |
| HASH_HMAC_SHA2_384        | hmac sha2-384        |
| HASH_HMAC_SHA2_512        | hmac sha2-512        |
| HASH_AES_128_XCBC_MAC_96  | aes-128-xcbc-mac-96  |
| HASH_AES_192_XCBC_MAC_96  | aes-192-xcbc-mac-96  |
| HASH_AES_256_XCBC_MAC_96  | aes-256-xcbc-mac-96  |
| HASH_AES_128_XCBC_MAC_PRF | aes-128-xcbc-mac-prf |
| HASH_AES_192_XCBC_MAC_PRF | aes-192-xcbc-mac-prf |
| HASH_AES_256_XCBC_MAC_PRF | aes-256-xcbc-mac-prf |
| HASH_AES_128_CMAC         | aes-128-cmac         |
| HASH_AES_192_CMAC         | aes-192-cmac         |
| HASH_AES_256_CMAC         | aes-256-cmac         |
| HASH_AES_128_CBC_MAC      | aes-128-cbc-mac      |
| HASH_AES_192_CBC_MAC      | aes-192-cbc-mac      |
| HASH_AES_256_CBC_MAC      | aes-256-cbc-mac      |
| HASH_GHASH                | ghash                |
| HASH_CRC32                | crc32                |

* 摘要计算

```c
int itcs_digest_update(md_ctx *ctx, const void *in, unsigned long len, bool blocked);
```

参数/返回值列表:  

| 参数名 | 参数说明               |
| ------ | ---------------------- |
| ctx    | message digest context |
| in     | 原始内容               |
| len    | 原始内容长度           |
|blocked|1为阻塞，0为非阻塞|

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 1      | 成功       |
| 0      | 失败       |

* 摘要输出

```c
int itcs_digest_final(md_ctx *ctx, unsigned char *md, unsigned int *len);
```

参数/返回值列表:  

| 参数名 | 参数说明               |
| ------ | ---------------------- |
| ctx    | message digest context |
| md     | 摘要结果               |
| len    | 摘要结果长度           |

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 1      | 成功       |
| 0      | 失败       |

* 释放message digest context

```c
void itcs_md_ctx_free(md_ctx *ctx);
```

参数列表:  

| 参数名 | 参数说明               |
| ------ | ---------------------- |
| ctx    | message digest context |

* 混合模式context创建

```c
misc_ctx *itcs_misc_ctx_new(void);
```

返回值列表:  

| 返回值 | 返回值说明 |
| ------ | ---------- |
| !NULL  | 成功       |
| NULL   | 失败       |

* 混合模式初始化

```c
int itcs_misc_init(misc_ctx *ctx, misc_params *misc_paras);
```

参数/返回值列表:  

| 参数名     | 参数说明       |
| ---------- | -------------- |
| ctx        | misc context   |
| misc_paras | 参数配置结构体 |

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 1      | 成功       |
| 0      | 失败       |

结构体说明:  

1. misc_params

| 结构体参数  | 必填 | 参数说明                                  |
| ----------- | ---- | ----------------------------------------- |
| crypto_type | 是   | 加解密算法类型                            |
| hash_type   | 是   | 摘要算法类型                              |
| crypto_key  | 是   | 加密算法对应的密钥                        |
| iv          | 是   | 加密算法对应的偏移量                      |
| nonce       | 是   | nonce                                     |
| aad         | 是   | 额外认证数据                              |
| enc         | 是   | 加密或解密，1表示加密                     |
| hash_key    | 是   | 摘要算法对应的密钥                        |
| proto_type  | 是   | 协议类型，[见下](proto_type)              |
| ssl_ver     | 是   | ssl/tls/dtls协议版本，[见下](ssl_version) |
| ipsec_proto | 是   | ipsec协议类型，[见下](ipsec_protocol)     |
| ipsec_wm    | 是   | ipsec工作模式，[见下](ipsec_work_mode)    |
| ipsec_im    | 是   | ipsec ip模式，[见下](ipsec_ip_mode)       |
| hash_first  | 是   | 为1则表示先哈希，为0表示先加解密          |

协议类型：

<a id="proto_type"></a>

| 协议类型     | 协议类型说明   |
| ------------ | -------------- |
| PROTO_NULL   | 不指向任何协议 |
| PROTO_IPSEC  | ipsec          |
| PROTO_SSL    | ssl/tls/dtls   |
| PROTO_MACSEC | macsec         |
| PROTO_SRTP   | srtp           |

ssl/tls/dtls协议版本：

<a id="ssl_version"></a>

| 协议版本         | 版本说明       |
| ---------------- | -------------- |
| SSL_VERSION_NULL | 不指向任何版本 |
| SSL_VERSION_3_0  | ssl 3.0        |
| TLS_VERSION_1_0  | tls 1.0        |
| TLS_VERSION_1_1  | tls 1.1        |
| TLS_VERSION_1_2  | tls 1.2        |
| TLS_VERSION_1_3  | tls 1.3        |
| DTLS_VERSION_1_0 | dtls 1.0       |
| DTLS_VERSION_1_2 | dtls 1.2       |

ipsec协议类型：

<a id="ipsec_protocol"></a>

| 协议类型         | 类型说明       |
| ---------------- | -------------- |
| IPSEC_PROTO_NULL | 不指向任何协议 |
| IPSEC_PROTO_ESP  | esp            |
| IPSEC_PROTO_AH   | ah             |

ipsec工作模式：

<a id="ipsec_work_mode"></a>

| 工作模式                  | 模式说明       |
| ------------------------- | -------------- |
| IPSEC_WORK_MODE_NULL      | 不指向任何模式 |
| IPSEC_WORK_MODE_TUNNEL    | 隧道模式       |
| IPSEC_WORK_MODE_TRANSPORT | 传输模式       |

ipsec ip模式：

<a id="ipsec_ip_mode"></a>

| ip模式             | 模式说明       |
| ------------------ | -------------- |
| IPSEC_IP_MODE_NULL | 不指向任何模式 |
| IPSEC_IP_MODE_IPV4 | ipv4           |
| IPSEC_IP_MODE_IPV6 | ipv6           |

* 混合模式padding设置

```c
int itcs_misc_ctx_set_padding(misc_ctx *ctx, int pad);
```

参数/返回值列表:  

| 参数名 | 参数说明                      |
| ------ | ----------------------------- |
| ctx    | misc context                  |
| pad    | 启用或关闭填充，1表示启用填充 |

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 1      | 成功       |
| 0      | 失败       |

* 混合模式加密和摘要计算

```c
int itcs_misc_update(misc_ctx *ctx, const void *in, unsigned long in_len);
```

参数/返回值列表:  

| 参数名 | 参数说明         |
| ------ | ---------------- |
| ctx    | misc context     |
| in     | 要处理的数据     |
| in_len | 要处理的数据长度 |

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 1      | 成功       |
| 0      | 失败       |

* 获取混合模式摘要结果

```c
int itcs_misc_final(misc_ctx *ctx, unsigned char *md,
					unsigned int *len);
```

参数/返回值列表:  

| 参数名 | 参数说明     |
| ------ | ------------ |
| ctx    | misc context |
| md     | 摘要内容     |
| len    | 摘要长度     |

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 1      | 成功       |
| 0      | 失败       |

* 释放混合模式context

```c
void itcs_misc_ctx_free(misc_ctx *ctx);
```

参数列表:  

| 参数名 | 参数说明     |
| ------ | ------------ |
| ctx    | misc context |

## 示例代码

```c
static int misc_test(void)
{
	int ret = -1;
	misc_ctx *ctx;
	unsigned char in_1[] = "0123456789";
	unsigned char in_2[] = "abcdef";
	int in_1_len = strlen((char *)in_1);
	int in_2_len = strlen((char *)in_2);
	unsigned char digest[] = {0x55, 0xe9, 0xd7, 0xeb, 0x7f, 0x0f, 0x6e, 0x2c, 0x57, 0x4e, 0xf8, 0xfe, 0x2a, 0x42, 0xa5, 0x84};
	unsigned char md[16] = {0};
	unsigned int len = 0;

	unsigned char key[] = "123";
	unsigned char iv[] = "abc";

	itcs_cae_init();

	ctx = itcs_misc_ctx_new();
	if (!ctx)
		return ret;
	if (itcs_misc_init(ctx, CIPHER_AES_256_CBC, HASH_MD5, key, iv, 1, NULL, NULL) != 1)
		goto cleanup;
	if (itcs_misc_ctx_set_padding(ctx, 1) != 1)
		goto cleanup;
	if (itcs_misc_update(ctx, in_1, in_1_len) != 1)
		goto cleanup;
	if (itcs_misc_update(ctx, in_2, in_2_len) != 1)
		goto cleanup;
	if (itcs_misc_final(ctx, md, &len) != 1)
		goto cleanup;
	if (!memcmp(digest, md, sizeof(digest))) {
		if (hash_type == HASH_MD5)
			printf("Test Crypto MD5-Basic Pass\n");
	}
	ret = 0;
cleanup:
	itcs_misc_ctx_free(ctx);
	return ret;
}

int rtc_main(int argc, char *argv[])
{
    return misc_test();
}
```
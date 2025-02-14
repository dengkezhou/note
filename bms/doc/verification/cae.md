# CAE 相关测试例

## CAE Triple-DES CBC模式

----
`FPGA` `P1`

**Description**

1. 调用cae的Triple-DES接口，配置成CBC，计算获得加密或解密结果

**Expectation**

1. 原文128字节，密钥64字节，iv 32字节，加密后结果长度为77字节，内容与预期加密结果相同；同时解密后与原文相同
2. 打印Test Crypto Triple-DES-CBC enc and dec Pass

**FPGA&RTL Params**

```c
cae --id 0 --3des cbc
cae --id 1 --3des cbc
```

## CAE AES-256 CBC模式

----
`FPGA` `P1`

**Description**

1. 调用cae的AES-256接口，配置成CBC，计算获得加密或解密结果

**Expectation**

1. 原文128字节，密钥64字节，iv 32字节，加密后结果长度为80字节，内容与预期加密结果相同；同时解密后与原文相同
2. 打印Test Crypto AES-256-CBC enc and dec Pass

**FPGA&RTL Params**

```c
cae --id 0 --aes-256 cbc
cae --id 1 --aes-256 cbc
```

## CAE HASH MD5 Basic模式

----
`FPGA` `P1`

**Description**

1. 调用cae的MD5接口，配置成Basic模式，计算获得hash结果

**Expectation**

1. 原文6字节，hash后结果长度为16字节，内容与预期hash结果相同
2. 打印Test Crypto MD5-Basic Pass

**FPGA&RTL Params**

```c
cae --id 0 --md5 basic
cae --id 1 --md5 basic
```

## CAE HASH SHA-1 Basic模式

----
`FPGA` `P1`

**Description**

1. 调用cae的SHA-1接口，配置成Basic模式，计算获得hash结果

**Expectation**

1. 原文27字节，hash后结果长度为20字节，内容与预期hash结果相同
2. 打印Test Hash SHA-1-Basic Pass

**FPGA&RTL Params**

```c
cae --id 0 --sha1 basic
cae --id 1 --sha1 basic
```

## CAE HASH SHA2-512 Basic模式

----
`FPGA` `P1`

**Description**

1. 调用cae的SHA2-512接口，配置成Basic模式，计算获得hash结果

**Expectation**

1. 原文27字节，hash后结果长度为64字节，内容与预期hash结果相同
2. 打印Test Hash SHA2-512-Basic Pass

**FPGA&RTL Params**

```c
cae --id 0 --sha2-512 basic
cae --id 1 --sha2-512 basic
```

## CAE aes-128-cbc speed fpga测试

----
`FPGA` `P1`

**Description**

1. 使用aes-128-cbc，分别按不同大小的块进行加密或解密测试，并持续3秒（rtl使用ivp进行加解密测速）

**Expectation**

1. 得到算法平均每秒可以加密或解密的字节数

**FPGA&RTL Params**

```c
cae --id 0 --speed enc --crypto aes-128-cbc
cae --id 0 --speed dec --crypto aes-128-cbc
cae --id 0 --speed enc --crypto aes-128-cbc --fpga_ivp_speed
cae --id 0 --speed dec --crypto aes-128-cbc --fpga_ivp_speed
```

## CAE aes-128-cbc speed rtl测试

----
`RTL` `P0`

**Description**

1. 使用aes-128-cbc，单核以64字节为测试长度，双核以131068字节为测试长度，进行单核和双核的加解密测试，rtl通过波形算出加解密速度
2. rtlcase需要关闭rom.bin和soc.bin的cache，请查看tool/cae/ivp/readme.md

**Expectation**

1. rtl能看到有效波形算出速度且dual core波形有重叠

**FPGA&RTL Params**

```c
cae --speed enc --ivp_speed dual_core
cae --speed dec --ivp_speed dual_core
cae --id 0 --speed enc --ivp_speed single_core
cae --id 0 --speed dec --ivp_speed single_core
```

## CAE macsec aes-128-gcm speed rtl测试

----
`RTL` `P0`

**Description**

1. 使用macsec aes-128-gcm，双核以加密1436字节为测试长度，进行双核的加密测试，rtl通过波形算出加密速度
2. rtlcase需要关闭rom.bin和soc.bin的cache，请查看tool/cae/ivp/readme.md

**Expectation**

1. rtl能看到有效波形算出速度且dual core波形有重叠

**FPGA&RTL Params**

```c
cae --speed enc --ivp_speed dual_core_aes_128_gcm
```

## CAE dual core aes-128-cbc测试

----
`FPGA` `RTL` `P0`

**Description**

1. 同时调用cae0和cae1的接口，同时配置成aes-128-cb模式，同时计算获得加解密结果
2. rtlcase需要打开cache和mmu

**Expectation**

1. 两个core均能正确加解密
2. 打印Test dual core aes-128-cbc Pass

**FPGA&RTL Params**

```c
cae --dual --crypto aes-128-cbc
```

## CAE ivp测试

----
`FPGA` `RTL` `P0`

**Description**

1. 裸写寄存器，等待处理完成得到预期结果
2. rtlcase需要关闭rom.bin和soc.bin的cache，请查看tool/cae/ivp/readme.md

**Expectation**

1. 打印test_ipsec_esp_in_aes_ctr_sha1_transport Pass
2. 对于e906，core1 intc_hia测试例由于芯片中断没接无法测过，为正常现象

**FPGA&RTL Params**

```c
cae --id 0 --ivp test_ipsec_esp_in_aes_ctr_sha1_transport
cae --id 0 --ivp test_ipsec_esp_out_aes_ctr_sha1_transport_esn
cae --id 0 --ivp test_ipsec_esp_in_aes_ctr_sha1_transport_esn
cae --id 0 --ivp test_ipsec_esp_out_aes_ctr_sha1_transport
cae --id 0 --ivp test_ipsec_esp_out_aes_ctr_sha2_transport
cae --id 0 --ivp test_ipsec_esp_out_aes_cbc_sha1_transport
cae --id 0 --ivp test_ipsec_esp_in_aes_ctr_sha2_transport
cae --id 0 --ivp test_ipsec_esp_in_aes_cbc_sha1_transport
cae --id 0 --ivp intc_hia
cae --id 0 --ivp eip97_reg_test
cae --id 0 --ivp test_aes_ecb_nist_dec
cae --id 0 --ivp test_hmac_sha384_fips
cae --id 0 --ivp test_hmac_sha1
cae --id 0 --ivp test_tdes_ecb_nist_dec
cae --id 0 --ivp test_crc32_chained
cae --id 0 --ivp test_sha384_fips
cae --id 0 --ivp test_aes_ctr_nist
cae --id 0 --ivp test_sha256
cae --id 0 --ivp test_tdes_ecb_length
cae --id 0 --ivp test_hmac_sha224
cae --id 0 --ivp test_bypass
cae --id 0 --ivp test_hmac_sha256
cae --id 0 --ivp test_hmac_sha256_fips
cae --id 0 --ivp test_aes_cbc_nist
cae --id 0 --ivp test_hmac_sha1_fips
cae --id 0 --ivp test_sha1_save_hash
cae --id 0 --ivp test_sha224_fips
cae --id 0 --ivp test_md5
cae --id 0 --ivp test_sha1_fips
cae --id 0 --ivp test_crc32
cae --id 0 --ivp test_aes_ctr_nist_dec
cae --id 0 --ivp test_hmac_md5_rfc
cae --id 0 --ivp test_sha512_fips
cae --id 0 --ivp test_md5_rfc
cae --id 0 --ivp test_hmac_sha224_fips
cae --id 0 --ivp test_hmac_sha512_fips
cae --id 0 --ivp test_aes_cbc_nist_dec
cae --id 0 --ivp test_tdes_ecb_nist
cae --id 0 --ivp test_hmac_md5
cae --id 0 --ivp test_aes_ecb_nist
cae --id 0 --ivp test_des_cbc_length
cae --id 0 --ivp test_sha1
cae --id 0 --ivp test_sha256_fips
cae --id 0 --ivp test_des_ecb_length
cae --id 0 --ivp test_sha224
cae --id 0 --ivp test_macsec_in_default
cae --id 0 --ivp test_macsec_out_default
cae --id 1 --ivp test_ipsec_esp_in_aes_ctr_sha1_transport
cae --id 1 --ivp test_ipsec_esp_out_aes_ctr_sha1_transport_esn
cae --id 1 --ivp test_ipsec_esp_in_aes_ctr_sha1_transport_esn
cae --id 1 --ivp test_ipsec_esp_out_aes_ctr_sha1_transport
cae --id 1 --ivp test_ipsec_esp_out_aes_ctr_sha2_transport
cae --id 1 --ivp test_ipsec_esp_out_aes_cbc_sha1_transport
cae --id 1 --ivp test_ipsec_esp_in_aes_ctr_sha2_transport
cae --id 1 --ivp test_ipsec_esp_in_aes_cbc_sha1_transport
cae --id 1 --ivp intc_hia
cae --id 1 --ivp eip97_reg_test
cae --id 1 --ivp test_aes_ecb_nist_dec
cae --id 1 --ivp test_hmac_sha384_fips
cae --id 1 --ivp test_hmac_sha1
cae --id 1 --ivp test_tdes_ecb_nist_dec
cae --id 1 --ivp test_crc32_chained
cae --id 1 --ivp test_sha384_fips
cae --id 1 --ivp test_aes_ctr_nist
cae --id 1 --ivp test_sha256
cae --id 1 --ivp test_tdes_ecb_length
cae --id 1 --ivp test_hmac_sha224
cae --id 1 --ivp test_bypass
cae --id 1 --ivp test_hmac_sha256
cae --id 1 --ivp test_hmac_sha256_fips
cae --id 1 --ivp test_aes_cbc_nist
cae --id 1 --ivp test_hmac_sha1_fips
cae --id 1 --ivp test_sha1_save_hash
cae --id 1 --ivp test_sha224_fips
cae --id 1 --ivp test_md5
cae --id 1 --ivp test_sha1_fips
cae --id 1 --ivp test_crc32
cae --id 1 --ivp test_aes_ctr_nist_dec
cae --id 1 --ivp test_hmac_md5_rfc
cae --id 1 --ivp test_sha512_fips
cae --id 1 --ivp test_md5_rfc
cae --id 1 --ivp test_hmac_sha224_fips
cae --id 1 --ivp test_hmac_sha512_fips
cae --id 1 --ivp test_aes_cbc_nist_dec
cae --id 1 --ivp test_tdes_ecb_nist
cae --id 1 --ivp test_hmac_md5
cae --id 1 --ivp test_aes_ecb_nist
cae --id 1 --ivp test_des_cbc_length
cae --id 1 --ivp test_sha1
cae --id 1 --ivp test_sha256_fips
cae --id 1 --ivp test_des_ecb_length
cae --id 1 --ivp test_sha224
cae --id 1 --ivp test_macsec_in_default
cae --id 1 --ivp test_macsec_out_default
```

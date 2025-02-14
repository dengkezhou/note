# PUFsecurity 相关测试例


## PUFSecurity基础功能测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用于测试pufcc模块中的dma，ka，kdf模块
2. dma，ka，kdf属于pufcc中的基础模块，其他模块大多会使用到它们
3. dma用于在ram和pufcc内部模块直接进行数据交换
4. ka用于保存密钥，pufcc各个模块使用的密钥都会保存在ka中
5. kdf用派生、扩展密钥，可以通过KDK，shared secret,salt等方式派生密钥，并保存在ka中

**Expectation**

1. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_key_export_test Pass!"。失败则会打印Pufcc xxx Failed!

**FPGA&RTL Params**

```c
pufcc dma
pufcc ka
pufcc kdf
```

## PUFsecurity SHA2测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用例用于测试pufcc模块的sha2功能，包括SHA_224，SHA_256，SHA_384，SHA_512，SHA_512_224，SHA_512_256。分别使用IUF方式、DMA SG进行测试,最后将计算结果与期望结果比较。
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_sha2.h`。其中，`const void* msg`为原始数据，`const void* md`为预期结果。

**Expectation**

1. 通过pufcc算出的hash与预期结果相同。
2. 以sha224为例，输入数据为"\xf1\x49\xe4\x1d\x84\x8f\x59\x27\x6c\xfd\xdd\x74\x3b\xaf\xa9\xa9\x0e\x1e\xe4\xa2\x63\xa1\x18\x14\x2b\x33\xe3\x70\x21\x76\xef\x0a\x59\xf8\x23\x7a\x1c\xb5\x1b\x42\xf3\xde\xd6\xb2\x02\xd9\xaf\x09\x97\x89\x8f\xdd\x03\xcf\x60\xbd\xa9\x51\xc5\x14\x54\x7a\x08\x50\xce\xc2\x54\x44\xae\x2f\x24\xcb\x71\x1b\xfb\xaf\xcc\x39\x56\xc9\x41\xd3\xde\x69\xf1\x55\xe3\xf8\xb1\x0f\x06\xdb\x5f\x37\x35\x9b\x77\x2d\xdd\x43\xe1\x03\x5a\x0a\x0d\x3d\xb3\x32\x42\xd5\x84\x30\x33\x83\x3b\x0d\xd4\x3b\x87\x0c\x6b\xf6\x0e\x8d\xea\xb5\x5f\x31\x7c\xc3\x27\x3f\x5e\x3b\xa7\x47\xf0\xcb\x65\x05\x0c\xb7\x22\x87\x96\x21\x0d\x92\x54\x87\x36\x43\x00\x8d\x45\xf2\x9c\xfd\x6c\x5b\x06\x0c\x9a"，得到的结果为"\x9d\xb6\xdc\x3a\x23\xab\xd7\xb6\xc3\xd7\x2c\x38\xf4\x84\x3c\x7d\xe4\x8a\x71\xd0\xba\x91\xa8\x6b\x18\x39\x3e\x5f"，与预期结果相同，测试通过。
3. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_sha2_iuf_test Pass!"。失败则会打印Pufcc xxx Failed!

**FPGA&RTL Params**

```c
pufcc sha2
```


## PUFsecurity SM3测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用例用于测试pufcc模块的sm3功能，分别使用IUF方式、DMA SG进行测试,最后将计算结果与期望结果比较。
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_sm3.h`。其中，`const void* msg`为原始数据，`const void* md`为预期结果。

**Expectation**

1. 通过pufcc算出的hash与预期结果相同。
2. 如：输入数据为"abc"，经过sm3计算后，得到的结果为"\x66\xc7\xf0\xf4\x62\xee\xed\xd9\xd1\xf2\xd4\x6b\xdc\x10\xe4\xe2\x41\x67\xc4\x87\x5c\xf2\xf7\xa2\x29\x7d\xa0\x2b\x8f\x4b\xa8\xe0"，与预期结果相同。
3. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_sm3_iuf_test Pass!"。失败则会打印Pufcc xxx Failed!

**FPGA&RTL Params**

```c
pufcc sm3
```

## PUFsecurity HMAC测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用例用于测试pufcc模块的hmac功能，包括hmac-sha224，hmac-sha256，hmac-sha384，hmac-sha512，分别使用IUF方式、DMA SG进行测试,最后将计算结果与期望结果比较。
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_hmac.h`。其中，`const void* key`为hmac的key，`const void* msg`为原始数据，`const void* md`为预期结果。
3. 以IUF模式为例，计算步骤为：a. 先将key导入ka中；b. 调用hmac相关函数计算出hmac结果；c. 与预期结果比较。

**Expectation**

1. 通过pufcc算出的hmac与预期结果相同。
2. 以HMAC-SHA224为例，输入的key为"Jefe"，原始数据为"what do ya want for nothing?",最后得到的hmac-sha224结果为"\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44"，测试通过。
3. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_hmac_iuf_test Pass!"。失败则会打印Pufcc xxx Failed!


**FPGA&RTL Params**

```c
pufcc hmac
```


## PUFsecurity CMAC测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用例用于测试pufcc模块的cmac功能，包括cmac-aes128，cmac-aes192，cmac-aes256，分别使用IUF方式、DMA SG进行测试,最后将计算结果与期望结果比较。
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_cmac.h`。其中，`const void* key`为cmac的key，`const void* msg`为原始数据，`const void* md`为预期结果。
3. 以IUF模式为例，计算步骤为：a. 先将key导入ka中；b. 调用hmac相关函数计算出cmac结果；c. 与预期结果比较。

**Expectation**

1. 通过pufcc算出的cmac与预期结果相同。
2. 以HMAC-SHA224为例，输入的key为"\x2B\x7E\x15\x16\x28\xAE\xD2\xA6\xAB\xF7\x15\x88\x09\xCF\x4F\x3C"，原始数据为"",最后得到的cmac-aes128结果为"\xBB\x1D\x69\x29\xE9\x59\x37\x28\x7F\xA3\x7D\x12\x9B\x75\x67\x46"，测试通过。
3. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_cmac_iuf_test Pass!"。失败则会打印Pufcc xxx Failed!


**FPGA&RTL Params**

```c
pufcc cmac
```

## PUFsecurity AES加解密测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用例用于测试pufcc模块的aes功能，同时测试分组加密中的ecb，cfb，ofb，cbc，ctr，xts模式，分别使用IUF方式、DMA SG进行测试,最后将计算结果与期望结果比较。
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_aesecb.h`, `drivers/pufcc/include/pufs_tv_aesctr.h`,`drivers/pufcc/include/pufs_tv_aescbc.h`,`drivers/pufcc/include/pufs_tv_aescfb.h`,`drivers/pufcc/include/pufs_tv_aesofb.h`。其中，`const void* key`, `const void* iv`, `const void* pt`分别为key，iv和原始数据，`const void* ct`为预期结果。
3. 以DMA-SG模式为例，计算步骤为：a. 先将key导入ka中；b. 初始化dma sglist, c. 调用sm4相关函数，并启动dma计算出结果；c. 与预期结果比较。


**Expectation**

1. 通过pufcc算出的aes加密结果或解密结果与预期结果相同。
2. 以aes-128-ctr加密测试为例，原始数据为"\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a\xae\x2d\x8a\x57\x1e\x03\xac\x9c\x9e\xb7\x6f\xac\x45\xaf\x8e\x51\x30\xc8\x1c\x46\xa3\x5c\xe4\x11\xe5\xfb\xc1\x19\x1a\x0a\x52\xef\xf6\x9f\x24\x45\xdf\x4f\x9b\x17\xad\x2b\x41\x7b\xe6\x6c\x37\x10"，key为"\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c"，iv为"\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff"，经过加密后的结果为"\x87\x4d\x61\x91\xb6\x20\xe3\x26\x1b\xef\x68\x64\x99\x0d\xb6\xce\x98\x06\xf6\x6b\x79\x70\xfd\xff\x86\x17\x18\x7b\xb9\xff\xfd\xff\x5a\xe4\xdf\x3e\xdb\xd5\xd3\x5e\x5b\x4f\x09\x02\x0d\xb0\x3e\xab\x1e\x03\x1d\xda\x2f\xbe\x03\xd1\x79\x21\x70\xa0\xf3\x00\x9c\xee"，与预期结果相同，测试通过。
3. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_aes_ctr_enc_sg_test Pass!"。失败则会打印Pufcc xxx Failed!

**FPGA&RTL Params**

```c
pufcc aes
pufcc aes_xts
```

## PUFsecurity SM4加解密测试

----
`FPGA` `RTL` `P0`

**Description**

`drivers/pufcc/include/pufs_tv_sm4cbc.h`,`drivers/pufcc/include/pufs_tv_sm4cfb.h`,`drivers/pufcc/include/pufs_tv_sm4ctr.h`,`drivers/pufcc/include/pufs_tv_sm4ecb.h`,`drivers/pufcc/include/pufs_tv_sm4ofb.h`,
1. 本测试用例用于测试pufcc模块的sm4功能，同时测试分组加密中的ecb，cfb，ofb，cbc，ctr模式，分别使用IUF方式、DMA SG进行测试,最后将计算结果与期望结果比较。
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_sm4cbc.h`,`drivers/pufcc/include/pufs_tv_sm4cfb.h`,`drivers/pufcc/include/pufs_tv_sm4ctr.h`,`drivers/pufcc/include/pufs_tv_sm4ecb.h`,`drivers/pufcc/include/pufs_tv_sm4ofb.h`,。其中，`const void* key`, `const void* iv`, `const void* pt`分别为key，iv和原始数据，`const void* ct`为预期结果。
3. 以IUF模式为例，计算步骤为：a. 先将key导入ka中；b. 调用aes相关函数计算出结果；c. 与预期结果比较。


**Expectation**

1. 通过pufcc算出的sm4加密结果或解密结果与预期结果相同。
2. 以sm4-128-cbc加密测试为例，原始数据为"\xaa\xaa\xaa\xaa\xbb\xbb\xbb\xbb\xcc\xcc\xcc\xcc\xdd\xdd\xdd\xdd\xee\xee\xee\xee\xff\xff\xff\xff\xaa\xaa\xaa\xaa\xbb\xbb\xbb\xbb"，key为"\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10"，iv为"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"，经过加密后的结果为"\x78\xeb\xb1\x1c\xc4\x0b\x0a\x48\x31\x2a\xae\xb2\x04\x02\x44\xcb\x4c\xb7\x01\x69\x51\x90\x92\x26\x97\x9b\x0d\x15\xdc\x6a\x8f\x6d"，与预期结果相同，测试通过。
3. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_sm4_ctr_enc_iuf_test Pass!"。失败则会打印Pufcc xxx Failed!

**FPGA&RTL Params**

```c
pufcc sm4
```


## PUFsecurity chacha20加解密测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用例用于测试pufcc模块的chacha20功能，同时测试分组加密中的ecb，cfb，ofb，cbc，ctr，xts模式，分别使用IUF方式、DMA SG进行测试,最后将计算结果与期望结果比较。
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_chacha20.h`。其中，`const void* key`, `const void* nonce`, `const void* pt`分别为key，nonce和原始数据，`const void* ct`为预期结果。
3. 以IUF模式为例，计算步骤为：a. 先将key导入ka中；b. 一般情况下,round取20 c. 调用chacha20相关函数计算出结果；d. 与预期结果比较。


**Expectation**

1. 通过pufcc算出的chacha20加密结果或解密结果与预期结果相同。
2. 例如，原始数据为"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 经过加密后的结果为"\x76\xb8\xe0\xad\xa0\xf1\x3d\x90\x40\x5d\x6a\xe5\x53\x86\xbd\x28\xbd\xd2\x19\xb8\xa0\x8d\xed\x1a\xa8\x36\xef\xcc\x8b\x77\x0d\xc7\xda\x41\x59\x7c\x51\x57\x48\x8d\x77\x24\xe0\x3f\xb8\xd8\x4a\x37\x6a\x43\xb8\xf4\x15\x18\xa1\x1c\xc3\x87\xb6\x69\xb2\xee\x65\x86"，与预期结果相同，测试通过。
3. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_chacha_enc_iuf_test Pass!"。失败则会打印Pufcc xxx Failed!

**FPGA&RTL Params**

```c
pufcc chacha20
```

## PUFsecurity aes_ccm，aes_gcm测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用例用于测试pufcc模块的aes_ccm和aes_gcm功能，分别使用IUF方式、DMA SG进行测试,最后将计算结果与期望结果比较。
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_aesgcm.h`和`drivers/pufcc/include/pufs_tv_aesccm.h`
3. 以DMA-SG模式为例，计算步骤为：a. 先将key导入ka中；b. 初始化dma sglist, c. 调用aes_ccm，aes_gcm相关函数，并启动dma计算出结果；c. 与预期结果比较。

**Expectation**

1. 通过pufcc算出的aes_ccm,aes_gcm加密结果或解密结果与预期结果相同。
2.  测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_aes_ccm_enc_iuf_test Pass!"。失败则会打印Pufcc xxx Failed!

**FPGA&RTL Params**

```c
pufcc aes_ccm
pufcc aes_gcm
```

## PUFsecurity chacha20_poly1305测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用例用于测试pufcc模块的chacha20_poly1305功能，分别使用IUF方式、DMA SG进行测试,最后将计算结果与期望结果比较。
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_chacha20-poly1305.h`
3. 以DMA-SG模式为例，计算步骤为：a. 先将key导入ka中；b. 初始化dma sglist, c. 调用chacha20_poly1305的加密/解密函数，并启动dma计算出结果；c. 与预期结果比较。


**Expectation**

1. 通过pufcc算出的chacha20_poly1305加密结果或解密结果与预期结果相同。
2. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_chacha20_poly1305_enc_iuf_test Pass!"。失败则会打印Pufcc xxx Failed!


**FPGA&RTL Params**

```c
pufcc chacha20_poly1305
```

## PUFsecurity 伪随机数测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用例用于测试pufcc模块的伪随机数（DRBG）功能
2. 从PUFrt中获取一个真随机数作为seed，启动DRBG，获取一个伪随机数
3. 多次获取伪随机数，每次的结果应该都不相同

**Expectation**

1. 每次获取的伪随机数都不相同
2. 若测试通过，则打印Pufcc pufs_drbg_test Pass!失败则会打印Pufcc pufs_drbg_test Failed!

**FPGA&RTL Params**

```c
pufcc drbg
```

## PUFsecurity PUFrt user模式测试

----
`FPGA` `RTL` `P0`

**Description**

1. 本测试用例用于测试PUFrt中的读取，随机读取功能

**Expectation**

1.  测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_rt_read_mode_test Pass!"。失败则会打印Pufcc xxx Failed!

**FPGA&RTL Params**

```c
pufcc rt_user
```

## PUFsecurity rsa测试

----
`FPGA` `P0`

**Description**

1. 本测试用例用于测试pufcc中的rsa功能，包括RSA1024,RSA2048,RSA3072,RSA4096等模式
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_rsaexp.h`,`drivers/pufcc/include/pufs_tv_rsap1v15.h`,`drivers/pufcc/include/pufs_tv_rsapss.h`,`drivers/pufcc/include/pufs_tv_rsax931.h`
3. sign测试：a. 准备一段原始数据msg，b.指定rsa算法中的e（一般取0x10001）,d(即私钥)和n（即公钥）， c. 调用pufs_rsa_sign对msg签名，d. 比对签名的结果与预期结果是否相同
4. verify测试： a. 准备一段原始数据msg和它的签名sign，b.指定rsa算法中的e（一般取0x10001）和n（即公钥）， c. 调用pufs_rsa_verify对msg验证
6. 注意，此项测试非常耗时

**Expectation**

1. sign测试：签名成功，且签名的结果能够通过验证
2. verify：对原始数据及其签名的验证通过
3. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_rsa_verify_test Pass!"。失败则会打印Pufcc xxx Failed!

**FPGA&RTL Params**

```c
pufcc rsa
```


## PUFsecurity ecp测试

----
`FPGA` `P0`

**Description**

1. 本测试用例用于测试pufcc中的ec公钥、私钥生成，ecdsa及ecdh功能，测试了NIST的各种标准，详细标准见`drivers/pufcc/include/pufs_ecc.h`
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_ecccdh.h`,`drivers/pufcc/include/pufs_tv_ecdsas.h`,`drivers/pufcc/include/pufs_tv_ecdsav.h`,`drivers/pufcc/include/pufs_tv_ecpkv.h`,`drivers/pufcc/include/pufs_tv_ecpuk.h`
3. 根据私钥生成公钥：a. 准备私钥prk，b.指定加密曲线类型，c.根据私钥调用pufs_ecp_gen_puk，生成公钥，d.将生成的公钥与预期结果进行比较
4. 验证公钥合法性：a. 准备公钥puk，b.指定加密曲线类型，c.调用pufs_ecp_validate_puk，验证公钥合法性
5. ecdh：a. 生成两对密钥对，b.调用ecdh相关函数进行密钥协商，c. 与期望数据进行比对
6. ecdsa：a.准备一段数据msg（一般为hash的结果）和私钥prk，b. 指定加密曲线类型, c. 使用对私钥prk msg进行签名, d. 使用公钥对签名进行验证
7. 注意，此项测试非常耗时

**Expectation**

1. 私钥生成公钥：生成的公钥与预期结果相同
2. 验证公钥合法性：输入的公钥验证通过
3. ecdh: 协商的私钥与预期结果相同
4. ecdsa：对数据的签名通过公钥验证
5. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_ecp_ecdsa_verify_test Pass!"。失败则会打印Pufcc xxx Failed!

**FPGA&RTL Params**

```c
pufcc ecp
```

## PUFsecurity sm2测试

----
`FPGA` `P0`

**Description**

1. 本测试用例用于测试pufcc中的sm2模块，包括加密，解密，kex,verify,sign
2. 相关测试数据位于`drivers/pufcc/include/pufs_tv_sm2_enc.h`,`drivers/pufcc/include/pufs_tv_sm2_kex.h`,`drivers/pufcc/include/pufs_tv_sm2_sign.h`
3. 加密：a. 准备一段数据msg和公钥puk，b.将puk导入ka，c. 对msg进行加密 d. 与预期结果比对
3. 解密：a. 准备一段数据msg和私钥prk，b.将prk导入ka，c. 对msg进行解密 d. 与预期结果比对
5. kex：a. 生成两对密钥对，b.调用sm2 kex相关函数进行密钥协商，c. 与期望数据进行比对
6. verify：a.准备一段原始数据msg和它的签名sign，b. 调用pufs_sm2_verify对签名进行验证
7. sign：a.准备一段数据msg和私钥prk，b. 指定加密曲线类型, c. 使用对私钥prk msg进行签名, d. 使用公钥对签名进行验证
8. 注意，此项测试非常耗时

**Expectation**

1. 加密：加密的结果与预期结果相同
2. 解密：解密的结果与预期结果相同
3. kex：协商的私钥与预期结果相同
4. verify：对原始数据及其签名的验证通过
5. sign：签名成功，且签名的结果能够通过验证
6.  测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc pufs_sm2_sign_test Pass!"。失败则会打印Pufcc xxx Failed!


**FPGA&RTL Params**

```c
pufcc sm2
```

## PUFsecurity 中断测试

----
`FPGA` `RTL` `P0`


**Description**

1. 本测试用于测试pufcc模块中断

**Expectation**

1. 测试完成后，若测试通过，则打印Pufcc irq_test Pass!，失败则会打印Pufcc irq_test Failed!

**FPGA&RTL Params**

```c
pufcc irq
```

## PUFsecurity全部测试

----
`FPGA` `P0`

**Description**

1. 包含以上所有case
2. 在安全模式下重新测试以上所有case

**Expectation**

1. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称,失败则会打印Pufcc xxx Failed!.
2. 安全模式下，C920全部Failed，E906全部Pass

**FPGA&RTL Params**

```c
pufcc all
pufcc sec_en; pufcc all
```

## PUFsecurity PUFrt OTP 测试

----
`FPGA` `P0`

**Description**

1. 本测试用例用于测试PUFrt中的OTP模块
2. otp_zeroize: 用于测试OTP中的zeroize功能
3. otp_rw, otp_rwlck: 用于测试OTP的读写功能和权限配置功能
4. 注意，该项测试每条命令均不可恢复，需重刷bitfile
5. 需要使用blank good的bitfile进行测试
6. 注意，此项测试非常耗时
7. 在安全模式下重新测试以上所有case


**Expectation**

1. otp_zeroize: OTP能够正常zeroize
2. otp_rw: OTP能够正常读写，且写入后无法二次改写
3. otp_rwlck: 当权限被设置为RO时，OTP只读，当权限被设置为NA时，返回全1
4. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称,失败则会打印Pufcc xxx Failed!
5. 安全模式下，C920全部Failed，E906全部Pass

**FPGA&RTL Params**

```bash
pufcc otp_zeroize
pufcc otp_rw
pufcc otp_rwlck
pufcc sec_en; pufcc otp_zeroize
pufcc sec_en; pufcc otp_rw
pufcc sec_en; pufcc otp_rwlck
```

## PUFsecurity AES OTP Key 测试

----
`FPGA` `P0`

**Description**

1. 本测试用例使用预定义的OTP内容进行aes256加解密测试


**Expectation**

1. 打印Pufcc aes_otpkey_dec_test Pass!
1. 打印Pufcc aes_otpkey_enc_test Pass!

**FPGA&RTL Params**

```bash
pufcc aes_otp_enc # 使用OTP0进行AES256加密
pufcc aes_otp_dec # 使用OTP0进行AES256解密
```

## PUFsecurity PUFrt PUF 测试

----
`FPGA` `P0`

**Description**

1. 本测试用例用于测试PUFrt中的PUF模块
2. puf_enroll: 用于测试PUF中的enroll功能
3. uid_zeroize: 用于测试PUF中的zeroize功能
4. pif_uid_read: 用于测试PUF中的读取UID的功能
5. 注意，该项测试每条命令均不可恢复，需重刷bitfile
6. 需要使用blank good的bitfile进行测试
7. 注意，此项测试非常耗时
8. 在安全模式下重新测试以上所有case

**Expectation**

1. puf_enroll: OTP能够正常enroll
2. uid_zeroize: UID可以正常zeroize
3. pif_uid_read: 能够正常获取UID
4. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称,失败则会打印Pufcc xxx Failed!
5. 安全模式下，C920全部Failed，E906全部Pass

**FPGA&RTL Params**

```shell
pufcc puf_enroll
pufcc uid_zeroize
pufcc pif_uid_read
pufcc sec_en; pufcc puf_enroll
pufcc sec_en; pufcc uid_zeroize
pufcc sec_en; pufcc pif_uid_read
```

## PUFsecurity PUFrt factory测试

----
`FPGA` `P0`

**Description**

1. 本测试用例参照 PUFsecurity Test Methodology 给出的测试建议，详见PSCC_012CW01B_B22C_Test_Methodology_Repair_v1.0.pdf
2. 注意，该项测试每条命令均不可恢复，需重刷bitfile
3. 需要使用blank good的bitfile进行测试
4. 注意，此项测试非常耗时
5. 在安全模式下重新测试以上所有case

**Expectation**

1. 测试完成后，若测试通过，则打印Pufcc xxx Pass!，其中xxx为测试函数的名称，例如: "Pufcc puf_enroll Pass!"。失败则会打印Pufcc xxx Failed!
2. 安全模式下，C920全部Failed，E906全部Pass

**FPGA&RTL Params**

```c
pufcc ptm_st_wrong
pufcc ptm_st_warn
pufcc ini_off_chk
pufcc set_pin
pufcc rand_resume
pufcc puf_qty_chk
pufcc puf_health_chk
pufcc auto_repair
pufcc repair_prog
pufcc pif_set_flag
pufcc ptr_rw
pufcc sec_en; pufcc ptm_st_wrong
pufcc sec_en; pufcc ptm_st_warn
pufcc sec_en; pufcc ini_off_chk
pufcc sec_en; pufcc set_pin
pufcc sec_en; pufcc rand_resume
pufcc sec_en; pufcc puf_qty_chk
pufcc sec_en; pufcc puf_health_chk
pufcc sec_en; pufcc auto_repair
pufcc sec_en; pufcc repair_prog
pufcc sec_en; pufcc pif_set_flag
pufcc sec_en; pufcc ptr_rw
```

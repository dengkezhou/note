# 芯片加密验证自动化脚本使用说明 
## 简介  
  **支持基础加解密算法:**  
| 加密算法| 加密模式 | 
| :-----| ----: | 
| DES,Triple-DES | ECB,CBC |
|AES 128,192,256 bit key| ECB,CBC,OFB,CFB,CTR,ICM,CCM,GCM | 


  **支持的HASH算法:**  
| HASH算法 | HASH模式 | 
| :-----| ----: | 
| MD5 | BASIC,HMAC |
| SHA1 | BASIC,HMAC | 
| SHA2 | BASIC,HMAC |
| AES-XCBC-MAC-96 | -- | 
| AES-XCBC-MAC-PRF | -- | 
| GHASH| -- | 
| CRC32| -- |

 **支持的混合加密算法**
| 加密算法| 加密模式 | 哈希算法|哈希模式|
| :-----| :---- | :-----| :-----|
| DES,3DES | ECB,CBC|MD5 |BASIC |
|        |       |SHA1 |  HMAC |    
|        |       |SHA2 |   |
|        |       |AES-XCBC-MAC-96 |   |
|        |       |AES-XCBC-MAC-PRF |   |
|        |       |CRC32 |   |
|   AES     |  ECB,CBC,OFB,CFB,CTR,ICM     | MD5| BASIC  |
|           |       | SHA1| HMAC  |
|           |       | SHA2|   |
|        |       |AES-XCBC-MAC-96 |   |
|        |       |AES-XCBC-MAC-PRF |   |
|        |       |CRC32 | 


## 使用环境
 **Ubuntu 18.04 LTS**


## 使用脚本的加密算法的参数

**加密算法参数：** 

|  |  |  |  |  |  |  | |
|:-----|:----- |:-----|:----- |:----- |:----- |:----- |:-----| 
| aes-128-ecb | aes-128-cbc | aes-128-ofb | aes-128-cfb | aes-128-ctr| aes-128-icm | aes-128-ccm|aes-128-gcm|
| aes-192-ecb | aes-192-cbc | aes-192-ofb | aes-192-cfb | aes-192-ctr| aes-192-icm | aes-192-ccm|aes-192-gcm|
| aes-256-ecb | aes-256-cbc | aes-256-ofb | aes-256-cfb | aes-256-ctr| aes-256-icm | aes-256-ccm|aes-256-gcm|
| des-ecb | des-cbc | des-ede3-ecb | des-ede3-cbc  |




**HASH加密算法参数:**  

|  |  |  |  |  
|:-----|:----- |:-----|:----- |
| aes-128-cmac | aes-128-cbcmac | aes-128-xcbcmac96 |  aes-128-xcbcmacprf |
| aes-192-cmac | aes-192-cbcmac | aes-192-xcbcmac96 |  aes-192-xcbcmacprf |
| aes-256-cmac | aes-256-cbcmac | aes-256-xcbcmac96 |  aes-256-xcbcmacprf |
| md5 | sha1 | sha2-224 |sha2-256   |
| sha2-384 | sha2-512 | ghash |crc32   |

**MD5，SHA哈希加密模式**
| HASH算法 | HASH模式 | 
|:-----|:----- |
| basic | hmac |



## 指令使用示例 
 - 执行所有算法

```
./generate_demo_data.sh all
```

 - 执行所有单加密算法

  ```shell
  ./generate_demo_data.sh single_all
  ```
 - 执行单个普通加密算法
 ###   bash  crypto.sh single  加密算法参数  
  ```shell       
  ./generate_demo_data.sh single aes-128-cbc
  ```
 - 执行单个含HASH模式的HASH算法
 ###   bash  crypto.sh single  HASH加密算法参数  HASH加密模式  
  ```shell
  ./generate_demo_data.sh single md5-basic
  ```
 ###   bash  crypto.sh single  HASH加密算法参数  HASH加密模式 
```shell
./generate_demo_data.sh single sha-1-hmac
```
- 执行单个不含HASH模式的HASH算法
 ###   bash  crypto.sh single  HASH加密算法参数   
```shell 
./generate_demo_data.sh single crc32
```
- 执行所有混合算法
```shell
./generate_demo_data.sh combined_all
```


## 例子

- md5 basic模式

```shell
$ ./generate_demo_data.sh single md5-basic
md5-basic plain string: 
12345678901234567890123456789012345678901234567890123456789012345678901234567890
md5-basic hashed hex: 
MD5(./plain_data/hash/md5/md5_basic.txt)= 57edf4a22be3c955ac49da2e2107b67a
```

- sha1 hmac模式

```shell
$ ./generate_demo_data.sh single sha1-hmac
sha1-hmac plain string: 
what do ya want for nothing?
sha1-hmac key string: 
Jefe
sha1-hmac hashed hex: 
HMAC-SHA1(./plain_data/hash/sha1_and_sha2/sha_hmac.txt)= effcdf6ae5eb2fa2d27416d5f184df9c259a7c79
```

- 普通加密算法
  
```shell
$ ./generate_demo_data.sh single aes-128-cfb
aes-128-cfb plain string: 
Single block msg
aes-128-cfb key hex: 
06a9214036b8a15b512e03d534120006
aes-128-cfb iv hex: 
3dafba429d9eb430b422da802c9fac41
aes-128-cfb cipher hex: 
d43130f652c4c81be62fdf5e72e48cbc
```

* 全部单个加密算法
 ```shell
$ ./generate_demo_data.sh single_all
sha512-basic plain string: 
abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq
sha512-basic hashed hex: 
SHA2-512(./plain_data/hash/sha1_and_sha2/sha.txt)= 204a8fc6dda82f0a0ced7beb8e08a41657c16ef468b228a8279be331a703c33596fd15c13b1b07f9aa1d3bea57789ca031ad85c7a71dd70354ec631238ca3445

md5-hmac plain string: 
what do ya want for nothing?
md5-hmac key string: 
Jefe
md5-hmac hashed hex: 
HMAC-MD5(./plain_data/hash/md5/md5_hmac.txt)= 750c783e6ab0b503eaa86e310a5db738
 ```

* 全部混合加密算法
 ```shell
$ ./generate_demo_data.sh combined_all
des-ecb plain string: 
Single block msg
des-ecb key hex: 
1122334455667788
des-ecb cipher hex: 
5e5d4a9042883467e7dce2a03b1e410951d57f923ee29886

md5-basic plain string: 
5e5d4a9042883467e7dce2a03b1e410951d57f923ee29886

md5-basic hashed hex: 
MD5(./tmp_hash_input.txt)= 1bddd4e398059f0709907bbc8c3c79f4
 ```
# 部分加密算法调试方法

##  思科源码调试  AES-ICM
- 需要升级OPENSSL 到3.10-DEV 
  *  从官网下载最新github上下载最新版本 升级到OpenSSL 3.1.0-dev
      参考http://www.wjhsh.net/tinywan-p-13961228.html 

```shell
    cd libsrtp
    ./configure --enable-openssl
    make 
    make runtest
```
**例子**
```shell
   ./cipher_driver icm.txt 2b7e151628aed2a6abf7158809cf4f3cf0f1f2f3f4f5f6f7f8f9fafbfcfd 00000000000000000000000000000000
```

##  JS 调试AES-CBC-MAC
*  安装nodejs 和aes-cbc-mac包
  ```shell
  sudo apt install curl
  curl -sL https://deb.nodesource.com/setup_14.x | sudo -E bash -
  sudo apt-get install -y nodejs
  node -v
  npm config set registry http://registry.npm.taobao.org
  sudo npm install -g cnpm
  
  cd bms/tools/cae
  如果当前目录没有node_modules目录，则需要执行以下两条命令或拷贝别的目录下node_modules文件夹到当前目录
  cnpm init -y
  cnpm install aes-cbc-mac
  ```
  **例子**
```shell
  cd  demojs
  node aescbcmac.js aescbcmac.txt  2b7e151628aed2a6abf7158809cf4f3c1122334455667788  
```

## RUST 调试 GHASH
* 参考https://blog.csdn.net/cacique111/article/details/125952700 安装rust环境
```shell
  cd demorust
  cargo build --release
```
  **例子**
```shell
 ./demorust ghash.txt 25629347589242761d31f826ba4b757b
```

## openssl 源码调试 AES-CCM,AES-GCM,AES-XCBCMAC,AES-CMAC
```shell
cd cipher
make OPENSSL_INCS_LOCATION=-I../../include OPENSSL_LIBS_LOCATION=-L../..
```
进行编译


**例子**
- aes-cmac
```shell
./aescmac  aescmac256.txt 2b7e151628aed2a6abf7158809cf4f3c11223344556677881122334455667788
```
- aes-gcm
```shell
./aesxcbcmac  xcbc96.txt  000102030405060708090a0b0c0d0e0f0001020304050607 
```
- aes-ccm
```shell
./aesccm aesccmdata128.txt ceb009aea4454451feadf0e6b36f4555 6e80dd7f1badf3a1c9ab25c75f10bde78c23fa0eb8f9aaa53adefbf4cbf78fe1 764043c49460b1 
```
- aes-xcbcmac
```shell
./aesxcbcmac  xcbc96.txt 000102030405060708090a0b0c0d0e0f
```



  

  

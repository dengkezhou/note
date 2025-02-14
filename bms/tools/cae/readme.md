## 脚本运行环境搭建（ubuntu18.04.6）

运行脚本时推荐使用另一台ubuntu虚拟机，避免修改当前虚拟机的openssl版本。

> 安装openssl

```
下载openssl最新版本openssl-3.0.7.tar.gz并解压
./config
make
sudo make install
sudo vim /etc/ld.so.conf.d/libc.conf，在其末尾添加/usr/local/lib64
sudo ldconfig -v
```

> 安装nodejs

```
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



## test vectors from rfc

| 加解密算法  | input                                                        | output(hex)                      |
| ----------- | ------------------------------------------------------------ | -------------------------------- |
| aes-128-cbc | plain: "This is a 48-byte message (exactly 3 AES blocks)"<br />key(hex): 6c3ea0477630ce21a2ce334aa746c2cd<br />iv(hex): c782dc4c098c66cbd9cd27d825682c81 | d0a02b3836451753d493665d33f0e8862dea54cdb293abc7506939276772f8d5021c19216bad525c8579695d83ba2684 |

| 哈希算法            | input                                                        | output(hex)                                                  |
| ------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| md5                 | plain: "12345678901234567890123456789012345678<br />9012345678901234567890123456<br/>78901234567890" | 57edf4a22be3c955ac49da2e2107b67a                             |
| md5 hmac            | plain: "what do ya want for nothing?"<br />key: "Jefe"       | 750c783e6ab0b503eaa86e310a5db738                             |
| sha224 hmac         | plain: "what do ya want for nothing?"<br />key: "Jefe"       | a30e01098bc6dbbf45690f3a7e9e6d0f<br/>8bbea2a39e6148008fd05e44 |
| sha256 hmac         | plain: "what do ya want for nothing?"<br />key: "Jefe"       | 5bdcc146bf60754e6a042426089575c7<br/>5a003f089d2739839dec58b964ec3843 |
| sha384 hmac         | plain: "what do ya want for nothing?"<br />key: "Jefe"       | af45d2e376484031617f78d2b58a6b1b<br/>9c7ef464f5a01b47e42ec3736322445e<br/>8e2240ca5e69e2c78b3239ecfab21649 |
| sha512 hmac         | plain: "what do ya want for nothing?"<br />key: "Jefe"       | 164b7a7bfcf819e2e395fbe73b56e0a3<br/>87bd64222e831fd610270cd7ea250554<br/>9758bf75c05a994a6d034f65f8f0e6fd<br/>caeab1a34d4a6b4b636e070a38bce737 |
| aes-128-cmac        | plain(hex): 6bc1bee22e409f96e93d7e11 7393172a<br/>ae2d8a571e03ac9c9eb76fac45af8e51<br/>30c81c46 a35ce411<br />key(hex): 2b7e151628aed2a6abf7158809cf4f3c | dfa66747de9ae63030ca32611497c827                             |
| aes-128-xcbc-mac-96 | plain(hex): 000102030405060708090a0b0c0d0e0f10111213<br />key(hex): 000102030405060708090a0b0c0d0e0f | 47f51b4564966215b8985c63                                     |
| aes-128-cbc-mac     | plain(hex): 000102030405060708090a0b0c0d0e0f1011121314<br />15161718191a1b1c1d1e<br />key(hex): c0c1c2c3c4c5c6c7c8c9cacbcccdcecf | 0001020304050607588c979a61c663d2<br/>f066d0c2c0f989806d5f6b61dac38417<br/>e8d12cfdf926e0 |


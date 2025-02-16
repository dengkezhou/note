#!/usr/bin/python3

from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives.ciphers.aead import AESGCM

# 加密函数
def encrypt(cipher, plaintext, associated_data):
    encryptor = cipher.encryptor()
    encryptor.authenticate_additional_data(associated_data)
    ciphertext = encryptor.update(plaintext) + encryptor.finalize()
    tag = encryptor.tag
    return ciphertext, tag

# 解密函数
def decrypt(cipher, ciphertext, tag, associated_data):
    decryptor = cipher.decryptor()
    decryptor.authenticate_additional_data(associated_data)
    plaintext = decryptor.update(ciphertext) + decryptor.finalize_with_tag(tag)
    return plaintext

if __name__ == "__main__":
    ## 生成256位的随机密钥 
    #key = b"\xee\xbc\x1f\x57\x48\x7f\x51\x92\x1c\x04\x65\x66\x5f\x8a\xe6\xd1\x65\x8b\xb2\x6d\xe6\xf8\xa0\x69\xa3\x52\x02\x93\xa5\x72\x07\x8f"
#
    ## 生成12字节的随机初始化向量
    #iv = b"\x99\xaa\x3e\x68\xed\x81\x73\xa0\xee\xd0\x66\x84"
    #
    ## 创建AES-GCM实例
    #cipher_instance = Cipher(algorithms.AES(key), modes.GCM(iv))
#
    ## 示例使用
    ##plaintext = b"Hello, AES-256-GCM!"
    ##associated_data = b"Additional data for authentication"
    #plaintext = b'\xf5\x6e\x87\x05\x5b\xc3\x2d\x0e\xeb\x31\xb2\xea\xcc\x2b\xf2\xa5'
    #associated_data = b"\x4d\x23\xc3\xce\xc3\x34\xb4\x9b\xdb\x37\x0c\x43\x7f\xec\x78\xde"
#
    ##key = b"\xfe\xff\xe9\x92\x86\x65\x73\x1c\x6d\x6a\x8f\x94\x67\x30\x83\x08\xfe\xff\xe9\x92\x86\x65\x73\x1c\x6d\x6a\x8f\x94\x67\x30\x83\x08"
    ##iv = b"\xca\xfe\xba\xbe\xfa\xce\xdb\xad\xde\xca\xf8\x88"
    ##cipher_instance = Cipher(algorithms.AES(key), modes.GCM(iv))
    ##plaintext = b"\xd9\x31\x32\x25\xf8\x84\x06\xe5\xa5\x59\x09\xc5\xaf\xf5\x26\x9a\x86\xa7\xa9\x53\x15\x34\xf7\xda\x2e\x4c\x30\x3d\x8a\x31\x8a\x72\x1c\x3c\x0c\x95\x95\x68\x09\x53\x2f\xcf\x0e\x24\x49\xa6\xb5\x25\xb1\x6a\xed\xf5\xaa\x0d\xe6\x57\xba\x63\x7b\x39"
    ##associated_data = b"\xfe\xed\xfa\xce\xde\xad\xbe\xef\xfe\xed\xfa\xce\xde\xad\xbe\xef\xab\xad\xda\xd2"

    #plaintext = b'\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69'
    #key = b"\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab"
    #iv = b"\xad\x1e\x65\x35\x0a\xf2\x37\x25\x00\x00\x43\x21"
    #associated_data = b"\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\x88\xe5\x2c\x0c\x00\x00\x43\x21\xad\x1e\x65\x35\x0a\xf2\x37\x25"

    plaintext = b'\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e'
    key = b"\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab"
    iv = b"\xad\x1e\x65\x35\x0a\xf2\x37\x25\x00\x00\x43\x21"
    associated_data = b"\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\x88\xe5\x2c\x0c\x00\x00\x43\x21\xad\x1e\x65\x35\x0a\xf2\x37\x25"

    cipher_instance = Cipher(algorithms.AES(key), modes.GCM(iv))
    

    ciphertext, tag = encrypt(cipher_instance, plaintext, associated_data)
    decrypted_plaintext = decrypt(cipher_instance, ciphertext, tag, associated_data)

    #print("Plaintext:", plaintext)
    #print("Decrypted plaintext:", decrypted_plaintext)
    print("Plaintext:", plaintext.hex())
    print("key:", key.hex())
    print("iv:", iv.hex())
    print("aad:", associated_data.hex())
    print("ciphertext:", ciphertext.hex())
    print("tag:", tag.hex())
    print("Decrypted plaintext:", decrypted_plaintext.hex())

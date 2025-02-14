#ifndef __DATA_H__
 #define __DATA_H__
 struct crypto {
 char *name;
 unsigned char *in;
 unsigned char *key;
 unsigned char *iv;
 unsigned char *nonce;
 unsigned char *aad;
 unsigned char *out;
 };
 struct hash {
 char *name;
 unsigned char *in;
 unsigned char *key;
 unsigned char *out;
 };
 struct combined {
 char *crypto_name;
 unsigned char *in;
 unsigned char *crypto_key;
 unsigned char *iv;
 unsigned char *nonce;
 unsigned char *aad;
 char *hash_name;
 unsigned char *hash_key;
 unsigned char *out;
 };

static unsigned char des_ecb_in[] = "Single block msg";
static unsigned char des_ecb_key_hex[] = "1122334455667788";
static unsigned char des_ecb_out[] = "\x5e\x5d\x4a\x90\x42\x88\x34\x67\xe7\xdc\xe2\xa0\x3b\x1e\x41\x09\x51\xd5\x7f\x92\x3e\xe2\x98\x86";

static unsigned char des_cbc_in[] = "Single block msg";
static unsigned char des_cbc_key_hex[] = "1122334455667788";
static unsigned char des_cbc_iv_hex[] = "1122334455667788";
static unsigned char des_cbc_out[] = "\xf1\x56\x3b\x45\x12\x6d\xf5\x7a\x94\x39\x6f\xfd\x7d\xe7\x69\xd5\x5b\x5d\xde\x9d\x20\x5b\x77\xd3";

static unsigned char des_ede3_ecb_in[] = "Single block msg";
static unsigned char des_ede3_ecb_key_hex[] = "112233445566778811223344556677881122334455667788";
static unsigned char des_ede3_ecb_out[] = "\x5e\x5d\x4a\x90\x42\x88\x34\x67\xe7\xdc\xe2\xa0\x3b\x1e\x41\x09\x51\xd5\x7f\x92\x3e\xe2\x98\x86";

static unsigned char des_ede3_cbc_in[] = "Single block msg";
static unsigned char des_ede3_cbc_key_hex[] = "112233445566778811223344556677881122334455667788";
static unsigned char des_ede3_cbc_iv_hex[] = "1122334455667788";
static unsigned char des_ede3_cbc_out[] = "\xf1\x56\x3b\x45\x12\x6d\xf5\x7a\x94\x39\x6f\xfd\x7d\xe7\x69\xd5\x5b\x5d\xde\x9d\x20\x5b\x77\xd3";

static unsigned char aes_128_ecb_in[] = "Single block msg";
static unsigned char aes_128_ecb_key_hex[] = "06a9214036b8a15b512e03d534120006";
static unsigned char aes_128_ecb_out[] = "\x3a\xe0\x0f\xbd\x31\xdf\xae\xed\x4d\xa6\xe4\x4f\xe2\xc1\x1b\x4f\x8b\x1c\xcc\x6f\x8c\xd5\x25\xff\xe2\x2d\x63\x27\xd8\x91\xa0\x63";

static unsigned char aes_128_cbc_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char aes_128_cbc_key_hex[] = "6c3ea0477630ce21a2ce334aa746c2cd";
static unsigned char aes_128_cbc_iv_hex[] = "c782dc4c098c66cbd9cd27d825682c81";
static unsigned char aes_128_cbc_out[] = "\xd0\xa0\x2b\x38\x36\x45\x17\x53\xd4\x93\x66\x5d\x33\xf0\xe8\x86\x2d\xea\x54\xcd\xb2\x93\xab\xc7\x50\x69\x39\x27\x67\x72\xf8\xd5\x02\x1c\x19\x21\x6b\xad\x52\x5c\x85\x79\x69\x5d\x83\xba\x26\x84\xd2\x48\xb3\xe0\xf2\x38\x8c\x13\x71\x02\x84\x6e\xb0\x62\x72\xff";

static unsigned char aes_128_ofb_in[] = "Single block msg";
static unsigned char aes_128_ofb_key_hex[] = "06a9214036b8a15b512e03d534120006";
static unsigned char aes_128_ofb_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_128_ofb_out[] = "\xd4\x31\x30\xf6\x52\xc4\xc8\x1b\xe6\x2f\xdf\x5e\x72\xe4\x8c\xbc";

static unsigned char aes_128_cfb_in[] = "Single block msg";
static unsigned char aes_128_cfb_key_hex[] = "06a9214036b8a15b512e03d534120006";
static unsigned char aes_128_cfb_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_128_cfb_out[] = "\xd4\x31\x30\xf6\x52\xc4\xc8\x1b\xe6\x2f\xdf\x5e\x72\xe4\x8c\xbc";

static unsigned char aes_128_ctr_in[] = "Single block msg";
static unsigned char aes_128_ctr_key_hex[] = "06a9214036b8a15b512e03d534120006";
static unsigned char aes_128_ctr_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_128_ctr_out[] = "\xd4\x31\x30\xf6\x52\xc4\xc8\x1b\xe6\x2f\xdf\x5e\x72\xe4\x8c\xbc";

static unsigned char aes_128_icm_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char aes_128_icm_key_hex[] = "2b7e151628aed2a6abf7158809cf4f3cf0f1f2f3f4f5f6f7f8f9fafbfcfd";
static unsigned char aes_128_icm_nonce_hex[] = "00000000000000000000000000000000";
static unsigned char aes_128_icm_out[] = "\xe0\x3e\xad\x09\x35\xc9\x5e\x80\xe1\x66\xb1\x6d\xd9\x2b\x4e\xb4\xd2\x35\x13\x16\x2b\x02\xd0\xf7\x2a\x43\xa2\xfe\x4a\x5f\x97\xab";

static unsigned char aes_128_ccm_in[] = "c8d275f919e17d7fe69c2a1f58939dfe";
static unsigned char aes_128_ccm_key_hex[] = "ceb009aea4454451feadf0e6b36f4555";
static unsigned char aes_128_ccm_aad_hex[] = "6e80dd7f1badf3a1c9ab25c75f10bde78c23fa0eb8f9aaa53adefbf4cbf78fe1";
static unsigned char aes_128_ccm_nonce_hex[] = "764043c49460b1";
static unsigned char aes_128_ccm_out[] = "\x94\x5a\xfe\x21\x28\x44\x05\x21\x34\xb1\xb4\x80\x73\x45\xc4\xf2";

static unsigned char aes_128_gcm_in[] = "f56e87055bc32d0eeb31b2eacc2bf2a5";
static unsigned char aes_128_gcm_key_hex[] = "eebc1f57487f51921c0465665f8ae6d1";
static unsigned char aes_128_gcm_aad_hex[] = "64d23c3cec334b49bdb370c437fec78d1";
static unsigned char aes_128_gcm_iv_hex[] = "99aa3e68ed8173a0eed06681";
static unsigned char aes_128_gcm_out[] = "\x6e\x96\xf2\x5f\x8a\xa3\x58\x0a\xbb\x53\xca\xea\xb2\xe5\x16\xc6";

static unsigned char aes_192_ecb_in[] = "Single block msg";
static unsigned char aes_192_ecb_key_hex[] = "112233445566778811223344556677881122334455667788";
static unsigned char aes_192_ecb_out[] = "\x4c\x8f\xe3\x94\x77\xfe\xb5\x5d\x05\x6d\x1d\xc9\x7c\x41\x69\x7a\x5f\xd6\x7d\x23\xf4\xdc\xde\x44\x94\x7e\xef\x7a\xfa\x78\x08\xbb";

static unsigned char aes_192_cbc_in[] = "Single block msg";
static unsigned char aes_192_cbc_key_hex[] = "112233445566778811223344556677881122334455667788";
static unsigned char aes_192_cbc_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_192_cbc_out[] = "\xb4\x79\x60\x88\x0a\x0d\x71\x1f\x83\xe5\x79\xf5\xd5\x47\xb0\xdf\xbe\x80\x96\x72\x30\x79\xb8\x7b\xdf\x52\xae\xea\xd8\x7b\x2e\x1a";

static unsigned char aes_192_ofb_in[] = "Single block msg";
static unsigned char aes_192_ofb_key_hex[] = "112233445566778811223344556677881122334455667788";
static unsigned char aes_192_ofb_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_192_ofb_out[] = "\xe4\xb5\xcd\xa5\xf0\xd6\x8d\xe9\xd8\x14\x41\xc9\x5b\xe9\xe0\x9a";

static unsigned char aes_192_cfb_in[] = "Single block msg";
static unsigned char aes_192_cfb_key_hex[] = "112233445566778811223344556677881122334455667788";
static unsigned char aes_192_cfb_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_192_cfb_out[] = "\xe4\xb5\xcd\xa5\xf0\xd6\x8d\xe9\xd8\x14\x41\xc9\x5b\xe9\xe0\x9a";

static unsigned char aes_192_ctr_in[] = "Single block msg";
static unsigned char aes_192_ctr_key_hex[] = "112233445566778811223344556677881122334455667788";
static unsigned char aes_192_ctr_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_192_ctr_out[] = "\xe4\xb5\xcd\xa5\xf0\xd6\x8d\xe9\xd8\x14\x41\xc9\x5b\xe9\xe0\x9a";

static unsigned char aes_192_icm_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char aes_192_icm_key_hex[] = "eab234764e517b2d3d160d587d8c86219740f65f99b6bcf7f0f1f2f3f4f5f6f7f8f9fafbfcfd";
static unsigned char aes_192_icm_nonce_hex[] = "00000000000000000000000000000000";
static unsigned char aes_192_icm_out[] = "\x35\x09\x6c\xba\x46\x10\x02\x8d\xc1\xb5\x75\x03\x80\x4c\xe3\x7c\x5d\xe9\x86\x29\x1d\xcc\xe1\x61\xd5\x16\x5e\xc4\x56\x8f\x5c\x9a";

static unsigned char aes_192_ccm_in[] = "c8d275f919e17d7fe69c2a1f58939dfe4d403791b5df1310";
static unsigned char aes_192_ccm_key_hex[] = "ceb009aea4454451feadf0e6b36f45555dd04723baa448e8";
static unsigned char aes_192_ccm_aad_hex[] = "6e80dd7f1badf3a1c9ab25c75f10bde78c23fa0eb8f9aaa53adefbf4cbf78fe4";
static unsigned char aes_192_ccm_nonce_hex[] = "764043c49460b7";
static unsigned char aes_192_ccm_out[] = "\x8a\x0f\x3d\x82\x29\xe4\x8e\x74\x87\xfd\x95\xa2\x8a\xd3\x92\xc8\x0b\x36\x81\xd4\xfb\xc7\xbb\xed";

static unsigned char aes_192_gcm_in[] = "f56e87055bc32d0eeb31b2eacc2bf2a5";
static unsigned char aes_192_gcm_key_hex[] = "eebc1f57487f51921c0465665f8ae6d1658bb26de6f8a062";
static unsigned char aes_192_gcm_aad_hex[] = "4d23c3cec334b49bdb370c437fec78d2";
static unsigned char aes_192_gcm_iv_hex[] = "99aa3e68ed8173a0eed06682";
static unsigned char aes_192_gcm_out[] = "\x1f\xff\x18\x6a\xff\x38\xee\x9f\xe7\x61\xc2\x39\x65\x69\x4e\xdb";

static unsigned char aes_256_ecb_in[] = "Single block msg";
static unsigned char aes_256_ecb_key_hex[] = "1122334455667788112233445566778811223344556677888877665544332211";
static unsigned char aes_256_ecb_out[] = "\x37\xc4\xf7\xbf\xfd\x73\x65\x84\xe9\x50\x45\x5b\x72\xbc\x04\x70\x9d\xc3\x9d\xbf\x65\x7e\xd9\xfc\x41\xe1\x61\xc9\x51\xc0\x76\xae";

static unsigned char aes_256_cbc_in[] = "Single block msg";
static unsigned char aes_256_cbc_key_hex[] = "1122334455667788112233445566778811223344556677888877665544332211";
static unsigned char aes_256_cbc_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_256_cbc_out[] = "\x73\x68\xde\x82\x05\xb8\xee\xe1\xaf\xab\x60\x31\xc4\x09\xb3\xd8\xb4\x6e\x1b\x68\xf5\x0c\xd9\x1e\x02\x9d\x38\xcd\xa2\x53\x6d\x39";

static unsigned char aes_256_ofb_in[] = "Single block msg";
static unsigned char aes_256_ofb_key_hex[] = "1122334455667788112233445566778811223344556677888877665544332211";
static unsigned char aes_256_ofb_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_256_ofb_out[] = "\xe9\x5d\xe1\x47\xd8\x33\x62\x77\x07\x99\x12\x19\x1a\xb9\xdd\x24";

static unsigned char aes_256_cfb_in[] = "Single block msg";
static unsigned char aes_256_cfb_key_hex[] = "1122334455667788112233445566778811223344556677888877665544332211";
static unsigned char aes_256_cfb_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_256_cfb_out[] = "\xe9\x5d\xe1\x47\xd8\x33\x62\x77\x07\x99\x12\x19\x1a\xb9\xdd\x24";

static unsigned char aes_256_ctr_in[] = "Single block msg";
static unsigned char aes_256_ctr_key_hex[] = "1122334455667788112233445566778811223344556677888877665544332211";
static unsigned char aes_256_ctr_iv_hex[] = "3dafba429d9eb430b422da802c9fac41";
static unsigned char aes_256_ctr_out[] = "\xe9\x5d\xe1\x47\xd8\x33\x62\x77\x07\x99\x12\x19\x1a\xb9\xdd\x24";

static unsigned char aes_256_icm_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char aes_256_icm_key_hex[] = "57f82fe3613fd170a85ec93c40b1f0922ec4cb0dc025b58272147cc438944a98f0f1f2f3f4f5f6f7f8f9fafbfcfd";
static unsigned char aes_256_icm_nonce_hex[] = "00000000000000000000000000000000";
static unsigned char aes_256_icm_out[] = "\x92\xbd\xd2\x8a\x93\xc3\xf5\x25\x11\xc6\x77\xd0\x8b\x55\x15\xa4\x9d\xa7\x1b\x23\x78\xa8\x54\xf6\x70\x50\x75\x6d\xed\x16\x5b\xac";

static unsigned char aes_256_ccm_in[] = "c8d275f919e17d7fe69c2a1f58939dfe4d403791b5df13101020304050607080";
static unsigned char aes_256_ccm_key_hex[] = "ceb009aea4454451feadf0e6b36f455555dd04723baa448e80102030405060708";
static unsigned char aes_256_ccm_aad_hex[] = "6e80dd7f1badf3a1c9ab25c75f10bde78c23fa0eb8f9aaa53adefbf4cbf78fe3";
static unsigned char aes_256_ccm_nonce_hex[] = "764043c49460b3";
static unsigned char aes_256_ccm_out[] = "\x09\xdf\x6d\x72\x7d\x88\xc6\x64\xcb\xb3\x3c\x9b\xf8\x5c\x07\x50\x5f\xd7\xe6\x1a\x3c\x60\x4c\x82\x5b\x8a\xf9\xf1\xb3\x24\xc6\xbe";

static unsigned char aes_256_gcm_in[] = "f56e87055bc32d0eeb31b2eacc2bf2a5";
static unsigned char aes_256_gcm_key_hex[] = "eebc1f57487f51921c0465665f8ae6d1658bb26de6f8a069a3520293a572078f";
static unsigned char aes_256_gcm_aad_hex[] = "4d23c3cec334b49bdb370c437fec78de";
static unsigned char aes_256_gcm_iv_hex[] = "99aa3e68ed8173a0eed06684";
static unsigned char aes_256_gcm_out[] = "\xf7\x26\x44\x13\xa8\x4c\x0e\x7c\xd5\x36\x86\x7e\xb9\xf2\x17\x93";

static unsigned char md5_in[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
static unsigned char md5_out[] = "\x57\xed\xf4\xa2\x2b\xe3\xc9\x55\xac\x49\xda\x2e\x21\x07\xb6\x7a";

static unsigned char sha1_in[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
static unsigned char sha1_out[] = "\x84\x98\x3e\x44\x1c\x3b\xd2\x6e\xba\xae\x4a\xa1\xf9\x51\x29\xe5\xe5\x46\x70\xf1";

static unsigned char sha224_in[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
static unsigned char sha224_out[] = "\x75\x38\x8b\x16\x51\x27\x76\xcc\x5d\xba\x5d\xa1\xfd\x89\x01\x50\xb0\xc6\x45\x5c\xb4\xf5\x8b\x19\x52\x52\x25\x25";

static unsigned char sha256_in[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
static unsigned char sha256_out[] = "\x24\x8d\x6a\x61\xd2\x06\x38\xb8\xe5\xc0\x26\x93\x0c\x3e\x60\x39\xa3\x3c\xe4\x59\x64\xff\x21\x67\xf6\xec\xed\xd4\x19\xdb\x06\xc1";

static unsigned char sha384_in[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
static unsigned char sha384_out[] = "\x33\x91\xfd\xdd\xfc\x8d\xc7\x39\x37\x07\xa6\x5b\x1b\x47\x09\x39\x7c\xf8\xb1\xd1\x62\xaf\x05\xab\xfe\x8f\x45\x0d\xe5\xf3\x6b\xc6\xb0\x45\x5a\x85\x20\xbc\x4e\x6f\x5f\xe9\x5b\x1f\xe3\xc8\x45\x2b";

static unsigned char sha512_in[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
static unsigned char sha512_out[] = "\x20\x4a\x8f\xc6\xdd\xa8\x2f\x0a\x0c\xed\x7b\xeb\x8e\x08\xa4\x16\x57\xc1\x6e\xf4\x68\xb2\x28\xa8\x27\x9b\xe3\x31\xa7\x03\xc3\x35\x96\xfd\x15\xc1\x3b\x1b\x07\xf9\xaa\x1d\x3b\xea\x57\x78\x9c\xa0\x31\xad\x85\xc7\xa7\x1d\xd7\x03\x54\xec\x63\x12\x38\xca\x34\x45";

static unsigned char md5_hmac_in[] = "what do ya want for nothing?";
static unsigned char md5_hmac_key[] = "Jefe";
static unsigned char md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";

static unsigned char sha1_hmac_in[] = "what do ya want for nothing?";
static unsigned char sha1_hmac_key[] = "Jefe";
static unsigned char sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";

static unsigned char sha224_hmac_in[] = "what do ya want for nothing?";
static unsigned char sha224_hmac_key[] = "Jefe";
static unsigned char sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";

static unsigned char sha256_hmac_in[] = "what do ya want for nothing?";
static unsigned char sha256_hmac_key[] = "Jefe";
static unsigned char sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";

static unsigned char sha384_hmac_in[] = "what do ya want for nothing?";
static unsigned char sha384_hmac_key[] = "Jefe";
static unsigned char sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";

static unsigned char sha512_hmac_in[] = "what do ya want for nothing?";
static unsigned char sha512_hmac_key[] = "Jefe";
static unsigned char sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";

static unsigned char crc32_in[] = "12345678";
static unsigned char crc32_out[] = "\x9a\xe0\xda\xaf";

static unsigned char ghash_in[] = "4f4f95668c83dfb6401762bb2d01a262d1a24ddd2721d006bbe45f20d3c9f362";
static unsigned char ghash_key[] = "25629347589242761d31f826ba4b757b";
static unsigned char ghash_out[] = "\xbd\x9b\x39\x97\x04\x67\x31\xfb\x96\x25\x1b\x91\xf9\xc9\x9d\x7a";

static unsigned char aes_128_cmac_in[] = "6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411";
static unsigned char aes_128_cmac_key[] = "2b7e151628aed2a6abf7158809cf4f3c";
static unsigned char aes_128_cmac_out[] = "\x07\x0a\x16\xb4\x6b\x4d\x41\x44\xf7\x9b\xdd\x9d\xd0\x4a\x28\x7c";

static unsigned char aes_192_cmac_in[] = "6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411";
static unsigned char aes_192_cmac_key[] = "2b7e151628aed2a6abf7158809cf4f3c1122334455667788";
static unsigned char aes_192_cmac_out[] = "\x49\xfa\x48\x0c\x28\xa7\x52\x6f\x6b\x4c\x8b\x55\x95\x8b\x62\x53";

static unsigned char aes_256_cmac_in[] = "6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411";
static unsigned char aes_256_cmac_key[] = "2b7e151628aed2a6abf7158809cf4f3c11223344556677881122334455667788";
static unsigned char aes_256_cmac_out[] = "\x44\x18\x0a\x6c\x08\x56\xf4\x40\xcd\xe2\xf6\xa1\xb1\x2f\xa8\x77";

static unsigned char aes_128_xcbc_mac_96_in[] = "000102030405060708090a0b0c0d0e0f10111213";
static unsigned char aes_128_xcbc_mac_96_key[] = "000102030405060708090a0b0c0d0e0f";
static unsigned char aes_128_xcbc_mac_96_out[] = "\x8e\x98\x6f\x4c\x0b\xb8\xc2\xa5\x19\xc8\x87\x27\x76\x63\x26\x2a";

static unsigned char aes_192_xcbc_mac_96_in[] = "000102030405060708090a0b0c0d0e0f10111213";
static unsigned char aes_192_xcbc_mac_96_key[] = "000102030405060708090a0b0c0d0e0f0001020304050607";
static unsigned char aes_192_xcbc_mac_96_out[] = "\x24\xf3\x58\xa9\xc7\xb2\x01\xc5\x95\xbf\x77\x90\xaa\x57\xff\x4a";

static unsigned char aes_256_xcbc_mac_96_in[] = "000102030405060708090a0b0c0d0e0f10111213";
static unsigned char aes_256_xcbc_mac_96_key[] = "000102030405060708090a0b0c0d0e0f00010203040506070001020304050607";
static unsigned char aes_256_xcbc_mac_96_out[] = "\x2b\x16\xf2\x56\x65\xc1\xe7\x7a\xc1\xb4\xb9\xf3\xfa\x49\xe0\x97";

static unsigned char aes_128_xcbc_mac_prf_in[] = "000102030405060708090a0b0c0d0e0f10111213";
static unsigned char aes_128_xcbc_mac_prf_key[] = "000102030405060708090a0b0c0d0e0f";
static unsigned char aes_128_xcbc_mac_prf_out[] = "\x8e\x98\x6f\x4c\x0b\xb8\xc2\xa5\x19\xc8\x87\x27\x76\x63\x26\x2a";

static unsigned char aes_192_xcbc_mac_prf_in[] = "000102030405060708090a0b0c0d0e0f10111213";
static unsigned char aes_192_xcbc_mac_prf_key[] = "000102030405060708090a0b0c0d0e0f0001020304050607";
static unsigned char aes_192_xcbc_mac_prf_out[] = "\x24\xf3\x58\xa9\xc7\xb2\x01\xc5\x95\xbf\x77\x90\xaa\x57\xff\x4a";

static unsigned char aes_256_xcbc_mac_prf_in[] = "000102030405060708090a0b0c0d0e0f10111213";
static unsigned char aes_256_xcbc_mac_prf_key[] = "000102030405060708090a0b0c0d0e0f00010203040506070001020304050607";
static unsigned char aes_256_xcbc_mac_prf_out[] = "\x2b\x16\xf2\x56\x65\xc1\xe7\x7a\xc1\xb4\xb9\xf3\xfa\x49\xe0\x97";

static unsigned char aes_128_cbc_mac_in[] = "1234567812345678";
static unsigned char aes_128_cbc_mac_key[] = "c0c1c2c3c4c5c6c7c8c9cacbcccdcecf";
static unsigned char aes_128_cbc_mac_out[] = "\x76\xf1\xaa\xb3\x2c\xc5\x18\xc6";

static unsigned char aes_192_cbc_mac_in[] = "1234567812345678";
static unsigned char aes_192_cbc_mac_key[] = "2b7e151628aed2a6abf7158809cf4f3c1122334455667788";
static unsigned char aes_192_cbc_mac_out[] = "\xc2\x77\x17\x4e\xa1\x04\x7b\xaf";

static unsigned char aes_256_cbc_mac_in[] = "1234567812345678";
static unsigned char aes_256_cbc_mac_key[] = "2b7e151628aed2a6abf7158809cf4f3c11223344556677881122334455667788";
static unsigned char aes_256_cbc_mac_out[] = "\xde\x0e\x9d\x3d\x34\x2b\xa3\x9d";

struct crypto crypto_data[] = {
{"des-ecb",des_ecb_in,des_ecb_key_hex,NULL,NULL,NULL,des_ecb_out,},
{"des-ede3-ecb",des_ede3_ecb_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,des_ede3_ecb_out,},
{"aes-128-ecb",aes_128_ecb_in,aes_128_ecb_key_hex,NULL,NULL,NULL,aes_128_ecb_out,},
{"aes-192-ecb",aes_192_ecb_in,aes_192_ecb_key_hex,NULL,NULL,NULL,aes_192_ecb_out,},
{"aes-256-ecb",aes_256_ecb_in,aes_256_ecb_key_hex,NULL,NULL,NULL,aes_256_ecb_out,},
{"des-cbc",des_cbc_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,des_cbc_out,},
{"des-ede3-cbc",des_ede3_cbc_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,des_ede3_cbc_out,},
{"aes-128-cbc",aes_128_cbc_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,aes_128_cbc_out,},
{"aes-128-ofb",aes_128_ofb_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,aes_128_ofb_out,},
{"aes-128-cfb",aes_128_cfb_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,aes_128_cfb_out,},
{"aes-128-ctr",aes_128_ctr_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,aes_128_ctr_out,},
{"aes-192-cbc",aes_192_cbc_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,aes_192_cbc_out,},
{"aes-192-ofb",aes_192_ofb_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,aes_192_ofb_out,},
{"aes-192-cfb",aes_192_cfb_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,aes_192_cfb_out,},
{"aes-192-ctr",aes_192_ctr_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,aes_192_ctr_out,},
{"aes-256-cbc",aes_256_cbc_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,aes_256_cbc_out,},
{"aes-256-ofb",aes_256_ofb_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,aes_256_ofb_out,},
{"aes-256-cfb",aes_256_cfb_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,aes_256_cfb_out,},
{"aes-256-ctr",aes_256_ctr_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,aes_256_ctr_out,},
{"aes-128-icm",aes_128_icm_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,aes_128_icm_out,},
{"aes-192-icm",aes_192_icm_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,aes_192_icm_out,},
{"aes-256-icm",aes_256_icm_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,aes_256_icm_out,},
{"aes-128-ccm",aes_128_ccm_in,aes_128_ccm_key_hex,NULL,aes_128_ccm_nonce_hex,aes_128_ccm_aad_hex,aes_128_ccm_out,},
{"aes-192-ccm",aes_192_ccm_in,aes_192_ccm_key_hex,NULL,aes_192_ccm_nonce_hex,aes_192_ccm_aad_hex,aes_192_ccm_out,},
{"aes-256-ccm",aes_256_ccm_in,aes_256_ccm_key_hex,NULL,aes_256_ccm_nonce_hex,aes_256_ccm_aad_hex,aes_256_ccm_out,},
{"aes-128-gcm",aes_128_gcm_in,aes_128_gcm_key_hex,aes_128_gcm_iv_hex,NULL,aes_128_gcm_aad_hex,aes_128_gcm_out,},
{"aes-192-gcm",aes_192_gcm_in,aes_192_gcm_key_hex,aes_192_gcm_iv_hex,NULL,aes_192_gcm_aad_hex,aes_192_gcm_out,},
{"aes-256-gcm",aes_256_gcm_in,aes_256_gcm_key_hex,aes_256_gcm_iv_hex,NULL,aes_256_gcm_aad_hex,aes_256_gcm_out,},
};
struct hash hash_data[] = {
{"md5",md5_in,NULL,md5_out,},
{"sha1",sha1_in,NULL,sha1_out,},
{"sha224",sha224_in,NULL,sha224_out,},
{"sha256",sha256_in,NULL,sha256_out,},
{"sha384",sha384_in,NULL,sha384_out,},
{"sha512",sha512_in,NULL,sha512_out,},
{"crc32",crc32_in,NULL,crc32_out,},
{"md5-hmac",md5_hmac_in,md5_hmac_key,md5_hmac_out,},
{"sha1-hmac",sha1_hmac_in,sha1_hmac_key,sha1_hmac_out,},
{"sha224-hmac",sha224_hmac_in,sha224_hmac_key,sha224_hmac_out,},
{"sha256-hmac",sha256_hmac_in,sha256_hmac_key,sha256_hmac_out,},
{"sha384-hmac",sha384_hmac_in,sha384_hmac_key,sha384_hmac_out,},
{"sha512-hmac",sha512_hmac_in,sha512_hmac_key,sha512_hmac_out,},
{"ghash",ghash_in,ghash_key,ghash_out,},
{"aes-128-cmac",aes_128_cmac_in,aes_128_cmac_key,aes_128_cmac_out,},
{"aes-192-cmac",aes_192_cmac_in,aes_192_cmac_key,aes_192_cmac_out,},
{"aes-256-cmac",aes_256_cmac_in,aes_256_cmac_key,aes_256_cmac_out,},
{"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_in,aes_128_xcbc_mac_96_key,aes_128_xcbc_mac_96_out,},
{"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_in,aes_192_xcbc_mac_96_key,aes_192_xcbc_mac_96_out,},
{"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_in,aes_256_xcbc_mac_96_key,aes_256_xcbc_mac_96_out,},
{"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_in,aes_128_xcbc_mac_prf_key,aes_128_xcbc_mac_prf_out,},
{"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_in,aes_192_xcbc_mac_prf_key,aes_192_xcbc_mac_prf_out,},
{"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_in,aes_256_xcbc_mac_prf_key,aes_256_xcbc_mac_prf_out,},
{"aes-128-cbc-mac",aes_128_cbc_mac_in,aes_128_cbc_mac_key,aes_128_cbc_mac_out,},
{"aes-192-cbc-mac",aes_192_cbc_mac_in,aes_192_cbc_mac_key,aes_192_cbc_mac_out,},
{"aes-256-cbc-mac",aes_256_cbc_mac_in,aes_256_cbc_mac_key,aes_256_cbc_mac_out,},
};
static unsigned char enc_des_ecb_md5_in[] = "Single block msg";
static unsigned char enc_des_ecb_md5_out[] = "\x1b\xdd\xd4\xe3\x98\x05\x9f\x07\x09\x90\x7b\xbc\x8c\x3c\x79\xf4";
static unsigned char enc_des_ecb_sha1_in[] = "Single block msg";
static unsigned char enc_des_ecb_sha1_out[] = "\xca\x2e\x20\x4f\x12\xe1\x93\xb3\x80\x58\xe9\xe5\xfe\x45\xa6\xff\x37\x5f\xaa\xcc";
static unsigned char enc_des_ecb_sha224_in[] = "Single block msg";
static unsigned char enc_des_ecb_sha224_out[] = "\x39\x19\xc1\x5f\x23\xc7\x0b\x7d\x7e\x6b\x45\xca\x03\x56\xe2\x65\x5e\x1f\x4c\xe0\x58\x63\x9f\x26\x37\x99\xa9\x26";
static unsigned char enc_des_ecb_sha256_in[] = "Single block msg";
static unsigned char enc_des_ecb_sha256_out[] = "\xb1\x22\x5e\xae\x5e\xd2\x67\x42\x7b\x92\xd9\x11\x23\x32\xc2\x79\x88\x0f\x34\xf5\xcd\x5a\xeb\x63\xdb\xd7\x20\xb4\x03\x75\x05\x74";
static unsigned char enc_des_ecb_sha384_in[] = "Single block msg";
static unsigned char enc_des_ecb_sha384_out[] = "\x48\x30\x27\x6f\xa1\xaf\x80\x67\xdb\xdf\x6e\x83\x36\xc7\x95\x96\x3f\x08\xb1\x99\x7f\x4d\x61\xf5\x59\x5d\x2f\x21\xe6\xba\x6b\x9f\x24\x84\xcf\x43\x84\x9d\x13\xcc\x10\xb1\xce\xa8\x5d\x11\xeb\xf9";
static unsigned char enc_des_ecb_sha512_in[] = "Single block msg";
static unsigned char enc_des_ecb_sha512_out[] = "\x8f\x54\xf4\x3a\x32\xcb\x7c\xde\xa5\xea\x45\xd9\x38\x81\xf5\x6a\x33\xeb\x68\x07\xaf\x68\xa5\x9b\x21\x9f\x27\x92\xc9\xd8\x8f\x64\x16\x1f\x72\x4f\x49\x01\xfb\xee\xe9\x52\xac\x5a\x47\x19\xec\xc2\x20\x0a\xb3\x52\xd5\x08\x96\xbf\xb7\xc0\xdb\x01\x63\xd8\xd8\x74";
static unsigned char enc_des_ecb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_des_ecb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_des_ecb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_des_ecb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_des_ecb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_des_ecb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_des_ecb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_des_ecb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_des_ecb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_des_ecb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_des_ecb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_des_ecb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_des_ecb_crc32_in[] = "Single block msg";
static unsigned char enc_des_ecb_crc32_out[] = "\x82\xb6\xeb\xae";
static unsigned char enc_des_ecb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_ecb_aes_128_xcbc_mac_96_out[] = "\xd7\xf1\x90\x57\x86\xc5\xd7\xee\x0c\x36\xe7\x83\xe9\x23\x59\x44";
static unsigned char enc_des_ecb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_ecb_aes_192_xcbc_mac_96_out[] = "\x02\xb4\xc0\xe0\x07\x81\xda\xe8\x6b\x45\x1c\xf5\x11\x9a\xec\x99";
static unsigned char enc_des_ecb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_ecb_aes_256_xcbc_mac_96_out[] = "\x0c\x34\x2d\x3a\x64\x53\x2b\xdd\x62\xa6\x2f\xe4\x6f\xe7\xf4\xf7";
static unsigned char enc_des_ecb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_ecb_aes_128_xcbc_mac_prf_out[] = "\xd7\xf1\x90\x57\x86\xc5\xd7\xee\x0c\x36\xe7\x83\xe9\x23\x59\x44";
static unsigned char enc_des_ecb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_ecb_aes_192_xcbc_mac_prf_out[] = "\x02\xb4\xc0\xe0\x07\x81\xda\xe8\x6b\x45\x1c\xf5\x11\x9a\xec\x99";
static unsigned char enc_des_ecb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_ecb_aes_256_xcbc_mac_prf_out[] = "\x0c\x34\x2d\x3a\x64\x53\x2b\xdd\x62\xa6\x2f\xe4\x6f\xe7\xf4\xf7";
static unsigned char enc_des_cbc_md5_in[] = "Single block msg";
static unsigned char enc_des_cbc_md5_out[] = "\x9c\xd2\x71\xcb\xad\xd6\x71\x93\xab\xc4\x0b\x7a\xd2\x2d\x9b\x32";
static unsigned char enc_des_cbc_sha1_in[] = "Single block msg";
static unsigned char enc_des_cbc_sha1_out[] = "\xce\xf4\x98\x3a\x17\xd4\xee\x4d\x15\x07\x3d\x85\xbf\xf1\xb9\x1b\xb8\x21\xa7\xe4";
static unsigned char enc_des_cbc_sha224_in[] = "Single block msg";
static unsigned char enc_des_cbc_sha224_out[] = "\x32\x0e\xb8\x35\xc4\xeb\x42\x50\x3b\xe6\xf4\x57\xfa\xbe\xea\xff\xab\xf1\x06\xff\xa0\x37\xd7\xbd\x81\x2f\xfb\x00";
static unsigned char enc_des_cbc_sha256_in[] = "Single block msg";
static unsigned char enc_des_cbc_sha256_out[] = "\xd4\xed\x87\x5b\xf3\x20\xf5\xf6\xc8\x92\xcd\x20\x05\x89\x07\x0a\x3d\x93\x99\x42\x2f\x56\xf2\x4c\xc7\xa1\xfa\xc5\x27\xc4\x70\x14";
static unsigned char enc_des_cbc_sha384_in[] = "Single block msg";
static unsigned char enc_des_cbc_sha384_out[] = "\x2c\x38\x20\xc0\xe2\xa3\x58\x14\x28\x52\x57\x7e\x38\xde\x15\xbe\x1e\xfe\x80\x6f\xb5\x35\xed\x64\xff\xda\x46\x47\x17\xdc\xb0\x6d\x85\xb6\x93\xdd\x42\x55\xf9\x3c\x9d\x67\x66\xa2\x5d\x89\xb6\xa8";
static unsigned char enc_des_cbc_sha512_in[] = "Single block msg";
static unsigned char enc_des_cbc_sha512_out[] = "\x69\x53\x74\x0f\x81\x58\x5f\x23\xfe\xcf\xa0\x82\x3d\x98\xfe\x6a\x34\x05\xdc\x4b\x99\xc4\x78\x67\x60\x57\xce\x8b\x42\x4f\x35\x3b\xad\xb9\x84\x2d\xe6\xa3\xf6\x6e\x31\x35\xbd\x6a\x34\x0a\x44\x57\xf6\x46\x20\x79\xf5\xff\xfc\xf2\xbe\x04\x97\xf9\x1a\x72\x8e\xd7";
static unsigned char enc_des_cbc_md5_hmac_in[] = "Single block msg";
static unsigned char enc_des_cbc_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_des_cbc_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_des_cbc_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_des_cbc_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_des_cbc_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_des_cbc_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_des_cbc_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_des_cbc_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_des_cbc_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_des_cbc_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_des_cbc_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_des_cbc_crc32_in[] = "Single block msg";
static unsigned char enc_des_cbc_crc32_out[] = "\x70\xda\xb6\xd3";
static unsigned char enc_des_cbc_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_cbc_aes_128_xcbc_mac_96_out[] = "\x27\x02\x6a\xde\x56\xdf\xaf\x34\x18\x08\xa8\xfa\x76\x3d\x85\x7d";
static unsigned char enc_des_cbc_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_cbc_aes_192_xcbc_mac_96_out[] = "\xca\xd6\xf2\xa1\xb3\xed\x57\x6b\xea\x23\x3a\x09\x2e\x0c\x66\x70";
static unsigned char enc_des_cbc_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_cbc_aes_256_xcbc_mac_96_out[] = "\xa5\xe7\x51\x6c\x7a\xd4\x60\xb3\x81\x0e\x6d\xe3\x5e\xcc\x41\x78";
static unsigned char enc_des_cbc_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_cbc_aes_128_xcbc_mac_prf_out[] = "\x27\x02\x6a\xde\x56\xdf\xaf\x34\x18\x08\xa8\xfa\x76\x3d\x85\x7d";
static unsigned char enc_des_cbc_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_cbc_aes_192_xcbc_mac_prf_out[] = "\xca\xd6\xf2\xa1\xb3\xed\x57\x6b\xea\x23\x3a\x09\x2e\x0c\x66\x70";
static unsigned char enc_des_cbc_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_cbc_aes_256_xcbc_mac_prf_out[] = "\xa5\xe7\x51\x6c\x7a\xd4\x60\xb3\x81\x0e\x6d\xe3\x5e\xcc\x41\x78";
static unsigned char enc_des_ede3_ecb_md5_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_md5_out[] = "\x1b\xdd\xd4\xe3\x98\x05\x9f\x07\x09\x90\x7b\xbc\x8c\x3c\x79\xf4";
static unsigned char enc_des_ede3_ecb_sha1_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_sha1_out[] = "\xca\x2e\x20\x4f\x12\xe1\x93\xb3\x80\x58\xe9\xe5\xfe\x45\xa6\xff\x37\x5f\xaa\xcc";
static unsigned char enc_des_ede3_ecb_sha224_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_sha224_out[] = "\x39\x19\xc1\x5f\x23\xc7\x0b\x7d\x7e\x6b\x45\xca\x03\x56\xe2\x65\x5e\x1f\x4c\xe0\x58\x63\x9f\x26\x37\x99\xa9\x26";
static unsigned char enc_des_ede3_ecb_sha256_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_sha256_out[] = "\xb1\x22\x5e\xae\x5e\xd2\x67\x42\x7b\x92\xd9\x11\x23\x32\xc2\x79\x88\x0f\x34\xf5\xcd\x5a\xeb\x63\xdb\xd7\x20\xb4\x03\x75\x05\x74";
static unsigned char enc_des_ede3_ecb_sha384_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_sha384_out[] = "\x48\x30\x27\x6f\xa1\xaf\x80\x67\xdb\xdf\x6e\x83\x36\xc7\x95\x96\x3f\x08\xb1\x99\x7f\x4d\x61\xf5\x59\x5d\x2f\x21\xe6\xba\x6b\x9f\x24\x84\xcf\x43\x84\x9d\x13\xcc\x10\xb1\xce\xa8\x5d\x11\xeb\xf9";
static unsigned char enc_des_ede3_ecb_sha512_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_sha512_out[] = "\x8f\x54\xf4\x3a\x32\xcb\x7c\xde\xa5\xea\x45\xd9\x38\x81\xf5\x6a\x33\xeb\x68\x07\xaf\x68\xa5\x9b\x21\x9f\x27\x92\xc9\xd8\x8f\x64\x16\x1f\x72\x4f\x49\x01\xfb\xee\xe9\x52\xac\x5a\x47\x19\xec\xc2\x20\x0a\xb3\x52\xd5\x08\x96\xbf\xb7\xc0\xdb\x01\x63\xd8\xd8\x74";
static unsigned char enc_des_ede3_ecb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_des_ede3_ecb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_des_ede3_ecb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_des_ede3_ecb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_des_ede3_ecb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_des_ede3_ecb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_des_ede3_ecb_crc32_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_crc32_out[] = "\x82\xb6\xeb\xae";
static unsigned char enc_des_ede3_ecb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_aes_128_xcbc_mac_96_out[] = "\xd7\xf1\x90\x57\x86\xc5\xd7\xee\x0c\x36\xe7\x83\xe9\x23\x59\x44";
static unsigned char enc_des_ede3_ecb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_aes_192_xcbc_mac_96_out[] = "\x02\xb4\xc0\xe0\x07\x81\xda\xe8\x6b\x45\x1c\xf5\x11\x9a\xec\x99";
static unsigned char enc_des_ede3_ecb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_aes_256_xcbc_mac_96_out[] = "\x0c\x34\x2d\x3a\x64\x53\x2b\xdd\x62\xa6\x2f\xe4\x6f\xe7\xf4\xf7";
static unsigned char enc_des_ede3_ecb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_aes_128_xcbc_mac_prf_out[] = "\xd7\xf1\x90\x57\x86\xc5\xd7\xee\x0c\x36\xe7\x83\xe9\x23\x59\x44";
static unsigned char enc_des_ede3_ecb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_aes_192_xcbc_mac_prf_out[] = "\x02\xb4\xc0\xe0\x07\x81\xda\xe8\x6b\x45\x1c\xf5\x11\x9a\xec\x99";
static unsigned char enc_des_ede3_ecb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_ede3_ecb_aes_256_xcbc_mac_prf_out[] = "\x0c\x34\x2d\x3a\x64\x53\x2b\xdd\x62\xa6\x2f\xe4\x6f\xe7\xf4\xf7";
static unsigned char enc_des_ede3_cbc_md5_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_md5_out[] = "\x9c\xd2\x71\xcb\xad\xd6\x71\x93\xab\xc4\x0b\x7a\xd2\x2d\x9b\x32";
static unsigned char enc_des_ede3_cbc_sha1_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_sha1_out[] = "\xce\xf4\x98\x3a\x17\xd4\xee\x4d\x15\x07\x3d\x85\xbf\xf1\xb9\x1b\xb8\x21\xa7\xe4";
static unsigned char enc_des_ede3_cbc_sha224_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_sha224_out[] = "\x32\x0e\xb8\x35\xc4\xeb\x42\x50\x3b\xe6\xf4\x57\xfa\xbe\xea\xff\xab\xf1\x06\xff\xa0\x37\xd7\xbd\x81\x2f\xfb\x00";
static unsigned char enc_des_ede3_cbc_sha256_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_sha256_out[] = "\xd4\xed\x87\x5b\xf3\x20\xf5\xf6\xc8\x92\xcd\x20\x05\x89\x07\x0a\x3d\x93\x99\x42\x2f\x56\xf2\x4c\xc7\xa1\xfa\xc5\x27\xc4\x70\x14";
static unsigned char enc_des_ede3_cbc_sha384_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_sha384_out[] = "\x2c\x38\x20\xc0\xe2\xa3\x58\x14\x28\x52\x57\x7e\x38\xde\x15\xbe\x1e\xfe\x80\x6f\xb5\x35\xed\x64\xff\xda\x46\x47\x17\xdc\xb0\x6d\x85\xb6\x93\xdd\x42\x55\xf9\x3c\x9d\x67\x66\xa2\x5d\x89\xb6\xa8";
static unsigned char enc_des_ede3_cbc_sha512_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_sha512_out[] = "\x69\x53\x74\x0f\x81\x58\x5f\x23\xfe\xcf\xa0\x82\x3d\x98\xfe\x6a\x34\x05\xdc\x4b\x99\xc4\x78\x67\x60\x57\xce\x8b\x42\x4f\x35\x3b\xad\xb9\x84\x2d\xe6\xa3\xf6\x6e\x31\x35\xbd\x6a\x34\x0a\x44\x57\xf6\x46\x20\x79\xf5\xff\xfc\xf2\xbe\x04\x97\xf9\x1a\x72\x8e\xd7";
static unsigned char enc_des_ede3_cbc_md5_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_des_ede3_cbc_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_des_ede3_cbc_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_des_ede3_cbc_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_des_ede3_cbc_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_des_ede3_cbc_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_des_ede3_cbc_crc32_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_crc32_out[] = "\x70\xda\xb6\xd3";
static unsigned char enc_des_ede3_cbc_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_aes_128_xcbc_mac_96_out[] = "\x27\x02\x6a\xde\x56\xdf\xaf\x34\x18\x08\xa8\xfa\x76\x3d\x85\x7d";
static unsigned char enc_des_ede3_cbc_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_aes_192_xcbc_mac_96_out[] = "\xca\xd6\xf2\xa1\xb3\xed\x57\x6b\xea\x23\x3a\x09\x2e\x0c\x66\x70";
static unsigned char enc_des_ede3_cbc_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_aes_256_xcbc_mac_96_out[] = "\xa5\xe7\x51\x6c\x7a\xd4\x60\xb3\x81\x0e\x6d\xe3\x5e\xcc\x41\x78";
static unsigned char enc_des_ede3_cbc_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_aes_128_xcbc_mac_prf_out[] = "\x27\x02\x6a\xde\x56\xdf\xaf\x34\x18\x08\xa8\xfa\x76\x3d\x85\x7d";
static unsigned char enc_des_ede3_cbc_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_aes_192_xcbc_mac_prf_out[] = "\xca\xd6\xf2\xa1\xb3\xed\x57\x6b\xea\x23\x3a\x09\x2e\x0c\x66\x70";
static unsigned char enc_des_ede3_cbc_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_des_ede3_cbc_aes_256_xcbc_mac_prf_out[] = "\xa5\xe7\x51\x6c\x7a\xd4\x60\xb3\x81\x0e\x6d\xe3\x5e\xcc\x41\x78";
static unsigned char enc_aes_128_ecb_md5_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_md5_out[] = "\x5b\x62\x66\xef\x7e\x2f\x02\x56\x71\x35\xbd\x00\x98\xee\x7a\x60";
static unsigned char enc_aes_128_ecb_sha1_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_sha1_out[] = "\x7d\xae\xd2\x12\x69\x57\x5a\xf7\x61\x26\x36\xa1\x74\x08\x6a\x90\x39\xd3\xa3\x73";
static unsigned char enc_aes_128_ecb_sha224_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_sha224_out[] = "\x21\x2f\x92\x0f\x78\x4d\x69\xb2\xd0\x2c\x4f\xd0\x3d\x13\x07\xd8\xd4\xfd\x6e\xfb\x01\xbf\x84\x27\x09\xd4\x90\x48";
static unsigned char enc_aes_128_ecb_sha256_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_sha256_out[] = "\x02\x3c\xd5\xe4\x87\x58\x0e\x98\xa0\x9e\xdb\x7a\xa7\x82\xeb\x00\x17\x9b\x29\x59\x9d\x90\x26\x3d\xa7\xd8\x99\x97\xf1\xd8\x30\x17";
static unsigned char enc_aes_128_ecb_sha384_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_sha384_out[] = "\x63\xc1\xee\x97\x52\x4d\xbb\x87\xb2\x84\x8b\x52\x2a\x60\x05\x4f\x56\x3d\x8b\xc8\x7e\x60\x8e\x68\x12\xf7\xad\xa7\xb9\xdf\xc2\x28\xe0\x47\xff\x30\x59\x51\x9e\x29\xe7\x7f\xe9\xc1\x5f\xf8\x50\x45";
static unsigned char enc_aes_128_ecb_sha512_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_sha512_out[] = "\x1e\xa1\xc0\x56\x5c\x33\xd8\xc1\x9e\x73\x7e\x98\xdd\x3b\x23\xc0\xcf\xbd\xe4\x49\x5d\x24\x23\xc5\x19\xf8\xf4\x2b\x1b\xd3\x6c\xab\x62\x50\x78\x32\x6f\x7f\xa4\x41\x03\xb6\x3a\xa5\x9f\x2c\x22\xc7\xf7\xd9\xac\xa2\xac\xad\x68\xd4\x0f\x29\xd9\xfb\xfd\x98\xe2\x3d";
static unsigned char enc_aes_128_ecb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_128_ecb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_128_ecb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_128_ecb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_128_ecb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_128_ecb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_128_ecb_crc32_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_crc32_out[] = "\x32\xdd\x82\xc4";
static unsigned char enc_aes_128_ecb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_aes_128_xcbc_mac_96_out[] = "\x90\x4f\x9a\xf0\x00\xc6\x11\x23\xdc\x45\xea\x04\xd9\x9c\x5a\x5f";
static unsigned char enc_aes_128_ecb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_aes_192_xcbc_mac_96_out[] = "\xad\x41\x21\xf0\xef\x68\x62\x14\x9f\xae\x89\x3a\x61\xa8\x9b\x52";
static unsigned char enc_aes_128_ecb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_aes_256_xcbc_mac_96_out[] = "\x6a\x9e\x80\x6e\xad\x62\x86\x76\x4e\xe2\xeb\xe9\x51\x63\x69\x37";
static unsigned char enc_aes_128_ecb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_aes_128_xcbc_mac_prf_out[] = "\x90\x4f\x9a\xf0\x00\xc6\x11\x23\xdc\x45\xea\x04\xd9\x9c\x5a\x5f";
static unsigned char enc_aes_128_ecb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_aes_192_xcbc_mac_prf_out[] = "\xad\x41\x21\xf0\xef\x68\x62\x14\x9f\xae\x89\x3a\x61\xa8\x9b\x52";
static unsigned char enc_aes_128_ecb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_ecb_aes_256_xcbc_mac_prf_out[] = "\x6a\x9e\x80\x6e\xad\x62\x86\x76\x4e\xe2\xeb\xe9\x51\x63\x69\x37";
static unsigned char enc_aes_128_cbc_md5_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_md5_out[] = "\x43\x51\x2e\x29\x7a\x01\x0e\xda\xf7\x09\xba\x46\x10\x72\x22\x61";
static unsigned char enc_aes_128_cbc_sha1_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_sha1_out[] = "\x5f\xad\x85\xce\x1d\xd0\xcb\xe7\x9b\x10\xe5\xf4\x9e\x82\xc6\xdb\x2d\x2f\x4e\x18";
static unsigned char enc_aes_128_cbc_sha224_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_sha224_out[] = "\x08\x16\x89\xf4\x1c\xde\x5f\x50\x0d\x35\x9f\xcd\x9d\x87\x17\xe5\xad\x66\x4f\xa1\x0e\x38\x79\xfc\xe2\x3a\x2f\x5d";
static unsigned char enc_aes_128_cbc_sha256_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_sha256_out[] = "\x01\x43\x22\x1c\x27\xba\x22\x49\x17\x52\x4a\xa6\x16\xe5\x95\xb0\x05\x1b\xb1\xb1\x9e\xfc\x92\xcb\x07\x2c\x13\xad\x11\x34\x85\x6c";
static unsigned char enc_aes_128_cbc_sha384_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_sha384_out[] = "\x3a\xde\x93\x13\x9f\x4f\x48\x74\x68\x33\xee\xc3\x54\xab\x46\x8f\xac\x04\x74\x3c\x4b\x0c\xd3\x71\x43\xae\x00\xfd\xc2\xa9\xef\xf5\x4a\x52\x85\xc7\xc3\x35\x6f\xaa\x11\xaf\x1e\x15\x58\xa2\x1d\xbf";
static unsigned char enc_aes_128_cbc_sha512_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_sha512_out[] = "\xcf\x20\x75\x37\xf9\xd0\xc9\x72\xc7\x4b\xb1\xc8\x01\x72\x50\xa8\x34\xad\x24\x86\xb7\x72\x47\x9b\xa2\x67\x1e\x78\x81\x54\xec\x11\x4c\xc4\xba\xec\xaf\xb7\x72\xfc\x32\xa3\xcb\x79\x45\x97\x7d\xbb\x9c\x54\xc9\x28\x6e\xd8\x87\xcc\x4d\x4c\xa8\xf0\x18\xb4\x0d\x97";
static unsigned char enc_aes_128_cbc_md5_hmac_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_128_cbc_sha1_hmac_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_128_cbc_sha224_hmac_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_128_cbc_sha256_hmac_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_128_cbc_sha384_hmac_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_128_cbc_sha512_hmac_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_128_cbc_crc32_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_crc32_out[] = "\xb4\x0f\x89\x4a";
static unsigned char enc_aes_128_cbc_aes_128_xcbc_mac_96_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_aes_128_xcbc_mac_96_out[] = "\x91\x3c\xa5\x85\x92\xb2\x22\xfc\x3e\xe0\xc8\x00\x2d\x5b\x58\x28";
static unsigned char enc_aes_128_cbc_aes_192_xcbc_mac_96_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_aes_192_xcbc_mac_96_out[] = "\x2d\x69\x7c\x10\xb7\xc8\xc3\x67\x63\x58\x3d\x3a\x63\x46\x08\xda";
static unsigned char enc_aes_128_cbc_aes_256_xcbc_mac_96_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_aes_256_xcbc_mac_96_out[] = "\x93\xad\xa0\x72\x61\x38\x6f\x0b\xb9\x3c\x8e\x19\x39\xf3\x26\xb3";
static unsigned char enc_aes_128_cbc_aes_128_xcbc_mac_prf_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_aes_128_xcbc_mac_prf_out[] = "\x91\x3c\xa5\x85\x92\xb2\x22\xfc\x3e\xe0\xc8\x00\x2d\x5b\x58\x28";
static unsigned char enc_aes_128_cbc_aes_192_xcbc_mac_prf_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_aes_192_xcbc_mac_prf_out[] = "\x2d\x69\x7c\x10\xb7\xc8\xc3\x67\x63\x58\x3d\x3a\x63\x46\x08\xda";
static unsigned char enc_aes_128_cbc_aes_256_xcbc_mac_prf_in[] = "This is a 48-byte message (exactly 3 AES blocks)";
static unsigned char enc_aes_128_cbc_aes_256_xcbc_mac_prf_out[] = "\x93\xad\xa0\x72\x61\x38\x6f\x0b\xb9\x3c\x8e\x19\x39\xf3\x26\xb3";
static unsigned char enc_aes_128_ofb_md5_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_md5_out[] = "\x73\x30\x1b\xcf\xe8\x7e\x77\x84\x7d\x65\x69\x22\x44\xb4\x9a\xe3";
static unsigned char enc_aes_128_ofb_sha1_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_sha1_out[] = "\x20\xfe\x84\x6c\xeb\x63\x07\xd2\xa6\xbf\xf0\x28\xe5\xb6\xd4\x09\x29\xd4\xda\xc3";
static unsigned char enc_aes_128_ofb_sha224_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_sha224_out[] = "\x08\x17\x43\x5a\xc5\xe0\x94\x34\x79\xdb\x40\xbb\x5e\x3b\x54\x0d\xe1\x89\xd0\x3c\x38\x6c\x3c\x3a\x86\x8c\x20\xa9";
static unsigned char enc_aes_128_ofb_sha256_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_sha256_out[] = "\xac\xb1\x38\x21\x08\x8c\x58\xea\x7c\x77\x21\x36\xb1\xcc\xee\xc9\x5f\x56\x11\x91\x87\x6d\xcf\x65\x20\x07\x36\xe9\x7b\x86\xc9\x4c";
static unsigned char enc_aes_128_ofb_sha384_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_sha384_out[] = "\x31\x5b\xb7\xd4\xc1\x4a\xf5\xc4\x52\x8d\x25\x5a\xa9\x9e\x00\x84\xec\x2b\xf5\xe6\x99\x05\x7e\x73\xaa\x1b\xda\xda\xcb\x6f\x58\x76\x4d\x7e\xcf\x2c\x41\x73\x52\x82\x76\xbe\x53\x90\xcf\xef\x39\x42";
static unsigned char enc_aes_128_ofb_sha512_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_sha512_out[] = "\xf5\x20\x55\xbe\x46\x2a\x8b\xe6\x89\xe5\x8d\xed\x22\xad\xd8\xd3\x2d\x7a\xbd\xa0\x7e\x3f\x1a\xd0\x87\xcf\xa2\xfc\x64\x97\x50\x5c\xd5\xab\x47\xa8\xc7\x7e\xef\xca\xa8\x8f\xa1\xd3\xdd\x8e\x39\x11\x9c\x0f\x2c\xf8\x54\x1a\x40\x96\xf7\x85\x1d\x4c\x10\xae\x80\xb2";
static unsigned char enc_aes_128_ofb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_128_ofb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_128_ofb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_128_ofb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_128_ofb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_128_ofb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_128_ofb_crc32_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_crc32_out[] = "\x20\xfe\x5a\xd6";
static unsigned char enc_aes_128_ofb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_aes_128_xcbc_mac_96_out[] = "\x60\x29\x9d\xf4\x6f\x4a\x15\x17\xd5\x59\x94\x56\x4e\x63\x17\x89";
static unsigned char enc_aes_128_ofb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_aes_192_xcbc_mac_96_out[] = "\x95\x78\xc9\xa1\x8e\x03\xed\x3d\xde\xa1\xae\xaa\xfe\x1b\x3a\x16";
static unsigned char enc_aes_128_ofb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_aes_256_xcbc_mac_96_out[] = "\x18\x0a\x26\x50\xdb\x2e\xa7\x91\x88\xf9\x1b\xd0\xee\x62\x7b\xd5";
static unsigned char enc_aes_128_ofb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_aes_128_xcbc_mac_prf_out[] = "\x60\x29\x9d\xf4\x6f\x4a\x15\x17\xd5\x59\x94\x56\x4e\x63\x17\x89";
static unsigned char enc_aes_128_ofb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_aes_192_xcbc_mac_prf_out[] = "\x95\x78\xc9\xa1\x8e\x03\xed\x3d\xde\xa1\xae\xaa\xfe\x1b\x3a\x16";
static unsigned char enc_aes_128_ofb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_ofb_aes_256_xcbc_mac_prf_out[] = "\x18\x0a\x26\x50\xdb\x2e\xa7\x91\x88\xf9\x1b\xd0\xee\x62\x7b\xd5";
static unsigned char enc_aes_128_cfb_md5_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_md5_out[] = "\x73\x30\x1b\xcf\xe8\x7e\x77\x84\x7d\x65\x69\x22\x44\xb4\x9a\xe3";
static unsigned char enc_aes_128_cfb_sha1_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_sha1_out[] = "\x20\xfe\x84\x6c\xeb\x63\x07\xd2\xa6\xbf\xf0\x28\xe5\xb6\xd4\x09\x29\xd4\xda\xc3";
static unsigned char enc_aes_128_cfb_sha224_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_sha224_out[] = "\x08\x17\x43\x5a\xc5\xe0\x94\x34\x79\xdb\x40\xbb\x5e\x3b\x54\x0d\xe1\x89\xd0\x3c\x38\x6c\x3c\x3a\x86\x8c\x20\xa9";
static unsigned char enc_aes_128_cfb_sha256_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_sha256_out[] = "\xac\xb1\x38\x21\x08\x8c\x58\xea\x7c\x77\x21\x36\xb1\xcc\xee\xc9\x5f\x56\x11\x91\x87\x6d\xcf\x65\x20\x07\x36\xe9\x7b\x86\xc9\x4c";
static unsigned char enc_aes_128_cfb_sha384_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_sha384_out[] = "\x31\x5b\xb7\xd4\xc1\x4a\xf5\xc4\x52\x8d\x25\x5a\xa9\x9e\x00\x84\xec\x2b\xf5\xe6\x99\x05\x7e\x73\xaa\x1b\xda\xda\xcb\x6f\x58\x76\x4d\x7e\xcf\x2c\x41\x73\x52\x82\x76\xbe\x53\x90\xcf\xef\x39\x42";
static unsigned char enc_aes_128_cfb_sha512_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_sha512_out[] = "\xf5\x20\x55\xbe\x46\x2a\x8b\xe6\x89\xe5\x8d\xed\x22\xad\xd8\xd3\x2d\x7a\xbd\xa0\x7e\x3f\x1a\xd0\x87\xcf\xa2\xfc\x64\x97\x50\x5c\xd5\xab\x47\xa8\xc7\x7e\xef\xca\xa8\x8f\xa1\xd3\xdd\x8e\x39\x11\x9c\x0f\x2c\xf8\x54\x1a\x40\x96\xf7\x85\x1d\x4c\x10\xae\x80\xb2";
static unsigned char enc_aes_128_cfb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_128_cfb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_128_cfb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_128_cfb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_128_cfb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_128_cfb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_128_cfb_crc32_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_crc32_out[] = "\x20\xfe\x5a\xd6";
static unsigned char enc_aes_128_cfb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_aes_128_xcbc_mac_96_out[] = "\x60\x29\x9d\xf4\x6f\x4a\x15\x17\xd5\x59\x94\x56\x4e\x63\x17\x89";
static unsigned char enc_aes_128_cfb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_aes_192_xcbc_mac_96_out[] = "\x95\x78\xc9\xa1\x8e\x03\xed\x3d\xde\xa1\xae\xaa\xfe\x1b\x3a\x16";
static unsigned char enc_aes_128_cfb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_aes_256_xcbc_mac_96_out[] = "\x18\x0a\x26\x50\xdb\x2e\xa7\x91\x88\xf9\x1b\xd0\xee\x62\x7b\xd5";
static unsigned char enc_aes_128_cfb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_aes_128_xcbc_mac_prf_out[] = "\x60\x29\x9d\xf4\x6f\x4a\x15\x17\xd5\x59\x94\x56\x4e\x63\x17\x89";
static unsigned char enc_aes_128_cfb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_aes_192_xcbc_mac_prf_out[] = "\x95\x78\xc9\xa1\x8e\x03\xed\x3d\xde\xa1\xae\xaa\xfe\x1b\x3a\x16";
static unsigned char enc_aes_128_cfb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_cfb_aes_256_xcbc_mac_prf_out[] = "\x18\x0a\x26\x50\xdb\x2e\xa7\x91\x88\xf9\x1b\xd0\xee\x62\x7b\xd5";
static unsigned char enc_aes_128_ctr_md5_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_md5_out[] = "\x73\x30\x1b\xcf\xe8\x7e\x77\x84\x7d\x65\x69\x22\x44\xb4\x9a\xe3";
static unsigned char enc_aes_128_ctr_sha1_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_sha1_out[] = "\x20\xfe\x84\x6c\xeb\x63\x07\xd2\xa6\xbf\xf0\x28\xe5\xb6\xd4\x09\x29\xd4\xda\xc3";
static unsigned char enc_aes_128_ctr_sha224_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_sha224_out[] = "\x08\x17\x43\x5a\xc5\xe0\x94\x34\x79\xdb\x40\xbb\x5e\x3b\x54\x0d\xe1\x89\xd0\x3c\x38\x6c\x3c\x3a\x86\x8c\x20\xa9";
static unsigned char enc_aes_128_ctr_sha256_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_sha256_out[] = "\xac\xb1\x38\x21\x08\x8c\x58\xea\x7c\x77\x21\x36\xb1\xcc\xee\xc9\x5f\x56\x11\x91\x87\x6d\xcf\x65\x20\x07\x36\xe9\x7b\x86\xc9\x4c";
static unsigned char enc_aes_128_ctr_sha384_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_sha384_out[] = "\x31\x5b\xb7\xd4\xc1\x4a\xf5\xc4\x52\x8d\x25\x5a\xa9\x9e\x00\x84\xec\x2b\xf5\xe6\x99\x05\x7e\x73\xaa\x1b\xda\xda\xcb\x6f\x58\x76\x4d\x7e\xcf\x2c\x41\x73\x52\x82\x76\xbe\x53\x90\xcf\xef\x39\x42";
static unsigned char enc_aes_128_ctr_sha512_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_sha512_out[] = "\xf5\x20\x55\xbe\x46\x2a\x8b\xe6\x89\xe5\x8d\xed\x22\xad\xd8\xd3\x2d\x7a\xbd\xa0\x7e\x3f\x1a\xd0\x87\xcf\xa2\xfc\x64\x97\x50\x5c\xd5\xab\x47\xa8\xc7\x7e\xef\xca\xa8\x8f\xa1\xd3\xdd\x8e\x39\x11\x9c\x0f\x2c\xf8\x54\x1a\x40\x96\xf7\x85\x1d\x4c\x10\xae\x80\xb2";
static unsigned char enc_aes_128_ctr_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_128_ctr_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_128_ctr_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_128_ctr_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_128_ctr_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_128_ctr_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_128_ctr_crc32_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_crc32_out[] = "\x20\xfe\x5a\xd6";
static unsigned char enc_aes_128_ctr_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_aes_128_xcbc_mac_96_out[] = "\x60\x29\x9d\xf4\x6f\x4a\x15\x17\xd5\x59\x94\x56\x4e\x63\x17\x89";
static unsigned char enc_aes_128_ctr_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_aes_192_xcbc_mac_96_out[] = "\x95\x78\xc9\xa1\x8e\x03\xed\x3d\xde\xa1\xae\xaa\xfe\x1b\x3a\x16";
static unsigned char enc_aes_128_ctr_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_aes_256_xcbc_mac_96_out[] = "\x18\x0a\x26\x50\xdb\x2e\xa7\x91\x88\xf9\x1b\xd0\xee\x62\x7b\xd5";
static unsigned char enc_aes_128_ctr_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_aes_128_xcbc_mac_prf_out[] = "\x60\x29\x9d\xf4\x6f\x4a\x15\x17\xd5\x59\x94\x56\x4e\x63\x17\x89";
static unsigned char enc_aes_128_ctr_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_aes_192_xcbc_mac_prf_out[] = "\x95\x78\xc9\xa1\x8e\x03\xed\x3d\xde\xa1\xae\xaa\xfe\x1b\x3a\x16";
static unsigned char enc_aes_128_ctr_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_128_ctr_aes_256_xcbc_mac_prf_out[] = "\x18\x0a\x26\x50\xdb\x2e\xa7\x91\x88\xf9\x1b\xd0\xee\x62\x7b\xd5";
static unsigned char enc_aes_128_icm_md5_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_md5_out[] = "\x0b\xd9\xb8\x29\x90\x86\x40\x7a\x64\xb1\xa0\x16\xcc\x0d\xff\x57";
static unsigned char enc_aes_128_icm_sha1_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_sha1_out[] = "\x7f\x1e\xf6\x8f\x2d\x84\x6c\xff\x58\xbf\x90\xe9\x62\x07\xfd\x7f\xee\xaa\x54\xe9";
static unsigned char enc_aes_128_icm_sha224_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_sha224_out[] = "\x0b\xac\x14\x6e\xcc\x22\xc3\xc9\xc8\x25\x30\xb2\x2f\x2f\xb4\xff\x4e\xf5\x15\xf4\x1f\x1d\xd4\xea\x98\xd0\x40\x26";
static unsigned char enc_aes_128_icm_sha256_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_sha256_out[] = "\x07\x39\x64\x50\x60\x0a\x87\x42\x5d\xc2\xee\x92\xd3\xf7\x0d\xb2\x4a\x48\xe9\x6e\x0f\xb1\x59\x9f\xc8\xe3\xcf\x84\x29\xf8\x72\x7d";
static unsigned char enc_aes_128_icm_sha384_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_sha384_out[] = "\x71\xa9\xfa\xd7\xd4\x79\xff\xd0\xaa\xd2\x76\x81\x9c\x7c\x6b\xe4\x2c\x65\xbf\xc4\x4d\x4f\x8b\xcb\x63\x3b\xe2\x0d\x24\x56\x08\x9e\xe3\x52\x6c\xb2\x20\x80\x0c\x2a\x0a\xde\x0e\xc3\x81\x46\xac\x18";
static unsigned char enc_aes_128_icm_sha512_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_sha512_out[] = "\x4e\x3f\xf1\x30\xa0\x3c\x10\x52\x63\xb1\xe0\x48\x30\x42\xf5\xa0\xfd\x2e\x60\x00\xa1\x29\xa0\xcd\x69\xeb\x0d\x2c\xaa\x07\xe1\xde\x64\x88\x75\x99\xe5\x8d\xb4\x92\x94\x37\x4f\xd9\x2e\xdf\xd6\xef\xf3\x2c\x06\x95\x83\xec\x2f\x1d\x0e\x4a\x2b\xe6\x1d\x93\xc5\x39";
static unsigned char enc_aes_128_icm_md5_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_128_icm_sha1_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_128_icm_sha224_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_128_icm_sha256_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_128_icm_sha384_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_128_icm_sha512_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_128_icm_crc32_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_crc32_out[] = "\xce\xbc\xbf\xd2";
static unsigned char enc_aes_128_icm_aes_128_xcbc_mac_96_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_aes_128_xcbc_mac_96_out[] = "\x50\x31\xed\x72\x76\x08\xee\x23\xd2\x76\x4e\xd9\x8f\x92\xc0\x31";
static unsigned char enc_aes_128_icm_aes_192_xcbc_mac_96_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_aes_192_xcbc_mac_96_out[] = "\x36\xfe\xc1\xaf\xea\x60\x9d\x20\xcb\x91\xda\x0f\xb4\xcc\x6d\x7b";
static unsigned char enc_aes_128_icm_aes_256_xcbc_mac_96_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_aes_256_xcbc_mac_96_out[] = "\xb1\x7a\x07\x71\x45\x93\x85\x82\x3c\xf3\x5b\x8d\x14\xdd\xdb\xad";
static unsigned char enc_aes_128_icm_aes_128_xcbc_mac_prf_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_aes_128_xcbc_mac_prf_out[] = "\x50\x31\xed\x72\x76\x08\xee\x23\xd2\x76\x4e\xd9\x8f\x92\xc0\x31";
static unsigned char enc_aes_128_icm_aes_192_xcbc_mac_prf_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_aes_192_xcbc_mac_prf_out[] = "\x36\xfe\xc1\xaf\xea\x60\x9d\x20\xcb\x91\xda\x0f\xb4\xcc\x6d\x7b";
static unsigned char enc_aes_128_icm_aes_256_xcbc_mac_prf_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_128_icm_aes_256_xcbc_mac_prf_out[] = "\xb1\x7a\x07\x71\x45\x93\x85\x82\x3c\xf3\x5b\x8d\x14\xdd\xdb\xad";
static unsigned char enc_aes_192_ecb_md5_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_md5_out[] = "\xac\xe1\xe5\xc4\xdc\xbe\x52\x00\x57\xf5\x15\xed\x6b\xdc\xb9\x83";
static unsigned char enc_aes_192_ecb_sha1_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_sha1_out[] = "\x33\xcf\x56\xdd\x9b\x67\x61\x13\xaf\xa6\xa1\xe1\x1b\xcf\x34\x9a\x34\x9e\x0d\xb0";
static unsigned char enc_aes_192_ecb_sha224_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_sha224_out[] = "\xb7\x9d\x34\x2b\x51\x63\x7c\x85\x52\xdd\xf6\xec\xa3\x63\x77\xa2\x4e\xa9\xdc\x8d\x86\x22\xdb\x00\x2e\xa7\x6e\x22";
static unsigned char enc_aes_192_ecb_sha256_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_sha256_out[] = "\xde\xc3\x9b\xd9\x03\xf6\xa5\x7c\x2b\x64\xa5\x29\xdb\x0e\x92\x16\xa3\xc7\x2a\x17\x21\xb7\x5d\x6a\x06\xad\xe8\x36\x05\x9a\xaf\xea";
static unsigned char enc_aes_192_ecb_sha384_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_sha384_out[] = "\x92\x11\x19\x68\xe9\xd1\x4f\x5a\x2d\xdc\x4f\x1f\xe7\xcf\xe0\x8e\xde\x82\x70\x72\x99\x34\xec\xae\x7a\x60\x93\xdd\x24\x8e\x7c\xe8\x11\x40\xec\x15\x48\x78\xed\xdf\x2c\x72\x01\x53\xf0\x01\x47\xbb";
static unsigned char enc_aes_192_ecb_sha512_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_sha512_out[] = "\x94\xb4\x47\x0c\x8a\x84\xfc\x2c\xd4\x52\xc9\x8b\xfd\x38\x02\x8e\x7c\x85\xac\xbe\x47\x4e\xec\x93\x30\x7c\xeb\x60\x38\xc6\x78\xf5\xc4\xd5\x46\xd3\x28\x1a\x91\xa3\x61\x2c\x3d\xfd\x72\x7a\xf5\x80\xb7\x69\xbb\x5d\x10\x78\xf7\x56\x02\xab\x26\x2c\xf6\x59\xe2\x83";
static unsigned char enc_aes_192_ecb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_192_ecb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_192_ecb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_192_ecb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_192_ecb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_192_ecb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_192_ecb_crc32_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_crc32_out[] = "\x93\x1a\x24\xf0";
static unsigned char enc_aes_192_ecb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_aes_128_xcbc_mac_96_out[] = "\x22\x66\x91\x06\x09\x17\x8f\x7f\x94\x8d\xaa\xd7\x2f\xf2\x7f\xe9";
static unsigned char enc_aes_192_ecb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_aes_192_xcbc_mac_96_out[] = "\x32\x1c\xd7\x2b\x7a\xe9\x33\xb5\x06\x43\xca\xf8\x30\x62\xbd\xeb";
static unsigned char enc_aes_192_ecb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_aes_256_xcbc_mac_96_out[] = "\x28\x3e\x31\x85\xe5\x06\x41\xc9\xad\xdc\x24\x42\x14\x34\x6f\x93";
static unsigned char enc_aes_192_ecb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_aes_128_xcbc_mac_prf_out[] = "\x22\x66\x91\x06\x09\x17\x8f\x7f\x94\x8d\xaa\xd7\x2f\xf2\x7f\xe9";
static unsigned char enc_aes_192_ecb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_aes_192_xcbc_mac_prf_out[] = "\x32\x1c\xd7\x2b\x7a\xe9\x33\xb5\x06\x43\xca\xf8\x30\x62\xbd\xeb";
static unsigned char enc_aes_192_ecb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_ecb_aes_256_xcbc_mac_prf_out[] = "\x28\x3e\x31\x85\xe5\x06\x41\xc9\xad\xdc\x24\x42\x14\x34\x6f\x93";
static unsigned char enc_aes_192_cbc_md5_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_md5_out[] = "\x58\x5f\xaa\xdf\xa4\xe1\x69\x92\xf9\xa9\x01\x67\xdc\x71\xcb\x78";
static unsigned char enc_aes_192_cbc_sha1_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_sha1_out[] = "\x26\x0a\x5e\x72\x9d\xc7\xef\x63\x02\xf6\xc9\x71\x05\xf9\x15\x71\x78\xab\xaf\x78";
static unsigned char enc_aes_192_cbc_sha224_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_sha224_out[] = "\xd5\x7f\x04\xce\x40\x1c\x8b\xa2\xdf\xbe\x5a\x29\xc8\xa0\x30\xb7\x3b\x33\xe3\xff\x23\x6a\x4e\x2e\x61\xae\x35\x9c";
static unsigned char enc_aes_192_cbc_sha256_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_sha256_out[] = "\x02\x7f\xfa\x7d\xc1\xcb\xd6\x2f\x97\x15\x85\x87\x08\x84\xf8\x09\x7e\xaf\x83\x6d\xa4\xc8\x29\x2f\xa0\x3b\xf0\x84\xc9\x15\x15\x5f";
static unsigned char enc_aes_192_cbc_sha384_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_sha384_out[] = "\xce\x36\x23\xd8\xca\x78\x04\x2d\x79\xe3\x2c\x1b\xed\x88\x42\x05\xac\x7a\xb6\x33\xbb\x61\x26\x2f\x8a\x41\x74\x6c\x02\x87\x4b\xde\x87\x63\x0a\xcc\x7f\x84\x3a\x3d\xc8\xc2\x36\x1f\x0c\x1b\x3e\x6d";
static unsigned char enc_aes_192_cbc_sha512_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_sha512_out[] = "\xd8\x8d\x17\xbd\x9c\x56\x39\x4b\xea\xe7\xdd\xda\xa8\xe3\x2a\x0e\xbd\xc1\xa3\xfe\x9c\xb3\xac\xc3\x03\xd4\x0d\x30\x46\x69\x25\xf8\x60\x7e\x44\x87\x1c\x3d\xed\x27\xaa\x5b\xf4\xcb\x99\x30\x18\x2c\x80\xa6\x2f\x8b\x14\x30\x48\xb6\xee\xd8\x48\xc6\x48\x64\x10\x25";
static unsigned char enc_aes_192_cbc_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_192_cbc_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_192_cbc_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_192_cbc_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_192_cbc_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_192_cbc_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_192_cbc_crc32_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_crc32_out[] = "\x69\x86\x6e\x05";
static unsigned char enc_aes_192_cbc_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_aes_128_xcbc_mac_96_out[] = "\xf7\x90\xb0\x06\xa4\x57\x47\x93\x21\x2c\xfa\x1b\xc7\xb1\x7d\xc8";
static unsigned char enc_aes_192_cbc_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_aes_192_xcbc_mac_96_out[] = "\x07\x15\x49\x87\x0f\xfa\x96\x84\x7d\x03\xf4\x5a\xc8\xdb\xb1\x08";
static unsigned char enc_aes_192_cbc_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_aes_256_xcbc_mac_96_out[] = "\x51\x5d\x44\x0c\x64\x2e\x7e\x49\x33\x0b\xcd\x14\x28\x02\xc4\x05";
static unsigned char enc_aes_192_cbc_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_aes_128_xcbc_mac_prf_out[] = "\xf7\x90\xb0\x06\xa4\x57\x47\x93\x21\x2c\xfa\x1b\xc7\xb1\x7d\xc8";
static unsigned char enc_aes_192_cbc_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_aes_192_xcbc_mac_prf_out[] = "\x07\x15\x49\x87\x0f\xfa\x96\x84\x7d\x03\xf4\x5a\xc8\xdb\xb1\x08";
static unsigned char enc_aes_192_cbc_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_cbc_aes_256_xcbc_mac_prf_out[] = "\x51\x5d\x44\x0c\x64\x2e\x7e\x49\x33\x0b\xcd\x14\x28\x02\xc4\x05";
static unsigned char enc_aes_192_ofb_md5_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_md5_out[] = "\x18\x6c\x91\xbd\x38\xa8\xfc\x75\xb9\x30\xf1\x35\xa8\xe6\x5c\xfb";
static unsigned char enc_aes_192_ofb_sha1_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_sha1_out[] = "\xe9\xa5\x67\x71\xf1\x2e\x31\xe3\x24\xca\x40\x83\x69\x89\xeb\xa8\x7c\x80\x8a\xb1";
static unsigned char enc_aes_192_ofb_sha224_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_sha224_out[] = "\x65\xf4\x34\x32\xaf\xf8\xbf\x30\xee\x25\x88\x16\x1d\x78\xd9\xcf\x4c\x4d\x11\x17\x1b\x7d\x2d\x5f\xfe\xa0\xc9\x77";
static unsigned char enc_aes_192_ofb_sha256_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_sha256_out[] = "\x83\xde\x1f\x20\x11\x88\x94\x2c\xef\x4f\x10\xe8\xe9\x7b\xb2\xfc\x52\x6c\xf9\x00\x99\xd5\xcb\x8e\xf1\xe9\x59\x31\x8f\x6f\xae\x88";
static unsigned char enc_aes_192_ofb_sha384_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_sha384_out[] = "\x7f\x6d\x29\xd6\x00\x52\xbb\xe5\x51\x98\x8f\xdb\x06\xd8\x37\xd4\xaf\x95\x7e\x0d\x9f\x5e\xf0\x27\xe5\xde\x21\x67\xdd\xe3\xf2\xab\xb6\x57\xaa\xaa\x5f\xb5\xbb\xfc\x58\xe2\xbe\x03\x18\xbd\x96\x55";
static unsigned char enc_aes_192_ofb_sha512_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_sha512_out[] = "\x4a\x28\xb8\x3f\xd7\x65\x9b\x30\x39\x91\x65\xe0\x29\x1d\x98\xcf\x42\x19\x31\xc9\xc3\x47\xc0\x1c\xe5\xef\xaf\x31\xc5\x27\xbb\xb3\x60\xd1\xc3\xa8\xe7\xf0\xf8\x18\x4e\xba\x9f\xc8\xea\x69\xf1\x2a\xb3\xff\x48\x7f\x5c\x61\x69\xe7\x4e\xbb\x29\xed\xa5\x8a\x36\xdb";
static unsigned char enc_aes_192_ofb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_192_ofb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_192_ofb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_192_ofb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_192_ofb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_192_ofb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_192_ofb_crc32_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_crc32_out[] = "\x48\xe1\xfc\xa4";
static unsigned char enc_aes_192_ofb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_aes_128_xcbc_mac_96_out[] = "\x03\x8a\x69\xbb\xcb\x07\x6d\x2e\x1f\x3e\x94\x3b\x8f\x82\x7a\xf8";
static unsigned char enc_aes_192_ofb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_aes_192_xcbc_mac_96_out[] = "\x50\x7b\x60\x6c\xfb\x74\xa1\x51\x55\x03\x34\x19\x50\xbd\x09\xfb";
static unsigned char enc_aes_192_ofb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_aes_256_xcbc_mac_96_out[] = "\xfe\x71\x54\x81\xf3\x38\x9f\xe5\x4c\xfa\xe7\xdd\x8b\xaf\x35\x07";
static unsigned char enc_aes_192_ofb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_aes_128_xcbc_mac_prf_out[] = "\x03\x8a\x69\xbb\xcb\x07\x6d\x2e\x1f\x3e\x94\x3b\x8f\x82\x7a\xf8";
static unsigned char enc_aes_192_ofb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_aes_192_xcbc_mac_prf_out[] = "\x50\x7b\x60\x6c\xfb\x74\xa1\x51\x55\x03\x34\x19\x50\xbd\x09\xfb";
static unsigned char enc_aes_192_ofb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_ofb_aes_256_xcbc_mac_prf_out[] = "\xfe\x71\x54\x81\xf3\x38\x9f\xe5\x4c\xfa\xe7\xdd\x8b\xaf\x35\x07";
static unsigned char enc_aes_192_cfb_md5_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_md5_out[] = "\x18\x6c\x91\xbd\x38\xa8\xfc\x75\xb9\x30\xf1\x35\xa8\xe6\x5c\xfb";
static unsigned char enc_aes_192_cfb_sha1_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_sha1_out[] = "\xe9\xa5\x67\x71\xf1\x2e\x31\xe3\x24\xca\x40\x83\x69\x89\xeb\xa8\x7c\x80\x8a\xb1";
static unsigned char enc_aes_192_cfb_sha224_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_sha224_out[] = "\x65\xf4\x34\x32\xaf\xf8\xbf\x30\xee\x25\x88\x16\x1d\x78\xd9\xcf\x4c\x4d\x11\x17\x1b\x7d\x2d\x5f\xfe\xa0\xc9\x77";
static unsigned char enc_aes_192_cfb_sha256_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_sha256_out[] = "\x83\xde\x1f\x20\x11\x88\x94\x2c\xef\x4f\x10\xe8\xe9\x7b\xb2\xfc\x52\x6c\xf9\x00\x99\xd5\xcb\x8e\xf1\xe9\x59\x31\x8f\x6f\xae\x88";
static unsigned char enc_aes_192_cfb_sha384_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_sha384_out[] = "\x7f\x6d\x29\xd6\x00\x52\xbb\xe5\x51\x98\x8f\xdb\x06\xd8\x37\xd4\xaf\x95\x7e\x0d\x9f\x5e\xf0\x27\xe5\xde\x21\x67\xdd\xe3\xf2\xab\xb6\x57\xaa\xaa\x5f\xb5\xbb\xfc\x58\xe2\xbe\x03\x18\xbd\x96\x55";
static unsigned char enc_aes_192_cfb_sha512_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_sha512_out[] = "\x4a\x28\xb8\x3f\xd7\x65\x9b\x30\x39\x91\x65\xe0\x29\x1d\x98\xcf\x42\x19\x31\xc9\xc3\x47\xc0\x1c\xe5\xef\xaf\x31\xc5\x27\xbb\xb3\x60\xd1\xc3\xa8\xe7\xf0\xf8\x18\x4e\xba\x9f\xc8\xea\x69\xf1\x2a\xb3\xff\x48\x7f\x5c\x61\x69\xe7\x4e\xbb\x29\xed\xa5\x8a\x36\xdb";
static unsigned char enc_aes_192_cfb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_192_cfb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_192_cfb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_192_cfb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_192_cfb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_192_cfb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_192_cfb_crc32_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_crc32_out[] = "\x48\xe1\xfc\xa4";
static unsigned char enc_aes_192_cfb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_aes_128_xcbc_mac_96_out[] = "\x03\x8a\x69\xbb\xcb\x07\x6d\x2e\x1f\x3e\x94\x3b\x8f\x82\x7a\xf8";
static unsigned char enc_aes_192_cfb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_aes_192_xcbc_mac_96_out[] = "\x50\x7b\x60\x6c\xfb\x74\xa1\x51\x55\x03\x34\x19\x50\xbd\x09\xfb";
static unsigned char enc_aes_192_cfb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_aes_256_xcbc_mac_96_out[] = "\xfe\x71\x54\x81\xf3\x38\x9f\xe5\x4c\xfa\xe7\xdd\x8b\xaf\x35\x07";
static unsigned char enc_aes_192_cfb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_aes_128_xcbc_mac_prf_out[] = "\x03\x8a\x69\xbb\xcb\x07\x6d\x2e\x1f\x3e\x94\x3b\x8f\x82\x7a\xf8";
static unsigned char enc_aes_192_cfb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_aes_192_xcbc_mac_prf_out[] = "\x50\x7b\x60\x6c\xfb\x74\xa1\x51\x55\x03\x34\x19\x50\xbd\x09\xfb";
static unsigned char enc_aes_192_cfb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_cfb_aes_256_xcbc_mac_prf_out[] = "\xfe\x71\x54\x81\xf3\x38\x9f\xe5\x4c\xfa\xe7\xdd\x8b\xaf\x35\x07";
static unsigned char enc_aes_192_ctr_md5_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_md5_out[] = "\x18\x6c\x91\xbd\x38\xa8\xfc\x75\xb9\x30\xf1\x35\xa8\xe6\x5c\xfb";
static unsigned char enc_aes_192_ctr_sha1_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_sha1_out[] = "\xe9\xa5\x67\x71\xf1\x2e\x31\xe3\x24\xca\x40\x83\x69\x89\xeb\xa8\x7c\x80\x8a\xb1";
static unsigned char enc_aes_192_ctr_sha224_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_sha224_out[] = "\x65\xf4\x34\x32\xaf\xf8\xbf\x30\xee\x25\x88\x16\x1d\x78\xd9\xcf\x4c\x4d\x11\x17\x1b\x7d\x2d\x5f\xfe\xa0\xc9\x77";
static unsigned char enc_aes_192_ctr_sha256_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_sha256_out[] = "\x83\xde\x1f\x20\x11\x88\x94\x2c\xef\x4f\x10\xe8\xe9\x7b\xb2\xfc\x52\x6c\xf9\x00\x99\xd5\xcb\x8e\xf1\xe9\x59\x31\x8f\x6f\xae\x88";
static unsigned char enc_aes_192_ctr_sha384_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_sha384_out[] = "\x7f\x6d\x29\xd6\x00\x52\xbb\xe5\x51\x98\x8f\xdb\x06\xd8\x37\xd4\xaf\x95\x7e\x0d\x9f\x5e\xf0\x27\xe5\xde\x21\x67\xdd\xe3\xf2\xab\xb6\x57\xaa\xaa\x5f\xb5\xbb\xfc\x58\xe2\xbe\x03\x18\xbd\x96\x55";
static unsigned char enc_aes_192_ctr_sha512_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_sha512_out[] = "\x4a\x28\xb8\x3f\xd7\x65\x9b\x30\x39\x91\x65\xe0\x29\x1d\x98\xcf\x42\x19\x31\xc9\xc3\x47\xc0\x1c\xe5\xef\xaf\x31\xc5\x27\xbb\xb3\x60\xd1\xc3\xa8\xe7\xf0\xf8\x18\x4e\xba\x9f\xc8\xea\x69\xf1\x2a\xb3\xff\x48\x7f\x5c\x61\x69\xe7\x4e\xbb\x29\xed\xa5\x8a\x36\xdb";
static unsigned char enc_aes_192_ctr_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_192_ctr_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_192_ctr_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_192_ctr_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_192_ctr_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_192_ctr_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_192_ctr_crc32_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_crc32_out[] = "\x48\xe1\xfc\xa4";
static unsigned char enc_aes_192_ctr_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_aes_128_xcbc_mac_96_out[] = "\x03\x8a\x69\xbb\xcb\x07\x6d\x2e\x1f\x3e\x94\x3b\x8f\x82\x7a\xf8";
static unsigned char enc_aes_192_ctr_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_aes_192_xcbc_mac_96_out[] = "\x50\x7b\x60\x6c\xfb\x74\xa1\x51\x55\x03\x34\x19\x50\xbd\x09\xfb";
static unsigned char enc_aes_192_ctr_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_aes_256_xcbc_mac_96_out[] = "\xfe\x71\x54\x81\xf3\x38\x9f\xe5\x4c\xfa\xe7\xdd\x8b\xaf\x35\x07";
static unsigned char enc_aes_192_ctr_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_aes_128_xcbc_mac_prf_out[] = "\x03\x8a\x69\xbb\xcb\x07\x6d\x2e\x1f\x3e\x94\x3b\x8f\x82\x7a\xf8";
static unsigned char enc_aes_192_ctr_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_aes_192_xcbc_mac_prf_out[] = "\x50\x7b\x60\x6c\xfb\x74\xa1\x51\x55\x03\x34\x19\x50\xbd\x09\xfb";
static unsigned char enc_aes_192_ctr_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_192_ctr_aes_256_xcbc_mac_prf_out[] = "\xfe\x71\x54\x81\xf3\x38\x9f\xe5\x4c\xfa\xe7\xdd\x8b\xaf\x35\x07";
static unsigned char enc_aes_192_icm_md5_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_md5_out[] = "\x04\xdc\xb2\x21\x3e\x42\x10\x54\x61\x1b\x4b\xe4\xb0\x13\x67\x57";
static unsigned char enc_aes_192_icm_sha1_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_sha1_out[] = "\x1c\x9f\x1a\x24\x24\xd8\xd2\x66\x5a\x67\x1b\x3d\x12\x24\xba\xed\x62\x72\x05\xd0";
static unsigned char enc_aes_192_icm_sha224_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_sha224_out[] = "\x7a\xd4\x7a\x4d\xa3\xcd\xdf\x1a\xd7\xc8\xba\x60\xe0\x01\x67\x3f\x94\x1d\xb4\x17\x63\x88\xdc\x0f\x41\x8d\xa5\x55";
static unsigned char enc_aes_192_icm_sha256_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_sha256_out[] = "\xf7\xb2\x93\xa8\x43\x3a\xc7\x08\xbe\x60\x5c\x72\xd9\x4f\x6c\x91\xf8\x03\x9a\x76\x07\x40\xd4\x72\x42\xf6\x85\x6d\xd6\x2a\x5e\x85";
static unsigned char enc_aes_192_icm_sha384_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_sha384_out[] = "\xb7\xb0\x8e\x15\x93\x7b\xbc\x3b\x70\x80\xfd\x80\xd0\x0c\x2a\xdd\x3c\x2a\xa0\xcc\x06\xfa\x5f\x2d\x5f\xba\x91\xe4\x40\x64\x04\xe2\x40\xfe\x02\x71\xfe\x7b\xc0\xcc\xd1\xe4\x39\xb9\x46\x09\xd1\x0b";
static unsigned char enc_aes_192_icm_sha512_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_sha512_out[] = "\xb3\x64\x03\x02\x35\x3a\x98\x18\xd8\x74\x46\x83\xc8\xf6\xf6\xba\x64\xd2\x3c\x08\xc1\xcc\x5c\xcb\x6a\x71\x43\x89\xf9\xa8\x8f\x08\x2f\x64\x27\xf7\x2e\xa8\x93\xbf\xe8\x8e\x1d\xea\xc4\x96\x91\xd3\xa7\xe0\x7f\x5e\x1d\x0d\x20\x75\x72\x0b\xad\x97\xd2\x69\x57\xa3";
static unsigned char enc_aes_192_icm_md5_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_192_icm_sha1_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_192_icm_sha224_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_192_icm_sha256_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_192_icm_sha384_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_192_icm_sha512_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_192_icm_crc32_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_crc32_out[] = "\xb8\x58\x0f\x29";
static unsigned char enc_aes_192_icm_aes_128_xcbc_mac_96_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_aes_128_xcbc_mac_96_out[] = "\xf4\xd8\x1d\xe0\x68\x71\x19\xb3\x1e\x12\x41\x93\x08\xb5\xe1\x56";
static unsigned char enc_aes_192_icm_aes_192_xcbc_mac_96_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_aes_192_xcbc_mac_96_out[] = "\x30\xa2\x60\x44\x70\xf7\x08\x03\xef\xae\x08\x4c\x84\x23\xd6\x69";
static unsigned char enc_aes_192_icm_aes_256_xcbc_mac_96_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_aes_256_xcbc_mac_96_out[] = "\x47\xd3\x73\x6f\xcb\xe0\x68\xd5\x56\x9a\x61\xb4\xe0\x85\x3a\x46";
static unsigned char enc_aes_192_icm_aes_128_xcbc_mac_prf_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_aes_128_xcbc_mac_prf_out[] = "\xf4\xd8\x1d\xe0\x68\x71\x19\xb3\x1e\x12\x41\x93\x08\xb5\xe1\x56";
static unsigned char enc_aes_192_icm_aes_192_xcbc_mac_prf_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_aes_192_xcbc_mac_prf_out[] = "\x30\xa2\x60\x44\x70\xf7\x08\x03\xef\xae\x08\x4c\x84\x23\xd6\x69";
static unsigned char enc_aes_192_icm_aes_256_xcbc_mac_prf_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_192_icm_aes_256_xcbc_mac_prf_out[] = "\x47\xd3\x73\x6f\xcb\xe0\x68\xd5\x56\x9a\x61\xb4\xe0\x85\x3a\x46";
static unsigned char enc_aes_256_ecb_md5_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_md5_out[] = "\xbd\xcf\x46\xdb\xb3\xe0\xb0\x7f\x8a\x00\x34\x8d\x67\x0a\x2f\xd8";
static unsigned char enc_aes_256_ecb_sha1_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_sha1_out[] = "\xce\x2c\xbf\xa0\x00\x33\x12\xa1\xfd\x46\xba\xb2\x10\x93\x82\xae\x8e\x16\x34\x52";
static unsigned char enc_aes_256_ecb_sha224_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_sha224_out[] = "\xb4\x36\xf3\xd2\x05\x57\xa3\x80\x40\x88\xf6\x7e\x71\x6e\x92\x11\x70\xeb\xd0\xc5\x20\x4f\xaa\xb7\x55\xcb\x1d\x18";
static unsigned char enc_aes_256_ecb_sha256_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_sha256_out[] = "\xb7\x07\x7b\x26\xcb\xa4\xf9\xd4\x20\x5f\x0f\x73\x20\xb4\xf2\xba\x97\xac\x77\xae\x7b\x82\x1d\xb3\x6f\x84\xab\xce\x32\xde\xaf\xdf";
static unsigned char enc_aes_256_ecb_sha384_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_sha384_out[] = "\x2f\x1e\x05\xe6\x19\x64\x9b\xeb\xd4\xac\x96\xe1\xf5\xd6\x64\xe0\xcd\x51\x5c\x61\xda\xe8\x07\x67\x53\xd5\xa2\xf5\x2d\x30\x4f\xeb\x50\x10\x9f\x9a\xa3\x67\x4d\x53\x46\x7f\xbc\xce\x70\x72\x26\x0e";
static unsigned char enc_aes_256_ecb_sha512_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_sha512_out[] = "\xbc\x71\x3b\x2a\x32\xe9\xd0\x5d\xae\x21\xb4\x0b\xa7\xc5\xee\x28\xa7\xf5\x91\x51\x99\x44\xa6\x72\x49\x31\x37\xf1\xd0\xe6\x19\x6a\xad\x15\x7b\x2a\x7e\x26\xef\x45\x52\xa3\x3c\xf1\xba\x89\x18\x4e\xce\x14\x66\x8d\xa8\xc5\x3f\xa2\x87\x7e\x1f\x11\x88\x2a\x07\x10";
static unsigned char enc_aes_256_ecb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_256_ecb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_256_ecb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_256_ecb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_256_ecb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_256_ecb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_256_ecb_crc32_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_crc32_out[] = "\x9e\xe2\x91\x43";
static unsigned char enc_aes_256_ecb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_aes_128_xcbc_mac_96_out[] = "\x08\x36\x4e\x5d\x15\x60\xd7\x5a\x26\x29\x8d\x7f\x1f\x44\x35\xbd";
static unsigned char enc_aes_256_ecb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_aes_192_xcbc_mac_96_out[] = "\xb2\x92\x19\x73\xf3\x4f\xc6\xa3\xd0\x0a\x37\x45\x35\x30\xff\x9e";
static unsigned char enc_aes_256_ecb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_aes_256_xcbc_mac_96_out[] = "\xa1\x5f\x77\x81\x27\x9f\x47\xb0\x86\xae\x5d\xf6\xfe\x69\x04\x2c";
static unsigned char enc_aes_256_ecb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_aes_128_xcbc_mac_prf_out[] = "\x08\x36\x4e\x5d\x15\x60\xd7\x5a\x26\x29\x8d\x7f\x1f\x44\x35\xbd";
static unsigned char enc_aes_256_ecb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_aes_192_xcbc_mac_prf_out[] = "\xb2\x92\x19\x73\xf3\x4f\xc6\xa3\xd0\x0a\x37\x45\x35\x30\xff\x9e";
static unsigned char enc_aes_256_ecb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_ecb_aes_256_xcbc_mac_prf_out[] = "\xa1\x5f\x77\x81\x27\x9f\x47\xb0\x86\xae\x5d\xf6\xfe\x69\x04\x2c";
static unsigned char enc_aes_256_cbc_md5_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_md5_out[] = "\x35\xcf\x4e\xc2\xb3\x82\xa3\x79\xda\x34\x13\x6e\xab\xee\xe0\x4c";
static unsigned char enc_aes_256_cbc_sha1_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_sha1_out[] = "\xe6\x8d\x7c\xda\x2c\x45\x93\x51\x35\xb7\xd8\xe3\xb0\x66\x68\xc6\x80\xd1\xc2\x4c";
static unsigned char enc_aes_256_cbc_sha224_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_sha224_out[] = "\xa8\x7f\x55\xe5\xe1\x66\x73\xef\x44\xd1\xa5\x95\x41\x44\x0d\x05\x31\x4b\x91\xa0\x76\x9b\x91\x45\x4a\x3f\xa4\x90";
static unsigned char enc_aes_256_cbc_sha256_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_sha256_out[] = "\x67\x10\xc3\x88\x6e\x08\xec\xc8\x4c\x22\x85\xb7\xe9\x2f\x8c\xbd\x14\x90\xa9\xb3\xf6\xf5\xb2\x37\x46\xff\x95\x1a\xc2\x43\xbe\x60";
static unsigned char enc_aes_256_cbc_sha384_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_sha384_out[] = "\x01\xcb\xc1\xe7\x4c\xbf\x5c\xed\x58\x79\x64\x38\x9d\xe8\x14\xdd\x86\x0e\xff\xe2\x7b\x91\xe9\x22\x6c\x03\x10\x94\x92\xac\xe4\x7d\xe4\xe0\xc8\x6d\x5d\x1d\xf3\x3a\x48\xa0\x14\x43\xab\x4b\xa9\x29";
static unsigned char enc_aes_256_cbc_sha512_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_sha512_out[] = "\x12\x62\xdf\xc6\x96\xda\xdb\x81\x11\x45\x0f\xa2\x88\x06\xdc\x50\xc5\xf5\xa3\x68\xc2\x63\xb8\xf8\xb0\x1d\x72\x9c\x56\xf6\xe1\x24\xa4\xae\xa4\xdc\xcc\x54\xe7\x8d\x14\x8a\xd9\xa0\xff\xb8\x3e\x16\xac\x01\xca\x41\x83\x94\x26\xf1\x88\x64\x44\x40\x58\xd0\xb6\x7e";
static unsigned char enc_aes_256_cbc_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_256_cbc_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_256_cbc_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_256_cbc_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_256_cbc_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_256_cbc_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_256_cbc_crc32_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_crc32_out[] = "\x56\x2d\x57\x86";
static unsigned char enc_aes_256_cbc_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_aes_128_xcbc_mac_96_out[] = "\x7c\x05\x5e\xb7\x09\x7b\x08\xb8\x37\xd5\x32\x2d\x07\xe8\xd0\xba";
static unsigned char enc_aes_256_cbc_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_aes_192_xcbc_mac_96_out[] = "\x50\xfb\x15\x8d\xf2\x67\x31\xb6\x43\x98\x9b\x45\x14\xbb\xb0\x3f";
static unsigned char enc_aes_256_cbc_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_aes_256_xcbc_mac_96_out[] = "\x3e\xb8\x84\x37\x99\x23\x55\x46\xd7\x31\x08\x39\x65\x8c\x29\x6b";
static unsigned char enc_aes_256_cbc_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_aes_128_xcbc_mac_prf_out[] = "\x7c\x05\x5e\xb7\x09\x7b\x08\xb8\x37\xd5\x32\x2d\x07\xe8\xd0\xba";
static unsigned char enc_aes_256_cbc_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_aes_192_xcbc_mac_prf_out[] = "\x50\xfb\x15\x8d\xf2\x67\x31\xb6\x43\x98\x9b\x45\x14\xbb\xb0\x3f";
static unsigned char enc_aes_256_cbc_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_cbc_aes_256_xcbc_mac_prf_out[] = "\x3e\xb8\x84\x37\x99\x23\x55\x46\xd7\x31\x08\x39\x65\x8c\x29\x6b";
static unsigned char enc_aes_256_ofb_md5_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_md5_out[] = "\xaa\xc1\x32\x6d\xc5\xd3\x6a\x1a\xea\x18\x19\xb1\x87\x88\xd7\x74";
static unsigned char enc_aes_256_ofb_sha1_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_sha1_out[] = "\x31\x7d\x7e\xa8\x20\xc6\xf0\xaf\x82\x39\x6f\xaf\xc9\xc0\x6c\xf1\x07\x10\x76\x05";
static unsigned char enc_aes_256_ofb_sha224_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_sha224_out[] = "\xba\x13\x72\xc7\xec\xff\x04\x60\xef\xad\x16\xf2\xf2\x7f\x8a\x75\xfa\x59\xc1\x1b\xf8\xf4\x0d\x22\x3f\xc7\xb6\x02";
static unsigned char enc_aes_256_ofb_sha256_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_sha256_out[] = "\xb7\x60\x14\xd3\x21\x50\xb3\x7b\xb5\x94\x00\xe9\xff\x08\x8a\x2a\x30\x61\xa2\xd4\xa0\x55\x68\x77\x0b\xeb\x6d\xd2\x3f\x05\x0f\xf4";
static unsigned char enc_aes_256_ofb_sha384_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_sha384_out[] = "\x21\xcc\xef\xc9\x62\x3a\x72\x1a\xf2\x38\x97\x81\x57\x7e\xc2\x10\x00\x57\xf0\xff\x96\x91\x27\xce\x3e\xd2\x12\x37\x56\xf4\x59\xee\xc2\x25\x6d\x9a\x56\x42\xc2\xc8\x0e\x3c\x7c\xa8\xef\x92\x76\xf3";
static unsigned char enc_aes_256_ofb_sha512_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_sha512_out[] = "\xcb\xcf\x2d\xd2\x57\x4a\xb3\x1d\xf6\x68\xd5\x5b\x8b\xcf\x53\x8a\x71\xe6\xdb\x54\xa1\x33\x49\x70\x00\xe2\x43\xfe\xd1\xa0\xb9\xc1\x0b\xd7\xdb\x39\x34\x3a\x8e\x3c\x7e\xbd\x01\x7e\x28\x10\x42\xa6\xcc\x83\xf8\x12\x23\x0c\x49\xc4\x48\xe8\x85\x8d\xe3\x08\x58\x82";
static unsigned char enc_aes_256_ofb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_256_ofb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_256_ofb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_256_ofb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_256_ofb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_256_ofb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_256_ofb_crc32_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_crc32_out[] = "\x5b\x1f\x8c\x12";
static unsigned char enc_aes_256_ofb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_aes_128_xcbc_mac_96_out[] = "\x8a\x66\x71\x29\x56\x31\xb6\xb1\x21\x49\xed\x18\x12\x50\xfa\x16";
static unsigned char enc_aes_256_ofb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_aes_192_xcbc_mac_96_out[] = "\x4d\x90\x53\xfd\x39\x7f\xc2\xf2\x9d\xff\x7d\xe0\x16\x1d\xff\x7a";
static unsigned char enc_aes_256_ofb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_aes_256_xcbc_mac_96_out[] = "\x22\xc6\x03\xe6\x94\x21\xf8\x03\x47\xca\xfc\x80\xc1\x3f\x81\xca";
static unsigned char enc_aes_256_ofb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_aes_128_xcbc_mac_prf_out[] = "\x8a\x66\x71\x29\x56\x31\xb6\xb1\x21\x49\xed\x18\x12\x50\xfa\x16";
static unsigned char enc_aes_256_ofb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_aes_192_xcbc_mac_prf_out[] = "\x4d\x90\x53\xfd\x39\x7f\xc2\xf2\x9d\xff\x7d\xe0\x16\x1d\xff\x7a";
static unsigned char enc_aes_256_ofb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_ofb_aes_256_xcbc_mac_prf_out[] = "\x22\xc6\x03\xe6\x94\x21\xf8\x03\x47\xca\xfc\x80\xc1\x3f\x81\xca";
static unsigned char enc_aes_256_cfb_md5_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_md5_out[] = "\xaa\xc1\x32\x6d\xc5\xd3\x6a\x1a\xea\x18\x19\xb1\x87\x88\xd7\x74";
static unsigned char enc_aes_256_cfb_sha1_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_sha1_out[] = "\x31\x7d\x7e\xa8\x20\xc6\xf0\xaf\x82\x39\x6f\xaf\xc9\xc0\x6c\xf1\x07\x10\x76\x05";
static unsigned char enc_aes_256_cfb_sha224_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_sha224_out[] = "\xba\x13\x72\xc7\xec\xff\x04\x60\xef\xad\x16\xf2\xf2\x7f\x8a\x75\xfa\x59\xc1\x1b\xf8\xf4\x0d\x22\x3f\xc7\xb6\x02";
static unsigned char enc_aes_256_cfb_sha256_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_sha256_out[] = "\xb7\x60\x14\xd3\x21\x50\xb3\x7b\xb5\x94\x00\xe9\xff\x08\x8a\x2a\x30\x61\xa2\xd4\xa0\x55\x68\x77\x0b\xeb\x6d\xd2\x3f\x05\x0f\xf4";
static unsigned char enc_aes_256_cfb_sha384_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_sha384_out[] = "\x21\xcc\xef\xc9\x62\x3a\x72\x1a\xf2\x38\x97\x81\x57\x7e\xc2\x10\x00\x57\xf0\xff\x96\x91\x27\xce\x3e\xd2\x12\x37\x56\xf4\x59\xee\xc2\x25\x6d\x9a\x56\x42\xc2\xc8\x0e\x3c\x7c\xa8\xef\x92\x76\xf3";
static unsigned char enc_aes_256_cfb_sha512_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_sha512_out[] = "\xcb\xcf\x2d\xd2\x57\x4a\xb3\x1d\xf6\x68\xd5\x5b\x8b\xcf\x53\x8a\x71\xe6\xdb\x54\xa1\x33\x49\x70\x00\xe2\x43\xfe\xd1\xa0\xb9\xc1\x0b\xd7\xdb\x39\x34\x3a\x8e\x3c\x7e\xbd\x01\x7e\x28\x10\x42\xa6\xcc\x83\xf8\x12\x23\x0c\x49\xc4\x48\xe8\x85\x8d\xe3\x08\x58\x82";
static unsigned char enc_aes_256_cfb_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_256_cfb_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_256_cfb_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_256_cfb_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_256_cfb_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_256_cfb_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_256_cfb_crc32_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_crc32_out[] = "\x5b\x1f\x8c\x12";
static unsigned char enc_aes_256_cfb_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_aes_128_xcbc_mac_96_out[] = "\x8a\x66\x71\x29\x56\x31\xb6\xb1\x21\x49\xed\x18\x12\x50\xfa\x16";
static unsigned char enc_aes_256_cfb_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_aes_192_xcbc_mac_96_out[] = "\x4d\x90\x53\xfd\x39\x7f\xc2\xf2\x9d\xff\x7d\xe0\x16\x1d\xff\x7a";
static unsigned char enc_aes_256_cfb_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_aes_256_xcbc_mac_96_out[] = "\x22\xc6\x03\xe6\x94\x21\xf8\x03\x47\xca\xfc\x80\xc1\x3f\x81\xca";
static unsigned char enc_aes_256_cfb_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_aes_128_xcbc_mac_prf_out[] = "\x8a\x66\x71\x29\x56\x31\xb6\xb1\x21\x49\xed\x18\x12\x50\xfa\x16";
static unsigned char enc_aes_256_cfb_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_aes_192_xcbc_mac_prf_out[] = "\x4d\x90\x53\xfd\x39\x7f\xc2\xf2\x9d\xff\x7d\xe0\x16\x1d\xff\x7a";
static unsigned char enc_aes_256_cfb_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_cfb_aes_256_xcbc_mac_prf_out[] = "\x22\xc6\x03\xe6\x94\x21\xf8\x03\x47\xca\xfc\x80\xc1\x3f\x81\xca";
static unsigned char enc_aes_256_ctr_md5_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_md5_out[] = "\xaa\xc1\x32\x6d\xc5\xd3\x6a\x1a\xea\x18\x19\xb1\x87\x88\xd7\x74";
static unsigned char enc_aes_256_ctr_sha1_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_sha1_out[] = "\x31\x7d\x7e\xa8\x20\xc6\xf0\xaf\x82\x39\x6f\xaf\xc9\xc0\x6c\xf1\x07\x10\x76\x05";
static unsigned char enc_aes_256_ctr_sha224_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_sha224_out[] = "\xba\x13\x72\xc7\xec\xff\x04\x60\xef\xad\x16\xf2\xf2\x7f\x8a\x75\xfa\x59\xc1\x1b\xf8\xf4\x0d\x22\x3f\xc7\xb6\x02";
static unsigned char enc_aes_256_ctr_sha256_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_sha256_out[] = "\xb7\x60\x14\xd3\x21\x50\xb3\x7b\xb5\x94\x00\xe9\xff\x08\x8a\x2a\x30\x61\xa2\xd4\xa0\x55\x68\x77\x0b\xeb\x6d\xd2\x3f\x05\x0f\xf4";
static unsigned char enc_aes_256_ctr_sha384_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_sha384_out[] = "\x21\xcc\xef\xc9\x62\x3a\x72\x1a\xf2\x38\x97\x81\x57\x7e\xc2\x10\x00\x57\xf0\xff\x96\x91\x27\xce\x3e\xd2\x12\x37\x56\xf4\x59\xee\xc2\x25\x6d\x9a\x56\x42\xc2\xc8\x0e\x3c\x7c\xa8\xef\x92\x76\xf3";
static unsigned char enc_aes_256_ctr_sha512_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_sha512_out[] = "\xcb\xcf\x2d\xd2\x57\x4a\xb3\x1d\xf6\x68\xd5\x5b\x8b\xcf\x53\x8a\x71\xe6\xdb\x54\xa1\x33\x49\x70\x00\xe2\x43\xfe\xd1\xa0\xb9\xc1\x0b\xd7\xdb\x39\x34\x3a\x8e\x3c\x7e\xbd\x01\x7e\x28\x10\x42\xa6\xcc\x83\xf8\x12\x23\x0c\x49\xc4\x48\xe8\x85\x8d\xe3\x08\x58\x82";
static unsigned char enc_aes_256_ctr_md5_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_256_ctr_sha1_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_256_ctr_sha224_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_256_ctr_sha256_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_256_ctr_sha384_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_256_ctr_sha512_hmac_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_256_ctr_crc32_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_crc32_out[] = "\x5b\x1f\x8c\x12";
static unsigned char enc_aes_256_ctr_aes_128_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_aes_128_xcbc_mac_96_out[] = "\x8a\x66\x71\x29\x56\x31\xb6\xb1\x21\x49\xed\x18\x12\x50\xfa\x16";
static unsigned char enc_aes_256_ctr_aes_192_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_aes_192_xcbc_mac_96_out[] = "\x4d\x90\x53\xfd\x39\x7f\xc2\xf2\x9d\xff\x7d\xe0\x16\x1d\xff\x7a";
static unsigned char enc_aes_256_ctr_aes_256_xcbc_mac_96_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_aes_256_xcbc_mac_96_out[] = "\x22\xc6\x03\xe6\x94\x21\xf8\x03\x47\xca\xfc\x80\xc1\x3f\x81\xca";
static unsigned char enc_aes_256_ctr_aes_128_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_aes_128_xcbc_mac_prf_out[] = "\x8a\x66\x71\x29\x56\x31\xb6\xb1\x21\x49\xed\x18\x12\x50\xfa\x16";
static unsigned char enc_aes_256_ctr_aes_192_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_aes_192_xcbc_mac_prf_out[] = "\x4d\x90\x53\xfd\x39\x7f\xc2\xf2\x9d\xff\x7d\xe0\x16\x1d\xff\x7a";
static unsigned char enc_aes_256_ctr_aes_256_xcbc_mac_prf_in[] = "Single block msg";
static unsigned char enc_aes_256_ctr_aes_256_xcbc_mac_prf_out[] = "\x22\xc6\x03\xe6\x94\x21\xf8\x03\x47\xca\xfc\x80\xc1\x3f\x81\xca";
static unsigned char enc_aes_256_icm_md5_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_md5_out[] = "\xbb\x98\xc9\x36\x85\x09\xe8\x5d\x5e\x37\x93\x5d\xc0\xd4\xc2\x65";
static unsigned char enc_aes_256_icm_sha1_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_sha1_out[] = "\x05\xca\x27\xb1\xb1\xe9\x6d\x23\x9f\x61\x91\x22\x07\x8e\x34\x09\x8e\x27\x42\xd0";
static unsigned char enc_aes_256_icm_sha224_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_sha224_out[] = "\xd9\xe1\xc4\xad\xb1\xc1\xac\x23\x29\x47\x17\x49\x40\xc1\x4a\xdd\x36\x3a\x44\x20\x7a\xfc\x66\x45\xd0\xcb\x1e\xcf";
static unsigned char enc_aes_256_icm_sha256_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_sha256_out[] = "\xff\x6e\xad\x50\xa9\xbe\x79\x47\x0a\x2f\x1b\x75\xf3\xa4\xea\x79\xad\xa9\x6d\xb3\xe5\x8b\x35\x77\x2f\xb3\x20\xfb\x1f\x38\xca\xcd";
static unsigned char enc_aes_256_icm_sha384_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_sha384_out[] = "\x64\x23\x84\x85\x74\x64\x2f\x49\x5e\x23\x73\xee\x48\x83\x5f\x7a\xcc\x4d\x5f\x46\x5b\xf1\x1a\xd5\x5a\x78\x18\xff\xa5\x48\x62\xc2\x39\xbc\x42\x6e\x24\x0c\xf4\x9b\x19\x55\xa6\xe7\x3c\xeb\x25\x2b";
static unsigned char enc_aes_256_icm_sha512_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_sha512_out[] = "\x3f\x20\x01\xa9\xdf\xaa\xdf\x0f\x7b\x72\x2e\x29\xee\x0e\xea\xf2\x69\x3a\xe0\xef\x15\xd2\x56\x08\x17\x36\xc6\xc3\xa1\x7a\x4c\x92\x42\x93\xd2\x55\xd3\x15\xfb\x35\xed\xb1\x20\x77\x71\x69\x22\x79\x4e\x7e\xde\x3d\x7c\xc3\xfb\x95\xb3\x32\xe6\x2c\x94\xd5\xb5\x1c";
static unsigned char enc_aes_256_icm_md5_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_md5_hmac_out[] = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38";
static unsigned char enc_aes_256_icm_sha1_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_sha1_hmac_out[] = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79";
static unsigned char enc_aes_256_icm_sha224_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_sha224_hmac_out[] = "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44";
static unsigned char enc_aes_256_icm_sha256_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_sha256_hmac_out[] = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43";
static unsigned char enc_aes_256_icm_sha384_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_sha384_hmac_out[] = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49";
static unsigned char enc_aes_256_icm_sha512_hmac_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_sha512_hmac_out[] = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37";
static unsigned char enc_aes_256_icm_crc32_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_crc32_out[] = "\x83\xf6\xcf\x04";
static unsigned char enc_aes_256_icm_aes_128_xcbc_mac_96_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_aes_128_xcbc_mac_96_out[] = "\x62\x78\x35\x48\xf5\xd1\xba\x69\x9a\x44\xd3\xee\x05\xb5\x60\xbd";
static unsigned char enc_aes_256_icm_aes_192_xcbc_mac_96_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_aes_192_xcbc_mac_96_out[] = "\x31\x80\xfb\x0b\x8f\x8c\x0a\x7e\x5c\x7c\x56\xf2\x3e\x4a\xc7\xb7";
static unsigned char enc_aes_256_icm_aes_256_xcbc_mac_96_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_aes_256_xcbc_mac_96_out[] = "\x2c\xd0\x4d\xa4\xbb\xed\x9e\x00\xff\xf7\xdf\xe3\xea\x38\x0c\x56";
static unsigned char enc_aes_256_icm_aes_128_xcbc_mac_prf_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_aes_128_xcbc_mac_prf_out[] = "\x62\x78\x35\x48\xf5\xd1\xba\x69\x9a\x44\xd3\xee\x05\xb5\x60\xbd";
static unsigned char enc_aes_256_icm_aes_192_xcbc_mac_prf_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_aes_192_xcbc_mac_prf_out[] = "\x31\x80\xfb\x0b\x8f\x8c\x0a\x7e\x5c\x7c\x56\xf2\x3e\x4a\xc7\xb7";
static unsigned char enc_aes_256_icm_aes_256_xcbc_mac_prf_in[] = "0000000000000000000000000000000000000000000000000000000000000000";
static unsigned char enc_aes_256_icm_aes_256_xcbc_mac_prf_out[] = "\x2c\xd0\x4d\xa4\xbb\xed\x9e\x00\xff\xf7\xdf\xe3\xea\x38\x0c\x56";
struct combined enc_hash_data[] = {
{"des-ecb",enc_des_ecb_md5_in,des_ecb_key_hex,NULL,NULL,NULL,"md5",NULL,enc_des_ecb_md5_out,},
{"des-ecb",enc_des_ecb_sha1_in,des_ecb_key_hex,NULL,NULL,NULL,"sha1",NULL,enc_des_ecb_sha1_out,},
{"des-ecb",enc_des_ecb_sha224_in,des_ecb_key_hex,NULL,NULL,NULL,"sha224",NULL,enc_des_ecb_sha224_out,},
{"des-ecb",enc_des_ecb_sha256_in,des_ecb_key_hex,NULL,NULL,NULL,"sha256",NULL,enc_des_ecb_sha256_out,},
{"des-ecb",enc_des_ecb_sha384_in,des_ecb_key_hex,NULL,NULL,NULL,"sha384",NULL,enc_des_ecb_sha384_out,},
{"des-ecb",enc_des_ecb_sha512_in,des_ecb_key_hex,NULL,NULL,NULL,"sha512",NULL,enc_des_ecb_sha512_out,},
{"des-ecb",enc_des_ecb_crc32_in,des_ecb_key_hex,NULL,NULL,NULL,"crc32",NULL,enc_des_ecb_crc32_out,},
{"des-ecb",enc_des_ecb_md5_hmac_in,des_ecb_key_hex,NULL,NULL,NULL,"md5-hmac",md5_hmac_key,enc_des_ecb_md5_hmac_out,},
{"des-ecb",enc_des_ecb_sha1_hmac_in,des_ecb_key_hex,NULL,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_des_ecb_sha1_hmac_out,},
{"des-ecb",enc_des_ecb_sha224_hmac_in,des_ecb_key_hex,NULL,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_des_ecb_sha224_hmac_out,},
{"des-ecb",enc_des_ecb_sha256_hmac_in,des_ecb_key_hex,NULL,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_des_ecb_sha256_hmac_out,},
{"des-ecb",enc_des_ecb_sha384_hmac_in,des_ecb_key_hex,NULL,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_des_ecb_sha384_hmac_out,},
{"des-ecb",enc_des_ecb_sha512_hmac_in,des_ecb_key_hex,NULL,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_des_ecb_sha512_hmac_out,},
{"des-ecb",enc_des_ecb_aes_128_xcbc_mac_96_in,des_ecb_key_hex,NULL,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_des_ecb_aes_128_xcbc_mac_96_out,},
{"des-ecb",enc_des_ecb_aes_192_xcbc_mac_96_in,des_ecb_key_hex,NULL,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_des_ecb_aes_192_xcbc_mac_96_out,},
{"des-ecb",enc_des_ecb_aes_256_xcbc_mac_96_in,des_ecb_key_hex,NULL,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_des_ecb_aes_256_xcbc_mac_96_out,},
{"des-ecb",enc_des_ecb_aes_128_xcbc_mac_prf_in,des_ecb_key_hex,NULL,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_des_ecb_aes_128_xcbc_mac_prf_out,},
{"des-ecb",enc_des_ecb_aes_192_xcbc_mac_prf_in,des_ecb_key_hex,NULL,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_des_ecb_aes_192_xcbc_mac_prf_out,},
{"des-ecb",enc_des_ecb_aes_256_xcbc_mac_prf_in,des_ecb_key_hex,NULL,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_des_ecb_aes_256_xcbc_mac_prf_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_md5_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"md5",NULL,enc_des_ede3_ecb_md5_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_sha1_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"sha1",NULL,enc_des_ede3_ecb_sha1_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_sha224_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"sha224",NULL,enc_des_ede3_ecb_sha224_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_sha256_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"sha256",NULL,enc_des_ede3_ecb_sha256_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_sha384_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"sha384",NULL,enc_des_ede3_ecb_sha384_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_sha512_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"sha512",NULL,enc_des_ede3_ecb_sha512_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_crc32_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"crc32",NULL,enc_des_ede3_ecb_crc32_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_md5_hmac_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"md5-hmac",md5_hmac_key,enc_des_ede3_ecb_md5_hmac_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_sha1_hmac_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_des_ede3_ecb_sha1_hmac_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_sha224_hmac_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_des_ede3_ecb_sha224_hmac_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_sha256_hmac_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_des_ede3_ecb_sha256_hmac_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_sha384_hmac_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_des_ede3_ecb_sha384_hmac_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_sha512_hmac_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_des_ede3_ecb_sha512_hmac_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_aes_128_xcbc_mac_96_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_des_ede3_ecb_aes_128_xcbc_mac_96_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_aes_192_xcbc_mac_96_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_des_ede3_ecb_aes_192_xcbc_mac_96_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_aes_256_xcbc_mac_96_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_des_ede3_ecb_aes_256_xcbc_mac_96_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_aes_128_xcbc_mac_prf_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_des_ede3_ecb_aes_128_xcbc_mac_prf_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_aes_192_xcbc_mac_prf_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_des_ede3_ecb_aes_192_xcbc_mac_prf_out,},
{"des-ede3-ecb",enc_des_ede3_ecb_aes_256_xcbc_mac_prf_in,des_ede3_ecb_key_hex,NULL,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_des_ede3_ecb_aes_256_xcbc_mac_prf_out,},
{"aes-128-ecb",enc_aes_128_ecb_md5_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"md5",NULL,enc_aes_128_ecb_md5_out,},
{"aes-128-ecb",enc_aes_128_ecb_sha1_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"sha1",NULL,enc_aes_128_ecb_sha1_out,},
{"aes-128-ecb",enc_aes_128_ecb_sha224_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"sha224",NULL,enc_aes_128_ecb_sha224_out,},
{"aes-128-ecb",enc_aes_128_ecb_sha256_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"sha256",NULL,enc_aes_128_ecb_sha256_out,},
{"aes-128-ecb",enc_aes_128_ecb_sha384_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"sha384",NULL,enc_aes_128_ecb_sha384_out,},
{"aes-128-ecb",enc_aes_128_ecb_sha512_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"sha512",NULL,enc_aes_128_ecb_sha512_out,},
{"aes-128-ecb",enc_aes_128_ecb_crc32_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"crc32",NULL,enc_aes_128_ecb_crc32_out,},
{"aes-128-ecb",enc_aes_128_ecb_md5_hmac_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_128_ecb_md5_hmac_out,},
{"aes-128-ecb",enc_aes_128_ecb_sha1_hmac_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_128_ecb_sha1_hmac_out,},
{"aes-128-ecb",enc_aes_128_ecb_sha224_hmac_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_128_ecb_sha224_hmac_out,},
{"aes-128-ecb",enc_aes_128_ecb_sha256_hmac_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_128_ecb_sha256_hmac_out,},
{"aes-128-ecb",enc_aes_128_ecb_sha384_hmac_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_128_ecb_sha384_hmac_out,},
{"aes-128-ecb",enc_aes_128_ecb_sha512_hmac_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_128_ecb_sha512_hmac_out,},
{"aes-128-ecb",enc_aes_128_ecb_aes_128_xcbc_mac_96_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_128_ecb_aes_128_xcbc_mac_96_out,},
{"aes-128-ecb",enc_aes_128_ecb_aes_192_xcbc_mac_96_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_128_ecb_aes_192_xcbc_mac_96_out,},
{"aes-128-ecb",enc_aes_128_ecb_aes_256_xcbc_mac_96_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_128_ecb_aes_256_xcbc_mac_96_out,},
{"aes-128-ecb",enc_aes_128_ecb_aes_128_xcbc_mac_prf_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_128_ecb_aes_128_xcbc_mac_prf_out,},
{"aes-128-ecb",enc_aes_128_ecb_aes_192_xcbc_mac_prf_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_128_ecb_aes_192_xcbc_mac_prf_out,},
{"aes-128-ecb",enc_aes_128_ecb_aes_256_xcbc_mac_prf_in,aes_128_ecb_key_hex,NULL,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_128_ecb_aes_256_xcbc_mac_prf_out,},
{"aes-192-ecb",enc_aes_192_ecb_md5_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"md5",NULL,enc_aes_192_ecb_md5_out,},
{"aes-192-ecb",enc_aes_192_ecb_sha1_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"sha1",NULL,enc_aes_192_ecb_sha1_out,},
{"aes-192-ecb",enc_aes_192_ecb_sha224_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"sha224",NULL,enc_aes_192_ecb_sha224_out,},
{"aes-192-ecb",enc_aes_192_ecb_sha256_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"sha256",NULL,enc_aes_192_ecb_sha256_out,},
{"aes-192-ecb",enc_aes_192_ecb_sha384_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"sha384",NULL,enc_aes_192_ecb_sha384_out,},
{"aes-192-ecb",enc_aes_192_ecb_sha512_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"sha512",NULL,enc_aes_192_ecb_sha512_out,},
{"aes-192-ecb",enc_aes_192_ecb_crc32_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"crc32",NULL,enc_aes_192_ecb_crc32_out,},
{"aes-192-ecb",enc_aes_192_ecb_md5_hmac_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_192_ecb_md5_hmac_out,},
{"aes-192-ecb",enc_aes_192_ecb_sha1_hmac_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_192_ecb_sha1_hmac_out,},
{"aes-192-ecb",enc_aes_192_ecb_sha224_hmac_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_192_ecb_sha224_hmac_out,},
{"aes-192-ecb",enc_aes_192_ecb_sha256_hmac_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_192_ecb_sha256_hmac_out,},
{"aes-192-ecb",enc_aes_192_ecb_sha384_hmac_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_192_ecb_sha384_hmac_out,},
{"aes-192-ecb",enc_aes_192_ecb_sha512_hmac_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_192_ecb_sha512_hmac_out,},
{"aes-192-ecb",enc_aes_192_ecb_aes_128_xcbc_mac_96_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_192_ecb_aes_128_xcbc_mac_96_out,},
{"aes-192-ecb",enc_aes_192_ecb_aes_192_xcbc_mac_96_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_192_ecb_aes_192_xcbc_mac_96_out,},
{"aes-192-ecb",enc_aes_192_ecb_aes_256_xcbc_mac_96_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_192_ecb_aes_256_xcbc_mac_96_out,},
{"aes-192-ecb",enc_aes_192_ecb_aes_128_xcbc_mac_prf_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_192_ecb_aes_128_xcbc_mac_prf_out,},
{"aes-192-ecb",enc_aes_192_ecb_aes_192_xcbc_mac_prf_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_192_ecb_aes_192_xcbc_mac_prf_out,},
{"aes-192-ecb",enc_aes_192_ecb_aes_256_xcbc_mac_prf_in,aes_192_ecb_key_hex,NULL,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_192_ecb_aes_256_xcbc_mac_prf_out,},
{"aes-256-ecb",enc_aes_256_ecb_md5_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"md5",NULL,enc_aes_256_ecb_md5_out,},
{"aes-256-ecb",enc_aes_256_ecb_sha1_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"sha1",NULL,enc_aes_256_ecb_sha1_out,},
{"aes-256-ecb",enc_aes_256_ecb_sha224_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"sha224",NULL,enc_aes_256_ecb_sha224_out,},
{"aes-256-ecb",enc_aes_256_ecb_sha256_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"sha256",NULL,enc_aes_256_ecb_sha256_out,},
{"aes-256-ecb",enc_aes_256_ecb_sha384_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"sha384",NULL,enc_aes_256_ecb_sha384_out,},
{"aes-256-ecb",enc_aes_256_ecb_sha512_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"sha512",NULL,enc_aes_256_ecb_sha512_out,},
{"aes-256-ecb",enc_aes_256_ecb_crc32_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"crc32",NULL,enc_aes_256_ecb_crc32_out,},
{"aes-256-ecb",enc_aes_256_ecb_md5_hmac_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_256_ecb_md5_hmac_out,},
{"aes-256-ecb",enc_aes_256_ecb_sha1_hmac_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_256_ecb_sha1_hmac_out,},
{"aes-256-ecb",enc_aes_256_ecb_sha224_hmac_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_256_ecb_sha224_hmac_out,},
{"aes-256-ecb",enc_aes_256_ecb_sha256_hmac_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_256_ecb_sha256_hmac_out,},
{"aes-256-ecb",enc_aes_256_ecb_sha384_hmac_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_256_ecb_sha384_hmac_out,},
{"aes-256-ecb",enc_aes_256_ecb_sha512_hmac_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_256_ecb_sha512_hmac_out,},
{"aes-256-ecb",enc_aes_256_ecb_aes_128_xcbc_mac_96_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_256_ecb_aes_128_xcbc_mac_96_out,},
{"aes-256-ecb",enc_aes_256_ecb_aes_192_xcbc_mac_96_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_256_ecb_aes_192_xcbc_mac_96_out,},
{"aes-256-ecb",enc_aes_256_ecb_aes_256_xcbc_mac_96_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_256_ecb_aes_256_xcbc_mac_96_out,},
{"aes-256-ecb",enc_aes_256_ecb_aes_128_xcbc_mac_prf_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_256_ecb_aes_128_xcbc_mac_prf_out,},
{"aes-256-ecb",enc_aes_256_ecb_aes_192_xcbc_mac_prf_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_256_ecb_aes_192_xcbc_mac_prf_out,},
{"aes-256-ecb",enc_aes_256_ecb_aes_256_xcbc_mac_prf_in,aes_256_ecb_key_hex,NULL,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_256_ecb_aes_256_xcbc_mac_prf_out,},
{"des-cbc",enc_des_cbc_md5_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"md5",NULL,enc_des_cbc_md5_out,},
{"des-cbc",enc_des_cbc_sha1_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"sha1",NULL,enc_des_cbc_sha1_out,},
{"des-cbc",enc_des_cbc_sha224_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"sha224",NULL,enc_des_cbc_sha224_out,},
{"des-cbc",enc_des_cbc_sha256_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"sha256",NULL,enc_des_cbc_sha256_out,},
{"des-cbc",enc_des_cbc_sha384_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"sha384",NULL,enc_des_cbc_sha384_out,},
{"des-cbc",enc_des_cbc_sha512_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"sha512",NULL,enc_des_cbc_sha512_out,},
{"des-cbc",enc_des_cbc_crc32_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"crc32",NULL,enc_des_cbc_crc32_out,},
{"des-cbc",enc_des_cbc_md5_hmac_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_des_cbc_md5_hmac_out,},
{"des-cbc",enc_des_cbc_sha1_hmac_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_des_cbc_sha1_hmac_out,},
{"des-cbc",enc_des_cbc_sha224_hmac_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_des_cbc_sha224_hmac_out,},
{"des-cbc",enc_des_cbc_sha256_hmac_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_des_cbc_sha256_hmac_out,},
{"des-cbc",enc_des_cbc_sha384_hmac_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_des_cbc_sha384_hmac_out,},
{"des-cbc",enc_des_cbc_sha512_hmac_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_des_cbc_sha512_hmac_out,},
{"des-cbc",enc_des_cbc_aes_128_xcbc_mac_96_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_des_cbc_aes_128_xcbc_mac_96_out,},
{"des-cbc",enc_des_cbc_aes_192_xcbc_mac_96_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_des_cbc_aes_192_xcbc_mac_96_out,},
{"des-cbc",enc_des_cbc_aes_256_xcbc_mac_96_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_des_cbc_aes_256_xcbc_mac_96_out,},
{"des-cbc",enc_des_cbc_aes_128_xcbc_mac_prf_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_des_cbc_aes_128_xcbc_mac_prf_out,},
{"des-cbc",enc_des_cbc_aes_192_xcbc_mac_prf_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_des_cbc_aes_192_xcbc_mac_prf_out,},
{"des-cbc",enc_des_cbc_aes_256_xcbc_mac_prf_in,des_cbc_key_hex,des_cbc_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_des_cbc_aes_256_xcbc_mac_prf_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_md5_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"md5",NULL,enc_des_ede3_cbc_md5_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_sha1_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"sha1",NULL,enc_des_ede3_cbc_sha1_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_sha224_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"sha224",NULL,enc_des_ede3_cbc_sha224_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_sha256_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"sha256",NULL,enc_des_ede3_cbc_sha256_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_sha384_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"sha384",NULL,enc_des_ede3_cbc_sha384_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_sha512_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"sha512",NULL,enc_des_ede3_cbc_sha512_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_crc32_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"crc32",NULL,enc_des_ede3_cbc_crc32_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_md5_hmac_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_des_ede3_cbc_md5_hmac_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_sha1_hmac_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_des_ede3_cbc_sha1_hmac_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_sha224_hmac_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_des_ede3_cbc_sha224_hmac_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_sha256_hmac_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_des_ede3_cbc_sha256_hmac_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_sha384_hmac_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_des_ede3_cbc_sha384_hmac_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_sha512_hmac_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_des_ede3_cbc_sha512_hmac_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_aes_128_xcbc_mac_96_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_des_ede3_cbc_aes_128_xcbc_mac_96_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_aes_192_xcbc_mac_96_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_des_ede3_cbc_aes_192_xcbc_mac_96_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_aes_256_xcbc_mac_96_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_des_ede3_cbc_aes_256_xcbc_mac_96_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_aes_128_xcbc_mac_prf_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_des_ede3_cbc_aes_128_xcbc_mac_prf_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_aes_192_xcbc_mac_prf_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_des_ede3_cbc_aes_192_xcbc_mac_prf_out,},
{"des-ede3-cbc",enc_des_ede3_cbc_aes_256_xcbc_mac_prf_in,des_ede3_cbc_key_hex,des_ede3_cbc_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_des_ede3_cbc_aes_256_xcbc_mac_prf_out,},
{"aes-128-cbc",enc_aes_128_cbc_md5_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"md5",NULL,enc_aes_128_cbc_md5_out,},
{"aes-128-cbc",enc_aes_128_cbc_sha1_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_128_cbc_sha1_out,},
{"aes-128-cbc",enc_aes_128_cbc_sha224_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_128_cbc_sha224_out,},
{"aes-128-cbc",enc_aes_128_cbc_sha256_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_128_cbc_sha256_out,},
{"aes-128-cbc",enc_aes_128_cbc_sha384_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_128_cbc_sha384_out,},
{"aes-128-cbc",enc_aes_128_cbc_sha512_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_128_cbc_sha512_out,},
{"aes-128-cbc",enc_aes_128_cbc_crc32_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_128_cbc_crc32_out,},
{"aes-128-cbc",enc_aes_128_cbc_md5_hmac_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_128_cbc_md5_hmac_out,},
{"aes-128-cbc",enc_aes_128_cbc_sha1_hmac_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_128_cbc_sha1_hmac_out,},
{"aes-128-cbc",enc_aes_128_cbc_sha224_hmac_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_128_cbc_sha224_hmac_out,},
{"aes-128-cbc",enc_aes_128_cbc_sha256_hmac_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_128_cbc_sha256_hmac_out,},
{"aes-128-cbc",enc_aes_128_cbc_sha384_hmac_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_128_cbc_sha384_hmac_out,},
{"aes-128-cbc",enc_aes_128_cbc_sha512_hmac_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_128_cbc_sha512_hmac_out,},
{"aes-128-cbc",enc_aes_128_cbc_aes_128_xcbc_mac_96_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_128_cbc_aes_128_xcbc_mac_96_out,},
{"aes-128-cbc",enc_aes_128_cbc_aes_192_xcbc_mac_96_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_128_cbc_aes_192_xcbc_mac_96_out,},
{"aes-128-cbc",enc_aes_128_cbc_aes_256_xcbc_mac_96_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_128_cbc_aes_256_xcbc_mac_96_out,},
{"aes-128-cbc",enc_aes_128_cbc_aes_128_xcbc_mac_prf_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_128_cbc_aes_128_xcbc_mac_prf_out,},
{"aes-128-cbc",enc_aes_128_cbc_aes_192_xcbc_mac_prf_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_128_cbc_aes_192_xcbc_mac_prf_out,},
{"aes-128-cbc",enc_aes_128_cbc_aes_256_xcbc_mac_prf_in,aes_128_cbc_key_hex,aes_128_cbc_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_128_cbc_aes_256_xcbc_mac_prf_out,},
{"aes-128-ofb",enc_aes_128_ofb_md5_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"md5",NULL,enc_aes_128_ofb_md5_out,},
{"aes-128-ofb",enc_aes_128_ofb_sha1_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_128_ofb_sha1_out,},
{"aes-128-ofb",enc_aes_128_ofb_sha224_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_128_ofb_sha224_out,},
{"aes-128-ofb",enc_aes_128_ofb_sha256_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_128_ofb_sha256_out,},
{"aes-128-ofb",enc_aes_128_ofb_sha384_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_128_ofb_sha384_out,},
{"aes-128-ofb",enc_aes_128_ofb_sha512_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_128_ofb_sha512_out,},
{"aes-128-ofb",enc_aes_128_ofb_crc32_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_128_ofb_crc32_out,},
{"aes-128-ofb",enc_aes_128_ofb_md5_hmac_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_128_ofb_md5_hmac_out,},
{"aes-128-ofb",enc_aes_128_ofb_sha1_hmac_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_128_ofb_sha1_hmac_out,},
{"aes-128-ofb",enc_aes_128_ofb_sha224_hmac_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_128_ofb_sha224_hmac_out,},
{"aes-128-ofb",enc_aes_128_ofb_sha256_hmac_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_128_ofb_sha256_hmac_out,},
{"aes-128-ofb",enc_aes_128_ofb_sha384_hmac_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_128_ofb_sha384_hmac_out,},
{"aes-128-ofb",enc_aes_128_ofb_sha512_hmac_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_128_ofb_sha512_hmac_out,},
{"aes-128-ofb",enc_aes_128_ofb_aes_128_xcbc_mac_96_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_128_ofb_aes_128_xcbc_mac_96_out,},
{"aes-128-ofb",enc_aes_128_ofb_aes_192_xcbc_mac_96_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_128_ofb_aes_192_xcbc_mac_96_out,},
{"aes-128-ofb",enc_aes_128_ofb_aes_256_xcbc_mac_96_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_128_ofb_aes_256_xcbc_mac_96_out,},
{"aes-128-ofb",enc_aes_128_ofb_aes_128_xcbc_mac_prf_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_128_ofb_aes_128_xcbc_mac_prf_out,},
{"aes-128-ofb",enc_aes_128_ofb_aes_192_xcbc_mac_prf_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_128_ofb_aes_192_xcbc_mac_prf_out,},
{"aes-128-ofb",enc_aes_128_ofb_aes_256_xcbc_mac_prf_in,aes_128_ofb_key_hex,aes_128_ofb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_128_ofb_aes_256_xcbc_mac_prf_out,},
{"aes-128-cfb",enc_aes_128_cfb_md5_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"md5",NULL,enc_aes_128_cfb_md5_out,},
{"aes-128-cfb",enc_aes_128_cfb_sha1_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_128_cfb_sha1_out,},
{"aes-128-cfb",enc_aes_128_cfb_sha224_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_128_cfb_sha224_out,},
{"aes-128-cfb",enc_aes_128_cfb_sha256_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_128_cfb_sha256_out,},
{"aes-128-cfb",enc_aes_128_cfb_sha384_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_128_cfb_sha384_out,},
{"aes-128-cfb",enc_aes_128_cfb_sha512_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_128_cfb_sha512_out,},
{"aes-128-cfb",enc_aes_128_cfb_crc32_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_128_cfb_crc32_out,},
{"aes-128-cfb",enc_aes_128_cfb_md5_hmac_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_128_cfb_md5_hmac_out,},
{"aes-128-cfb",enc_aes_128_cfb_sha1_hmac_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_128_cfb_sha1_hmac_out,},
{"aes-128-cfb",enc_aes_128_cfb_sha224_hmac_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_128_cfb_sha224_hmac_out,},
{"aes-128-cfb",enc_aes_128_cfb_sha256_hmac_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_128_cfb_sha256_hmac_out,},
{"aes-128-cfb",enc_aes_128_cfb_sha384_hmac_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_128_cfb_sha384_hmac_out,},
{"aes-128-cfb",enc_aes_128_cfb_sha512_hmac_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_128_cfb_sha512_hmac_out,},
{"aes-128-cfb",enc_aes_128_cfb_aes_128_xcbc_mac_96_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_128_cfb_aes_128_xcbc_mac_96_out,},
{"aes-128-cfb",enc_aes_128_cfb_aes_192_xcbc_mac_96_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_128_cfb_aes_192_xcbc_mac_96_out,},
{"aes-128-cfb",enc_aes_128_cfb_aes_256_xcbc_mac_96_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_128_cfb_aes_256_xcbc_mac_96_out,},
{"aes-128-cfb",enc_aes_128_cfb_aes_128_xcbc_mac_prf_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_128_cfb_aes_128_xcbc_mac_prf_out,},
{"aes-128-cfb",enc_aes_128_cfb_aes_192_xcbc_mac_prf_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_128_cfb_aes_192_xcbc_mac_prf_out,},
{"aes-128-cfb",enc_aes_128_cfb_aes_256_xcbc_mac_prf_in,aes_128_cfb_key_hex,aes_128_cfb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_128_cfb_aes_256_xcbc_mac_prf_out,},
{"aes-128-ctr",enc_aes_128_ctr_md5_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"md5",NULL,enc_aes_128_ctr_md5_out,},
{"aes-128-ctr",enc_aes_128_ctr_sha1_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_128_ctr_sha1_out,},
{"aes-128-ctr",enc_aes_128_ctr_sha224_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_128_ctr_sha224_out,},
{"aes-128-ctr",enc_aes_128_ctr_sha256_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_128_ctr_sha256_out,},
{"aes-128-ctr",enc_aes_128_ctr_sha384_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_128_ctr_sha384_out,},
{"aes-128-ctr",enc_aes_128_ctr_sha512_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_128_ctr_sha512_out,},
{"aes-128-ctr",enc_aes_128_ctr_crc32_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_128_ctr_crc32_out,},
{"aes-128-ctr",enc_aes_128_ctr_md5_hmac_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_128_ctr_md5_hmac_out,},
{"aes-128-ctr",enc_aes_128_ctr_sha1_hmac_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_128_ctr_sha1_hmac_out,},
{"aes-128-ctr",enc_aes_128_ctr_sha224_hmac_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_128_ctr_sha224_hmac_out,},
{"aes-128-ctr",enc_aes_128_ctr_sha256_hmac_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_128_ctr_sha256_hmac_out,},
{"aes-128-ctr",enc_aes_128_ctr_sha384_hmac_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_128_ctr_sha384_hmac_out,},
{"aes-128-ctr",enc_aes_128_ctr_sha512_hmac_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_128_ctr_sha512_hmac_out,},
{"aes-128-ctr",enc_aes_128_ctr_aes_128_xcbc_mac_96_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_128_ctr_aes_128_xcbc_mac_96_out,},
{"aes-128-ctr",enc_aes_128_ctr_aes_192_xcbc_mac_96_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_128_ctr_aes_192_xcbc_mac_96_out,},
{"aes-128-ctr",enc_aes_128_ctr_aes_256_xcbc_mac_96_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_128_ctr_aes_256_xcbc_mac_96_out,},
{"aes-128-ctr",enc_aes_128_ctr_aes_128_xcbc_mac_prf_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_128_ctr_aes_128_xcbc_mac_prf_out,},
{"aes-128-ctr",enc_aes_128_ctr_aes_192_xcbc_mac_prf_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_128_ctr_aes_192_xcbc_mac_prf_out,},
{"aes-128-ctr",enc_aes_128_ctr_aes_256_xcbc_mac_prf_in,aes_128_ctr_key_hex,aes_128_ctr_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_128_ctr_aes_256_xcbc_mac_prf_out,},
{"aes-192-cbc",enc_aes_192_cbc_md5_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"md5",NULL,enc_aes_192_cbc_md5_out,},
{"aes-192-cbc",enc_aes_192_cbc_sha1_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_192_cbc_sha1_out,},
{"aes-192-cbc",enc_aes_192_cbc_sha224_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_192_cbc_sha224_out,},
{"aes-192-cbc",enc_aes_192_cbc_sha256_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_192_cbc_sha256_out,},
{"aes-192-cbc",enc_aes_192_cbc_sha384_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_192_cbc_sha384_out,},
{"aes-192-cbc",enc_aes_192_cbc_sha512_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_192_cbc_sha512_out,},
{"aes-192-cbc",enc_aes_192_cbc_crc32_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_192_cbc_crc32_out,},
{"aes-192-cbc",enc_aes_192_cbc_md5_hmac_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_192_cbc_md5_hmac_out,},
{"aes-192-cbc",enc_aes_192_cbc_sha1_hmac_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_192_cbc_sha1_hmac_out,},
{"aes-192-cbc",enc_aes_192_cbc_sha224_hmac_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_192_cbc_sha224_hmac_out,},
{"aes-192-cbc",enc_aes_192_cbc_sha256_hmac_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_192_cbc_sha256_hmac_out,},
{"aes-192-cbc",enc_aes_192_cbc_sha384_hmac_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_192_cbc_sha384_hmac_out,},
{"aes-192-cbc",enc_aes_192_cbc_sha512_hmac_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_192_cbc_sha512_hmac_out,},
{"aes-192-cbc",enc_aes_192_cbc_aes_128_xcbc_mac_96_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_192_cbc_aes_128_xcbc_mac_96_out,},
{"aes-192-cbc",enc_aes_192_cbc_aes_192_xcbc_mac_96_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_192_cbc_aes_192_xcbc_mac_96_out,},
{"aes-192-cbc",enc_aes_192_cbc_aes_256_xcbc_mac_96_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_192_cbc_aes_256_xcbc_mac_96_out,},
{"aes-192-cbc",enc_aes_192_cbc_aes_128_xcbc_mac_prf_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_192_cbc_aes_128_xcbc_mac_prf_out,},
{"aes-192-cbc",enc_aes_192_cbc_aes_192_xcbc_mac_prf_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_192_cbc_aes_192_xcbc_mac_prf_out,},
{"aes-192-cbc",enc_aes_192_cbc_aes_256_xcbc_mac_prf_in,aes_192_cbc_key_hex,aes_192_cbc_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_192_cbc_aes_256_xcbc_mac_prf_out,},
{"aes-192-ofb",enc_aes_192_ofb_md5_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"md5",NULL,enc_aes_192_ofb_md5_out,},
{"aes-192-ofb",enc_aes_192_ofb_sha1_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_192_ofb_sha1_out,},
{"aes-192-ofb",enc_aes_192_ofb_sha224_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_192_ofb_sha224_out,},
{"aes-192-ofb",enc_aes_192_ofb_sha256_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_192_ofb_sha256_out,},
{"aes-192-ofb",enc_aes_192_ofb_sha384_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_192_ofb_sha384_out,},
{"aes-192-ofb",enc_aes_192_ofb_sha512_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_192_ofb_sha512_out,},
{"aes-192-ofb",enc_aes_192_ofb_crc32_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_192_ofb_crc32_out,},
{"aes-192-ofb",enc_aes_192_ofb_md5_hmac_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_192_ofb_md5_hmac_out,},
{"aes-192-ofb",enc_aes_192_ofb_sha1_hmac_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_192_ofb_sha1_hmac_out,},
{"aes-192-ofb",enc_aes_192_ofb_sha224_hmac_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_192_ofb_sha224_hmac_out,},
{"aes-192-ofb",enc_aes_192_ofb_sha256_hmac_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_192_ofb_sha256_hmac_out,},
{"aes-192-ofb",enc_aes_192_ofb_sha384_hmac_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_192_ofb_sha384_hmac_out,},
{"aes-192-ofb",enc_aes_192_ofb_sha512_hmac_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_192_ofb_sha512_hmac_out,},
{"aes-192-ofb",enc_aes_192_ofb_aes_128_xcbc_mac_96_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_192_ofb_aes_128_xcbc_mac_96_out,},
{"aes-192-ofb",enc_aes_192_ofb_aes_192_xcbc_mac_96_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_192_ofb_aes_192_xcbc_mac_96_out,},
{"aes-192-ofb",enc_aes_192_ofb_aes_256_xcbc_mac_96_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_192_ofb_aes_256_xcbc_mac_96_out,},
{"aes-192-ofb",enc_aes_192_ofb_aes_128_xcbc_mac_prf_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_192_ofb_aes_128_xcbc_mac_prf_out,},
{"aes-192-ofb",enc_aes_192_ofb_aes_192_xcbc_mac_prf_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_192_ofb_aes_192_xcbc_mac_prf_out,},
{"aes-192-ofb",enc_aes_192_ofb_aes_256_xcbc_mac_prf_in,aes_192_ofb_key_hex,aes_192_ofb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_192_ofb_aes_256_xcbc_mac_prf_out,},
{"aes-192-cfb",enc_aes_192_cfb_md5_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"md5",NULL,enc_aes_192_cfb_md5_out,},
{"aes-192-cfb",enc_aes_192_cfb_sha1_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_192_cfb_sha1_out,},
{"aes-192-cfb",enc_aes_192_cfb_sha224_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_192_cfb_sha224_out,},
{"aes-192-cfb",enc_aes_192_cfb_sha256_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_192_cfb_sha256_out,},
{"aes-192-cfb",enc_aes_192_cfb_sha384_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_192_cfb_sha384_out,},
{"aes-192-cfb",enc_aes_192_cfb_sha512_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_192_cfb_sha512_out,},
{"aes-192-cfb",enc_aes_192_cfb_crc32_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_192_cfb_crc32_out,},
{"aes-192-cfb",enc_aes_192_cfb_md5_hmac_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_192_cfb_md5_hmac_out,},
{"aes-192-cfb",enc_aes_192_cfb_sha1_hmac_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_192_cfb_sha1_hmac_out,},
{"aes-192-cfb",enc_aes_192_cfb_sha224_hmac_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_192_cfb_sha224_hmac_out,},
{"aes-192-cfb",enc_aes_192_cfb_sha256_hmac_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_192_cfb_sha256_hmac_out,},
{"aes-192-cfb",enc_aes_192_cfb_sha384_hmac_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_192_cfb_sha384_hmac_out,},
{"aes-192-cfb",enc_aes_192_cfb_sha512_hmac_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_192_cfb_sha512_hmac_out,},
{"aes-192-cfb",enc_aes_192_cfb_aes_128_xcbc_mac_96_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_192_cfb_aes_128_xcbc_mac_96_out,},
{"aes-192-cfb",enc_aes_192_cfb_aes_192_xcbc_mac_96_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_192_cfb_aes_192_xcbc_mac_96_out,},
{"aes-192-cfb",enc_aes_192_cfb_aes_256_xcbc_mac_96_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_192_cfb_aes_256_xcbc_mac_96_out,},
{"aes-192-cfb",enc_aes_192_cfb_aes_128_xcbc_mac_prf_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_192_cfb_aes_128_xcbc_mac_prf_out,},
{"aes-192-cfb",enc_aes_192_cfb_aes_192_xcbc_mac_prf_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_192_cfb_aes_192_xcbc_mac_prf_out,},
{"aes-192-cfb",enc_aes_192_cfb_aes_256_xcbc_mac_prf_in,aes_192_cfb_key_hex,aes_192_cfb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_192_cfb_aes_256_xcbc_mac_prf_out,},
{"aes-192-ctr",enc_aes_192_ctr_md5_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"md5",NULL,enc_aes_192_ctr_md5_out,},
{"aes-192-ctr",enc_aes_192_ctr_sha1_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_192_ctr_sha1_out,},
{"aes-192-ctr",enc_aes_192_ctr_sha224_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_192_ctr_sha224_out,},
{"aes-192-ctr",enc_aes_192_ctr_sha256_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_192_ctr_sha256_out,},
{"aes-192-ctr",enc_aes_192_ctr_sha384_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_192_ctr_sha384_out,},
{"aes-192-ctr",enc_aes_192_ctr_sha512_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_192_ctr_sha512_out,},
{"aes-192-ctr",enc_aes_192_ctr_crc32_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_192_ctr_crc32_out,},
{"aes-192-ctr",enc_aes_192_ctr_md5_hmac_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_192_ctr_md5_hmac_out,},
{"aes-192-ctr",enc_aes_192_ctr_sha1_hmac_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_192_ctr_sha1_hmac_out,},
{"aes-192-ctr",enc_aes_192_ctr_sha224_hmac_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_192_ctr_sha224_hmac_out,},
{"aes-192-ctr",enc_aes_192_ctr_sha256_hmac_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_192_ctr_sha256_hmac_out,},
{"aes-192-ctr",enc_aes_192_ctr_sha384_hmac_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_192_ctr_sha384_hmac_out,},
{"aes-192-ctr",enc_aes_192_ctr_sha512_hmac_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_192_ctr_sha512_hmac_out,},
{"aes-192-ctr",enc_aes_192_ctr_aes_128_xcbc_mac_96_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_192_ctr_aes_128_xcbc_mac_96_out,},
{"aes-192-ctr",enc_aes_192_ctr_aes_192_xcbc_mac_96_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_192_ctr_aes_192_xcbc_mac_96_out,},
{"aes-192-ctr",enc_aes_192_ctr_aes_256_xcbc_mac_96_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_192_ctr_aes_256_xcbc_mac_96_out,},
{"aes-192-ctr",enc_aes_192_ctr_aes_128_xcbc_mac_prf_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_192_ctr_aes_128_xcbc_mac_prf_out,},
{"aes-192-ctr",enc_aes_192_ctr_aes_192_xcbc_mac_prf_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_192_ctr_aes_192_xcbc_mac_prf_out,},
{"aes-192-ctr",enc_aes_192_ctr_aes_256_xcbc_mac_prf_in,aes_192_ctr_key_hex,aes_192_ctr_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_192_ctr_aes_256_xcbc_mac_prf_out,},
{"aes-256-cbc",enc_aes_256_cbc_md5_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"md5",NULL,enc_aes_256_cbc_md5_out,},
{"aes-256-cbc",enc_aes_256_cbc_sha1_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_256_cbc_sha1_out,},
{"aes-256-cbc",enc_aes_256_cbc_sha224_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_256_cbc_sha224_out,},
{"aes-256-cbc",enc_aes_256_cbc_sha256_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_256_cbc_sha256_out,},
{"aes-256-cbc",enc_aes_256_cbc_sha384_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_256_cbc_sha384_out,},
{"aes-256-cbc",enc_aes_256_cbc_sha512_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_256_cbc_sha512_out,},
{"aes-256-cbc",enc_aes_256_cbc_crc32_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_256_cbc_crc32_out,},
{"aes-256-cbc",enc_aes_256_cbc_md5_hmac_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_256_cbc_md5_hmac_out,},
{"aes-256-cbc",enc_aes_256_cbc_sha1_hmac_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_256_cbc_sha1_hmac_out,},
{"aes-256-cbc",enc_aes_256_cbc_sha224_hmac_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_256_cbc_sha224_hmac_out,},
{"aes-256-cbc",enc_aes_256_cbc_sha256_hmac_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_256_cbc_sha256_hmac_out,},
{"aes-256-cbc",enc_aes_256_cbc_sha384_hmac_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_256_cbc_sha384_hmac_out,},
{"aes-256-cbc",enc_aes_256_cbc_sha512_hmac_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_256_cbc_sha512_hmac_out,},
{"aes-256-cbc",enc_aes_256_cbc_aes_128_xcbc_mac_96_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_256_cbc_aes_128_xcbc_mac_96_out,},
{"aes-256-cbc",enc_aes_256_cbc_aes_192_xcbc_mac_96_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_256_cbc_aes_192_xcbc_mac_96_out,},
{"aes-256-cbc",enc_aes_256_cbc_aes_256_xcbc_mac_96_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_256_cbc_aes_256_xcbc_mac_96_out,},
{"aes-256-cbc",enc_aes_256_cbc_aes_128_xcbc_mac_prf_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_256_cbc_aes_128_xcbc_mac_prf_out,},
{"aes-256-cbc",enc_aes_256_cbc_aes_192_xcbc_mac_prf_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_256_cbc_aes_192_xcbc_mac_prf_out,},
{"aes-256-cbc",enc_aes_256_cbc_aes_256_xcbc_mac_prf_in,aes_256_cbc_key_hex,aes_256_cbc_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_256_cbc_aes_256_xcbc_mac_prf_out,},
{"aes-256-ofb",enc_aes_256_ofb_md5_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"md5",NULL,enc_aes_256_ofb_md5_out,},
{"aes-256-ofb",enc_aes_256_ofb_sha1_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_256_ofb_sha1_out,},
{"aes-256-ofb",enc_aes_256_ofb_sha224_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_256_ofb_sha224_out,},
{"aes-256-ofb",enc_aes_256_ofb_sha256_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_256_ofb_sha256_out,},
{"aes-256-ofb",enc_aes_256_ofb_sha384_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_256_ofb_sha384_out,},
{"aes-256-ofb",enc_aes_256_ofb_sha512_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_256_ofb_sha512_out,},
{"aes-256-ofb",enc_aes_256_ofb_crc32_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_256_ofb_crc32_out,},
{"aes-256-ofb",enc_aes_256_ofb_md5_hmac_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_256_ofb_md5_hmac_out,},
{"aes-256-ofb",enc_aes_256_ofb_sha1_hmac_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_256_ofb_sha1_hmac_out,},
{"aes-256-ofb",enc_aes_256_ofb_sha224_hmac_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_256_ofb_sha224_hmac_out,},
{"aes-256-ofb",enc_aes_256_ofb_sha256_hmac_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_256_ofb_sha256_hmac_out,},
{"aes-256-ofb",enc_aes_256_ofb_sha384_hmac_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_256_ofb_sha384_hmac_out,},
{"aes-256-ofb",enc_aes_256_ofb_sha512_hmac_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_256_ofb_sha512_hmac_out,},
{"aes-256-ofb",enc_aes_256_ofb_aes_128_xcbc_mac_96_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_256_ofb_aes_128_xcbc_mac_96_out,},
{"aes-256-ofb",enc_aes_256_ofb_aes_192_xcbc_mac_96_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_256_ofb_aes_192_xcbc_mac_96_out,},
{"aes-256-ofb",enc_aes_256_ofb_aes_256_xcbc_mac_96_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_256_ofb_aes_256_xcbc_mac_96_out,},
{"aes-256-ofb",enc_aes_256_ofb_aes_128_xcbc_mac_prf_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_256_ofb_aes_128_xcbc_mac_prf_out,},
{"aes-256-ofb",enc_aes_256_ofb_aes_192_xcbc_mac_prf_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_256_ofb_aes_192_xcbc_mac_prf_out,},
{"aes-256-ofb",enc_aes_256_ofb_aes_256_xcbc_mac_prf_in,aes_256_ofb_key_hex,aes_256_ofb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_256_ofb_aes_256_xcbc_mac_prf_out,},
{"aes-256-cfb",enc_aes_256_cfb_md5_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"md5",NULL,enc_aes_256_cfb_md5_out,},
{"aes-256-cfb",enc_aes_256_cfb_sha1_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_256_cfb_sha1_out,},
{"aes-256-cfb",enc_aes_256_cfb_sha224_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_256_cfb_sha224_out,},
{"aes-256-cfb",enc_aes_256_cfb_sha256_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_256_cfb_sha256_out,},
{"aes-256-cfb",enc_aes_256_cfb_sha384_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_256_cfb_sha384_out,},
{"aes-256-cfb",enc_aes_256_cfb_sha512_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_256_cfb_sha512_out,},
{"aes-256-cfb",enc_aes_256_cfb_crc32_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_256_cfb_crc32_out,},
{"aes-256-cfb",enc_aes_256_cfb_md5_hmac_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_256_cfb_md5_hmac_out,},
{"aes-256-cfb",enc_aes_256_cfb_sha1_hmac_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_256_cfb_sha1_hmac_out,},
{"aes-256-cfb",enc_aes_256_cfb_sha224_hmac_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_256_cfb_sha224_hmac_out,},
{"aes-256-cfb",enc_aes_256_cfb_sha256_hmac_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_256_cfb_sha256_hmac_out,},
{"aes-256-cfb",enc_aes_256_cfb_sha384_hmac_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_256_cfb_sha384_hmac_out,},
{"aes-256-cfb",enc_aes_256_cfb_sha512_hmac_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_256_cfb_sha512_hmac_out,},
{"aes-256-cfb",enc_aes_256_cfb_aes_128_xcbc_mac_96_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_256_cfb_aes_128_xcbc_mac_96_out,},
{"aes-256-cfb",enc_aes_256_cfb_aes_192_xcbc_mac_96_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_256_cfb_aes_192_xcbc_mac_96_out,},
{"aes-256-cfb",enc_aes_256_cfb_aes_256_xcbc_mac_96_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_256_cfb_aes_256_xcbc_mac_96_out,},
{"aes-256-cfb",enc_aes_256_cfb_aes_128_xcbc_mac_prf_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_256_cfb_aes_128_xcbc_mac_prf_out,},
{"aes-256-cfb",enc_aes_256_cfb_aes_192_xcbc_mac_prf_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_256_cfb_aes_192_xcbc_mac_prf_out,},
{"aes-256-cfb",enc_aes_256_cfb_aes_256_xcbc_mac_prf_in,aes_256_cfb_key_hex,aes_256_cfb_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_256_cfb_aes_256_xcbc_mac_prf_out,},
{"aes-256-ctr",enc_aes_256_ctr_md5_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"md5",NULL,enc_aes_256_ctr_md5_out,},
{"aes-256-ctr",enc_aes_256_ctr_sha1_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"sha1",NULL,enc_aes_256_ctr_sha1_out,},
{"aes-256-ctr",enc_aes_256_ctr_sha224_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"sha224",NULL,enc_aes_256_ctr_sha224_out,},
{"aes-256-ctr",enc_aes_256_ctr_sha256_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"sha256",NULL,enc_aes_256_ctr_sha256_out,},
{"aes-256-ctr",enc_aes_256_ctr_sha384_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"sha384",NULL,enc_aes_256_ctr_sha384_out,},
{"aes-256-ctr",enc_aes_256_ctr_sha512_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"sha512",NULL,enc_aes_256_ctr_sha512_out,},
{"aes-256-ctr",enc_aes_256_ctr_crc32_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"crc32",NULL,enc_aes_256_ctr_crc32_out,},
{"aes-256-ctr",enc_aes_256_ctr_md5_hmac_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"md5-hmac",md5_hmac_key,enc_aes_256_ctr_md5_hmac_out,},
{"aes-256-ctr",enc_aes_256_ctr_sha1_hmac_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_256_ctr_sha1_hmac_out,},
{"aes-256-ctr",enc_aes_256_ctr_sha224_hmac_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_256_ctr_sha224_hmac_out,},
{"aes-256-ctr",enc_aes_256_ctr_sha256_hmac_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_256_ctr_sha256_hmac_out,},
{"aes-256-ctr",enc_aes_256_ctr_sha384_hmac_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_256_ctr_sha384_hmac_out,},
{"aes-256-ctr",enc_aes_256_ctr_sha512_hmac_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_256_ctr_sha512_hmac_out,},
{"aes-256-ctr",enc_aes_256_ctr_aes_128_xcbc_mac_96_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_256_ctr_aes_128_xcbc_mac_96_out,},
{"aes-256-ctr",enc_aes_256_ctr_aes_192_xcbc_mac_96_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_256_ctr_aes_192_xcbc_mac_96_out,},
{"aes-256-ctr",enc_aes_256_ctr_aes_256_xcbc_mac_96_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_256_ctr_aes_256_xcbc_mac_96_out,},
{"aes-256-ctr",enc_aes_256_ctr_aes_128_xcbc_mac_prf_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_256_ctr_aes_128_xcbc_mac_prf_out,},
{"aes-256-ctr",enc_aes_256_ctr_aes_192_xcbc_mac_prf_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_256_ctr_aes_192_xcbc_mac_prf_out,},
{"aes-256-ctr",enc_aes_256_ctr_aes_256_xcbc_mac_prf_in,aes_256_ctr_key_hex,aes_256_ctr_iv_hex,NULL,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_256_ctr_aes_256_xcbc_mac_prf_out,},
{"aes-128-icm",enc_aes_128_icm_md5_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"md5",NULL,enc_aes_128_icm_md5_out,},
{"aes-128-icm",enc_aes_128_icm_sha1_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"sha1",NULL,enc_aes_128_icm_sha1_out,},
{"aes-128-icm",enc_aes_128_icm_sha224_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"sha224",NULL,enc_aes_128_icm_sha224_out,},
{"aes-128-icm",enc_aes_128_icm_sha256_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"sha256",NULL,enc_aes_128_icm_sha256_out,},
{"aes-128-icm",enc_aes_128_icm_sha384_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"sha384",NULL,enc_aes_128_icm_sha384_out,},
{"aes-128-icm",enc_aes_128_icm_sha512_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"sha512",NULL,enc_aes_128_icm_sha512_out,},
{"aes-128-icm",enc_aes_128_icm_crc32_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"crc32",NULL,enc_aes_128_icm_crc32_out,},
{"aes-128-icm",enc_aes_128_icm_md5_hmac_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"md5-hmac",md5_hmac_key,enc_aes_128_icm_md5_hmac_out,},
{"aes-128-icm",enc_aes_128_icm_sha1_hmac_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_128_icm_sha1_hmac_out,},
{"aes-128-icm",enc_aes_128_icm_sha224_hmac_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_128_icm_sha224_hmac_out,},
{"aes-128-icm",enc_aes_128_icm_sha256_hmac_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_128_icm_sha256_hmac_out,},
{"aes-128-icm",enc_aes_128_icm_sha384_hmac_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_128_icm_sha384_hmac_out,},
{"aes-128-icm",enc_aes_128_icm_sha512_hmac_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_128_icm_sha512_hmac_out,},
{"aes-128-icm",enc_aes_128_icm_aes_128_xcbc_mac_96_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_128_icm_aes_128_xcbc_mac_96_out,},
{"aes-128-icm",enc_aes_128_icm_aes_192_xcbc_mac_96_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_128_icm_aes_192_xcbc_mac_96_out,},
{"aes-128-icm",enc_aes_128_icm_aes_256_xcbc_mac_96_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_128_icm_aes_256_xcbc_mac_96_out,},
{"aes-128-icm",enc_aes_128_icm_aes_128_xcbc_mac_prf_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_128_icm_aes_128_xcbc_mac_prf_out,},
{"aes-128-icm",enc_aes_128_icm_aes_192_xcbc_mac_prf_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_128_icm_aes_192_xcbc_mac_prf_out,},
{"aes-128-icm",enc_aes_128_icm_aes_256_xcbc_mac_prf_in,aes_128_icm_key_hex,aes_128_icm_key_hex,aes_128_icm_nonce_hex,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_128_icm_aes_256_xcbc_mac_prf_out,},
{"aes-192-icm",enc_aes_192_icm_md5_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"md5",NULL,enc_aes_192_icm_md5_out,},
{"aes-192-icm",enc_aes_192_icm_sha1_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"sha1",NULL,enc_aes_192_icm_sha1_out,},
{"aes-192-icm",enc_aes_192_icm_sha224_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"sha224",NULL,enc_aes_192_icm_sha224_out,},
{"aes-192-icm",enc_aes_192_icm_sha256_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"sha256",NULL,enc_aes_192_icm_sha256_out,},
{"aes-192-icm",enc_aes_192_icm_sha384_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"sha384",NULL,enc_aes_192_icm_sha384_out,},
{"aes-192-icm",enc_aes_192_icm_sha512_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"sha512",NULL,enc_aes_192_icm_sha512_out,},
{"aes-192-icm",enc_aes_192_icm_crc32_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"crc32",NULL,enc_aes_192_icm_crc32_out,},
{"aes-192-icm",enc_aes_192_icm_md5_hmac_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"md5-hmac",md5_hmac_key,enc_aes_192_icm_md5_hmac_out,},
{"aes-192-icm",enc_aes_192_icm_sha1_hmac_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_192_icm_sha1_hmac_out,},
{"aes-192-icm",enc_aes_192_icm_sha224_hmac_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_192_icm_sha224_hmac_out,},
{"aes-192-icm",enc_aes_192_icm_sha256_hmac_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_192_icm_sha256_hmac_out,},
{"aes-192-icm",enc_aes_192_icm_sha384_hmac_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_192_icm_sha384_hmac_out,},
{"aes-192-icm",enc_aes_192_icm_sha512_hmac_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_192_icm_sha512_hmac_out,},
{"aes-192-icm",enc_aes_192_icm_aes_128_xcbc_mac_96_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_192_icm_aes_128_xcbc_mac_96_out,},
{"aes-192-icm",enc_aes_192_icm_aes_192_xcbc_mac_96_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_192_icm_aes_192_xcbc_mac_96_out,},
{"aes-192-icm",enc_aes_192_icm_aes_256_xcbc_mac_96_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_192_icm_aes_256_xcbc_mac_96_out,},
{"aes-192-icm",enc_aes_192_icm_aes_128_xcbc_mac_prf_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_192_icm_aes_128_xcbc_mac_prf_out,},
{"aes-192-icm",enc_aes_192_icm_aes_192_xcbc_mac_prf_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_192_icm_aes_192_xcbc_mac_prf_out,},
{"aes-192-icm",enc_aes_192_icm_aes_256_xcbc_mac_prf_in,aes_192_icm_key_hex,aes_192_icm_key_hex,aes_192_icm_nonce_hex,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_192_icm_aes_256_xcbc_mac_prf_out,},
{"aes-256-icm",enc_aes_256_icm_md5_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"md5",NULL,enc_aes_256_icm_md5_out,},
{"aes-256-icm",enc_aes_256_icm_sha1_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"sha1",NULL,enc_aes_256_icm_sha1_out,},
{"aes-256-icm",enc_aes_256_icm_sha224_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"sha224",NULL,enc_aes_256_icm_sha224_out,},
{"aes-256-icm",enc_aes_256_icm_sha256_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"sha256",NULL,enc_aes_256_icm_sha256_out,},
{"aes-256-icm",enc_aes_256_icm_sha384_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"sha384",NULL,enc_aes_256_icm_sha384_out,},
{"aes-256-icm",enc_aes_256_icm_sha512_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"sha512",NULL,enc_aes_256_icm_sha512_out,},
{"aes-256-icm",enc_aes_256_icm_crc32_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"crc32",NULL,enc_aes_256_icm_crc32_out,},
{"aes-256-icm",enc_aes_256_icm_md5_hmac_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"md5-hmac",md5_hmac_key,enc_aes_256_icm_md5_hmac_out,},
{"aes-256-icm",enc_aes_256_icm_sha1_hmac_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"sha1-hmac",sha1_hmac_key,enc_aes_256_icm_sha1_hmac_out,},
{"aes-256-icm",enc_aes_256_icm_sha224_hmac_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"sha224-hmac",sha224_hmac_key,enc_aes_256_icm_sha224_hmac_out,},
{"aes-256-icm",enc_aes_256_icm_sha256_hmac_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"sha256-hmac",sha256_hmac_key,enc_aes_256_icm_sha256_hmac_out,},
{"aes-256-icm",enc_aes_256_icm_sha384_hmac_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"sha384-hmac",sha384_hmac_key,enc_aes_256_icm_sha384_hmac_out,},
{"aes-256-icm",enc_aes_256_icm_sha512_hmac_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"sha512-hmac",sha512_hmac_key,enc_aes_256_icm_sha512_hmac_out,},
{"aes-256-icm",enc_aes_256_icm_aes_128_xcbc_mac_96_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"aes-128-xcbc-mac-96",aes_128_xcbc_mac_96_key,enc_aes_256_icm_aes_128_xcbc_mac_96_out,},
{"aes-256-icm",enc_aes_256_icm_aes_192_xcbc_mac_96_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"aes-192-xcbc-mac-96",aes_192_xcbc_mac_96_key,enc_aes_256_icm_aes_192_xcbc_mac_96_out,},
{"aes-256-icm",enc_aes_256_icm_aes_256_xcbc_mac_96_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"aes-256-xcbc-mac-96",aes_256_xcbc_mac_96_key,enc_aes_256_icm_aes_256_xcbc_mac_96_out,},
{"aes-256-icm",enc_aes_256_icm_aes_128_xcbc_mac_prf_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"aes-128-xcbc-mac-prf",aes_128_xcbc_mac_prf_key,enc_aes_256_icm_aes_128_xcbc_mac_prf_out,},
{"aes-256-icm",enc_aes_256_icm_aes_192_xcbc_mac_prf_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"aes-192-xcbc-mac-prf",aes_192_xcbc_mac_prf_key,enc_aes_256_icm_aes_192_xcbc_mac_prf_out,},
{"aes-256-icm",enc_aes_256_icm_aes_256_xcbc_mac_prf_in,aes_256_icm_key_hex,aes_256_icm_key_hex,aes_256_icm_nonce_hex,NULL,"aes-256-xcbc-mac-prf",aes_256_xcbc_mac_prf_key,enc_aes_256_icm_aes_256_xcbc_mac_prf_out,},
};
struct combined dec_hash_data[1];
struct combined hash_enc_data[1];
struct combined hash_dec_data[1];
#endif

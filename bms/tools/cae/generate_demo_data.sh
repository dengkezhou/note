#!/bin/bash

# crypto input
des_3des_iv_hex=1122334455667788
des_key_hex=1122334455667788
des_ede3_key_hex=112233445566778811223344556677881122334455667788

aes_128_key_hex=06a9214036b8a15b512e03d534120006
aes_192_key_hex=112233445566778811223344556677881122334455667788
aes_256_key_hex=1122334455667788112233445566778811223344556677888877665544332211
aes_iv_hex=3dafba429d9eb430b422da802c9fac41

aes_128_cbc_key_hex=6c3ea0477630ce21a2ce334aa746c2cd
aes_128_cbc_iv_hex=c782dc4c098c66cbd9cd27d825682c81

aes_128_icm_key_hex=2b7e151628aed2a6abf7158809cf4f3cf0f1f2f3f4f5f6f7f8f9fafbfcfd
aes_128_icm_nonce_hex=00000000000000000000000000000000
aes_192_icm_key_hex=eab234764e517b2d3d160d587d8c86219740f65f99b6bcf7f0f1f2f3f4f5f6f7f8f9fafbfcfd
aes_192_icm_nonce_hex=00000000000000000000000000000000
aes_256_icm_key_hex=57f82fe3613fd170a85ec93c40b1f0922ec4cb0dc025b58272147cc438944a98f0f1f2f3f4f5f6f7f8f9fafbfcfd
aes_256_icm_nonce_hex=00000000000000000000000000000000

aes_128_ccm_key_hex=ceb009aea4454451feadf0e6b36f4555
aes_128_ccm_aad_hex=6e80dd7f1badf3a1c9ab25c75f10bde78c23fa0eb8f9aaa53adefbf4cbf78fe1
aes_128_ccm_nonce_hex=764043c49460b1
aes_192_ccm_key_hex=ceb009aea4454451feadf0e6b36f45555dd04723baa448e8
aes_192_ccm_aad_hex=6e80dd7f1badf3a1c9ab25c75f10bde78c23fa0eb8f9aaa53adefbf4cbf78fe4
aes_192_ccm_nonce_hex=764043c49460b7
aes_256_ccm_key_hex=ceb009aea4454451feadf0e6b36f455555dd04723baa448e80102030405060708
aes_256_ccm_aad_hex=6e80dd7f1badf3a1c9ab25c75f10bde78c23fa0eb8f9aaa53adefbf4cbf78fe3
aes_256_ccm_nonce_hex=764043c49460b3

aes_128_gcm_key_hex=eebc1f57487f51921c0465665f8ae6d1
aes_128_gcm_aad_hex=64d23c3cec334b49bdb370c437fec78d1
aes_128_gcm_iv_hex=99aa3e68ed8173a0eed06681
aes_192_gcm_key_hex=eebc1f57487f51921c0465665f8ae6d1658bb26de6f8a062
aes_192_gcm_aad_hex=4d23c3cec334b49bdb370c437fec78d2
aes_192_gcm_iv_hex=99aa3e68ed8173a0eed06682
aes_256_gcm_key_hex=eebc1f57487f51921c0465665f8ae6d1658bb26de6f8a069a3520293a572078f
aes_256_gcm_aad_hex=4d23c3cec334b49bdb370c437fec78de
aes_256_gcm_iv_hex=99aa3e68ed8173a0eed06684

# hash input
md5_hmac_char_key=Jefe

sha_hmac_plain_string=./plain_data/hash/sha1_and_sha2/sha_hmac.txt
sha_hmac_char_key=Jefe

ghash_key_hex=25629347589242761d31f826ba4b757b

cbc_mac_key_128_hex=c0c1c2c3c4c5c6c7c8c9cacbcccdcecf
cbc_mac_key_192_hex=2b7e151628aed2a6abf7158809cf4f3c1122334455667788
cbc_mac_key_256_hex=2b7e151628aed2a6abf7158809cf4f3c11223344556677881122334455667788

xcbc_mac_key_128_hex=000102030405060708090a0b0c0d0e0f
xcbc_mac_key_192_hex=000102030405060708090a0b0c0d0e0f0001020304050607
xcbc_mac_key_256_hex=000102030405060708090a0b0c0d0e0f00010203040506070001020304050607

cmac_key_128_hex=2b7e151628aed2a6abf7158809cf4f3c
cmac_key_192_hex=2b7e151628aed2a6abf7158809cf4f3c1122334455667788
cmac_key_256_hex=2b7e151628aed2a6abf7158809cf4f3c11223344556677881122334455667788

function reset_plain_var()
{
	des_3des_plain_string=./plain_data/crypto/plain.txt
	aes_plain_string=./plain_data/crypto/plain.txt
	aes_128_cbc_plain_string=./plain_data/crypto/aes_128_cbc.txt
	aes_icm_plain_string=./plain_data/crypto/aes_icm.txt
	aes_128_ccm_plain_string=./plain_data/crypto/aes_128_ccm.txt
	aes_192_ccm_plain_string=./plain_data/crypto/aes_192_ccm.txt
	aes_256_ccm_plain_string=./plain_data/crypto/aes_256_ccm.txt
	aes_gcm_plain_string=./plain_data/crypto/aes_gcm.txt

	md5_plain_string=./plain_data/hash/md5/md5_basic.txt
	md5_hmac_plain_string=./plain_data/hash/md5/md5_hmac.txt
	sha_plain_string=./plain_data/hash/sha1_and_sha2/sha.txt
	crc32_plain_string=./plain_data/hash/crc32/crc32.txt
	ghash_plain_hex=./plain_data/hash/ghash/ghash.txt
	cbc_mac_plain_string=./plain_data/hash/mac/cbc_mac.txt
	xcbc_mac_96_plain_string=./plain_data/hash/mac/xcbc_mac_96.txt
	xcbc_mac_prf_plain_string=./plain_data/hash/mac/xcbc_mac_prf.txt
	cmac_plain_hex=./plain_data/hash/mac/cmac.txt
}

function confirm_only_for_dec_plain_str()
{
	des_cbc_plain=./plain_data/crypto/encrypted/des_cbc.txt
	des_ecb_plain=./plain_data/crypto/encrypted/des_ecb.txt
	des_ede3_ecb_plain=./plain_data/crypto/encrypted/des_ede3_ecb.txt
	des_ede3_cbc_plain=./plain_data/crypto/encrypted/des_ede3_cbc.txt
	aes_128_cbc_plain=./plain_data/crypto/encrypted/aes_128_cbc.txt
	aes_128_gcm_plain=./plain_data/crypto/encrypted/aes_128_gcm.txt
	aes_192_cbc_plain=./plain_data/crypto/encrypted/aes_192_cbc.txt
	aes_192_gcm_plain=./plain_data/crypto/encrypted/aes_192_gcm.txt
	aes_256_cbc_plain=./plain_data/crypto/encrypted/aes_256_cbc.txt
	aes_256_gcm_plain=./plain_data/crypto/encrypted/aes_256_gcm.txt
	aes_128_ccm_plain=./plain_data/crypto/encrypted/aes_128_ccm.txt
	aes_128_icm_plain=./plain_data/crypto/encrypted/aes_128_icm.txt
	aes_192_ccm_plain=./plain_data/crypto/encrypted/aes_192_ccm.txt
	aes_192_icm_plain=./plain_data/crypto/encrypted/aes_192_icm.txt
	aes_256_ccm_plain=./plain_data/crypto/encrypted/aes_256_ccm.txt
	aes_256_icm_plain=./plain_data/crypto/encrypted/aes_256_icm.txt
	aes_128_ecb_plain=./plain_data/crypto/encrypted/aes_128_ecb.txt
	aes_192_ecb_plain=./plain_data/crypto/encrypted/aes_192_ecb.txt
	aes_256_ecb_plain=./plain_data/crypto/encrypted/aes_256_ecb.txt
	aes_128_ofb_cfb_ctr_plain=./plain_data/crypto/encrypted/aes_128_ofb_cfb_ctr.txt
	aes_192_ofb_cfb_ctr_plain=./plain_data/crypto/encrypted/aes_192_ofb_cfb_ctr.txt
	aes_256_ofb_cfb_ctr_plain=./plain_data/crypto/encrypted/aes_256_ofb_cfb_ctr.txt
}

function add_to_struct_init()
{
	echo -e \
	"#ifndef __DATA_H__\n" \
	"#define __DATA_H__\n" \
	"struct crypto {\n" \
	"char *name;\n" \
	"unsigned char *in;\n" \
	"unsigned char *key;\n" \
	"unsigned char *iv;\n" \
	"unsigned char *nonce;\n" \
	"unsigned char *aad;\n" \
	"unsigned char *out;\n" \
	"};\n" \
	"struct hash {\n" \
	"char *name;\n" \
	"unsigned char *in;\n" \
	"unsigned char *key;\n" \
	"unsigned char *out;\n" \
	"};\n" \
	"struct combined {\n" \
	"char *crypto_name;\n" \
	"unsigned char *in;\n" \
	"unsigned char *crypto_key;\n" \
	"unsigned char *iv;\n" \
	"unsigned char *nonce;\n" \
	"unsigned char *aad;\n" \
	"char *hash_name;\n" \
	"unsigned char *hash_key;\n" \
	"unsigned char *out;\n" \
	"};\n" >> out/data.h
}

function crypto_struct_out()
{
	echo -n "{" >> out/data.h
	echo -n "\"$2\"," >> out/data.h
	if [ $single_to_file_flag == 1 ]
	then
		echo -n "$(echo $2 | sed 's/-/_/g')_in," >> out/data.h
	elif [ $single_to_file_flag == 0 ]
	then
		echo -n "$(echo $tmp_combined_name | sed 's/-/_/g')_in," >> out/data.h
	fi
	echo -n "$(echo $2 | sed 's/-/_/g')_key_hex," >> out/data.h
	if [ $1 == "iv" ]
	then
		echo -n "$(echo $2 | sed 's/-/_/g')_iv_hex," >> out/data.h
		echo -n "NULL," >> out/data.h
		echo -n "NULL," >> out/data.h
	elif [ $1 == "noiv" ]
	then
		echo -n "NULL," >> out/data.h
		echo -n "NULL," >> out/data.h
		echo -n "NULL," >> out/data.h
	elif [ $1 == "nonce" ]
	then
		echo -n "$(echo $2 | sed 's/-/_/g')_key_hex," >> out/data.h
		echo -n "$(echo $2 | sed 's/-/_/g')_nonce_hex," >> out/data.h
		echo -n "NULL," >> out/data.h
	elif [ $1 == "aad_nonce" ]
	then
		echo -n "NULL," >> out/data.h
		echo -n "$(echo $2 | sed 's/-/_/g')_nonce_hex," >> out/data.h
		echo -n "$(echo $2 | sed 's/-/_/g')_aad_hex," >> out/data.h
	elif [ $1 == "aad_iv" ]
	then
		echo -n "$(echo $2 | sed 's/-/_/g')_iv_hex," >> out/data.h
		echo -n "NULL," >> out/data.h
		echo -n "$(echo $2 | sed 's/-/_/g')_aad_hex," >> out/data.h
	fi
	if [ $single_to_file_flag == 1 ]
	then
		echo -n "$(echo $2 | sed 's/-/_/g')_out," >> out/data.h
		echo "}," >> out/data.h
	fi
}

function hash_struct_out()
{
	if [ $single_to_file_flag == 1 ]
	then
		echo -n "{" >> out/data.h
	fi
	echo -n "\"$2\"," >> out/data.h
	if [ $single_to_file_flag == 1 ]
	then
		echo -n "$(echo $2 | sed 's/-/_/g')_in," >> out/data.h
	fi
	if [ $1 == "nokey" ]
	then
		echo -n "NULL," >> out/data.h
	elif [ $1 == "key" ]
	then
		echo -n "$(echo $2 | sed 's/-/_/g')_key," >> out/data.h
	fi
	if [ $single_to_file_flag == 1 ]
	then
		echo -n "$(echo $2 | sed 's/-/_/g')_out," >> out/data.h
	elif [ $single_to_file_flag == 0 ]
	then
		echo -n "$(echo $tmp_combined_name | sed 's/-/_/g')_out," >> out/data.h
	fi
	echo "}," >> out/data.h
}

function append_struct()
{
	echo "struct crypto crypto_data[] = {" >> out/data.h
	for crypto_name in des-ecb des-ede3-ecb aes-128-ecb \
			   aes-192-ecb aes-256-ecb
	do
		crypto_struct_out noiv $crypto_name
	done
	for crypto_name in des-cbc des-ede3-cbc aes-128-cbc \
			   aes-128-ofb aes-128-cfb aes-128-ctr \
			   aes-192-cbc aes-192-ofb aes-192-cfb aes-192-ctr \
			   aes-256-cbc aes-256-ofb aes-256-cfb \
			   aes-256-ctr
	do
		crypto_struct_out iv $crypto_name
	done
	for crypto_name in aes-128-icm aes-192-icm aes-256-icm
	do
		crypto_struct_out nonce $crypto_name
	done
	for crypto_name in aes-128-ccm aes-192-ccm aes-256-ccm
	do
		crypto_struct_out aad_nonce $crypto_name
	done
	for crypto_name in aes-128-gcm aes-192-gcm aes-256-gcm
	do
		crypto_struct_out aad_iv $crypto_name
	done
	echo "};" >> out/data.h

	echo "struct hash hash_data[] = {" >> out/data.h
	for hash_name in md5 sha1 sha224 sha256 sha384 sha512 crc32		 
	do
		hash_struct_out nokey $hash_name
	done
	for hash_name in md5-hmac sha1-hmac sha224-hmac sha256-hmac sha384-hmac sha512-hmac \
			 ghash aes-128-cmac aes-192-cmac aes-256-cmac aes-128-xcbc-mac-96 \
			 aes-192-xcbc-mac-96 aes-256-xcbc-mac-96 aes-128-xcbc-mac-prf aes-192-xcbc-mac-prf \
			 aes-256-xcbc-mac-prf aes-128-cbc-mac aes-192-cbc-mac aes-256-cbc-mac
	do
		hash_struct_out key $hash_name
	done
	echo "};" >> out/data.h
}

function combined_hash_part()
{
	for hash_name in md5 sha1 sha224 sha256 sha384 sha512 crc32		 
	do
		tmp_combined_name=enc_$2_$hash_name
		crypto_struct_out $1 $2
		hash_struct_out nokey $hash_name
	done
	for hash_name in md5-hmac sha1-hmac sha224-hmac sha256-hmac sha384-hmac sha512-hmac \
			 aes-128-xcbc-mac-96 \
			 aes-192-xcbc-mac-96 aes-256-xcbc-mac-96 aes-128-xcbc-mac-prf aes-192-xcbc-mac-prf \
			 aes-256-xcbc-mac-prf
	do
		tmp_combined_name=enc_$2_$hash_name
		crypto_struct_out $1 $2
		hash_struct_out key $hash_name
	done
}

function left_combined()
{
	echo "struct combined dec_hash_data[1];" >> out/data.h
	echo "struct combined hash_enc_data[1];" >> out/data.h
	echo "struct combined hash_dec_data[1];" >> out/data.h
	echo "#endif" >> out/data.h
}

function append_combined_struct()
{
	echo "struct combined enc_hash_data[] = {" >> out/data.h
	for crypto_name in des-ecb des-ede3-ecb aes-128-ecb \
			   aes-192-ecb aes-256-ecb
	do
		combined_hash_part noiv $crypto_name
	done
	for crypto_name in des-cbc des-ede3-cbc aes-128-cbc \
			   aes-128-ofb aes-128-cfb aes-128-ctr \
			   aes-192-cbc aes-192-ofb aes-192-cfb aes-192-ctr \
			   aes-256-cbc aes-256-ofb aes-256-cfb \
			   aes-256-ctr
	do
		combined_hash_part iv $crypto_name
	done
	for crypto_name in aes-128-icm aes-192-icm aes-256-icm
	do
		combined_hash_part nonce $crypto_name
	done
	echo "};" >> out/data.h

	left_combined
}

function hex_format()
{
	i=0
	in_str=$1
	while [ $i -lt ${#in_str} ]
	do
		echo -n "\x" >> out/data.h
		echo -n ${in_str:i:2} >> out/data.h
		i=$((i+2))
	done
}

function crypto_output_to_file()
{
	if [ $1 == "plain" ] || [ $1 == "key" ] || [ $1 == "iv" ] || [ $1 == "nonce" ] || [ $1 == "aad" ]
	then
		if [ $1 == "key" ] || [ $1 == "iv" ] || [ $1 == "nonce" ] || [ $1 == "aad" ]
		then
			echo -n "static unsigned char $(echo $2 | sed 's/-/_/g')_$1_hex[] = \"" >> out/data.h
			echo -n $3 >> out/data.h
		else
			echo -n "static unsigned char $(echo $2 | sed 's/-/_/g')_in[] = \"" >> out/data.h
			cat $3 >> out/data.h
		fi
		echo "\";" >> out/data.h
	elif [ $1 == "out" ]
	then
		echo -n "static unsigned char $(echo $2 | sed 's/-/_/g')_$1[] = \"" >> out/data.h
		hex_format $3
		if [ $1 == "out" ]
		then
			echo -e "\";\n" >> out/data.h
		else
			echo "\";" >> out/data.h
		fi
	fi
}

function hash_output_to_file()
{
	if [ $1 == "plain" ]
	then
		echo -n "static unsigned char $(echo $2 | sed 's/-/_/g')_in[] = \"" >> out/data.h
		cat $3 >> out/data.h
		echo "\";" >> out/data.h
	elif [ $1 == "key" ]
	then
		echo "static unsigned char $(echo $2 | sed 's/-/_/g')_$1[] = \"$3\";" >> out/data.h
	elif [ $1 == "out" ]
	then
		echo -n "static unsigned char $(echo $2 | sed 's/-/_/g')_$1[] = \"" >> out/data.h
		hex_format $3
		if [ $1 == "out" ]
		then
			echo -e "\";\n" >> out/data.h
		else
			echo "\";" >> out/data.h
		fi
	fi
}

function crypto_log_output()
{
	if [ $2 == "iv" ]
	then
		echo "$1 plain string:"
		cat $3
		echo ""
		echo "$1 key hex:"
		echo $4
		echo "$1 iv hex:"
		echo $5
		echo "$1 cipher hex:"
		if [ $single_to_file_flag == 1 ]
		then
			crypto_output_to_file plain $1 $3
			crypto_output_to_file key $1 $4
			crypto_output_to_file iv $1 $5
		fi
	elif [ $2 == "noiv" ]
	then
		echo "$1 plain string:"
		cat $3
		echo ""
		echo "$1 key hex:"
		echo $4
		echo "$1 cipher hex:"
		if [ $single_to_file_flag == 1 ]
		then
			crypto_output_to_file plain $1 $3
			crypto_output_to_file key $1 $4
		fi
	elif [ $2 == "nonce" ]
	then
		echo "$1 plain string:"
		cat $3
		echo ""
		echo "$1 key hex:"
		echo $4
		echo "$1 nonce hex:"
		echo $5
		echo "$1 cipher hex:"
		if [ $single_to_file_flag == 1 ]
		then
			crypto_output_to_file plain $1 $3
			crypto_output_to_file key $1 $4
			crypto_output_to_file nonce $1 $5
		fi
	elif [ $2 == "aad_nonce" ]
	then
		echo "$1 plain string:"
		cat $3
		echo ""
		echo "$1 key hex:"
		echo $4
		echo "$1 aad hex:"
		echo $5
		echo "$1 nonce hex:"
		echo $6
		echo "$1 cipher hex:"
		if [ $single_to_file_flag == 1 ]
		then
			crypto_output_to_file plain $1 $3
			crypto_output_to_file key $1 $4
			crypto_output_to_file aad $1 $5
			crypto_output_to_file nonce $1 $6
		fi
	elif [ $2 == "aad_iv" ]
	then
		echo "$1 plain string:"
		cat $3
		echo ""
		echo "$1 key hex:"
		echo $4
		echo "$1 aad hex:"
		echo $5
		echo "$1 iv hex:"
		echo $6
		echo "$1 cipher hex:"
		if [ $single_to_file_flag == 1 ]
		then
			crypto_output_to_file plain $1 $3
			crypto_output_to_file key $1 $4
			crypto_output_to_file aad $1 $5
			crypto_output_to_file iv $1 $6
		fi
	fi
}

function calculate_crypto()
{
	if [ $3 == "osl_iv" ]
	then
		crypto_log_output $2 iv $4 $5 $6
		if [ $2 == "des-ecb" ] || [ $2 == "des-cbc" ]
		then
			if [ $1 == "enc" ]
			then
				openssl enc -e -$2 -in $4 -K $5 -iv $6 -provider legacy -provider default | xxd -ps -c 200 | tee out/tmp_value.txt
				if [ $single_to_file_flag == 1 ]
				then
					crypto_output_to_file out $2 $(cat out/tmp_value.txt)
				fi
				rm out/tmp_value.txt
			elif [ $1 == "dec" ]
			then
				openssl enc -d -$2 -in $4 -K $5 -iv $6 -provider legacy -provider default | xxd -ps -c 200
			fi
		else
			if [ $1 == "enc" ]
			then
				openssl enc -e -$2 -in $4 -K $5 -iv $6 | xxd -ps -c 200 | tee out/tmp_value.txt
				if [ $single_to_file_flag == 1 ]
				then
					crypto_output_to_file out $2 $(cat out/tmp_value.txt)
				fi
				rm out/tmp_value.txt
			elif [ $1 == "dec" ]
			then
				openssl enc -d -$2 -in $4 -K $5 -iv $6 | xxd -ps -c 200
			fi
		fi
		echo ""
	elif [ $3 == "osl_noiv" ]
	then
		crypto_log_output $2 noiv $4 $5
		if [ $2 == "des-ecb" ] || [ $2 == "des-cbc" ]
		then
			if [ $1 == "enc" ]
			then
				openssl enc -e -$2 -in $4 -K $5 -provider legacy -provider default | xxd -ps -c 200 | tee out/tmp_value.txt
				if [ $single_to_file_flag == 1 ]
				then
					crypto_output_to_file out $2 $(cat out/tmp_value.txt)
				fi
				rm out/tmp_value.txt
			elif [ $1 == "dec" ]
			then
				openssl enc -d -$2 -in $4 -K $5 -provider legacy -provider default | xxd -ps -c 200
			fi
		else
			if [ $1 == "enc" ]
			then
				openssl enc -e -$2 -in $4 -K $5 | xxd -ps -c 200 | tee out/tmp_value.txt
				if [ $single_to_file_flag == 1 ]
				then
					crypto_output_to_file out $2 $(cat out/tmp_value.txt)
				fi
				rm out/tmp_value.txt
			elif [ $1 == "dec" ]
			then
				openssl enc -d -$2 -in $4 -K $5 | xxd -ps -c 200
			fi
		fi
		echo ""
	elif [ $3 == "null" ]
	then
		if [ $2 == "aes-128-icm" ] || [ $2 == "aes-192-icm" ] || [ $2 == "aes-256-icm" ]
		then
			crypto_log_output $2 nonce $4 $5 $6
			./aesicm $4 $5 $6 | tee out/tmp_value.txt
			if [ $single_to_file_flag == 1 ]
			then
				crypto_output_to_file out $2 $(cat out/tmp_value.txt)
			fi
			rm out/tmp_value.txt
			echo ""
		elif [ $2 == "aes-128-ccm" ] || [ $2 == "aes-192-ccm" ] || [ $2 == "aes-256-ccm" ]
		then
			crypto_log_output $2 aad_nonce $4 $5 $6 $7
			./aesccm $4 $5 $6 $7 | tee out/tmp_value.txt
			if [ $single_to_file_flag == 1 ]
			then
				crypto_output_to_file out $2 $(cat out/tmp_value.txt)
			fi
			rm out/tmp_value.txt
			echo ""
		elif [ $2 == "aes-128-gcm" ] || [ $2 == "aes-192-gcm" ] || [ $2 == "aes-256-gcm" ]
		then
			crypto_log_output $2 aad_iv $4 $5 $6 $7
			./aesgcm $4 $5 $6 $7 | tee out/tmp_value.txt
			if [ $single_to_file_flag == 1 ]
			then
				crypto_output_to_file out $2 $(cat out/tmp_value.txt)
			fi
			rm out/tmp_value.txt
			echo ""
		fi
	fi
}

function name_tranform()
{
#	if [ $2 == "aes-128-ofb" ] || [ $2 == "aes-192-ofb" ] || [ $2 == "aes-256-ofb" ]
#	then
#		combined_crypto_name=aes_128_ofb
#	elif [ $2 == "aes-192-ofb" ]
#	then
#		combined_crypto_name=aes_192_ofb
#	elif [ $2 == "aes-256-ofb" ]
#	then
#		combined_crypto_name=aes_256_ofb
#	fi

	if [ $1 == "md5-basic" ]
	then
		combined_hash_name=md5
	elif [ $1 == "sha1-basic" ]
	then
		combined_hash_name=sha1
	elif [ $1 == "sha2-224-basic" ]
	then
		combined_hash_name=sha224
	elif [ $1 == "sha2-224-hmac" ]
	then
		combined_hash_name=sha224_hmac
	elif [ $1 == "sha2-256-basic" ]
	then
		combined_hash_name=sha256
	elif [ $1 == "sha2-256-hmac" ]
	then
		combined_hash_name=sha256_hmac
	elif [ $1 == "sha2-384-basic" ]
	then
		combined_hash_name=sha384
	elif [ $1 == "sha2-384-hmac" ]
	then
		combined_hash_name=sha384_hmac
	elif [ $1 == "sha2-512-basic" ]
	then
		combined_hash_name=sha512
	elif [ $1 == "sha2-512-hmac" ]
	then
		combined_hash_name=sha512_hmac
	fi
	combined_crypto_name=$(echo $combined_crypto_name | sed 's/-/_/g')
	combined_hash_name=$(echo $combined_hash_name | sed 's/-/_/g')
}

function crypto_hash_out_to_file()
{
	if [ $single_to_file_flag == 0 ] && [ $combined_flag == 1 ]
	then
		if [ $hash_first == 0 ]
		then
			echo "static unsigned char $1_${combined_crypto_name}_${combined_hash_name}_in[] = \"$(cat $2)\";" >> out/data.h
		fi
	fi
}

function crypto_func()
{
	if [ $2 == "des-ecb" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $des_3des_plain_string
			calculate_crypto $1 $2 osl_noiv $des_3des_plain_string $des_key_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_noiv $des_ecb_plain $des_key_hex
		fi
	elif [ $2 == "des-cbc" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $des_3des_plain_string
			calculate_crypto $1 $2 osl_iv $des_3des_plain_string $des_key_hex $des_3des_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $des_cbc_plain $des_key_hex $des_3des_iv_hex
		fi
	elif [ $2 == "des-ede3-ecb" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $des_3des_plain_string
			calculate_crypto $1 $2 osl_noiv $des_3des_plain_string $des_ede3_key_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_noiv $des_ede3_ecb_plain $des_ede3_key_hex
		fi
	elif [ $2 == "des-ede3-cbc" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $des_3des_plain_string
			calculate_crypto $1 $2 osl_iv $des_3des_plain_string $des_ede3_key_hex $des_3des_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $des_ede3_cbc_plain $des_ede3_key_hex $des_3des_iv_hex
		fi
	elif [ $2 == "aes-128-ecb" ] 
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_noiv $aes_plain_string $aes_128_key_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_noiv $aes_128_ecb_plain $aes_128_key_hex
		fi
	elif [ $2 == "aes-128-cbc" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_128_cbc_plain_string
			calculate_crypto $1 $2 osl_iv $aes_128_cbc_plain_string $aes_128_cbc_key_hex $aes_128_cbc_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $aes_128_cbc_plain $aes_128_cbc_key_hex $aes_128_cbc_iv_hex
		fi
	elif [ $2 == "aes-128-ofb" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 aes-128-ofb osl_iv $aes_plain_string $aes_128_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then

			calculate_crypto $1 aes-128-ofb osl_iv $aes_128_ofb_cfb_ctr_plain $aes_128_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-128-cfb" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_iv $aes_plain_string $aes_128_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $aes_128_ofb_cfb_ctr_plain $aes_128_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-128-ctr" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_iv $aes_plain_string $aes_128_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $aes_128_ofb_cfb_ctr_plain $aes_128_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-128-icm" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_icm_plain_string
			calculate_crypto $1 $2 null $aes_icm_plain_string $aes_128_icm_key_hex $aes_128_icm_nonce_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 null $aes_128_icm_plain $aes_128_icm_key_hex $aes_128_icm_nonce_hex
		fi
	elif [ $2 == "aes-128-ccm" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_128_ccm_plain_string
			calculate_crypto $1 $2 null $aes_128_ccm_plain_string $aes_128_ccm_key_hex $aes_128_ccm_aad_hex $aes_128_ccm_nonce_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 null $aes_128_ccm_plain $aes_128_ccm_key_hex $aes_128_ccm_aad_hex $aes_128_ccm_nonce_hex
		fi
	elif [ $2 == "aes-128-gcm" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_gcm_plain_string
			calculate_crypto $1 $2 null $aes_gcm_plain_string $aes_128_gcm_key_hex $aes_128_gcm_aad_hex $aes_128_gcm_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 null $aes_128_gcm_plain $aes_128_gcm_key_hex $aes_128_gcm_aad_hex $aes_128_gcm_iv_hex
		fi
	elif [ $2 == "aes-192-ecb" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_noiv $aes_plain_string $aes_192_key_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_noiv $aes_192_ecb_plain $aes_192_key_hex
		fi
	elif [ $2 == "aes-192-cbc" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_iv $aes_plain_string $aes_192_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $aes_192_cbc_plain $aes_192_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-192-ofb" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 aes-192-ofb osl_iv $aes_plain_string $aes_192_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 aes-192-ofb osl_iv $aes_192_ofb_cfb_ctr_plain $aes_192_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-192-cfb" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_iv $aes_plain_string $aes_192_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $aes_192_ofb_cfb_ctr_plain $aes_192_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-192-ctr" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_iv $aes_plain_string $aes_192_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $aes_192_ofb_cfb_ctr_plain $aes_192_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-192-icm" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_icm_plain_string
			calculate_crypto $1 $2 null $aes_icm_plain_string $aes_192_icm_key_hex $aes_192_icm_nonce_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 null $aes_192_icm_plain $aes_192_icm_key_hex $aes_192_icm_nonce_hex
		fi
	elif [ $2 == "aes-192-ccm" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_192_ccm_plain_string
			calculate_crypto $1 $2 null $aes_192_ccm_plain_string $aes_192_ccm_key_hex $aes_192_ccm_aad_hex $aes_192_ccm_nonce_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 null $aes_192_ccm_plain $aes_192_ccm_key_hex $aes_192_ccm_aad_hex $aes_192_ccm_nonce_hex
		fi
	elif [ $2 == "aes-192-gcm" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_gcm_plain_string
			calculate_crypto $1 $2 null $aes_gcm_plain_string $aes_192_gcm_key_hex $aes_192_gcm_aad_hex $aes_192_gcm_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 null $aes_192_gcm_plain $aes_192_gcm_key_hex $aes_192_gcm_aad_hex $aes_192_gcm_iv_hex
		fi
	elif [ $2 == "aes-256-ecb" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_noiv $aes_plain_string $aes_256_key_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_noiv $aes_256_ecb_plain $aes_256_key_hex
		fi
	elif [ $2 == "aes-256-cbc" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_iv $aes_plain_string $aes_256_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $aes_256_cbc_plain $aes_256_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-256-ofb" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 aes-256-ofb osl_iv $aes_plain_string $aes_256_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 aes-256-ofb osl_iv $aes_256_ofb_cfb_ctr_plain $aes_256_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-256-cfb" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_iv $aes_plain_string $aes_256_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $aes_256_ofb_cfb_ctr_plain $aes_256_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-256-ctr" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_plain_string
			calculate_crypto $1 $2 osl_iv $aes_plain_string $aes_256_key_hex $aes_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 osl_iv $aes_256_ofb_cfb_ctr_plain $aes_256_key_hex $aes_iv_hex
		fi
	elif [ $2 == "aes-256-icm" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_icm_plain_string
			calculate_crypto $1 $2 null $aes_icm_plain_string $aes_256_icm_key_hex $aes_256_icm_nonce_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 null $aes_256_icm_plain $aes_256_icm_key_hex $aes_256_icm_nonce_hex
		fi
	elif [ $2 == "aes-256-ccm" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_256_ccm_plain_string
			calculate_crypto $1 $2 null $aes_256_ccm_plain_string $aes_256_ccm_key_hex $aes_256_ccm_aad_hex $aes_256_ccm_nonce_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 null $aes_256_ccm_plain $aes_256_ccm_key_hex $aes_256_ccm_aad_hex $aes_256_ccm_nonce_hex
		fi
	elif [ $2 == "aes-256-gcm" ]
	then
		if [ $1 == "enc" ]
		then
			crypto_hash_out_to_file $1 $aes_gcm_plain_string
			calculate_crypto $1 $2 null $aes_gcm_plain_string $aes_256_gcm_key_hex $aes_256_gcm_aad_hex $aes_256_gcm_iv_hex
		elif [ $1 == "dec" ]
		then
			calculate_crypto $1 $2 null $aes_256_gcm_plain $aes_256_gcm_key_hex $aes_256_gcm_aad_hex $aes_256_gcm_iv_hex
		fi
	fi
}

function hash_log_output()
{
	if [ $2 == "key" ]
	then
		echo "$1 plain string:"
		cat $3
		echo ""
		echo "$1 key string:"
		echo $4
		echo "$1 hashed hex:"
		if [ $single_to_file_flag == 1 ]
		then
			hash_output_to_file plain $1 $3
			hash_output_to_file key $1 $4
		fi
	else
		echo "$1 plain string:"
		cat $2
		echo ""
		echo "$1 hashed hex:"
		if [ $single_to_file_flag == 1 ]
		then
			hash_output_to_file plain $1 $2
		fi
	fi
}

function calculate_digest()
{
	if [ $2 == "basic" ]
	then
		hash_log_output $1 $3
		openssl dgst -$1 $3 | awk '{print $2}' | tee out/tmp_value.txt
		echo ""
		if [ $single_to_file_flag == 1 ]
		then
			hash_output_to_file out $1 $(cat out/tmp_value.txt)
		fi
		rm out/tmp_value.txt
	elif [ $2 == "hmac" ]
	then
		hash_log_output $1-$2 key $3 $4
		openssl dgst -$1 -$2 $4 $3 | awk '{print $2}' | tee out/tmp_value.txt
		echo ""
		if [ $single_to_file_flag == 1 ]
		then
			hash_output_to_file out $1_$2 $(cat out/tmp_value.txt)
		fi
		rm out/tmp_value.txt
	elif [ $2 == "null" ]
	then
		if [ $1 == "crc32" ]
		then
			hash_log_output $1 $3
			crc32 $3 | tee out/tmp_value.txt
			echo ""
			if [ $single_to_file_flag == 1 ]
			then
				hash_output_to_file out $1 $(cat out/tmp_value.txt)
			fi
			rm out/tmp_value.txt
		elif [ $1 == "ghash" ]
		then
			hash_log_output $1 key $3 $4
			./rambusghash $3 $4 | tee out/tmp_value.txt
			echo ""
			if [ $single_to_file_flag == 1 ]
			then
				hash_output_to_file out $1 $(cat out/tmp_value.txt)
			fi
			rm out/tmp_value.txt
		elif [ $1 == "aes-128-cbc-mac" ] || [ $1 == "aes-192-cbc-mac" ] || [ $1 == "aes-256-cbc-mac" ]
		then
			hash_log_output $1 key $3 $4
			node aescbcmac.js $3 $4 | tee out/tmp_value.txt
			echo ""
			if [ $single_to_file_flag == 1 ]
			then
				hash_output_to_file out $1 $(cat out/tmp_value.txt)
			fi
			rm out/tmp_value.txt
		elif [ $1 == "aes-128-xcbc-mac-96" ] || [ $1 == "aes-192-xcbc-mac-96" ] || [ $1 == "aes-256-xcbc-mac-96" ] ||\
		     [ $1 == "aes-128-xcbc-mac-prf" ] || [ $1 == "aes-192-xcbc-mac-prf" ] || [ $1 == "aes-256-xcbc-mac-prf" ]
		then
			hash_log_output $1 key $3 $4
			./aesxcbcmac $3 $4 | tee out/tmp_value.txt
			echo ""
			if [ $single_to_file_flag == 1 ]
			then
				hash_output_to_file out $1 $(cat out/tmp_value.txt)
			fi
			rm out/tmp_value.txt
		elif [ $1 == "aes-128-cmac" ] || [ $1 == "aes-192-cmac" ] || [ $1 == "aes-256-cmac" ]
		then
			hash_log_output $1 key $3 $4
			./aescmac $3 $4 | tee out/tmp_value.txt
			echo ""
			if [ $single_to_file_flag == 1 ]
			then
				hash_output_to_file out $1 $(cat out/tmp_value.txt)
			fi
			rm out/tmp_value.txt
		fi
	fi
}

function hash_func()
{
	if [ $1 == "md5-basic" ]
	then
		calculate_digest md5 basic $md5_plain_string
	elif [ $1 == "md5-hmac" ]
	then
		calculate_digest md5 hmac $md5_hmac_plain_string $md5_hmac_char_key
	elif [ $1 == "sha1-basic" ]
	then
		calculate_digest sha1 basic $sha_plain_string
	elif [ $1 == "sha1-hmac" ]
	then
		calculate_digest sha1 hmac $sha_hmac_plain_string $sha_hmac_char_key
	elif [ $1 == "sha2-224-basic" ]
	then
		calculate_digest sha224 basic $sha_plain_string
	elif [ $1 == "sha2-224-hmac" ]
	then
		calculate_digest sha224 hmac $sha_hmac_plain_string $sha_hmac_char_key
	elif [ $1 == "sha2-256-basic" ]
	then
		calculate_digest sha256 basic $sha_plain_string
	elif [ $1 == "sha2-256-hmac" ]
	then
		calculate_digest sha256 hmac $sha_hmac_plain_string $sha_hmac_char_key
	elif [ $1 == "sha2-384-basic" ]
	then
		calculate_digest sha384 basic $sha_plain_string
	elif [ $1 == "sha2-384-hmac" ]
	then
		calculate_digest sha384 hmac $sha_hmac_plain_string $sha_hmac_char_key
	elif [ $1 == "sha2-512-basic" ]
	then
		calculate_digest sha512 basic $sha_plain_string
	elif [ $1 == "sha2-512-hmac" ]
	then
		calculate_digest sha512 hmac $sha_hmac_plain_string $sha_hmac_char_key
	elif [ $1 == "crc32" ]
	then
		calculate_digest crc32 null $crc32_plain_string
	elif [ $1 == "ghash" ]
	then
		calculate_digest ghash null $ghash_plain_hex $ghash_key_hex
	elif [ $1 == "aes-128-cbc-mac" ]
	then
		calculate_digest aes-128-cbc-mac null $cbc_mac_plain_string $cbc_mac_key_128_hex
	elif [ $1 == "aes-192-cbc-mac" ]
	then
		calculate_digest aes-192-cbc-mac null $cbc_mac_plain_string $cbc_mac_key_192_hex
	elif [ $1 == "aes-256-cbc-mac" ]
	then
		calculate_digest aes-256-cbc-mac null $cbc_mac_plain_string $cbc_mac_key_256_hex
	elif [ $1 == "aes-128-xcbc-mac-96" ]
	then
		calculate_digest aes-128-xcbc-mac-96 null $xcbc_mac_96_plain_string $xcbc_mac_key_128_hex
	elif [ $1 == "aes-192-xcbc-mac-96" ]
	then
		calculate_digest aes-192-xcbc-mac-96 null $xcbc_mac_96_plain_string $xcbc_mac_key_192_hex
	elif [ $1 == "aes-256-xcbc-mac-96" ]
	then
		calculate_digest aes-256-xcbc-mac-96 null $xcbc_mac_96_plain_string $xcbc_mac_key_256_hex
	elif [ $1 == "aes-128-xcbc-mac-prf" ]
	then
		calculate_digest aes-128-xcbc-mac-prf null $xcbc_mac_prf_plain_string $xcbc_mac_key_128_hex
	elif [ $1 == "aes-192-xcbc-mac-prf" ]
	then
	 	calculate_digest aes-192-xcbc-mac-prf null $xcbc_mac_prf_plain_string $xcbc_mac_key_192_hex
	elif [ $1 == "aes-256-xcbc-mac-prf" ]
	then
		calculate_digest aes-256-xcbc-mac-prf null $xcbc_mac_prf_plain_string $xcbc_mac_key_256_hex
	elif [ $1 == "aes-128-cmac" ]
	then
		calculate_digest aes-128-cmac null $cmac_plain_hex $cmac_key_128_hex
	elif [ $1 == "aes-192-cmac" ]
	then
		calculate_digest aes-192-cmac null $cmac_plain_hex $cmac_key_192_hex
	elif [ $1 == "aes-256-cmac" ]
	then
		calculate_digest aes-256-cmac null $cmac_plain_hex $cmac_key_256_hex
	fi
}

function single_all_func()
{
	for crypto_name in des-ecb des-cbc des-ede3-ecb des-ede3-cbc aes-128-ecb aes-128-cbc \
			   aes-128-ofb aes-128-cfb aes-128-ctr aes-128-icm aes-128-ccm aes-128-gcm \
			   aes-192-ecb aes-192-cbc aes-192-ofb aes-192-cfb aes-192-ctr aes-192-icm \
			   aes-192-ccm aes-192-gcm aes-256-ecb aes-256-cbc aes-256-ofb aes-256-cfb \
			   aes-256-ctr aes-256-icm aes-256-ccm aes-256-gcm
	do
		crypto_func enc $crypto_name
	done

	for hash_name in md5-basic sha1-basic sha2-224-basic sha2-256-basic sha2-384-basic sha2-512-basic \
			 md5-hmac sha1-hmac sha2-224-hmac sha2-256-hmac sha2-384-hmac sha2-512-hmac crc32 \
			 sha1-ssl-mac ghash aes-128-cmac aes-192-cmac aes-256-cmac aes-128-xcbc-mac-96 \
			 aes-192-xcbc-mac-96 aes-256-xcbc-mac-96 aes-128-xcbc-mac-prf aes-192-xcbc-mac-prf \
			 aes-256-xcbc-mac-prf aes-128-cbc-mac aes-192-cbc-mac aes-256-cbc-mac
	do
		hash_func $hash_name
	done

	if [ $single_to_file_flag == 1 ]
	then
		append_struct
	fi
}

function confirm_hash_input()
{
	tail -n 2 tmp_cipher.txt | head -n 1 > tmp_hash_input.txt
	if [ $1 == "md5-basic" ] || [ $1 == "md5-hmac" ]
	then
		md5_plain_string=./tmp_hash_input.txt
	elif [ $1 == "sha1-basic" ] || [ $1 == "sha1-hmac" ] || [ $1 == "sha2-224-basic" ] ||[ $1 == "sha2-224-hmac" ] ||\
	     [ $1 == "sha2-256-basic" ] || [ $1 == "sha2-256-hmac" ] || [ $1 == "sha2-384-basic" ] || [ $1 == "sha2-384-hmac" ] ||\
	     [ $1 == "sha2-512-basic" ] || [ $1 == "sha2-512-hmac" ]
	then
		sha_plain_string=./tmp_hash_input.txt
	elif [ $1 == "crc32" ]
	then
		crc32_plain_string=./tmp_hash_input.txt
	elif [ $1 == "ghash" ]
	then
		ghash_plain_hex=./tmp_hash_input.txt
	elif [ $1 == "aes-128-cbc-mac" ] || [ $1 == "aes-192-cbc-mac" ] || [ $1 == "aes-256-cbc-mac" ]
	then
		cbc_mac_plain_string=./tmp_hash_input.txt
	elif [ $1 == "aes-128-xcbc-mac-96" ] || [ $1 == "aes-192-xcbc-mac-96" ] || [ $1 == "aes-256-xcbc-mac-96" ]
	then
		xcbc_mac_96_plain_string=./tmp_hash_input.txt
	elif [ $1 == "aes-128-xcbc-mac-prf" ] || [ $1 == "aes-192-xcbc-mac-prf" ] || [ $1 == "aes-256-xcbc-mac-prf" ]
	then
		xcbc_mac_prf_plain_string=./tmp_hash_input.txt
	elif [ $1 == "aes-128-cmac" ] || [ $1 == "aes-192-cmac" ] || [ $1 == "aes-256-cmac" ]
	then
		cmac_plain_hex=./tmp_hash_input.txt
	fi
	rm tmp_cipher.txt
}

function confirm_crypto_input()
{
	tail -n 2 tmp_hash.txt | head -n 1 > tmp_crypto_input.txt
	if [ $1 == "des-ecb" ] || [ $1 == "des-cbc" ] || [ $1 == "des-ede3-ecb" ] || [ $1 == "des-ede3-cbc" ]
	then
		des_3des_plain_string=./tmp_crypto_input.txt
	elif [ $1 == "aes-128-ecb" ] || [ $1 == "aes-128-cbc" ] || [ $1 == "aes-128-ofb" ] || [ $1 == "aes-128-cfb" ] ||\
	     [ $1 == "aes-128-ctr" ] || [ $1 == "aes-192-ecb" ] || [ $1 == "aes-192-cbc" ] || [ $1 == "aes-192-ofb" ] ||\
	     [ $1 == "aes-192-cfb" ] || [ $1 == "aes-192-ctr" ] || [ $1 == "aes-256-ecb" ] || [ $1 == "aes-256-cbc" ] ||\
	     [ $1 == "aes-256-ofb" ] || [ $1 == "aes-256-cfb" ] || [ $1 == "aes-256-ctr" ]
	then
		aes_plain_string=./tmp_crypto_input.txt
	elif [ $1 == "aes-128-icm" ] || [ $1 == "aes-192-icm" ] || [ $1 == "aes-256-icm" ]
	then
		aes_icm_plain_string=./tmp_crypto_input.txt
	elif [ $1 == "aes-128-ccm" ]
	then
		aes_128_ccm_plain_string=./tmp_crypto_input.txt
	elif [ $1 == "aes-128-gcm" ] || [ $1 == "aes-192-gcm" ] || [ $1 == "aes-256-gcm" ]
	then
		aes_gcm_plain_string=./tmp_crypto_input.txt
	elif [ $1 == "aes-192-ccm" ]
	then
		aes_192_ccm_plain_string=./tmp_crypto_input.txt
	elif [ $1 == "aes-256-ccm" ]
	then
		aes_256_ccm_plain_string=./tmp_crypto_input.txt
	fi

	rm tmp_hash.txt
}

function crypto_then_hash_func()
{
	combined_flag=1
	hash_first=0
	combined_crypto_name=$2
	combined_hash_name=$3
	name_tranform $combined_hash_name $combined_crypto_name
	if [ -f tmp_cipher.txt ]
	then
		rm tmp_cipher.txt
	fi
	crypto_func $1 $2 | tee tmp_cipher.txt
	confirm_hash_input $3
	hash_func $3 | tee tmp_result.txt
	if [ $single_to_file_flag == 0 ] && [ $combined_flag == 1 ]
	then
		if [ $hash_first == 0 ]
		then
			tail -n 2 tmp_result.txt | head -n 1 > tmp_result_value.txt
			echo -n "static unsigned char $1_${combined_crypto_name}_${combined_hash_name}_out[] = \"" >> out/data.h
			hex_format $(cat tmp_result_value.txt)
			echo "\";" >> out/data.h
			rm tmp_result_value.txt
		fi
	fi
	rm tmp_result.txt
	rm tmp_hash_input.txt
}

function hash_then_crypto_func()
{
	if [ -f tmp_hash.txt ]
	then
		rm tmp_hash.txt
	fi
	hash_func $2 | tee tmp_hash.txt
	confirm_crypto_input $3
	if [ $1 == "enc" ]
	then
		crypto_func enc $3
	elif [ $1 == "dec" ]
	then
		crypto_func dec $3
	fi
	rm tmp_crypto_input.txt
}

function combined_crypto_hash()
{
	# enc and then hash
	for crypto_name in des-ecb des-cbc des-ede3-ecb des-ede3-cbc aes-128-ecb aes-128-cbc aes-128-ofb \
			   aes-128-cfb aes-128-ctr aes-128-icm aes-192-ecb aes-192-cbc aes-192-ofb aes-192-cfb \
			   aes-192-ctr aes-192-icm aes-256-ecb aes-256-cbc aes-256-ofb aes-256-cfb aes-256-ctr \
			   aes-256-icm
	do
		for hash_name in md5-basic sha1-basic sha2-224-basic sha2-256-basic sha2-384-basic sha2-512-basic \
				 md5-hmac sha1-hmac sha2-224-hmac sha2-256-hmac sha2-384-hmac sha2-512-hmac crc32 \
				 aes-128-xcbc-mac-96 aes-192-xcbc-mac-96 aes-256-xcbc-mac-96 aes-128-xcbc-mac-prf \
				 aes-192-xcbc-mac-prf aes-256-xcbc-mac-prf
		do
			crypto_then_hash_func $1 $crypto_name $hash_name
		done
	done

	# here they was listed alone.
#	for crypto_name in aes-128-ctr aes-192-ctr aes-256-ctr
#	do
#		# ghash
#		for hash_name in ghash
#		do
#			crypto_then_hash_func $1 $crypto_name $hash_name
#		done
#	done
}

function combined_hash_crypto()
{
	# hash and then enc
	for hash_name in md5-basic sha1-basic sha2-224-basic sha2-256-basic sha2-384-basic sha2-512-basic \
			 md5-hmac sha1-hmac sha2-224-hmac sha2-256-hmac sha2-384-hmac sha2-512-hmac crc32 \
			 aes-128-xcbc-mac-96 aes-192-xcbc-mac-96 aes-256-xcbc-mac-96 aes-128-xcbc-mac-prf \
			 aes-192-xcbc-mac-prf aes-256-xcbc-mac-prf
	do
		for crypto_name in des-ecb des-cbc des-ede3-ecb des-ede3-cbc aes-128-ecb aes-128-cbc aes-128-ofb \
				   aes-128-cfb aes-128-ctr aes-128-icm aes-192-ecb aes-192-cbc aes-192-ofb aes-192-cfb \
				   aes-192-ctr aes-192-icm aes-256-ecb aes-256-cbc aes-256-ofb aes-256-cfb aes-256-ctr \
				   aes-256-icm
		do
			hash_then_crypto_func $1 $hash_name $crypto_name
		done
	done

	# here they was listed alone.
	# ghash
	for hash_name in ghash
	do
		for crypto_name in aes-128-ctr aes-192-ctr aes-256-ctr
		do
			hash_then_crypto_func $1 $hash_name $crypto_name
		done
	done
}

function combined_all_func()
{
	combined_crypto_hash enc
	if [ $single_to_file_flag == 0 ]
	then
		append_combined_struct
	fi
#	reset_plain_var
#	confirm_only_for_dec_plain_str
#	combined_crypto_hash dec
#
#	reset_plain_var
#	combined_hash_crypto enc
#	reset_plain_var
#	combined_hash_crypto dec
}

function single_process()
{
	if [ $1 == "des-ecb" ] || [ $1 == "des-cbc" ] ||[ $1 == "des-ede3-ecb" ] || [ $1 == "des-ede3-cbc" ] ||\
	   [ $1 == "aes-128-ecb" ] || [ $1 == "aes-128-cfb" ] || [ $1 == "aes-128-cbc" ] || [ $1 == "aes-128-ofb" ] ||\
	   [ $1 == "aes-128-ctr" ] || [ $1 == "aes-128-ccm" ] || [ $1 == "aes-128-gcm" ] || [ $1 == "aes-128-icm" ] ||\
	   [ $1 == "aes-192-ecb" ] || [ $1 == "aes-192-cfb" ] || [ $1 == "aes-192-cbc" ] || [ $1 == "aes-192-ofb" ] ||\
	   [ $1 == "aes-192-ctr" ] || [ $1 == "aes-192-ccm" ] || [ $1 == "aes-192-gcm" ] || [ $1 == "aes-192-icm" ] ||\
	   [ $1 == "aes-256-ecb" ] || [ $1 == "aes-256-cfb" ] || [ $1 == "aes-256-cbc" ] || [ $1 == "aes-256-ofb" ] ||\
	   [ $1 == "aes-256-ctr" ] || [ $1 == "aes-256-ccm" ] || [ $1 == "aes-256-gcm" ] || [ $1 == "aes-256-icm" ]
	then
		crypto_func enc $1
	elif [ $1 == "md5-basic" ] || [ $1 == "sha1-basic" ] || [ $1 == "sha2-224-basic" ] || [ $1 == "sha2-256-basic" ] ||\
	     [ $1 == "sha2-384-basic" ] || [ $1 == "sha2-512-basic" ] || [ $1 == "md5-hmac" ] || [ $1 == "sha1-hmac" ] ||\
	     [ $1 == "sha2-224-hmac" ] || [ $1 == "sha2-256-hmac" ] || [ $1 == "sha2-384-hmac" ] || [ $1 == "sha2-512-hmac" ] ||\
	     [ $1 == "crc32" ] || [ $1 == "sha1-ssl-mac" ] || [ $1 == "ghash" ] || [ $1 == "aes-128-cmac" ] ||\
	     [ $1 == "aes-192-cmac" ] || [ $1 == "aes-256-cmac" ] || [ $1 == "aes-128-xcbc-mac-96" ] ||\
	     [ $1 == "aes-192-xcbc-mac-96" ] || [ $1 == "aes-256-xcbc-mac-96" ] || [ $1 == "aes-128-xcbc-mac-prf" ] ||\
	     [ $1 == "aes-192-xcbc-mac-prf" ] || [ $1 == "aes-256-xcbc-mac-prf" ] || [ $1 == "aes-128-cbc-mac" ] ||\
	     [ $1 == "aes-192-cbc-mac" ] || [ $1 == "aes-256-cbc-mac" ]
	then
		hash_func $1
	else
		echo "crypto or hash name has error, please re-check!"
	fi
}

if [ -d out ]
then
	rm -rf out
	mkdir -p out
else
	mkdir -p out
fi

# confirm plain text input
reset_plain_var

single_to_file_flag=0
combined_flag=0

if [ $1 == "single_all" ]
then
	single_all_func
elif [ $1 == "combined_all" ]
then
	add_to_struct_init
	combined_all_func
elif [ $1 == "all" ]
then
	add_to_struct_init
	single_to_file_flag=1
	single_all_func
	single_to_file_flag=0
	combined_all_func
elif [ $1 == single ] && [ -n $2 ]
then
	single_process $2
fi

sync


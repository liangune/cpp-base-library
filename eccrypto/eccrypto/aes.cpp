/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   AES加解密
*************************************************************************/

#include "aes.h"
#include <string.h>
#include <ctype.h>
#include "pkcs.h"

uint8_t *Aes::rtrim(uint8_t *str, int *length)
{
	if (str == NULL || *str == '\0')
	{
		return str;
	}
 
	uint8_t *p = str + *length - 1;
	while (p >= str  && isspace(*p))
	{
		*p = '\0';
		--p;
        *length--;
	}
 
	return str;
}

size_t Aes::aes128_ecb_encrypt(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key)
{
    if (!input || !key || !output) {
        return 0;
    }
 
    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, 128, &aesKey) < 0) {
        return 0;
    }
 
    size_t enLen = 0;
    while (enLen < inLength)
    {
        AES_encrypt(input, output, &aesKey);
        input += AES_BLOCK_SIZE;
        output += AES_BLOCK_SIZE;
        enLen += AES_BLOCK_SIZE;
    }
 
    return enLen;
}

size_t Aes::aes128_ecb_decrypt(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key)
{
    if (!input || !key || !output) {
        return 0;
    }
 
    AES_KEY aesKey;
    if (AES_set_decrypt_key(key, 128, &aesKey) < 0)
    {
        return 0;
    }
 
    size_t enLen = 0;
    while (enLen < inLength)
    {
        AES_decrypt(input, output, &aesKey);
        input += AES_BLOCK_SIZE;
        output += AES_BLOCK_SIZE;
        enLen += AES_BLOCK_SIZE;
    }
 
    return enLen;
}

size_t Aes::aes128_ecb_encrypt_padding(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key)
{
    if (!input || !key || !output) {
        return 0;
    }
    
    size_t len = 0;
    char *padSrc = PKCS::PKCS5Padding(input, inLength, &len);

    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, 128, &aesKey) < 0)
    {
        return 0;
    }
 
    size_t enLen = 0;
    while (enLen < len)
    {
        AES_encrypt((uint8_t *)padSrc, output, &aesKey);
        input += AES_BLOCK_SIZE;
        output += AES_BLOCK_SIZE;
        enLen += AES_BLOCK_SIZE;
    }
    
    if(padSrc)
        free(padSrc);

    return enLen;
}

size_t Aes::aes128_ecb_decrypt_padding(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key)
{
    if (!input || !key || !output) {
        return 0;
    }
 
    AES_KEY aesKey;
    if (AES_set_decrypt_key(key, 128, &aesKey) < 0)
    {
        return 0;
    }
 
    size_t enLen = 0;
    while (enLen < inLength)
    {
        AES_decrypt(input, output, &aesKey);
        input += AES_BLOCK_SIZE;
        output += AES_BLOCK_SIZE;
        enLen += AES_BLOCK_SIZE;
    }
 
    size_t outLen = enLen;
    PKCS::PKCS5UnPadding(output, &outLen);

    return outLen;
}

size_t Aes::aes128_cbc_encrypt_padding(uint8_t* output, uint8_t* input, size_t inLength, const uint8_t* key, const uint8_t* iv)
{
    if (!input || !key || !output) {
        return 0;
    }

	size_t len = 0;
    char *padSrc = PKCS::PKCS5Padding(input, inLength, &len);
    
    EVP_CIPHER_CTX *ctx = NULL;
    if(!(ctx = EVP_CIPHER_CTX_new())) {
        return 0;
    }
    
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) {
        return 0;
    }

    int outLength = 0; 
    if(1 != EVP_EncryptUpdate(ctx, output, &outLength, (uint8_t *)padSrc, len)) {   
        return 0;
    }

    if(padSrc)
        free(padSrc);
        
    if (ctx != NULL)
        EVP_CIPHER_CTX_free(ctx);

    return outLength;
}

size_t Aes::aes128_cbc_decrypt_padding(uint8_t* output, uint8_t* input, size_t inLength, const uint8_t* key, const uint8_t* iv)
{
    if (!input || !key || !output) {
        return 0;
    }

    EVP_CIPHER_CTX *ctx = NULL;

    if(!(ctx = EVP_CIPHER_CTX_new())) {
        return 0;
    }

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) {
        return 0;
    }
    
    // outLength包含了尾部空格的长度
    int outLength = 0; 
    if(1 != EVP_DecryptUpdate(ctx, output, &outLength, (uint8_t *)input, inLength)) {   
        return 0;
    }

    if (ctx != NULL)
        EVP_CIPHER_CTX_free(ctx);

    // 去除空格
    output = rtrim(output, &outLength);

    return outLength;
}

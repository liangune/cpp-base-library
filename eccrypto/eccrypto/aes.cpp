/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   AES加解密
*************************************************************************/

#include "aes.h"
#include <string.h>
#include <ctype.h>

char *Aes::PKCS5Padding(uint8_t* input, int nLen) {
    int blockCount = 0;
    blockCount = nLen / AES_BLOCK_SIZE + 1;

    int padding = AES_BLOCK_SIZE - nLen % AES_BLOCK_SIZE;

    char *output = (char *)malloc(AES_BLOCK_SIZE*blockCount);
    memset(output, padding, AES_BLOCK_SIZE*blockCount);
    memcpy(output, input, nLen);

    return output;
}

void Aes::PKCS5UnPadding(uint8_t* input, int *len) {
    //PKCS5 UNPADDING
    int unpadding = input[*len - 1];
    *len = *len - unpadding;
    input[*len] = '\0';
}

uint8_t *Aes::rtrim(uint8_t *str)
{
	if (str == NULL || *str == '\0')
	{
		return str;
	}
 
	int len = strlen((char *)str);
	uint8_t *p = str + len - 1;
	while (p >= str  && isspace(*p))
	{
		*p = '\0';
		--p;
	}
 
	return str;
}

int Aes::aes128_ecb_encrypt(uint8_t* input, const uint8_t* key, uint8_t *output)
{
    if (!input || !key || !output) {
        return -1;
    }
 
    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, 128, &aesKey) < 0) {
        return -1;
    }
 
    int len = strlen((char *)input), enLlen = 0;

    while (enLlen < len)
    {
        AES_encrypt(input, output, &aesKey);
        input += AES_BLOCK_SIZE;
        output += AES_BLOCK_SIZE;
        enLlen += AES_BLOCK_SIZE;
    }
 
    return 0;
}

int Aes::aes128_ecb_decrypt(uint8_t* input, const uint8_t* key, uint8_t *output)
{
    if (!input || !key || !output) {
        return -1;
    }
 
    AES_KEY aesKey;
    if (AES_set_decrypt_key(key, 128, &aesKey) < 0)
    {
        return -1;
    }
 
    int len = strlen((char *)input), enLen = 0;
    while (enLen < len)
    {
        AES_decrypt(input, output, &aesKey);
        input += AES_BLOCK_SIZE;
        output += AES_BLOCK_SIZE;
        enLen += AES_BLOCK_SIZE;
    }
 
    return 0;
}

int Aes::aes128_cbc_encrypt_padding(uint8_t* output, uint8_t* input, int inLength, const uint8_t* key, const uint8_t* iv)
{
    if (!input || !key || !output) {
        return 0;
    }

    char *padSrc = PKCS5Padding(input, inLength);
    
    EVP_CIPHER_CTX *ctx = NULL;
    if(!(ctx = EVP_CIPHER_CTX_new())) {
        return 0;
    }
    
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) {
        return 0;
    }

    int outLength = 0; 
    if(1 != EVP_EncryptUpdate(ctx, output, &outLength, (uint8_t *)padSrc, strlen(padSrc))) {   
        return 0;
    }

    if(padSrc)
        free(padSrc);
        
    if (ctx != NULL)
        EVP_CIPHER_CTX_free(ctx);

    return outLength;
}

int Aes::aes128_cbc_decrypt_padding(uint8_t* output, uint8_t* input, int inLength, const uint8_t* key, const uint8_t* iv)
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
    output = rtrim(output);

    return strlen((char *)output);
}

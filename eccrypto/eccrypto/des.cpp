/*************************************************************************
	> Date:   2023-02-02
	> Author: liangjun
	> Desc:   DES加解密
*************************************************************************/

#include "des.h"
#include <string.h>
#include <ctype.h>
#include "pkcs.h"

size_t Des::des64_ecb_encrypt(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key)
{
    if (!input || !key || !output) {
        return 0;
    }

    DES_cblock keyEncrypt;  
    memset(keyEncrypt, 0, DES_ENCRYPT_KEY_SIZE);
    memcpy(keyEncrypt, key, DES_ENCRYPT_KEY_SIZE);

    DES_key_schedule keySchedule;  
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);
 
    size_t enLen = 0;
    DES_cblock inputText;  
    DES_cblock outputText; 
    while (enLen < inLength)   
    {
        memcpy(inputText, input + enLen, DES_BLOCK_SIZE);  
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
        memcpy(output + enLen, outputText, DES_BLOCK_SIZE);

        enLen += DES_BLOCK_SIZE;
    }
 
    return enLen;
}

size_t Des::des64_ecb_decrypt(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key)
{
    if (!input || !key || !output) {
        return 0;
    }

    DES_cblock keyEncrypt;  
    memset(keyEncrypt, 0, DES_ENCRYPT_KEY_SIZE);
    memcpy(keyEncrypt, key, DES_ENCRYPT_KEY_SIZE);

    DES_key_schedule keySchedule;  
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);

    size_t enLen = 0;
    DES_cblock inputText;  
    DES_cblock outputText;  
    while (enLen < inLength)   
    {
        memcpy(inputText, input + enLen, DES_BLOCK_SIZE);  
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
        memcpy(output + enLen, outputText, DES_BLOCK_SIZE);

        enLen += DES_BLOCK_SIZE;
    }

    return enLen;
}

size_t Des::des64_ecb_encrypt_padding(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key)
{
    if (!input || !key || !output) {
        return 0;
    }

    size_t len = 0;
    char *padSrc = PKCS::PKCS7Padding(input, inLength, DES_BLOCK_SIZE, &len);

    DES_cblock keyEncrypt;  
    memset(keyEncrypt, 0, DES_ENCRYPT_KEY_SIZE);
    memcpy(keyEncrypt, key, DES_ENCRYPT_KEY_SIZE);

    DES_key_schedule keySchedule;  
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);
    
    size_t enLen = 0;
    DES_cblock inputText;  
    DES_cblock outputText;  
    while (enLen < len)   
    {
        memcpy(inputText, padSrc + enLen, DES_BLOCK_SIZE);  
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
        memcpy(output + enLen, outputText, DES_BLOCK_SIZE);

        enLen += DES_BLOCK_SIZE;
    }
    
    if(padSrc)
        free(padSrc);

    return enLen;
}

size_t Des::des64_ecb_decrypt_padding(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key)
{
    if (!input || !key || !output) {
        return 0;
    }

    DES_cblock keyEncrypt;  
    memset(keyEncrypt, 0, DES_ENCRYPT_KEY_SIZE);
    memcpy(keyEncrypt, key, DES_ENCRYPT_KEY_SIZE);

    DES_key_schedule keySchedule;  
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);

    size_t enLen = 0;
    DES_cblock inputText;  
    DES_cblock outputText;  
    while (enLen < inLength)   
    {
        memcpy(inputText, input + enLen, DES_BLOCK_SIZE);  
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
        memcpy(output + enLen, outputText, DES_BLOCK_SIZE);

        enLen += DES_BLOCK_SIZE;
    }

    size_t outLen = enLen;
    PKCS::PKCS7UnPadding(output, &outLen);

    return outLen;
}

size_t Des::des64_cbc_encrypt_padding(uint8_t* output, uint8_t* input, size_t inLength, const uint8_t* key, const uint8_t* iv)
{
    if (!input || !key || !output) {
        return 0;
    }

    size_t len = 0;
    char *padSrc = PKCS::PKCS7Padding(input, inLength, DES_BLOCK_SIZE, &len);
    
    EVP_CIPHER_CTX *ctx = NULL;
    if(!(ctx = EVP_CIPHER_CTX_new())) {
        return 0;
    }
    
    if(1 != EVP_EncryptInit_ex(ctx, EVP_des_cbc(), NULL, key, iv)) {
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

size_t Des::des64_cbc_decrypt_padding(uint8_t* output, uint8_t* input, size_t inLength, const uint8_t* key, const uint8_t* iv)
{
    if (!input || !key || !output) {
        return 0;
    }

    EVP_CIPHER_CTX *ctx = NULL;
    if(!(ctx = EVP_CIPHER_CTX_new())) {
        return 0;
    }

    if(1 != EVP_DecryptInit_ex(ctx, EVP_des_cbc(), NULL, key, iv)) {
        return 0;
    }
    
    int outLength = 0; 
    if(1 != EVP_DecryptUpdate(ctx, output, &outLength, input, inLength)) {   
        return 0;
    }

    if (ctx != NULL)
        EVP_CIPHER_CTX_free(ctx);

    return outLength;
}

size_t Des::des64_cbc_encrypt(uint8_t* output, uint8_t* input, size_t inLength, const uint8_t* key, const uint8_t* iv)
{    
    EVP_CIPHER_CTX *ctx = NULL;
    if(!(ctx = EVP_CIPHER_CTX_new())) {
        return 0;
    }
    
    if(1 != EVP_EncryptInit_ex(ctx, EVP_des_cbc(), NULL, key, iv)) {
        return 0;
    }

    int outLength = 0; 
    if(1 != EVP_EncryptUpdate(ctx, output, &outLength, input, inLength)) {   
        return 0;
    }
        
    if (ctx != NULL)
        EVP_CIPHER_CTX_free(ctx);

    return outLength;   
}

size_t Des::des64_cbc_decrypt(uint8_t* output, uint8_t* input, size_t inLength, const uint8_t* key, const uint8_t* iv)
{
    if (!input || !key || !output) {
        return 0;
    }
    
    DES_cblock keyEncrypt;  
    memset(keyEncrypt, 0, DES_ENCRYPT_KEY_SIZE);
    memcpy(keyEncrypt, key, DES_ENCRYPT_KEY_SIZE);

    DES_cblock ivec;  
    memset(ivec, 0, DES_ENCRYPT_KEY_SIZE);
    memcpy(ivec, iv, DES_ENCRYPT_KEY_SIZE);

    DES_key_schedule keySchedule;  
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);
 
    DES_ncbc_encrypt(input, output, inLength, &keySchedule, &ivec, DES_DECRYPT);
    return inLength;
}
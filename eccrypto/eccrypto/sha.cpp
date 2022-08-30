/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   sha1
*************************************************************************/
#include "sha.h"
#include <stdio.h>

size_t Sha::SHA1(const uint8_t *input, size_t inLength, std::string &sDigest)
{
    unsigned char digest[SHA_DIGEST_LENGTH] = {0};
    // use openssl SHA1
    ::SHA1(input, inLength, digest);
    
    sDigest = std::string((char *)digest, SHA_DIGEST_LENGTH);

    return SHA_DIGEST_LENGTH;
}

size_t Sha::hmacSHA1(const void *key, int keyLen, const uint8_t *input, size_t inLength, std::string &sDigest)
{
    unsigned char digest[EVP_MAX_MD_SIZE] = {'\0'};
    unsigned int digestLen = 0;
    HMAC(EVP_sha1(), key, keyLen, input, inLength, digest, &digestLen);

    sDigest = std::string((char *)digest, digestLen);
    
    return SHA_DIGEST_LENGTH;
}

size_t Sha::SHA256(const uint8_t *input, size_t inLength, std::string &sDigest)
{
    unsigned char digest[SHA256_DIGEST_LENGTH] = {0};
    // use openssl SHA256
    ::SHA256(input, inLength, digest);
    
    sDigest = std::string((char *)digest, SHA256_DIGEST_LENGTH);

    return SHA256_DIGEST_LENGTH;
}

size_t Sha::hmacSHA256(const void *key, int keyLen, const uint8_t *input, size_t inLength, std::string &sDigest)
{
    unsigned char digest[EVP_MAX_MD_SIZE] = {'\0'};
    unsigned int digestLen = 0;
    HMAC(EVP_sha256(), key, keyLen, input, inLength, digest, &digestLen);

    sDigest = std::string((char *)digest, SHA256_DIGEST_LENGTH);

    return SHA256_DIGEST_LENGTH;
}

std::string Sha::EncodeToHex(const uint8_t *input, size_t inLength)
{
    // binary to hex, It is used to determine whether it is correct. 
    char mdString[EVP_MAX_MD_SIZE + 1] = {'\0'}; // sprintf会在buffer尾部写入一个'\0'字符, 所以长度需要+1处理
    for(int i = 0; i < inLength; i++) {
        sprintf(&mdString[i*2], "%02x", input[i]);
    }
    
    return std::string(mdString, inLength * 2);
}

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
    
    char mdString[SHA_DIGEST_LENGTH*2+1] = {'\0'};
    for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    }
    
    sDigest = mdString;

    return SHA_DIGEST_LENGTH*2;
}

size_t Sha::hmacSHA1(const void *key, int keyLen, const uint8_t *input, size_t inLength, std::string &sDigest)
{
    unsigned char digest[EVP_MAX_MD_SIZE] = {'\0'};
    unsigned int digestLen = 0;
    HMAC(EVP_sha1(), key, keyLen, input, inLength, digest, &digestLen);

    char mdString[SHA_DIGEST_LENGTH*2+1] = {'\0'};
    for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    sDigest = mdString;
    
    return SHA_DIGEST_LENGTH*2;
}

size_t Sha::SHA256(const uint8_t *input, size_t inLength, std::string &sDigest)
{
    unsigned char digest[SHA256_DIGEST_LENGTH] = {0};
    // use openssl SHA256
    ::SHA256(input, inLength, digest);
    
    char mdString[SHA256_DIGEST_LENGTH*2+1] = {'\0'};
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    }
    
    sDigest = mdString;

    return SHA256_DIGEST_LENGTH*2;
}

size_t Sha::hmacSHA256(const void *key, int keyLen, const uint8_t *input, size_t inLength, std::string &sDigest)
{
    unsigned char digest[EVP_MAX_MD_SIZE] = {'\0'};
    unsigned int digestLen = 0;
    HMAC(EVP_sha256(), key, keyLen, input, inLength, digest, &digestLen);

    char mdString[SHA256_DIGEST_LENGTH*2+1] = {'\0'};
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    sDigest = mdString;
    
    return SHA256_DIGEST_LENGTH*2;
}

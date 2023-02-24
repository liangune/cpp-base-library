#include "pkcs.h"
#include "openssl/aes.h"
#include <stdlib.h>

char *PKCS::PKCS5Padding(uint8_t* input, size_t inLen, size_t *outLen) 
{
    int blockCount = 0;
    blockCount = inLen / AES_BLOCK_SIZE + 1;

    int padding = AES_BLOCK_SIZE - inLen % AES_BLOCK_SIZE;

    *outLen = AES_BLOCK_SIZE*blockCount;
    char *output = (char *)malloc(AES_BLOCK_SIZE*blockCount);
    memset(output, padding, AES_BLOCK_SIZE*blockCount);
    memcpy(output, input, inLen);

    return output;
}

void PKCS::PKCS5UnPadding(uint8_t* input, size_t *len) {
    //PKCS5 UNPADDING
    int unpadding = input[*len - 1];
    *len = *len - unpadding;
    input[*len] = '\0';
}

char *PKCS::PKCS7Padding(uint8_t* input, size_t inLen, size_t blockSize, size_t *outLen)
{
    int blockCount = 0;
    blockCount = inLen / blockSize + 1;

    int padding = blockSize - inLen % blockSize;

    *outLen = blockSize*blockCount;
    char *output = (char *)malloc(blockSize*blockCount);
    memset(output, padding, blockSize*blockCount);
    memcpy(output, input, inLen);

    return output;
}

void PKCS::PKCS7UnPadding(uint8_t* input, size_t *len) {
    int unpadding = input[*len - 1];
    *len = *len - unpadding;
    input[*len] = '\0';
}

char *PKCS::PKCS7Padding(uint8_t* input, size_t inLen, int paddingChar, size_t blockSize, size_t *outLen)
{
    int blockCount = 0;
    blockCount = inLen / blockSize + 1;

    *outLen = blockSize*blockCount;
    char *output = (char *)malloc(blockSize*blockCount);
    memset(output, paddingChar, blockSize*blockCount);
    memcpy(output, input, inLen);

    return output;
}
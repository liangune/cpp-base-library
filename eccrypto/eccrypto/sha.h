/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   sha1
*************************************************************************/

#ifndef _SHA1_H_
#define _SHA1_H_

#include "openssl/sha.h"
#include "openssl/hmac.h"
#include <string>

#define SHA256_DIGEST_LENGTH 32

class Sha {
public:
    /**
     * @brief           sha1哈希函数
     * @param input     输入字符串指针
     * @param inLength  输入字符串长度
     * @param sDigest   sha1哈希值
     * @return          sha1哈希值的长度
    */
    static size_t SHA1(const uint8_t *input, size_t inLength, std::string &sDigest);

    /*
    * @brief           加密钥的sha1哈希函数
    */
    static size_t hmacSHA1(const void *key, int keyLen, const uint8_t *input, size_t inLength, std::string &sDigest);

    /**
     * @brief           sha256哈希函数
     * @param input     输入字符串指针
     * @param inLength  输入字符串长度
     * @param sDigest   sha256哈希值
     * @return          sha256哈希值的长度
    */
    static size_t SHA256(const uint8_t *input, size_t inLength, std::string &sDigest);
    static size_t hmacSHA256(const void *key, int keyLen, const uint8_t *input, size_t inLength, std::string &sDigest);

    
    /**
     * @brief           sha哈希值二进制转换为十六进制
     * @param input     输入字符串指针
     * @param inLength  输入字符串长度
     * @return          16进制可打印字符串
    */
    static std::string EncodeToHex(const uint8_t *input, size_t inLength);
};

#endif // _SHA1_H_
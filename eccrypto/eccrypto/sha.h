/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   sha1
*************************************************************************/

#ifndef _SHA1_H_
#define _SHA1_H_

#ifdef _MSC_VER
#include "openssl/sha.h"
#include "openssl/hmac.h"
#elif defined __GNUC__
#include "openssl/sha.h"
#include "openssl/hmac.h"
#endif

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
};

#endif // _SHA1_H_
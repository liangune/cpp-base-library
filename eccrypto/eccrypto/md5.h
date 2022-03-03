/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   md5
*************************************************************************/

#ifndef _MD5_H_
#define _MD5_H_

#ifdef _MSC_VER
#include "openssl/md5.h"
#elif defined __GNUC__
#include "openssl/md5.h"
#endif

#include <string>

#define MD5_HASH_LENGTH_16  16
#define MD5_HASH_LENGTH_32  32

class Md5 {
public:
    /**
     * @brief           md5哈希函数, 16字节, 默认小写散列值
     * @param input     输入字符串指针
     * @param inLength  输入字符串长度
     * @param sDigest   md5哈希值
     * @param isLower   是否是小写散列值
     * @return          md5字符串长度
    */
	static size_t hash16(const uint8_t *input, size_t inLength, std::string &sDigest, bool isLower=true);
    
    /**
     * @brief           md5哈希函数, 32字节, 默认小写散列值
     * @param input     输入字符串指针
     * @param inLength  输入字符串长度
     * @param sDigest   md5哈希值
     * @param isLower   是否是小写散列值
     * @return          md5字符串长度
    */
    static size_t hash(const uint8_t *input, size_t inLength, std::string &sDigest, bool isLower=true);

    /*
	static size_t HashFile(const char *pszFile, char *pszOutput);
	static size_t HashFile(const char *pszFile, std::string &sOutput, bool isLower = false);
    */
};

#endif // _MD5_H_
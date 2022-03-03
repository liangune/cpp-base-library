/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   AES加解密
*************************************************************************/

#ifndef _AES_H_
#define _AES_H_

#ifdef _MSC_VER
#include "openssl/aes.h"
#include "openssl/evp.h"
#elif defined __GNUC__
#include "openssl/aes.h"
#include "openssl/evp.h"
#endif

#include <stdint.h>

class Aes {
public:
    /**
     * @brief         ecb模式
     * @param  input  需要加密的数据
     * @param  key    必须是16个字节
     * @param  output 加密后的数据，比未加密前最多多16个字节
     * @return        错误码，0：成功，-1: 错误
     * 注意：output的长度等于input数据的长度+16+1,以'\0'结束
    */
    static int aes128_ecb_encrypt(uint8_t* input, const uint8_t* key, uint8_t *output);
    static int aes128_ecb_decrypt(uint8_t* input, const uint8_t* key, uint8_t *output);

    /**
     * @brief         加密时不足16个字节补充到16个字节, 采用PKCS5Padding, 填充的值为字节数，例如填充一个字节，则填充值为1。
     *                如果加密数为16个字节的整数倍，则填充16个字节, 解密时先解密，解密后去掉尾部空格
     * @param  input  需要加密的数据
     * @param  length 需要加密的数据长度
     * @param  key    必须是16个字节
     * @param  iv     必须是16个字节
     * @param  output 加密后的数据, 比未加密前最多多16个字节
     * @return        加密后数据长度
    */
    static int aes128_cbc_encrypt_padding(uint8_t* output, uint8_t* input, int inLength, const uint8_t* key, const uint8_t* iv);
    static int aes128_cbc_decrypt_padding(uint8_t* output, uint8_t* input, int inLength,  const uint8_t* key, const uint8_t* iv);

    // 去除尾部空格
    static uint8_t *rtrim(uint8_t *str);
    // PKCS5Padding
    static char *PKCS5Padding(uint8_t* input, int nLen);
    static void PKCS5UnPadding(uint8_t* input, int *len);
};

#endif // _AES_H_ 
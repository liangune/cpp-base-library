/*************************************************************************
	> Date:   2023-02-02
	> Author: liangjun
	> Desc:   DES加解密
*************************************************************************/

#ifndef _DES_H_
#define _DES_H_

#include "openssl/des.h"
#include "openssl/evp.h"
#include <stdint.h>

#define DES_BLOCK_SIZE 8
#define DES_ENCRYPT_KEY_SIZE 8

class Des {
public:
    /**
     * @brief         ecb模式, 不填充则要求数据源长度是8个字节的整数倍
     * @param  input  需要加密的数据
     * @param  key    必须是8个字节
     * @param  output 加密后的数据
     * @return        加密后数据长度
    */
    static size_t des64_ecb_encrypt(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key);
    static size_t des64_ecb_decrypt(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key);

    /**
     * @brief         ecb模式
     * @param  input  需要加密的数据
     * @param  key    必须是8个字节
     * @param  output 加密后的数据
     * @return        加密后数据长度
    */
    static size_t des64_ecb_encrypt_padding(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key);
    static size_t des64_ecb_decrypt_padding(uint8_t *output, uint8_t* input, size_t inLength, const uint8_t* key);

    /**
     * @brief         加密时不足8个字节补充到8个字节, 采用PKCS7Padding, 填充的值为字节数，例如填充一个字节，则填充值为1。
     *                如果加密数为8个字节的整数倍，则填充8个字节
     * @param  input  需要加密的数据
     * @param  length 需要加密的数据长度
     * @param  key    必须是8个字节
     * @param  iv     必须是8个字节
     * @param  output 加密后的数据, 比未加密前最多多8个字节
     * @return        加密后数据长度
    */
    static size_t des64_cbc_encrypt_padding(uint8_t* output, uint8_t* input, size_t inLength, const uint8_t* key, const uint8_t* iv);
    static size_t des64_cbc_decrypt_padding(uint8_t* output, uint8_t* input, size_t inLength,  const uint8_t* key, const uint8_t* iv);

    /**
     * @brief         cbc模式, 不填充则要求数据源长度是8个字节的整数倍
     * @param  input  需要加密的数据
     * @param  key    必须是8个字节
     * @param  output 加密后的数据
     * @return        加密后数据长度
    */
    static size_t des64_cbc_encrypt(uint8_t* output, uint8_t* input, size_t inLength, const uint8_t* key, const uint8_t* iv);
    static size_t des64_cbc_decrypt(uint8_t* output, uint8_t* input, size_t inLength,  const uint8_t* key, const uint8_t* iv);
};

#endif // _DES_H_ 
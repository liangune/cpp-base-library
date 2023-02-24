/*************************************************************************
	> Date:   2023-02-02
	> Author: liangjun
	> Desc:   pkcs填充
*************************************************************************/

#ifndef _PKCS_PADDING_H_
#define _PKCS_PADDING_H_

#include <stdint.h>
#include <string.h>

class PKCS {
public:
    /**
     * @brief         PKCS5填充, 当前函数填充块长度是16字节
     * @param  input  需要填充的源数据
     * @param  nLen   源数据长度
     * @return        填充后的数据
    */
    static char *PKCS5Padding(uint8_t* input, size_t inLen, size_t *outLen);
    static void PKCS5UnPadding(uint8_t* input, size_t *len);

    /**
     * @brief             PKCS7填充
     * @param  input      需要填充的源数据
     * @param  nLen       源数据长度
     * @param  blockSize  填充块大小
     * @return            填充后的数据
    */
    static char *PKCS7Padding(uint8_t* input, size_t inLen, size_t blockSize, size_t *outLen);
    static void PKCS7UnPadding(uint8_t* input, size_t *len);

    static char *PKCS7Padding(uint8_t* input, size_t inLen, int paddingChar, size_t blockSize, size_t *outLen);
};

#endif // _PKCS_PADDING_H_ 
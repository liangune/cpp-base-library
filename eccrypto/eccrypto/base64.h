/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   base64编解码
*************************************************************************/

#ifndef _BASE64_H_
#define _BASE64_H_

#include <string.h>
#include <stdint.h>
#include <string>
/*
 * Note: The 'output' variable should be a preallocated buffer that
 * should have enough allocated space for the encoded/decoded
 * result. Failure to do so will result in a buffer overrun.
 */

int base64_encode(uint8_t *input, size_t input_length, uint8_t *output);
int base64_decode(uint8_t *input, size_t outLength, uint8_t *output);

class B64
{
 public:
    /**
     * @brief           base64编码
     * @param input     需要编码字符串指针
     * @param inLength  需要编码字符串长度
     * @param sOutput   编码后的字符串
     * @return          返回编码后字符串的长度
    */
    static int base64Encode(uint8_t *input, size_t inLength, std::string &sOutput);

    /**
     * @brief           base64解码
     * @param input     输入字符串指针
     * @param inLength  输入字符串长度
     * @param sOutput   解码后的字符串
     * @return          解码后的字符串长度
    */
    static int base64Decode(uint8_t *input, size_t inLength, std::string &sOutput);
};



#endif /* _BASE64_H_ */

/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   url编解码
*************************************************************************/

#ifndef _URLCODE_H_
#define _URLCODE_H_
#include <string>

class UrlCode
{
 public:
	static std::string encode(const std::string &sInput);
	static std::string decode(const std::string &sInput);
	static void encode(const std::string &sInput, std::string &sOutput);
	static void decode(const std::string &sInput, std::string &sOutput);
};

#endif /* _URLCODE_H_ */

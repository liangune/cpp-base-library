/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   md5
*************************************************************************/

#include "md5.h"
#include <algorithm>

static std::string hex2String(const unsigned char *pszData, size_t inLen, size_t outLen, bool isLower)
{
	static char HEX1[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	static char HEX2[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	char *pHex = isLower ? &HEX1[0] : &HEX2[0];

	std::string sHex(outLen, 'X');
	std::string::iterator it = sHex.begin();

	for(unsigned int i=0; i<inLen; i++)
	{
		int n1 = pszData[i] >> 4;
		int n2 = pszData[i] & 0xF;
        if(outLen==MD5_HASH_LENGTH_16 && i>=4 && i<=11) {
		    *it++  = pHex[n1];
		    *it++  = pHex[n2];
        }
        if(outLen==MD5_HASH_LENGTH_32) {
            *it++  = pHex[n1];
		    *it++  = pHex[n2];
        }
	}
	return sHex;
}

size_t Md5::hash16(const uint8_t *input, size_t inLength, std::string &sDigest, bool isLower)
{
    unsigned char digest[MD5_DIGEST_LENGTH] = {0};
    MD5(input, inLength, digest);

    sDigest = hex2String(digest, MD5_DIGEST_LENGTH, MD5_HASH_LENGTH_16, isLower);

    return MD5_HASH_LENGTH_16; 
}

size_t Md5::hash(const uint8_t *input, size_t inLength, std::string &sDigest, bool isLower)
{
    unsigned char digest[MD5_DIGEST_LENGTH] = {0};
    MD5(input, inLength, digest);
    sDigest = hex2String(digest, MD5_DIGEST_LENGTH, MD5_HASH_LENGTH_32, isLower);

    return MD5_HASH_LENGTH_32; 
}
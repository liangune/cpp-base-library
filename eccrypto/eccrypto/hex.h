/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   十六进制转换
*************************************************************************/

#ifndef _HEX_H_
#define _HEX_H_

#include <string.h>
#include <string>

class Hex {
public:
    static char hex2Char(char c)
    {	
        if ((c >= 0x0A) && (c <= 0x0F))
            return c - 0x0A + 'a';
        else if ((c >= 0) && (c <= 9))
            return c + '0';
        else
            return '0';
    }

    static int encode(const char *src, char *dst) {
        int j = 0;
        int length = strlen(src);
        for(int i=0; i <length; i++) 
        {
            char c = (src[i] >> 4) & 0x0F;
            dst[j] = hex2Char(c);
            c = src[i] & 0x0F;
            dst[j+1] = hex2Char(c);
            j += 2;
        }
        return length * 2;
    }

    static std::string encodeToString(const char *src)
    {
        int length = strlen(src);
        //char dst[length];
        char *pszDst = new char[length*2];
        memset(pszDst, 0, length);
        encode(src, pszDst);
        std::string strDst = pszDst;

        if(pszDst)
            delete(pszDst);
	    
        return strDst;
    }

    static char fromHexChar(char c)
    {
        if('A' <= c && c <= 'F')
            return c - 'A' + 10;
        else if('a' <= c && c <= 'f')
            return c - 'a' + 10;
        else if('0' <= c && c <= '9')
            return c -'0';
        return 0;
    }
    
    static std::string decodeToString(const char *src)
    {
        int length = strlen(src);
        //char dst[length];
        char *pszDst = new char[length];
        memset(pszDst, 0, length);
        decode(src, pszDst);
        std::string strDst = pszDst;
        if(pszDst)
            delete(pszDst);
        
	    return strDst;
    }

    static int decode(const char *src, char *dst) {
        int length = strlen(src);
        int i=0, j = 0;
        for (; i < length - 1; j++)
        {
            uint8_t pC = fromHexChar(src[i++]);
            uint8_t nC = fromHexChar(src[i++]);
            uint8_t c = ((pC & 0x0F) << 4) + (nC & 0x0F);
            dst[j] = c;
        }
        return j;
    }	
};

#endif // _HEX_H_ 
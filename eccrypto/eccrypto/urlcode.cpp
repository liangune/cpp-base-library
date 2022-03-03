/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   url编解码
*************************************************************************/

#include "urlcode.h"

static const char DEC2HEX[] = "0123456789ABCDEF";

static const char HEX2DEC[256] = {
/*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
/* 0 */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* 1 */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* 2 */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* 3 */0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1,

/* 4 */-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* 5 */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* 6 */-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* 7 */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

/* 8 */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* 9 */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* A */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* B */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

/* C */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* D */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* E */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
/* F */-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

unsigned char hex2Dec(unsigned char c)
{
	if ('0' <= c && c <= '9') {
		return c - '0';
	}
	else if ('a' <= c && c <= 'f') {
		return (c - 'a') + 10;
	}
	else if ('A' <= c && c <= 'F') {
		return (c - 'A') + 10;
	}

    return 0;
}

std::string UrlCode::encode(const std::string &sInput)
{
    std::string strTemp = "";
    size_t length = sInput.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)sInput[i]) ||
            (sInput[i] == '-') ||
            (sInput[i] == '_') ||
            (sInput[i] == '.') ||
            (sInput[i] == '~'))
            strTemp += sInput[i];
        else if (sInput[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += DEC2HEX[(unsigned char)sInput[i] >> 4];
            strTemp += DEC2HEX[(unsigned char)sInput[i] % 16];
        }
    }
    return strTemp;
}

std::string UrlCode::decode(const std::string &sInput)
{
    std::string strTemp = "";
    size_t length = sInput.length();
    for (size_t i = 0; i < length; i++)
    {
        if (sInput[i] == '+')
			strTemp += ' ';
        else if (sInput[i] == '%' && (i+2) < length)
        {
			unsigned char high = (unsigned char)sInput[++i];
			unsigned char low = (unsigned char)sInput[++i];
			strTemp += hex2Dec(high) * 16 + hex2Dec(low);

            /*
            char high = HEX2DEC[(unsigned char)sInput[++i]];
            char low  = HEX2DEC[(unsigned char)sInput[++i]];
			if( high != -1 && low != -1 )
				strTemp += high*16 + low;
			else
			{
				strTemp += sInput[i-2]; // %
				strTemp += sInput[i-1];
				strTemp += sInput[i];
			}
            */
        }
        else
			strTemp += sInput[i];
    }
    return strTemp;
}

void UrlCode::encode(const std::string &sInput, std::string &sOutput)
{
    sOutput = encode(sInput);
}

void UrlCode::decode(const std::string &sInput, std::string &sOutput)
{
    sOutput = decode(sInput);
}

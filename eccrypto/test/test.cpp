#include "eccrypto/base64.h"
#include <string>
#include <iostream>
#include "eccrypto/urlcode.h"
#include "eccrypto/md5.h"
#include "eccrypto/sha.h"
#include "eccrypto/aes.h"
#include <string.h>
#include "eccrypto/hex.h"
#include <vector>
#include <stdio.h>
//#include <jsoncpp/value.h>
//#include <jsoncpp/reader.h>

using namespace std;

int main(int argc, char* argv[])
{
	std::cout << "test =======" << std::endl;
    // urlencode 
    string pszUrlencode = UrlCode::encode("http://tool.chinaz.com/tools/urlcrypt.aspx?a=&城市&b=%广州*$(._-~,)");
    string pszUrldecode = UrlCode::decode(pszUrlencode);

	std::cout << "test =======" << std::endl;

    std::cout << "url encode: " << pszUrlencode << endl;
    std::cout << "url decode: " << pszUrldecode << endl;

    // md5
    std::string strTemp = "12345";
    std::string strMd5;
    Md5::hash((uint8_t *)strTemp.c_str(), strTemp.length(), strMd5, true);
    std::cout << "md5: " << strMd5 << endl;

    std::string strSha1, strHmacSha1, strSha256, strHmacSha256;
    uint32_t sha1Size = Sha::SHA1((uint8_t *)strTemp.c_str(), strTemp.length(), strSha1); 
    std::cout << "sha1 size: " << sha1Size << " sha1: " << strSha1 << " size: " << strSha1.length() << endl;

    uint32_t sha256Size = Sha::SHA256((uint8_t *)strTemp.c_str(), strTemp.length(), strSha256); 
    std::cout << "sha256 size: " << sha256Size << " sha256: " << strSha256 << " size: " << strSha256.length() << endl;

    std::string strShaKey = "abcd";
    uint32_t hmacSha1Size = Sha::hmacSHA1(strShaKey.c_str(), strShaKey.size(), (uint8_t *)strTemp.c_str(), strTemp.length(), strHmacSha1); 
    std::cout << "hmac sha1 size: " << hmacSha1Size << " hmac sha1: " << strHmacSha1 << " size: " << strHmacSha1.length() << endl;

    uint32_t hmacSha256Size = Sha::hmacSHA256(strShaKey.c_str(), strShaKey.size(), (uint8_t *)strTemp.c_str(), strTemp.length(), strHmacSha256); 
    std::cout << "hmac sha256 size: " << hmacSha256Size << " hmac sha256: " << strHmacSha256 << " size: " << strHmacSha256.length() << endl;
    
    
    std::string aesKey = "1234567891234567";
    char p[64] = "123testgosuncn";
    uint8_t pszAesSrc[64] = {0};
    memcpy(pszAesSrc, p, strlen(p));

    uint8_t aesBuf[64+16+1] = {0};
    Aes::aes128_ecb_encrypt(pszAesSrc, (uint8_t *)aesKey.c_str(), aesBuf);
    std::cout << "aesBuf: " << std::string((char *)aesBuf) << std::endl;

    std::string hexEncode = Hex::encodeToString((char *)aesBuf);
    std::cout << "aesBuf hexEncode: " << hexEncode << std::endl;
    std::string hexDecode = Hex::decodeToString(hexEncode.c_str());
    std::cout << "aesBuf hexDecode: " << hexDecode << std::endl;

    int ecbDecodeLen = strlen((char *)aesBuf);
    uint8_t aesDecodeBuf[64];
    Aes::aes128_ecb_decrypt(aesBuf, (uint8_t *)aesKey.c_str(), aesDecodeBuf);
    
    std::cout << "ecbDecodeLen: " << ecbDecodeLen << std::endl;

    const char *pAesKey = "ZAV3141592653510";
    const char *pAesIv = "AHANCKH413566745";

    char * pSrc = "0JBz{\"liang\":\"123456789122222222333368888888889999999999999999100000000000001111111111111111111111111111188888\",\"mac\":\"8c:fe:b4:04:19:de\",\"model\":\"BS_32M\",\"uuid\":\"99ecbc9f98e14672bbf5303feb548451\",\"vendorID\":\"1230\",\"wifiMac\":\"A4:82:76:E6:1D:63\"}";
    //char * pSrc = "0JBz{\"mac\":\"8c:fe:b4:04:19:de\",\"model\":\"BS_32M\",\"uuid\":\"99ecbc9f98e14672bbf5303feb548451\",\"vendorID\":\"1230\",\"wifiMac\":\"A4:82:76:E6:1D:63\"}";
  
    int nSrcLen = strlen(pSrc);
    std::vector<char> penDst(nSrcLen+16+1);

    std::cout << "pSrc length: " << nSrcLen << std::endl;
    int aesenLen = Aes::aes128_cbc_encrypt_padding((uint8_t *)&penDst[0], (uint8_t *)pSrc, nSrcLen, (uint8_t *)pAesKey, (uint8_t *)pAesIv);
    penDst[aesenLen] = 0;
    std::cout << "penDst length: " << penDst.size() << "aesenLen: "  << aesenLen << std::endl;

    std::string pbase64;
    int pbase64Size = B64::base64Encode((uint8_t *)&penDst[0], penDst.size(), pbase64);
    std::cout << "pbase64: " << pbase64  << std::endl;
    std::cout << "pbase64 size: " << pbase64.size() << std::endl;

    string pUrlencode = UrlCode::encode(pbase64);
    std::cout << "pUrlencode size : " << pUrlencode.length() << std::endl;
    std::cout << "pUrlencode: " << pUrlencode << std::endl;

    std::string pUrlencode2 = "wMB7tGxuNQ0DYdHS3Xowl14TiVruzr7moTNBDfZjcoX0JkZLM3RiDhjHUxHueGApjDWMHX0VTEJZZBimIJB8qakE9yGKYaHiQJQIIm6JvEiv0VpVTzvqIGo7H8rsMJGFo6lmkPZWUv5wYb61LzknzGBdvlrv1PK2U3rh6MUhT3Xe%2F2WmJ0dGDxuO9oGKLugJO0%2BU003JXAyc36E7wKp8QE4kLMUsruaWC%2BhpcRtkZhrzIhjieS1%2FP9t7IptOtkPcbfOAYk8Xeip25qL3eFDzvPFbYip42zJn9VtKrkm6K3jGSgwDk5OeiyL4m9mJXX0%2FRclXjSe3yTO5FbQEu6IM1jfcjkVa6Y3XUgEPv7GuXc%2BI%2Frl77AZCjlXGx77UkdAI%2FdalAGcYPGmwS820Yjq%2F3u6Av6B9gLcAi%2FY%2FhPRVVM0%3D";
    string pValue = UrlCode::decode(pUrlencode);
    std::cout << "pUrldecodeValue len: " << pValue.length() << std::endl;
    std::cout << "pUrldecodeValue: " << pValue << std::endl;
    
    std::string vAes;
    int vAesSize = B64::base64Decode((uint8_t *)pValue.c_str(), pValue.length(), vAes);
    std::cout << "vAes len: " << vAes.size() << std::endl;
    std::cout << "vAesSize: " << vAesSize << std::endl;

    char * vDst = (char *)malloc(vAesSize);
    memset(vDst, 0, vAesSize);

    int cbcDecodeLen = Aes::aes128_cbc_decrypt_padding((uint8_t *)vDst, (uint8_t *)vAes.c_str(), vAesSize, (uint8_t *)pAesKey, (uint8_t *)pAesIv);
    vDst[vAesSize] = '\0';

    std::cout << "vDst len: " << strlen(vDst) << "cbcDecodeLen: " << cbcDecodeLen << std::endl;
    std::string vDstOut(vDst, vAesSize);
    std::cout << "vDstOut size: " << vDstOut.size() << std::endl;
    std::cout << "vDstOut: " << vDstOut << std::endl;

    /*
    Json::Reader jReader;
    Json::Value obj;
    std::string strjson(vDstOut, 4);
    if(!jReader.parse(strjson, obj)){
        std::cout << "str(" << strjson << ")" << "parse to json fail" << std::endl;
    }

    std::cout << "mac: " << obj["mac"].asString() << std::endl;
    */
    //cin.get(); 
}
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
#include "eccrypto/des.h"
#include "eccrypto/pkcs.h"

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

    // sha
    std::string strSha1, strHmacSha1, strSha256, strHmacSha256;
    uint32_t sha1Size = Sha::SHA1((uint8_t *)strTemp.c_str(), strTemp.length(), strSha1); 
    std::cout << "sha1 size: " << sha1Size << " sha1: " << Sha::EncodeToHex((uint8_t *)strSha1.c_str(), sha1Size) << " size: " << strSha1.length() << endl;

    uint32_t sha256Size = Sha::SHA256((uint8_t *)strTemp.c_str(), strTemp.length(), strSha256); 
    std::cout << "sha256 size: " << sha256Size << " sha256: " << Sha::EncodeToHex((uint8_t *)strSha256.c_str(), sha256Size) << " size: " << strSha256.length() << endl;

    std::string strShaKey = "abcd";
    uint32_t hmacSha1Size = Sha::hmacSHA1(strShaKey.c_str(), strShaKey.size(), (uint8_t *)strTemp.c_str(), strTemp.length(), strHmacSha1); 
    std::cout << "hmac sha1 size: " << hmacSha1Size << " hmac sha1: " << Sha::EncodeToHex((uint8_t *)strHmacSha1.c_str(), hmacSha1Size) << " size: " << strHmacSha1.length() << endl;

    uint32_t hmacSha256Size = Sha::hmacSHA256(strShaKey.c_str(), strShaKey.size(), (uint8_t *)strTemp.c_str(), strTemp.length(), strHmacSha256);
    std::cout << "hmac sha256 size: " << hmacSha256Size << " hmac sha256: " << Sha::EncodeToHex((uint8_t *)strHmacSha256.c_str(), hmacSha256Size) << " size: " << strHmacSha256.length() << endl;
    
    std::cout << "hmac sha256 1: " << strHmacSha256 << std::endl;

    // aes
    std::string aesKey = "1234567891234567";
    char p[64] = "123testgosuncn";
    uint8_t pszAesSrc[64] = {0};
    memcpy(pszAesSrc, p, strlen(p));

    uint8_t aesBuf[64+16+1] = {0};
    int aseEcbEnLen = Aes::aes128_ecb_encrypt(aesBuf, pszAesSrc, 64, (uint8_t *)aesKey.c_str());
    std::cout << "aesBuf: " << std::string((char *)aesBuf) << std::endl;

    std::string hexEncode = Hex::encodeToString((char *)aesBuf, aseEcbEnLen);
    std::cout << "aesBuf hexEncode: " << hexEncode << std::endl;
    std::string hexDecode = Hex::decodeToString(hexEncode.c_str(), hexEncode.size());
    std::cout << "aesBuf hexDecode: " << hexDecode << std::endl;

    int ecbDecodeLen = strlen((char *)aesBuf);
    uint8_t aesDecodeBuf[64];
    Aes::aes128_ecb_decrypt(aesDecodeBuf, aesBuf, ecbDecodeLen, (uint8_t *)aesKey.c_str());
    
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

    // des
    std::string sDesSrc = "12345678";
    const char *pDesKey = "abcdefgh";
    const char *pDesIv = "iv999999";

    int nDesSize = sDesSrc.size();

    std::cout << "===>>>DES Size:" << nDesSize << std::endl;
    // des ECB
    char * desECBEnDst = (char *)malloc(nDesSize + DES_BLOCK_SIZE);
    memset(desECBEnDst, 0, nDesSize + DES_BLOCK_SIZE);
    int desECBEnLen = Des::des64_ecb_encrypt_padding((uint8_t *)desECBEnDst, (uint8_t *)sDesSrc.c_str(), nDesSize, (uint8_t *)pDesKey);
    std::cout << "desECBEnLen: " << desECBEnLen << std::endl;
    std::string desECBHexEncode = Hex::encodeToString((char *)desECBEnDst, desECBEnLen);
    //std::string sDesECBEnDst(desECBEnDst, desECBEnLen);
    std::cout << "des64_ecb_encrypt_padding: " << desECBHexEncode.size() << " " << desECBHexEncode << std::endl; 

    char * desECBDeDst = (char *)malloc(desECBEnLen);
    memset(desECBDeDst, 0, desECBEnLen);
    int desECBDecodeLen = Des::des64_ecb_decrypt_padding((uint8_t *)desECBDeDst, (uint8_t *)desECBEnDst, desECBEnLen, (uint8_t *)pDesKey);
    std::cout << "desECBDecodeLen: " << desECBDecodeLen << std::endl;
    std::string sDesECBDeDst(desECBDeDst, desECBDecodeLen);
    std::cout << "des64_ecb_decrypt_padding: " << sDesECBDeDst.size() << " " << sDesECBDeDst << "tail" << std::endl;

    // des CBC
    char * desCBCEnDst = (char *)malloc(nDesSize + DES_BLOCK_SIZE);
    memset(desCBCEnDst, 0, nDesSize + DES_BLOCK_SIZE);

    //int desCBCEnLen = Des::des64_cbc_encrypt_padding((uint8_t *)desCBCEnDst, (uint8_t *)sDesSrc.c_str(), nDesSize, (uint8_t *)pDesKey, (uint8_t *)pDesIv);
    int desCBCEnLen = Des::des64_cbc_encrypt((uint8_t *)desCBCEnDst, (uint8_t *)sDesSrc.c_str(), nDesSize, (uint8_t *)pDesKey, (uint8_t *)pDesIv);
    std::cout << "desCBCEnLen: " << desCBCEnLen << std::endl;
    std::string desHexEncode = Hex::encodeToString((char *)desCBCEnDst, desCBCEnLen);
    std::cout << "des64_cbc_encrypt_padding: " << desHexEncode.size() << " " << desHexEncode << std::endl;

    char * desCBCDeDst = (char *)malloc(desCBCEnLen);
    memset(desCBCDeDst, 0, desCBCEnLen);
    
    //int desCBCDecodeLen = Des::des64_cbc_decrypt_padding((uint8_t *)desCBCDeDst, (uint8_t *)desCBCEnDst, desCBCEnLen, (uint8_t *)pDesKey, (uint8_t *)pDesIv);
    int desCBCDecodeLen = Des::des64_cbc_decrypt((uint8_t *)desCBCDeDst, (uint8_t *)desCBCEnDst, desCBCEnLen, (uint8_t *)pDesKey, (uint8_t *)pDesIv);
    std::cout << "desCBCDecodeLen: " << desCBCDecodeLen << std::endl;
    std::string sDesCBCDeDst(desCBCDeDst, desCBCDecodeLen);
    std::cout << "des64_cbc_decrypt_padding: " << sDesCBCDeDst.size() << " " << sDesCBCDeDst << "tail" << std::endl;

    // TEST 
    std::string sTDesCBCSrc = "[{\"FACE_ID\":\"test-faceId\",\"IMAGE_ID\":\"40e88e3f-391c-474e-ab09-90f67e016171\",\"FACE_URL\":\"http://rzx168:8877/group1/M00/03/CF/CgqgF1xuQCWABssSAAALN6lgqSo035.jpg\",\"IMSI_LIST\":\"test-imsiList\",\"NAME\":\"test-name\",\"SEX\":\"0\",\"AGE\":\"30\",\"ID_CARD\":\"test-idCard\",\"REMARK\":\"test-remark\",\"CREATE_TIME\":\"0\",\"LAST_APPEAR_TIME\":\"0\",\"LAST_APPEAR_SERVICE\":\"test-lastAppearService\",\"FIRST_APPEAR_TIME\":\"0\",\"FIRST_APPEAR_SERVICE\":\"test-firstAppearService\",\"VERSION\":\"test-version\",\"QUALITY\":\"1\"},{\"FACE_ID\":\"test-faceId\",\"IMAGE_ID\":\"40e88e3f-391c-474e-ab09-90f67e016171\",\"FACE_URL\":\"http://rzx168:8877/group1/M00/03/CF/CgqgF1xuQCWABssSAAALN6lgqSo035.jpg\",\"IMSI_LIST\":\"test-imsiList\",\"NAME\":\"test-name\",\"SEX\":\"0\",\"AGE\":\"30\",\"ID_CARD\":\"test-idCard\",\"REMARK\":\"test-remark\",\"CREATE_TIME\":\"0\",\"LAST_APPEAR_TIME\":\"0\",\"LAST_APPEAR_SERVICE\":\"test-lastAppearService\",\"FIRST_APPEAR_TIME\":\"0\",\"FIRST_APPEAR_SERVICE\":\"test-firstAppearService\",\"VERSION\":\"test-version\",\"QUALITY\":\"a\"}]";
    std::string sTDesKey = "pk$@gtjt";
    std::string sTDesIv = "thvn#&@@";

    std::string sPadding = "ABCD";
    sTDesCBCSrc += std::to_string(sTDesCBCSrc.size());
    sTDesCBCSrc += sPadding;

    size_t outPaddingLen = 0;
    // 注意要释放申请的内存
    char *pTDesCBCSrc = PKCS::PKCS7Padding((uint8_t *)sTDesCBCSrc.c_str(), sTDesCBCSrc.size(), 0, DES_BLOCK_SIZE, &outPaddingLen);
    char * pTdesCBCEnDst = (char *)malloc(outPaddingLen);
    memset(pTdesCBCEnDst, 0, outPaddingLen);

    int nTdesCBCDEcodeLen = Des::des64_cbc_encrypt((uint8_t *)pTdesCBCEnDst, (uint8_t *)pTDesCBCSrc, outPaddingLen, (uint8_t *)sTDesKey.c_str(), (uint8_t *)sTDesIv.c_str());
    std::cout << "TEST desCBCEnLen: " << nTdesCBCDEcodeLen << std::endl;
    std::string sTdesHexEncode = Hex::encodeToString(pTdesCBCEnDst, nTdesCBCDEcodeLen);
    std::cout << "TEST des64_cbc_encrypt " << sTdesHexEncode.size() << " " << sTdesHexEncode << std::endl;

    // 注意要释放申请的内存
    char * pTdesCBCDeDst = (char *)malloc(nTdesCBCDEcodeLen);
    memset(pTdesCBCDeDst, 0, nTdesCBCDEcodeLen);
    
    int nTdesCBCDecodeLen = Des::des64_cbc_decrypt((uint8_t *)pTdesCBCDeDst, (uint8_t *)pTdesCBCEnDst, nTdesCBCDEcodeLen, (uint8_t *)sTDesKey.c_str(), (uint8_t *)sTDesIv.c_str());
    std::cout << "TEST desCBCDecodeLen: " << nTdesCBCDecodeLen << std::endl;
    std::string sTDesCBCDeDst(pTdesCBCDeDst, nTdesCBCDecodeLen);
    std::cout << "des64_cbc_decrypt: " << sTDesCBCDeDst.size() << " " << sTDesCBCDeDst << std::endl;

    if(pTDesCBCSrc) {
        free(pTDesCBCSrc);
        pTDesCBCSrc = NULL;
    }
    if(pTdesCBCEnDst) {
        free(pTdesCBCEnDst);
        pTdesCBCEnDst = NULL;
    }
    if(pTdesCBCDeDst) {
        free(pTdesCBCDeDst);
        pTdesCBCDeDst = NULL;
    }

    cin.get(); 
}


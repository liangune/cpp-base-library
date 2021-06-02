/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   ini配置文件解析单例
*************************************************************************/

#include "ConfFile.h"
#include <assert.h>

CConfFile::CConfFile()
{

}

CConfFile::~CConfFile()
{

}

CConfFile *CConfFile::getInstance()
{
	static CConfFile instance;
	return &instance;
}

bool CConfFile::loadFile(const char * pszFile)
{
	m_ini.Reset();
    m_ini.SetUnicode(true);
    if(	m_ini.LoadFile(pszFile) != SI_OK)
    	return false;
    return true;
}

const char *CConfFile::getStrValue(const char *pszName, const char *pszDefValue)
{
	return m_ini.GetValue("", pszName, pszDefValue);
}
const char *CConfFile::getStrValue(const char *pszSection, const char *pszName, const char *pszDefValue)
{
	return m_ini.GetValue(pszSection, pszName, pszDefValue);
}

long CConfFile::getLongValue(const char *pszName, long lDefValue)
{
	return m_ini.GetLongValue("", pszName, lDefValue);
}

long CConfFile::getLongValue(const char *pszSection, const char *pszName, long lDefValue)
{
	return m_ini.GetLongValue(pszSection, pszName, lDefValue);
}

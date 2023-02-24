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

CSimpleIniA *CConfFile::getSimpleIniA()
{
	return &m_ini;
}

bool CConfFile::loadFile(const char * pszFile)
{
	m_ini.Reset();
    m_ini.SetUnicode(true);
    if(	m_ini.LoadFile(pszFile) != SI_OK)
    	return false;
    return true;
}

bool CConfFile::saveFile(const char * pszFile)
{
	if(m_ini.SaveFile(pszFile) != SI_OK) {
		return false;
	}
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

double CConfFile::getDoubleValue(const char *pszSection, const char *pszName, double nDefValue)
{
	return m_ini.GetDoubleValue(pszSection, pszName, nDefValue);
}

bool CConfFile::getBoolValue(const char *pszSection, const char *pszName, bool bDefValue)
{
	return m_ini.GetBoolValue(pszSection, pszName, bDefValue);
}

bool CConfFile::setStrValue(const char *pszSection, const char *pszName, const char *pszDefValue)
{
	SI_Error nCode = m_ini.SetValue(pszSection, pszName, pszDefValue); 
	if (nCode == SI_OK || nCode == SI_UPDATED || nCode == SI_INSERTED) {
		return true;
	}

	return false;
}

bool CConfFile::setLongValue(const char *pszSection, const char *pszName, long lDefValue)
{
	SI_Error nCode = m_ini.SetLongValue(pszSection, pszName, lDefValue); 
	if (nCode == SI_OK || nCode == SI_UPDATED || nCode == SI_INSERTED) {
		return true;
	}

	return false;
}

bool CConfFile::setDoubleValue(const char *pszSection, const char *pszName, double nDefValue)
{
	SI_Error nCode = m_ini.SetDoubleValue(pszSection, pszName, nDefValue); 
	if (nCode == SI_OK || nCode == SI_UPDATED || nCode == SI_INSERTED) {
		return true;
	}

	return false;
}

bool CConfFile::setBoolValue(const char *pszSection, const char *pszName, bool bDefValue)
{
	SI_Error nCode = m_ini.SetBoolValue(pszSection, pszName, bDefValue); 
	if (nCode == SI_OK || nCode == SI_UPDATED || nCode == SI_INSERTED) {
		return true;
	}

	return false;
}
/*************************************************************************
	> Date:   2020-12-08
	> Author: liangjun
	> Desc:   ini配置文件解析单例
*************************************************************************/

#ifndef _CONFFILE_H_
#define _CONFFILE_H_
#include "SimpleIni.h"

class CConfFile
{
public:
	typedef CSimpleIniA::TKeyVal TKeyVal;
	
public:
	static CConfFile *getInstance();
	bool loadFile(const char * pszFile);
	const char *getStrValue(const char *pszName, const char *pszDefValue=NULL);
	const char *getStrValue(const char *pszSection, const char *pszName, const char *pszDefValue);
	long getLongValue(const char *pszName, long lDefValue=0);
	long getLongValue(const char *pszSection, const char *pszName, long lDefValue=0);
	const TKeyVal *getSection(const char *pszSection);

private:
	CConfFile();
	~CConfFile();

private:
	//static CConfFile *m_pInstace;
	CSimpleIniA       m_ini;
};

inline const CConfFile::TKeyVal *CConfFile::getSection(const char *pszSection)
{
	return m_ini.GetSection(pszSection);
}
#endif /* _CONFFILE_H_ */

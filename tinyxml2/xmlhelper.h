#ifndef TINYXML2_HELPER_H
#define TINYXML2_HELPER_H

#include "tinyxml2.h"
#include <string>

/*
	xml 读写：
		例子:
                <?xml version="1.0" encoding="UTF-8"?>
				<root>
					<server>
						<ip>172.16.0.12</ip>
						<port>6000</port>
					</server>
				</root>
		    	--------------------------------------------------------------------------------
				XML* xmlHelper = new XMLHelper("./config.xml");
				XMLElement* node = xmlHelper->GetNode("server");

                printf("--%s--%s\n", "ip", xmlHelper->ToString(node, "ip").c_str());
                printf("--%s--%s\n", "port", xmlHelper->ToString(node, "port").c_str());

				delete xml;
		输出:
				--ip--172.16.0.12
				--port--6000
*/

namespace tinyxml2
{
class XMLHelper;

class XMLHelper {
public: 
	XMLHelper() : m_rootElement(NULL), m_isValid(false) {}

	XMLHelper(const char* xmlFile) : m_rootElement(NULL), m_isValid(false) {
		LoadFile(xmlFile);
	}

	~XMLHelper(){
		m_rootElement = NULL;
    }

	bool IsValid() const{ return m_isValid; }

    XMLError LoadFile(const char* xmlFile)
	{
	    XMLError ret = m_xmlDoc.LoadFile(xmlFile);
	    if (ret != 0) {
            m_isValid = false;
		    return ret;
	    }
        
		m_rootElement = m_xmlDoc.RootElement();
		m_isValid = true;
		return XML_SUCCESS;
	}

    /**获取根元素*/
	XMLElement* GetRootElement() {
		return m_rootElement;
	}

	/**获取根节点下的某个字根节点，参数key为范围根节点下的某个子节点根*/
	const XMLElement* GetNode(const char* key) {
		if(m_rootElement == NULL)
			return NULL;

		if(strlen(key) > 0){
			const XMLElement* node = m_rootElement->FirstChildElement(key);
			if(node == NULL)
				return NULL;
			return node;
		}

		return NULL;
	}

    XMLElement *GetElement(XMLElement *pNode, const char *pszKey) {
        if(pNode == NULL) 
            return NULL;
        return pNode->FirstChildElement(pszKey);
	}

    const char *GetText(const XMLElement *pNode, const char *pszKey) {
        if(pNode == NULL) 
            return 0;
            
        const XMLElement* pElement = pNode->FirstChildElement(pszKey);
        if(pElement == NULL)
            return 0;
        
        return pElement->GetText();
    }

    std::string ToString(const XMLElement *node, const char *pszKey) {
        const char *str = GetText(node, pszKey);
        return std::string(str);
	}

	int ToInt(const XMLElement *node, const char *pszKey) {
        int value = 0;
        const char *str = GetText(node, pszKey);
        XMLUtil::ToInt(str, &value);
        return value;
	}

	unsigned int ToUnsigned(const XMLElement *node, const char *pszKey) {
		unsigned int value = 0;
        const char *str = GetText(node, pszKey);
        XMLUtil::ToUnsigned(str, &value);
        return value;
	}

    float ToFloat(const XMLElement* node, const char *pszKey) {
		float value = 0.f;
        const char *str = GetText(node, pszKey);
        XMLUtil::ToFloat(str, &value);
        return value;
	}

	double ToDouble(const XMLElement* node, const char *pszKey) {
		double value = 0.f;
        const char *str = GetText(node, pszKey);
        XMLUtil::ToDouble(str, &value);
        return value;
	}

	int64_t ToInt64(const XMLElement* node, const char *pszKey) {
		int64_t value = 0;
        const char *str = GetText(node, pszKey);
        XMLUtil::ToInt64(str, &value);
        return value;
	}

	uint64_t ToUnsigned64(const XMLElement* node, const char *pszKey) {
		uint64_t value = 0;
        const char *str = GetText(node, pszKey);
        XMLUtil::ToUnsigned64(str, &value);
        return value;
	}
protected:
	XMLDocument m_xmlDoc;
	XMLElement* m_rootElement;
	bool m_isValid;
};

}

#endif // TINYXML2_HELPER_H
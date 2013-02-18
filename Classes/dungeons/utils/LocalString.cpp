#include "LocalString.h"
#include "CCFileUtils.h"

void LocalString::parse()
{
    string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
    path += "LocalString.xml";
    
    if(!isFileExistsInWritablePath("LocalString.xml"))
        return;
    
    unsigned long size;
    unsigned char* pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
    
	xmlDocPtr xmlDoc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
	if(NULL == xmlDoc)
	{
		CCLOG("LocalString xml parse failed!");
		return;
	}

	xmlNodePtr rootNode = xmlDocGetRootElement(xmlDoc);
	if(NULL == xmlDoc)
	{
		CCLOG("LocalString xml root null!");
		return;
	}

	xmlNodePtr curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "s"))
		{
			string id = attrToChar(curNode, "id");
			string value = attrToChar(curNode, "v");
			mStringMap[id] = value;
		}		
		curNode = curNode->next;
	}
}

const char* LocalString::getLocalizationString(const char* id)
{
	if (mStringMap.find(id) == mStringMap.end())
	{
		CCLOG("LocalString [%s] not found", id);
		return id;
	}
	
	return mStringMap[id].c_str();
//	xmlNodePtr curNode = childNode;
//	while(NULL != curNode)
//	{
//		xmlChar* ids = xmlGetProp(curNode,(const xmlChar*)"id");
//		if(xmlStrEqual((xmlChar*)id, ids))
//		{
//			xmlFree(ids);
//			return attrToChar(curNode, "v").c_str();
//		}
//		xmlFree(ids);
//		curNode = curNode->next;
//	}
//    CCLOG("LocalString [%s] not found", id);
//	return id;
}

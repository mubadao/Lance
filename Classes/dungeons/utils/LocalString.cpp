#include "LocalString.h"
#include "CCFileUtils.h"

void LocalString::parse()
{
	TargetPlatform target = CCApplication::sharedApplication()->getTargetPlatform();

    std::string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
    path += "LocalString.xml";
    
	if (target == kTargetWindows)
		path = CCFileUtils::sharedFileUtils()->fullPathForFilename("config/LocalString.xml");
	
    if(!isFileExistsInWritablePath("LocalString.xml"))
        return;
    
    unsigned long size;
    unsigned char* pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
    
	xmlDoc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
//	xmlDoc = xmlReadFile(path.c_str(), "utf-8", XML_PARSER_EOF);
	if(NULL == xmlDoc)
	{
		CCLOG("LocalString xml parse failed!");
		return;
	}

	rootNode = xmlDocGetRootElement(xmlDoc);
	if(NULL == xmlDoc)
	{
		CCLOG("LocalString xml root null!");
		return;
	}

	childNode = rootNode->children;
}

const char* LocalString::getLocalizationString( const char* id )
{
	xmlNodePtr curNode = childNode;
	while(NULL != curNode)
	{
		xmlChar* ids = xmlGetProp(curNode,(const xmlChar*)"id");
		if(xmlStrEqual((xmlChar*)id, ids))
		{
			xmlFree(ids);
			return attriToChar(curNode, "v");
		}
		xmlFree(ids);
		curNode = curNode->next;
	}
    CCLOG("LocalString [%s] not found", id);
	return id;
}

LocalString::LocalString()
{
	
}

LocalString::~LocalString()
{
	xmlFreeNode(childNode);
	xmlFreeDoc(xmlDoc);
}

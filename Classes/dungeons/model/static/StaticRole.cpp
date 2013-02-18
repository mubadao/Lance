#include "StaticRole.h"

StaticRole::StaticRole()
{
	parse();
}

StaticRole::~StaticRole()
{
}

void StaticRole::parse()
{
    string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
    path += "Boss.xml";

    if(!isFileExistsInWritablePath("Boss.xml"))
        assert(false);
    
    unsigned long size;
    unsigned char* pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	xmlDocPtr doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
	if(NULL == doc)
		CCLOG("Boss xml parse failed!");

	xmlNodePtr rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("Boss xml root null!");

	xmlNodePtr curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			string name = attrToChar(curNode, "name");
			if (name == "boss")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Boss"))
					{
						xmlBossInfo info;
						info.id = attrToInt(elem, "id");
						info.icon = attrToChar(elem,"icon");
						info.level = attrToInt(elem,"level");
						info.life = attrToInt(elem,"life");
						info.atk_min = attrToInt(elem,"atk_min");
						info.atk_max = attrToInt(elem,"atk_max");
						info.def_min = attrToInt(elem,"def_min");
						info.def_max = attrToInt(elem,"def_max");
						mBossMap[info.id] = info;
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
    
    path = CCFileUtils::sharedFileUtils()->getWriteablePath();
    path += "Player.xml";

    if(!isFileExistsInWritablePath("Player.xml"))
        assert(false);
    
    pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
	if(NULL == doc)
		CCLOG("Player xml parse failed!");

	rootNode = xmlDocGetRootElement(doc); 
	if(NULL == rootNode)
		CCLOG("Player xml root null!");

	curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			string name = attrToChar(curNode, "name");
			if (name == "player")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Player"))
					{
						xmlLevelInfo info;
						info.level = attrToInt(elem, "id");
						info.exp = attrToInt(elem,"exp");
						info.energyTime = attrToFloat(elem, "energytime") * 60 * 1000;
						info.powerTime = attrToFloat(elem,"powertime") * 60 * 1000;
						mLevelMap[info.level] = info;
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
}

xmlBossInfo* StaticRole::getBossInfo(int id)
{
	if (mBossMap.find(id) == mBossMap.end())
		assert(false);
	return &mBossMap[id];
}

xmlLevelInfo* StaticRole::getLevelInfo(int level)
{
    if(level > 35)
        return &mLevelMap[35];
    else
        return &mLevelMap[level];
}

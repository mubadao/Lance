#include "StaticRole.h"

void StaticRole::parse()
{
	TargetPlatform target = CCApplication::sharedApplication()->getTargetPlatform();

    std::string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
    path += "Boss.xml";

//	if (target == kTargetWindows)
		path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/Boss.xml");

	xmlDocPtr doc = xmlReadFile(path.c_str(), "utf-8", XML_PARSER_EOF);
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
			std::string name = attriToChar(curNode, "name");
			if (name == "boss")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Boss"))
					{
						BossInfo* bossInfo = new BossInfo();
						bossInfo->id = attriToInt(elem, "id");
						bossInfo->name = attriToChar(elem,"name");
						bossInfo->icon = attriToChar(elem,"icon");
						bossInfo->level = attriToInt(elem,"level");
						bossInfo->life = attriToInt(elem,"life");
						bossInfo->atk_min = attriToInt(elem,"atk_min");
						bossInfo->atk_max = attriToInt(elem,"atk_max");
						bossInfo->def_min = attriToInt(elem,"def_min");
						bossInfo->def_max = attriToInt(elem,"def_max");
						bossInfoMap[bossInfo->id] = bossInfo;
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

	if (target == kTargetWindows)
		path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/Player.xml");

	doc = xmlReadFile(path.c_str(), "utf-8", XML_PARSER_EOF);
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
			std::string name = attriToChar(curNode, "name");
			if (name == "player")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Player"))
					{
						LevelInfo* levelInfo = new LevelInfo();
						levelInfo->id = attriToInt(elem, "id");
						levelInfo->exp = attriToInt(elem,"exp");
						levelInfo->energytime = attriToFloat(elem, "energytime") * 60 * 1000;
						levelInfo->powertime = attriToFloat(elem,"powertime") * 60 * 1000;
						mLevelInfoMap[levelInfo->id] = levelInfo;
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
}

BossInfo* StaticRole::getBossInfo(int id)
{
	if (bossInfoMap.count(id) == 0)
		return NULL;
	return bossInfoMap[id];
}

RoleInfo* StaticRole::getRoleInfo( int id )
{
	return getBossInfo(id);
}

StaticRole::StaticRole()
{
	parse();
}

StaticRole::~StaticRole()
{

}

LevelInfo* StaticRole::getLevelInfo( int level )
{
    if(level > 35)
        return mLevelInfoMap[35];
    else
        return mLevelInfoMap[level];
}

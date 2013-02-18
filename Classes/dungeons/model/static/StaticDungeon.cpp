#include "StaticDungeon.h"
#include "json.h"

xmlDungeonInfo* StaticDungeon::getDungeonInfo(int dungeonID)
{
	if (dungeonMap.find(dungeonID) == dungeonMap.end())
		assert(false);
	return &dungeonMap[dungeonID];
}

xmlTaskInfo* StaticDungeon::getTaskInfo(int dungeonID, int floorID, int taskID)
{
	xmlFloorInfo* floorInfo = getFloorInfo(dungeonID, floorID);
	if (taskID >= floorInfo->taskList.size())
		assert(false);
	return &taskMap[floorInfo->taskList[taskID]];
}

xmlFloorInfo* StaticDungeon::getFloorInfo(int dungeonID, int floorID)
{
	return getDungeonInfo(dungeonID)->getFloor(floorID);
}

void StaticDungeon::parse()
{
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "Task.xml";

    if(!isFileExistsInWritablePath("Task.xml"))
        assert(false);
    
    unsigned long size;
    unsigned char* pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	xmlDocPtr doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
	if(NULL == doc)
		CCLOG("Task xml parse failed!");

	xmlNodePtr rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("Task xml root null!");

	xmlNodePtr curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			string name = attrToChar(curNode,"name");
			if (name == "task")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Task"))
					{
						xmlTaskInfo info;
						info.taskID = attrToInt(elem, "id");
						info.energy = attrToInt(elem,"energy");
						info.bossID = attrToInt(elem,"boss");
						info.drop = attrToInt(elem,"show");
						string s1 = attrToChar(elem,"exp");
						s1 = s1.substr(1, s1.length()-2);
						vector<string> idList = StringUtil::split(s1,",");
						info.expMin = charToInt(idList[0].c_str());
						info.expMax = charToInt(idList[1].c_str());
						s1 = attrToChar(elem,"coin");
						s1 = s1.substr(1, s1.length()-2);
						idList = StringUtil::split(s1,",");
						info.coinMin = charToInt(idList[0].c_str());
						info.coinMax = charToInt(idList[1].c_str());

						taskMap[info.taskID] = info;
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}

	path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "Dungeon.xml";

    if(!isFileExistsInWritablePath("Dungeon.xml"))
        assert(false);
    
    pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
	if(NULL == doc)
		CCLOG("Dungeons xml parse failed!");

	rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("Dungeons xml root null!");

	xmlDungeonInfo dungeonData;
	dungeonData.dungeonsID = 1;

	curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			std::string name = attrToChar(curNode,"name");
			if (name == "1")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Info"))
					{
						xmlFloorInfo floorData;
						floorData.floorID = attrToInt(elem,"id");
						string s1 = attrToChar(elem,"task");
						s1 = s1.substr(1, s1.length()-2);
						vector<string> idList = StringUtil::split(s1,",");
						for (int i = 0; i < idList.size(); i++)
						{
							floorData.taskList.push_back(strToInt(idList[i]));
						}
						dungeonData.floorList[floorData.floorID] = floorData;
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}
	dungeonMap[dungeonData.dungeonsID] = dungeonData;
}

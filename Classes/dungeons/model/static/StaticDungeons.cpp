#include "StaticDungeons.h"

DungeonsStatic* StaticDungeons::getDungeonsInfo( int dungeonsID )
{
	assert(dungeonsInfoMap.count(dungeonsID) != 0);
	return dungeonsInfoMap[dungeonsID];
}

TaskStatic* StaticDungeons::getTaskInfo( int dungeonsID, int floorID, int taskID )
{
	FloorStatic* floor = getFloorInfo(dungeonsID, floorID);
	return floor->getTask(taskID);
}

FloorStatic* StaticDungeons::getFloorInfo( int dungeonsID, int floorID )
{
	DungeonsStatic* dungeons = getDungeonsInfo(dungeonsID);
	return dungeons->getFloor(floorID);
}

void StaticDungeons::parse()
{
	TargetPlatform target = CCApplication::sharedApplication()->getTargetPlatform();

	std::string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "Task.xml";

	if (target == kTargetWindows)
		path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/Task.xml");
    
	xmlDocPtr doc = xmlReadFile(path.c_str(), "utf-8", XML_PARSER_EOF);
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
			std::string name = attriToChar(curNode,"name");
			if (name == "task")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Task"))
					{
						TaskStatic* dataVO = new TaskStatic();
						dataVO->taskID = attriToInt(elem, "id");
						dataVO->energy = attriToInt(elem,"energy");
						dataVO->bossID = attriToInt(elem,"boss");
						dataVO->drop = attriToInt(elem,"show");
						std::string s1 = attriToChar(elem,"exp");
						s1 = s1.substr(1, s1.length()-2);
						std::vector<std::string> idList = StringUtil::split(s1,", ");
						dataVO->expMin = charToInt(idList[0].c_str());
						dataVO->expMax = charToInt(idList[1].c_str());
						s1 = attriToChar(elem,"coin");
						s1 = s1.substr(1, s1.length()-2);
						idList = StringUtil::split(s1,", ");
						dataVO->coinMin = charToInt(idList[0].c_str());
						dataVO->coinMax = charToInt(idList[1].c_str());

						taskInfoMap[dataVO->taskID] = dataVO;
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}

	path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "Dungeon.xml";

	if (target == kTargetWindows)
		path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/Dungeon.xml");

	doc = xmlReadFile(path.c_str(), "utf-8", XML_PARSER_EOF);
	if(NULL == doc)
		CCLOG("Dungeons xml parse failed!");

	rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("Dungeons xml root null!");

	DungeonsStatic* dungeonsData = new DungeonsStatic();
	dungeonsData->dungeonsID = 1;
	curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			std::string name = attriToChar(curNode,"name");
			if (name == "1")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Info"))
					{
						FloorStatic* floorData = new FloorStatic();
						floorData->floorID = attriToInt(elem,"id");
						floorData->name = attriToChar(elem,"name");
						floorData->desc = attriToChar(elem,"description");
						floorData->scene = attriToChar(elem,"scene");
						std::string s1 = attriToChar(elem,"task");
						s1 = s1.substr(1, s1.length()-2);
						std::vector<std::string> idList = StringUtil::split(s1,", ");
						for (int i = 0; i < idList.size(); i++)
						{
							TaskStatic* taskData = taskInfoMap[strToInt(idList[i])];
							if (NULL != taskData)
								floorData->taskList[taskData->taskID] = taskData;
						}
						dungeonsData->floorList[floorData->floorID] = floorData;
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}
	dungeonsInfoMap[dungeonsData->dungeonsID] = dungeonsData;
}

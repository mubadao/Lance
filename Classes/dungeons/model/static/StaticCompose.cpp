#include "StaticCompose.h"

StaticCompose::StaticCompose()
{

}

StaticCompose::~StaticCompose()
{
	ComposeInfoStaticMap::iterator iter = mComposeInfoMap.begin();
	while(iter != mComposeInfoMap.end())
	{
		delete (iter->second);
		iter++;
	}
	mComposeInfoMap.clear();
}

void StaticCompose::parse()
{
	TargetPlatform target = CCApplication::sharedApplication()->getTargetPlatform();

    std::string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
    path += "Compose.xml";
    
	if (target == kTargetWindows)
		path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/Compose.xml");

	xmlDocPtr doc = xmlReadFile(path.c_str(), "utf-8", XML_PARSER_EOF);
	if(NULL == doc)
		CCLOG("Dungeons xml parse failed!");

	xmlNodePtr rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("Dungeons xml root null!");

	xmlNodePtr curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			std::string name = attriToChar(curNode,"name");
			if (name == "compose")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Compose"))
					{
						ComposeInfoStatic* composeInfoStatic = new ComposeInfoStatic();
						composeInfoStatic->mItemID = attriToInt(elem, "itemID");
						xmlNodePtr subNode = elem->children;
						while(NULL != subNode)
						{
							if (!xmlStrcmp(subNode->name, BAD_CAST "Compose"))
							{
								ComposeItemStatic* composeItemStatic = new ComposeItemStatic();
								composeItemStatic->mItemID = attriToInt(subNode, "itemID");
								composeItemStatic->mItemCount = attriToInt(subNode, "itemCount");
								composeInfoStatic->mComposeItemList.push_back(composeItemStatic);
							}
							subNode = subNode->next;
						}
						mComposeInfoMap[composeInfoStatic->mItemID] = composeInfoStatic;
					}
					elem =  elem->next;
				}
			}
		}
		curNode = curNode->next;
	}

	xmlFreeDoc(doc);
}

ComposeInfoStatic* StaticCompose::getComposeInfo( int itemID )
{
	return mComposeInfoMap[itemID];
}

ComposeInfoStaticMap& StaticCompose::getComposeMap()
{
	return mComposeInfoMap;
}


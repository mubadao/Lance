#include "StaticShop.h"

StaticShop::StaticShop()
{

}

StaticShop::~StaticShop()
{
	BuyMoneyStaticList::iterator iter = mBuyMoneyStaticList.begin();
	while(iter != mBuyMoneyStaticList.end())
		delete (*iter);
	mBuyMoneyStaticList.clear();
}

void StaticShop::parse()
{
	TargetPlatform target = CCApplication::sharedApplication()->getTargetPlatform();

	std::string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "BuyMoney.xml";

	if (target == kTargetWindows)
		path = CCFileUtils::sharedFileUtils()->fullPathForFilename("config/BuyMoney.xml");

    if(!isFileExistsInWritablePath("BuyMoney.xml"))
        assert(false);
    
    unsigned long size;
    unsigned char* pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	xmlDocPtr doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
//	xmlDocPtr doc = xmlReadFile(path.c_str(), "utf-8", XML_PARSER_EOF);
	if(NULL == doc)
		CCLOG("BuyMoney xml parse failed!");

	xmlNodePtr rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("BuyMoney xml root null!");

	xmlNodePtr curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			std::string name = attriToChar(curNode, "name");
			if (name == "items")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Item"))
					{
						BuyMoneyStatic* itemStatic = new BuyMoneyStatic();
						itemStatic->id = attriToInt(elem, "id");
                        itemStatic->identifier = attriToChar(elem, "identifier");
						itemStatic->money = attriToInt(elem, "money");
						itemStatic->dollar = attriToFloat(elem, "dollar");
						mBuyMoneyStaticList.push_back(itemStatic);
					}
					elem = elem->next;
				}

			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);

	path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "Supplement.xml";

    if (target == kTargetWindows)
        path = CCFileUtils::sharedFileUtils()->fullPathForFilename("config/Supplement.xml");

    if(!isFileExistsInWritablePath("Supplement.xml"))
        assert(false);
    
    pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
//	doc = xmlReadFile(path.c_str(), "utf-8", XML_PARSER_EOF);
	if(NULL == doc)
		CCLOG("Supplement xml parse failed!");

	rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("Supplement xml root null!");

	curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			std::string name = attriToChar(curNode,"name");
			if (name == "buycoin")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Item"))
					{
						BuyCoinStatic* itemStatic;
						itemStatic = new BuyCoinStatic();
						itemStatic->count = attriToInt(elem, "count");
						itemStatic->money = attriToInt(elem, "money");
						itemStatic->id = attriToInt(elem, "id");
						mBuyCoinStaticMap[itemStatic->id] = itemStatic;
					}
					elem = elem->next;
				}
			}
			else if (name == "properties")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Box"))
					{
						BuyEnergyOrPowerStatic* itemStatic = new BuyEnergyOrPowerStatic();
						itemStatic->id = attriToInt(elem, "id");
						itemStatic->costType.money = attriToInt(elem, "money");
						itemStatic->costType.coin = attriToInt(elem, "coin");
						itemStatic->costType.free = attriToInt(elem, "free");
						mBuyEnergyOrPowerStaticMap[itemStatic->id] = itemStatic;
					}
					elem = elem->next;
				}
			}
            else if (name == "buyfusion")
			{
                xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Item"))
					{
						mBuyFusionStatic.count = attriToInt(elem, "count");
						mBuyFusionStatic.costType.money = attriToInt(elem, "money");
                        mBuyFusionStatic.costType.coin = attriToInt(elem, "coin");
                        mBuyFusionStatic.costType.free = attriToInt(elem, "free");
						mBuyFusionStatic.id = attriToInt(elem, "id");
					}
					elem = elem->next;
				}
            }
            else if (name == "buycatalyst")
			{
                xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Item"))
					{
						BuyZhuRongStatic* itemStatic;
						itemStatic = new BuyZhuRongStatic();
						itemStatic->count = attriToInt(elem, "count");
						itemStatic->money = attriToInt(elem, "money");
						itemStatic->id = attriToInt(elem, "id");
						mBuyZhuRongStaticMap[itemStatic->count] = itemStatic;
					}
					elem = elem->next;
				}
            }
		}
		curNode = curNode->next;
	}

	xmlFreeDoc(doc);
    
    path = CCFileUtils::sharedFileUtils()->getWriteablePath();
    path += "Box.xml";
    
	if (target == kTargetWindows)
		path = CCFileUtils::sharedFileUtils()->fullPathForFilename("config/Box.xml");
    
    if(!isFileExistsInWritablePath("Box.xml"))
        assert(false);
    
    pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
//	doc = xmlReadFile(path.c_str(), "utf-8", XML_PARSE_NOBLANKS);
	if(NULL == doc)
		CCLOG("Box xml parse failed!");
    
	rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("Box xml root null!");
    
	curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			std::string name = attriToChar(curNode,"name");
			if (name == "properties")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Box"))
					{
						BoxStatic* itemStatic;
						itemStatic = new BoxStatic();
						itemStatic->name = attriToChar(elem, "name");
						itemStatic->id = attriToInt(elem, "id");
						itemStatic->desc = attriToChar(elem, "desc");
						itemStatic->costType.coin = attriToInt(elem, "coin");
						itemStatic->costType.money = attriToInt(elem, "money");
						itemStatic->costType.free = attriToInt(elem, "free");
						mBoxStaticList.push_back(itemStatic);
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}
    
    xmlFreeDoc(doc);
}

BuyMoneyStaticList& StaticShop::getBuyMoneyStaticList()
{
	return mBuyMoneyStaticList;
}

MoneyType StaticShop::getSupplyMoneyType( SupplyType type )
{
	BuyEnergyOrPowerStatic* staticItem = mBuyEnergyOrPowerStaticMap[type];
	return staticItem->costType.getMoneyType();
}

int StaticShop::getSupplyCostCount( SupplyType type )
{
	BuyEnergyOrPowerStatic* staticItem = mBuyEnergyOrPowerStaticMap[type];
	return staticItem->costType.getCostCount();
}

BuyCoinStatic* StaticShop::getBuyCoinStatic( int id )
{
	return mBuyCoinStaticMap[id];
}

BuyZhuRongStatic* StaticShop::getBuyZhuRongStatic(int count)
{
	return mBuyZhuRongStaticMap[count];
}


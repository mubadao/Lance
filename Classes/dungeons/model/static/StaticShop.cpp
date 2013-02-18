#include "StaticShop.h"

void StaticShop::parse()
{
	_parseBuyMoney();
	_parseSupplement();
	_parseBox();
}

void StaticShop::_parseBuyMoney()
{
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "BuyMoney.xml";
	
    if(!isFileExistsInWritablePath("BuyMoney.xml"))
        assert(false);
    
    unsigned long size;
    unsigned char* pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	xmlDocPtr doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
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
			string name = attrToChar(curNode, "name");
			if (name == "items")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Item"))
					{
						xmlBuyMoney item;
						item.id = attrToInt(elem, "id");
                        item.identifier = attrToChar(elem, "identifier");
						item.money = attrToInt(elem, "money");
						item.dollar = attrToChar(elem, "dollar");
						mBuyMoney.push_back(item);
					}
					elem = elem->next;
				}
				
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
}

void StaticShop::_parseSupplement()
{
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "Supplement.xml";
	
    if(!isFileExistsInWritablePath("Supplement.xml"))
        assert(false);
    
    unsigned long size;
    unsigned char* pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	xmlDocPtr doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
	if(NULL == doc)
		CCLOG("Supplement xml parse failed!");
	
	xmlNodePtr rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("Supplement xml root null!");
	
	xmlNodePtr curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			string name = attrToChar(curNode,"name");
			if (name == "buycoin")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Item"))
					{
						xmlBuy item;
						item.id = attrToInt(elem, "id");
						item.count = attrToInt(elem, "count");
						item.money = attrToInt(elem, "money");
						mBuyCoin[item.id] = item;
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
						xmlBuy item;
						item.id = attrToInt(elem, "id");
						item.money = attrToInt(elem, "money");
						mBuyEnergyOrPower[item.id] = item;
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
						xmlBuy item;
						item.id = attrToInt(elem, "id");
						item.count = attrToInt(elem, "count");
						item.money = attrToInt(elem, "money");
						mBuyFusion[item.id] = item;
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
						xmlBuy item;
						item.id = attrToInt(elem, "id");
						item.count = attrToInt(elem, "count");
						item.money = attrToInt(elem, "money");
						mBuyZhuRong[item.id] = item;
					}
					elem = elem->next;
				}
            }
		}
		curNode = curNode->next;
	}
	
	xmlFreeDoc(doc);
}

void StaticShop::_parseBox()
{
	
    string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
    path += "Box.xml";
    
    if(!isFileExistsInWritablePath("Box.xml"))
        assert(false);
    
    unsigned long size;
    unsigned char* pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	
	xmlDocPtr doc = xmlReadMemory((const char*)pBytes, size, NULL, "utf-8", XML_PARSE_RECOVER);
	if(NULL == doc)
		CCLOG("Box xml parse failed!");
    
	xmlNodePtr rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("Box xml root null!");
    
	xmlNodePtr curNode = rootNode->children;
	while(NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "Group"))
		{
			std::string name = attrToChar(curNode,"name");
			if (name == "properties")
			{
				xmlNodePtr elem = curNode->children;
				while (NULL != elem)
				{
					if (!xmlStrcmp(elem->name, BAD_CAST "Box"))
					{
						xmlBox item;
						item.id = attrToInt(elem, "id");
						//TODO: moneyType
//						item.moneyType = (MoneyType)attrToInt(elem, "moneyType");
						item.moneyType = MONEY_TYPE_MONEY;
						item.money = attrToInt(elem, "money");
						mBox.push_back(item);
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}
    
    xmlFreeDoc(doc);
}

int StaticShop::getSupplyCostCount(SupplyType type)
{
	return mBuyEnergyOrPower[type].money;
}

xmlBuy* StaticShop::getBuyCoin(int id)
{
	return &mBuyCoin[id];
}

xmlBuy* StaticShop::getBuyFusion(int count)
{
	return &mBuyFusion[count];
}

xmlBuy* StaticShop::getBuyZhuRong(int count)
{
	return &mBuyZhuRong[count];
}


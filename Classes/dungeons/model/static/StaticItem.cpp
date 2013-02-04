#include "StaticItem.h"
#include "ItemProxy.h"
#include "LocalString.h"

void StaticItem::parse()
{
	TargetPlatform target = CCApplication::sharedApplication()->getTargetPlatform();

    std::string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
    path += "Equipage.xml";
    
	if (target == kTargetWindows)
		path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/Equipage.xml");

	xmlDocPtr doc = xmlReadFile(path.c_str(), "utf-8", XML_PARSER_EOF);
	if(NULL == doc)
		CCLOG("Equipage xml parse failed!");

	xmlNodePtr rootNode = xmlDocGetRootElement(doc);
	if(NULL == rootNode)
		CCLOG("Equipage xml root null!");

	xmlNodePtr curNode = rootNode->children;
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
					if (!xmlStrcmp(elem->name, BAD_CAST "Properties"))
					{
						ItemStatic* itemStatic;
						ItemKind itemKind = (ItemKind)attriToInt(elem, "type");
						if (isEquip(itemKind))
						{
							EquipStatic* equipInfo = new EquipStatic();
							equipInfo->quality = attriToInt(elem, "quality");
							equipInfo->fusion = attriToInt(elem, "fusion");
							equipInfo->intensify_price = attriToInt(elem, "intensify_price");
							equipInfo->intensify_energy = attriToInt(elem, "intensify_energy");
							equipInfo->intensify_fusion = attriToInt(elem, "intensify_fusion");
							equipInfo->rule = attriToInt(elem, "rule");
                            equipInfo->level = attriToInt(elem, "level");
							equipInfo->id = attriToInt(elem, "id");
                            equipInfo->sell = attriToInt(elem, "sell");
//                            std::string s1 = attriToChar(elem,"def_min");
//                            s1 = s1.substr(1, s1.length()-2);
//                            std::vector<std::string> list = StringUtil::split(s1,", ");
//                            equipInfo->def_min = strToInt(list[0]);
//                            equipInfo->def_max = strToInt(list[1]);
//                            s1 = attriToChar(elem,"def_min");
//                            s1 = s1.substr(1, s1.length()-2);
//                            list = StringUtil::split(s1,", ");
//                            equipInfo->def_min = strToInt(list[0]);
//                            equipInfo->def_max = strToInt(list[1]);
							mEquipInfoMap[equipInfo->id] = equipInfo;
							itemStatic = equipInfo;
						}
						else
						{
							itemStatic = new ItemStatic();
						}

						itemStatic->icon = attriToChar(elem, "icon");
						itemStatic->name = attriToChar(elem, "name");
						itemStatic->desc = attriToChar(elem, "desc");
						itemStatic->id = attriToInt(elem, "id");
						itemStatic->kind = itemKind;

						//		std::string s1 = attriToChar(elem,"buy");
						//		s1 = s1.substr(1, s1.length()-2);
						//		std::vector<std::string> idList = StringUtil::split(s1,", ");
						//		itemStatic->buyGold = strToInt(idList[0]);
						//		itemStatic->buyMoney = strToInt(idList[1]);
						//		itemStatic->sell = attriToInt(elem, "sell");
						//		if (itemStatic->getMoneyType() != MONEY_TYPE_NONE)
						//			itemStatic->desc = attriToChar(elem, "desc");
						mItemInfoMap[itemStatic->id] = itemStatic;
					}
					elem = elem->next;
				}
			}
		}
		curNode = curNode->next;
	}

	xmlFreeDoc(doc);
}

EquipStatic* StaticItem::getEquipInfo(int id)
{
	if (mEquipInfoMap.count(id) == 0)
		return NULL;
	return mEquipInfoMap[id];
}

ItemStatic* StaticItem::getItemInfo( int id )
{
	if (mItemInfoMap.count(id) == 0)
		return NULL;
	return mItemInfoMap[id];
}

bool StaticItem::isEquip( ItemKind kind )
{
	return kind == ITEM_KIND_HELM ||
		kind == ITEM_KIND_NECKLACE ||
		kind == ITEM_KIND_WEAPON ||
		kind == ITEM_KIND_CLOTH ||
		kind == ITEM_KIND_RING ||
		kind == ITEM_KIND_SHOES;
}

bool StaticItem::isEquip( int id )
{
	ItemStatic* itemStatic = getItemInfo(id);
	return isEquip(itemStatic->kind);
}

void StaticItem::getMysteryStaticList( ItemStaticList& itemList )
{
	ItemStaticMap::iterator iter = mItemInfoMap.begin();
	int count = 0;
	while(count++ < 10)
	{
		if (isEquip(iter->second->kind))
		{
			itemList.push_back(iter->second);
		}
		iter++;
	}
}

void StaticItem::getPropList( ItemStaticList& itemList )
{
	itemList.clear();
	ItemStaticMap::iterator iter = mItemInfoMap.begin();
	while(iter != mItemInfoMap.end())
	{
		if(iter->second->kind == 8 || iter->second->kind == 9)
			itemList.push_back(iter->second);
		iter++;
	}
}

void StaticItem::getShopList( ItemStaticList& itemList )
{
	itemList.clear();
	ItemStaticMap::iterator iter = mItemInfoMap.begin();
	while(iter != mItemInfoMap.end())
	{
		if(iter->second->kind == ITEM_KIND_BOX)
			itemList.push_back(iter->second);
		iter++;
	}
}

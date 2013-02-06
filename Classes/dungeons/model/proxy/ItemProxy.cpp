#include "ItemProxy.h"
#include "CCFileUtils.h"
#include "StaticItem.h"
#include "LocalString.h"

ItemProxy::ItemProxy()
{
//	testData();
    lastQiangHuaEquip = new EquipInfo();
}

ItemProxy::~ItemProxy()
{
    delete lastQiangHuaEquip;
}

void ItemProxy::testData()
{
	std::vector<int> tempList;
	tempList.push_back(10000);
	tempList.push_back(11000);
	tempList.push_back(12000);
	tempList.push_back(13000);
	tempList.push_back(14000);
	tempList.push_back(15000);
	tempList.push_back(15000);
	tempList.push_back(15000);
	tempList.push_back(15000);
	bagInfo.bagmax = 10;
	bagInfo.bagid = 5;
	for (int i = 0; i < 9; i++)
	{
		EquipInfo* equip = new EquipInfo();
		equip->atkMax = 20 + i;
		equip->atkMin = 10 + i;
		equip->defMax = 15 + i;
        equip->defMin = 16 + i;
		equip->exp = 20 + i;
		equip->id = tempList[i];
		equip->index = i;
		equip->level = 2 + i;
		equip->life = 5 + i;
		equip->state = i<6?1:0;
		addEquip(equip, false);
	}

	ItemInfo* itemInfo = new ItemInfo();
	itemInfo->id = 26002;
	itemInfo->count = 10;
	itemInfo->index = 9;
	addItem(itemInfo);

	lastQiangHuaEquip = bagInfo.equipList[0];
	curQiangHuaEquip = bagInfo.equipList[0];
	
	
}

bool ItemProxy::isEquip(int id)
{
	ItemStatic* itemStatic = StaticItem::shared()->getItemInfo(id);
	return isEquip(itemStatic->kind);
}

bool ItemProxy::isEquip( ItemKind kind )
{
	return kind == ITEM_KIND_HELM ||
		kind == ITEM_KIND_NECKLACE ||
		kind == ITEM_KIND_WEAPON ||
		kind == ITEM_KIND_CLOTH ||
		kind == ITEM_KIND_RING ||
		kind == ITEM_KIND_SHOES;
}

bool ItemProxy::isEquipPutOn( int index )
{
    EquipInfo* equipInfo = getEquip(index);
	return equipInfo->state == 1;
}

bool ItemProxy::isEquipTakeOff( int index )
{
	return false;
}

void ItemProxy::putOnEquip( int index )
{
    EquipInfo* equipInfo = getEquip(index);
    takeOffEquip(getItemKind(equipInfo->id));
    equipInfo->state = 1;
}

void ItemProxy::takeOffEquip( int index )
{
    EquipInfo* equipInfo = getEquip(index);
    takeOffEquip(getItemKind(equipInfo->id));
    equipInfo->state = 0;
}

void ItemProxy::takeOffEquip( ItemKind part )
{
    EquipList& equipList = getEquipList();
    EquipList::iterator iter = equipList.begin();
    while(iter != equipList.end())
    {
        ItemKind srcPart = getItemKind((*iter)->id);
        if(part == srcPart && (*iter)->state == 1)
        {
            (*iter)->state = 0;
            break;
        }
        iter++;
    }
}

void ItemProxy::sellItem( vector<int>& sellsList )
{
    EquipList& equipList = getEquipList();
    vector<int>::iterator iter = sellsList.begin();
    while(iter != sellsList.end())
    {
        EquipList::iterator iter1 = equipList.begin();
        while(iter1 != equipList.end())
        {
            if((*iter1)->index == *iter)
            {
                iter1 = equipList.erase(iter1);
                break;
            }
            else
            {
                iter1++;
            }
        }
        iter++;
    }
}

void ItemProxy::removeEquip(int index)
{
    EquipList& equipList = getEquipList();
    EquipList::iterator iter = equipList.begin();
    while(iter != equipList.end())
    {
            if((*iter)->index == index)
            {
                iter = equipList.erase(iter);
                break;
            }
            else
            {
                iter++;
            }
    }
}

EquipList& ItemProxy::getEquipList()
{
	return bagInfo.equipList;
}

ItemList& ItemProxy::getItemList()
{
    return itemList;
}

int ItemProxy::getBagMax()
{
	return mBagMax;
}

int ItemProxy::getBagID()
{
	return bagInfo.bagid;
}

EquipInfo* ItemProxy::getEquip(int index)
{
	EquipList& equipList = getEquipList();
    for(int i = 0; i < equipList.size(); i++)
    {
        if(equipList[i]->index == index)
            return equipList[i];
    }
    return NULL;
}

void ItemProxy::addEquip( std::vector<EquipageInfo>& equipList )
{
	for (int i = 0; i < equipList.size(); i++)
		addEquip(equipList[i]);
}

void ItemProxy::addEquip( EquipInfo* equipInfo, bool isNew )
{
	EquipInfo* equip = getEquip(equipInfo->index);
	if (equip != NULL)
		equip->convert(equipInfo);
	else
    {
        EquipInfo* newInfo = NULL;
        if(isNew)
        {
            newInfo = new EquipInfo();
            newInfo->convert(equipInfo);
        }
        else
        {
            newInfo = equipInfo;
        }
        
		bagInfo.equipList.push_back(newInfo);
		addItem(equipInfo, false);
    }
}

void ItemProxy::addEquip( EquipageInfo& equipageInfo )
{
    EquipInfo* equipInfo = getEquip(equipageInfo.index);
    if(equipInfo == NULL)
    {
        equipInfo = new EquipInfo();
        addEquip(equipInfo);
    }
	equipInfo->convert(equipageInfo);
}

ItemInfo* ItemProxy::getItem(int index)
{
    ItemList& list = getItemList();
    for(int i = 0; i < list.size(); i++)
    {
        if(list[i]->index == index)
            return list[i];
    }
    return NULL;
}

void ItemProxy::addItem(ItemInfo* itemInfo, bool isNew)
{
    ItemInfo* iteminfo1 = getItem(itemInfo->index);
	if (iteminfo1 != NULL)
		iteminfo1->convert(itemInfo);
    else
    {
        ItemInfo* newInfo = NULL;
        if(isNew)
        {
            newInfo = new ItemInfo();
            newInfo->convert(itemInfo);
        }
        else
        {
            newInfo = itemInfo;
        }
        
        itemList.push_back(newInfo);
    }
}

void ItemProxy::clearMergeList()
{
	mSelectList.clear();
}

void ItemProxy::setLastQiangHuaEquip( EquipInfo* equipInfo )
{
//    lastQiangHuaEquip = equipInfo;
    this->lastQiangHuaEquip->convert(equipInfo);
}

void ItemProxy::getAffixTitle( Affix* affix, string& ret )
{
	switch (affix->type)
	{
//	case AFFIX_TYPE_HURT:
//		ret = gls("hurt");
//		break;
//	case AFFIX_TYPE_HIT:
//		ret = gls("hit");
//		break;
//    case AFFIX_TYPE_ATTACK:
//    case AFFIX_TYPE_DEFENSE:
//        break;
	}
}

void ItemProxy::getAffixValue( Affix* affix, string& ret )
{

}

int ItemProxy::getPutonCount()
{
	int count = 0;
	EquipList& equipList = getEquipList();
	EquipList::iterator iter = equipList.begin();
	while(iter != equipList.end())
	{
		if((*iter)->state == 1)count++;
		iter++;
	}
	return count;
}

int ItemProxy::getEquipCount()
{
	return getEquipList().size();
}

void ItemProxy::getPutOnList( EquipList& retEquipList )
{
	EquipList& equipList = getEquipList();
	for(int i = 0; i < equipList.size(); i++)
	{
		if(equipList[i]->isPutOn())
			retEquipList.push_back(equipList[i]);
	}
}

void ItemProxy::getTakeOffList( EquipList& retEquipList )
{
	EquipList& equipList = getEquipList();
	for(int i = 0; i < equipList.size(); i++)
	{
		if(!equipList[i]->isPutOn())
			retEquipList.push_back(equipList[i]);
	}
}

int ItemProxy::getItemCount(int id)
{
	int count = 0;
	for(int i = 0; i < itemList.size(); i++)
	{
		if(id == itemList[i]->id)
			count += itemList[i]->count;
	}
	return count;
}

ItemKind ItemProxy::getItemKind( int id )
{
	ItemStatic* itemStatic = StaticItem::shared()->getEquipInfo(id);
	return itemStatic->kind;
}

const char* ItemProxy::getTypeTitle( int id )
{
	EquipStatic* itemInfo = StaticItem::shared()->getEquipInfo(id);
	switch(itemInfo->kind)
	{
	case ITEM_KIND_HELM:
		return gls("helm");
		break;
	case ITEM_KIND_NECKLACE:
		return gls("necklace");
		break;
	case ITEM_KIND_WEAPON:
		return gls("weapon");
		break;
	case ITEM_KIND_CLOTH:
		return gls("cloth");
		break;
	case ITEM_KIND_RING:
		return gls("ring");
		break;
	case ITEM_KIND_SHOES:
		return gls("shoes");
		break;
	default:
		return "";
	}
	return NULL;
}

bool ItemProxy::isBagFull()
{
    return getEquipCount() >= getBagMax();
}

EquipInfo* ItemProxy::getPutOnEquip(ItemKind kind)
{
    EquipList& equipList = getEquipList();
	for(int i = 0; i < equipList.size(); i++)
	{
		if(equipList[i]->isPutOn() && equipList[i]->getKind() == kind)
			return equipList[i];
	}
    return NULL;
}

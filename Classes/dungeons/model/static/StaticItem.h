#ifndef _StaticItem_H_
#define _StaticItem_H_

#include "Global.h"
#include "TypeDefine.h"
#include "UserVO.h"

//struct ItemStatic
//{
//	int baseId;
//	string name;
//	string desc;
//	string icon;
//	ItemKind kind;
//	MoneyType moneyType;
//	int buyCost;
//	int sell;
//	
//    ItemStatic():baseId(-1),buyCost(0),moneyType(MONEY_TYPE_NONE),sell(0) {}
//};
//typedef vector<ItemStatic> ItemStaticList;
//typedef map<int, ItemStatic> ItemStaticMap;

struct xmlEquipInfo
{
	int baseId;
	string icon;
	EquipType type;
	int quality;
	int fusion;
	int intensify_price;
	int intensify_energy;
	int intensify_fusion;
	int rule;
    int level;
	int sell;
};
typedef vector<xmlEquipInfo> xmlEquipList;
typedef map<int, xmlEquipInfo> xmlEquipMap;

class StaticItem : public Singleton<StaticItem>
{
	xmlEquipMap mEquipInfoMap;
//	ItemStaticMap mItemInfoMap;

public:
	void parse();

//	void getMysteryStaticList(ItemStaticList& itemList);
//	void getPropList(ItemStaticList& itemList);
//	void getShopList(ItemStaticList& itemList);

	xmlEquipInfo* getEquipInfo(int baseId);
//	const ItemStatic& getItemInfo(int baseId);
};

#endif
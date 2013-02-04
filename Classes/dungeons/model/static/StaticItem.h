#ifndef StaticItem_h__
#define StaticItem_h__
#include "StaticData.h"
#include "Global.h"
#include "DataVO.h"

/*道具信息：装备，道具等*/

//物品分类
enum ItemKind
{
	ITEM_KIND_HELM=0,		//装备
	ITEM_KIND_NECKLACE=1,	//装备
	ITEM_KIND_WEAPON=2,		//装备
	ITEM_KIND_CLOTH=3,		//装备
	ITEM_KIND_RING=4,		//装备
	ITEM_KIND_SHOES=5,		//装备
	ITEM_KIND_MATERIAL=6,	//材料
	ITEM_KIND_BOX=7,			//宝箱
	ITEM_KIND_YAOSHUI=8,			//药水
	ITEM_KIND_QIANDAI=9			//钱袋
} ;

enum MoneyType
{
    MONEY_TYPE_FREE=0,
	MONEY_TYPE_GOLD,
	MONEY_TYPE_MONEY,
	MONEY_TYPE_NONE
};

struct ItemStatic
{
	int id;
	const char* name;
	const char* icon;
	int sell;
	int buyGold;
	int buyMoney;
    int buyFree;
	ItemKind kind;
	const char* desc;
	MoneyType getMoneyType()
	{
		if (buyGold > 0) return MONEY_TYPE_GOLD;
		else if(buyMoney > 0) return MONEY_TYPE_MONEY;
		return MONEY_TYPE_NONE;
	}
    
    MoneyType getRandomMoneyType()
	{
        if (buyGold > 0) return MONEY_TYPE_GOLD;
		else if(buyMoney > 0) return MONEY_TYPE_MONEY;
        else if(buyFree > 0) return MONEY_TYPE_FREE;
		return MONEY_TYPE_NONE;
    }

	int getMoneyCount()
	{
		if (getMoneyType() == MONEY_TYPE_GOLD)
			return buyGold;
		else if(getMoneyType() == MONEY_TYPE_MONEY)
			return buyMoney;
		return 0;
	}
    ItemStatic():buyFree(-1)
    {
        
    }
};
struct EquipStatic : public ItemStatic
{
	int quality;
	int atk_min;
	int atk_max;
	int def_min;
	int def_max;
	int life_min;
	int life_max;
	int fusion;
	int intensify_price;
	int intensify_energy;
	int intensify_fusion;
	int rule;
    int level;
};
typedef std::vector<ItemStatic*> ItemStaticList;
typedef std::map<int, ItemStatic*> ItemStaticMap;

class StaticItem : public StaticData, public Singleton<StaticItem>
{
	std::map<int, EquipStatic*> mEquipInfoMap;
	std::map<int, ItemStatic*> mItemInfoMap;
public:
	void parse();
	void getMysteryStaticList(ItemStaticList& itemList);
	void getPropList(ItemStaticList& itemList);
	void getShopList(ItemStaticList& itemList);
	EquipStatic* getEquipInfo(int id);
	ItemStatic* getItemInfo(int id);
	bool isEquip(ItemKind kind);
	bool isEquip(int id);
};
#endif // StaticItem_h__
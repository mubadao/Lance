#ifndef _StaticShop_H_
#define _StaticShop_H_

#include "Global.h"
#include "StaticItem.h"

enum SupplyType
{
	SUPPLY_TYPE_ENERGY = 1,
	SUPPLY_TYPE_POWER = 2,
    SUPPLY_TYPE_LIFE = 3
};

struct xmlBuy
{
	int id;
    int money;
    int count;
};
typedef map<int, xmlBuy> xmlBuyMap;

struct xmlBuyMoney
{
	int id;
    string identifier;
	int money;
	string dollar;
};
typedef vector<xmlBuyMoney> xmlBuyMoneyList;

struct xmlBox
{
    int id;
	MoneyType moneyType;
	int money;
};
typedef vector<xmlBox> xmlBoxList;

class StaticShop : public Singleton<StaticShop>
{
	void _parseBuyMoney();
	void _parseSupplement();
	void _parseBox();
	
public:
	void parse();
    
	xmlBuyMoneyList mBuyMoney;
	xmlBuyMap mBuyCoin;
	xmlBuyMap mBuyEnergyOrPower;
    xmlBuyMap mBuyFusion;
    xmlBuyMap mBuyZhuRong;
    xmlBoxList mBox;

	int getSupplyCostCount(SupplyType type);
	xmlBuy* getBuyCoin(int id);
	xmlBuy* getBuyFusion(int count);
    xmlBuy* getBuyZhuRong(int count);
};

#endif

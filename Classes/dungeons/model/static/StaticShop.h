#ifndef _StaticShop_h__
#define _StaticShop_h__
#include "Global.h"
#include "StaticItem.h"

enum SupplyType
{
	SUPPLY_TYPE_ENERGY = 1,
	SUPPLY_TYPE_POWER = 2,
    SUPPLY_TYPE_LIFE = 3
};
struct CostType
{
    int free;
    int coin;
    int money;
    MoneyType getMoneyType()
	{
		if (coin > 0) return MONEY_TYPE_GOLD;
		else if(money > 0) return MONEY_TYPE_MONEY;
		else if(free > 0) return MONEY_TYPE_FREE;
		return MONEY_TYPE_NONE;
	}
	int getCostCount()
	{
		if (getMoneyType() == MONEY_TYPE_GOLD)
			return coin;
		else if(getMoneyType() == MONEY_TYPE_MONEY)
			return money;
		return 0;
	}
};
struct BuyEnergyOrPowerStatic
{
	int id;
	CostType costType;
};
struct BuyCoinStatic
{
	int id;
	int count;
	int money;
};
struct BuyMoneyStatic
{
	int id;
    const char* identifier;
	int money;
	float dollar;
};

struct BoxStatic
{
    int id;
    const char* desc;
    const char* name;
    CostType costType;
};

typedef std::vector<BuyMoneyStatic*> BuyMoneyStaticList;
typedef std::map<int, BuyEnergyOrPowerStatic*> BuyEnergyOrPowerStaticMap;
typedef std::map<int, BuyCoinStatic*> BuyCoinStaticMap;
typedef std::vector<BoxStatic*> BoxStaticList;

class StaticShop : public Singleton<StaticShop>
{
private:
	
protected:
public:
	StaticShop();
	~StaticShop();

	void parse();
    
	BuyMoneyStaticList mBuyMoneyStaticList;
	BuyEnergyOrPowerStaticMap mBuyEnergyOrPowerStaticMap;
	BuyCoinStaticMap mBuyCoinStaticMap;
    BoxStaticList mBoxStaticList;

	BuyMoneyStaticList& getBuyMoneyStaticList();
	MoneyType getSupplyMoneyType(SupplyType type);
	int getSupplyCostCount(SupplyType type);
	BuyCoinStatic* getBuyCoinStatic(int id);

};
#endif // _StaticShop_h__
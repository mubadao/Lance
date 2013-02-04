#include "SnatchProxy.h"
#include "ItemProxy.h"

SnatchProxy::SnatchProxy()
{
	testData();
}

SnatchProxy::~SnatchProxy()
{
	clearSnatchEnemyList();
}

void SnatchProxy::clearSnatchEnemyList()
{
    for(int i = 0; i < mSnatchEnemyList.size(); i++)
        delete mSnatchEnemyList[i];
    mSnatchEnemyList.clear();
}

EquipInfo* SnatchProxy::getEquipInfo( int id )
{
	for (int i = 0; i < mEquipList.size(); i++)
	{
		if (mEquipList[i]->id == id)
			return mEquipList[i];
	}
	return NULL;
}

void SnatchProxy::testData()
{
	std::vector<int> tempList;
	tempList.push_back(10000);
	tempList.push_back(11000);
	tempList.push_back(12000);
	tempList.push_back(13000);
	tempList.push_back(14000);
	tempList.push_back(15000);
	for (int i = 0; i < 6; i++)
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
		equip->state = i%3==0?0:1;
		mEquipList.push_back(equip);
	}

	for (int i = 0; i < 8; i++)
	{
		SnatchEnemyInfo* snatchEnemyInfo = new SnatchEnemyInfo();
		snatchEnemyInfo->atkMax = 10;
		snatchEnemyInfo->atkMin = 10;
		snatchEnemyInfo->avatar = 1;
		snatchEnemyInfo->failedGold = 10;
		snatchEnemyInfo->gold = 30;
		snatchEnemyInfo->itemID = 11002;
		snatchEnemyInfo->level = 10;
		snatchEnemyInfo->name = "panpan";
		snatchEnemyInfo->pid = 10333;
		snatchEnemyInfo->succeedExp = 20;
		snatchEnemyInfo->succeedGold = 40;
		snatchEnemyInfo->time = 2;
		mSnatchEnemyList.push_back(snatchEnemyInfo);
	}
	mSnatchResult.result = 1;
}


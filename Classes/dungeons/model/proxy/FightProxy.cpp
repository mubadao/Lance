#include "FightProxy.h"

FightProxy::FightProxy()
	:dungeons(-1),floor(-1),task(-1),bossID(1)
{
//	testData();
}

FightProxy::~FightProxy()
{
}

void FightProxy::testData()
{
	awardInfo.coin = 122;
	awardInfo.exp = 200;
	EquipInfo* equipInfo = new EquipInfo();
	equipInfo->atkMin = 10;
	equipInfo->atkMax = 20;
	equipInfo->defMin = 10;
    equipInfo->defMax = 30;
	equipInfo->exp = 100;
	equipInfo->id = 10003;
	equipInfo->index  = 6;
	equipInfo->level = 2;
	equipInfo->life = 20;
	equipInfo->state = 0;
	awardInfo.equipList.push_back(equipInfo);
	bossID = 1;
}

void FightProxy::reset()
{
	awardInfo.clear();
}

EquipInfo* FightProxy::getAwardEquip()
{
	if(awardInfo.equipList.size() > 0)
		return awardInfo.equipList[0];
	return NULL;
}


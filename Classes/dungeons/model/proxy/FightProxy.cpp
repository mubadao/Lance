#include "FightProxy.h"
#include "EquipProxy.h"

FightProxy::FightProxy()
	: mDungeons(-1)
	, mFloor(-1)
	, mTask(-1)
	, mBossID(1)
{
//	testData();
}

FightProxy::~FightProxy()
{
}

void FightProxy::testData()
{
	mEventInfo.coin = 122;
	mEventInfo.exp = 200;
	mBossID = 1;

	EquipInfo info;
	info.atkMin = 10;
	info.atkMax = 20;
	info.defMin = 10;
    info.defMax = 30;
	info.exp = 100;
	info.baseId = 10003;
	info.index  = 6;
	info.level = 2;
	info.life = 20;
	info.state = 0;
	mEventInfo.equipList.push_back(info);
}

void FightProxy::reset()
{
	mEventInfo.clear();
}

EquipInfo* FightProxy::getAwardEquip()
{
	if(mEventInfo.equipList.size() > 0)
		return &mEventInfo.equipList[0];
	return NULL;
}


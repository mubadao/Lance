#include "UserProxy.h"
#include "StaticRole.h"
UserProxy::UserProxy()
    :mHtmlUrl("")
{
//	userVO = new UserVO();
//	testData();
}

UserProxy::~UserProxy()
{
}

void UserProxy::testData()
{
	userVO.gid = -1;
	userVO.platform = 110;
	userVO.defMin = 20;
	userVO.defMax = 50;
	userVO.life = 1500;
	userVO.lifeCur = 1000;
	userVO.dropRate = 26;
	userVO.name = "ddddddd";
	userVO.exp = 60;
	userVO.coin = 300;
	userVO.powerCur = 100;
	userVO.powerMax = 200;
	userVO.energyCur = 1;
	userVO.energyMax = 3;
	userVO.atkMin = 100;
	userVO.atkMax = 150;
	userVO.level = 1;
	userVO.agility = 100;
	userVO.naili = 20;
	userVO.strength = 40;
	userVO.proficiency = 5;
	userVO.energyTime = 10000;
}

long UserProxy::getAllEnergyTime()
{
    LevelInfo* levelInfo = StaticRole::shared()->getLevelInfo(userVO.level);
	int energy = userVO.energyMax-userVO.energyCur;
	energy = energy > 0 ? energy - 1 : 0;
	return long(userVO.energyTime+energy*levelInfo->energytime);
}

long UserProxy::getAllPowerTime()
{
    LevelInfo* levelInfo = StaticRole::shared()->getLevelInfo(userVO.level);
	int power = userVO.powerMax-userVO.powerCur;
	power = power > 0 ? power - 1 : 0;
	return long(userVO.powerTime+power*levelInfo->powertime);
}

int UserProxy::getEnergyMax()
{
    return 0;
}

void UserProxy::saveUserInfo()
{
	userVO.wirte(mLastUserVO);
}

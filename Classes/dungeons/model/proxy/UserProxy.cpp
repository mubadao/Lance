#include "UserProxy.h"
#include "StaticRole.h"

UserProxy::UserProxy()
{
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
	userVO.proficiency = 5;
	userVO.energyTime = 10000;
}

long UserProxy::getAllEnergyTime()
{
	int energy = userVO.energyMax - userVO.energyCur;
	energy = energy > 0 ? energy - 1 : 0;
	return long(userVO.energyTime + energy * StaticRole::shared()->getLevelInfo(userVO.level)->energyTime);
}

long UserProxy::getAllPowerTime()
{
	int power = userVO.powerMax - userVO.powerCur;
	power = power > 0 ? power - 1 : 0;
	return long(userVO.powerTime + power * StaticRole::shared()->getLevelInfo(userVO.level)->powerTime);
}

void UserProxy::saveUserInfo()
{
	mLastUserVO = userVO;
}

#include "ChallengeProxy.h"

ChallengeProxy::ChallengeProxy()
{
	testData();
}

ChallengeProxy::~ChallengeProxy()
{
}

void ChallengeProxy::clearChallengeEnemyList()
{
    mChallengeEnemyList.clear();
}

void ChallengeProxy::testData()
{
	for(int i = 0; i < 8; i++)
	{
		ChallengeEnemyInfo info;
		info.name = "hello";
		info.gid = 1;
		info.avatar = 2;
		info.level = 3;
		info.atkMin = i + 10;
		info.atkMax = i + 15;
		info.succeedExp = i + 20;
		info.succeedGold = i + 10;
		info.failedGold = i + 10;
		info.time = i + 10;
		info.gold = i + 10;
		mChallengeEnemyList.push_back(info);
	}
}

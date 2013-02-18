#ifndef _FightProxy_H_
#define _FightProxy_H_

#include "Global.h"
#include "TypeDefine.h"
#include "EquipProxy.h"

// 探索事件
struct ExploreEvent
{
	ExploreEventType type;
	int exp;
	int coin;
    int energy;
    int life;
	int eventCoin;
	vector<EquipInfo> equipList;
	
	int getCoin() {return coin + eventCoin; }

	void clear()
	{
		exp = coin = energy = life = eventCoin = 0;
		equipList.clear();
		type = EVENT_TYPE_NONE;
	}
	
	ExploreEvent() : exp(0),coin(0),eventCoin(0),energy(0),life(0), type(EVENT_TYPE_NONE) {}
};

// Boss属性
struct BossInfo
{
    int atkMax;
    int atkMin;
    int defMax;
    int defMin;
    int level;
    int life;
};

// 对战回合定义。
struct RoundInfo
{
    int act;        // 攻击方 (0:自己， 1:对方)
    int type;       // 攻击类型
    int value;      // 攻击失血
};

// 对战信息定义。
struct BattleInfo
{
    int win;
    vector<RoundInfo> roundInfo;
};

class FightProxy : public Singleton<FightProxy>
{
	void testData();

public:
	FightProxy();
	~FightProxy();

	int mDungeons;
	int mFloor;
	int mTask;
	int mBossID;

	ExploreEvent mEventInfo;
	BattleInfo mBattleInfo;
    BossInfo mFightBoss;
    
	EquipInfo* getAwardEquip();
    void reset();
};

#endif
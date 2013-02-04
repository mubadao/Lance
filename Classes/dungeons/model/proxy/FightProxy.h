#ifndef _FightProxy_h_
#define _FightProxy_h_

#include "Global.h"
#include "NCDefines.h"
#include "ItemProxy.h"

enum AwardEventType
{
	EVENT_TYPE_NONE=0,
	EVENT_TYPE_LOST_LIFE,
	EVENT_TYPE_GET_COIN,
	EVENT_TYPE_GET_ENERGY,
	EVENT_TYPE_GET_EQUIP
};

//½±Àø
struct Award
{
	AwardEventType eventType;
	int exp;
	int coin;
    int energy;
    int life;
	int eventCoin;
	std::vector<EquipInfo*> equipList;
	void clear()
	{
        equipList.clear();
        exp = 0;
        coin = 0;
        energy = 0;
        life = 0;
        eventCoin = 0;
		eventType = EVENT_TYPE_NONE;
	}
	Award():exp(30),coin(100),eventCoin(20),energy(2),life(50),eventType(EVENT_TYPE_LOST_LIFE){}
	~Award(){clear();}
	int getCoin(){return coin + eventCoin;}
};

struct FightBoss
{
    int atkMax;
    int atkMin;
    int defMax;
    int defMin;
    int level;
    int life;
};

class FightProxy : public Singleton<FightProxy>
{
	void testData();
public:
	FightProxy();
	~FightProxy();

	int dungeons;
	int floor;
	int task;
	int bossID;
	Award awardInfo;
	BattleInfo battleInfo;
	EquipInfo* getAwardEquip();
    
    FightBoss mFightBoss;
    
    void reset();
};

#endif
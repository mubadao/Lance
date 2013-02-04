#ifndef _SnatchProxy_h_
#define _SnatchProxy_h_

#include "Global.h"
#include "ItemProxy.h"

struct SnatchEnemyInfo
{
	string name;//昵称
	int pid;//pid
	int avatar;//形象
	int level;//等级
	int atkMin;//最小攻击力
	int atkMax;//最大攻击力
	int succeedExp;//挑战成功后获得的经验
	int succeedGold;//挑战成功后获得的金币
	int failedGold;//挑战失败后获得的金币
	int time;//抢夺自己的时间，没有为0
	int gold;//失去的金币数量
	int itemID;//失去的道具id，没有为-1
	SnatchEnemyInfo():time(0),gold(0){}
};

struct SnatchResult
{
	int result;
};

typedef std::vector<SnatchEnemyInfo*> SnatchEnemyList;

class SnatchProxy : public Singleton<SnatchProxy>
{
public:
	SnatchProxy();
	~SnatchProxy();

	SnatchEnemyList mSnatchEnemyList;

	SnatchEnemyInfo* mCurSnatchEnemyInfo;
	SnatchResult mSnatchResult;
	EquipList mEquipList;
    void clearSnatchEnemyList();
	EquipInfo* getEquipInfo(int id);
protected:
	
private:
	void testData();
};

#endif // _SnatchProxy_h_

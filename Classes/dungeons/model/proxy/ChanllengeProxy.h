#ifndef _ChanllengeProxy_h_
#define _ChanllengeProxy_h_

#include "Global.h"

struct ChallengeEnemyInfo
{
	string name;//昵称
	int gid;//pid
	int avatar;//形象
	int level;//等级
	int atkMin;//最小攻击力
	int atkMax;//最大攻击力
    int defMin;//最小攻击力
	int defMax;//最大攻击力
    int life;
	int succeedExp;//挑战成功后获得的经验
	int succeedGold;//挑战成功后获得的金币
	int failedGold;//挑战失败后获得的金币
	int time;//抢夺自己的时间，没有为0
	int gold;//失去的金币数量
	ChallengeEnemyInfo():time(0),gold(0){}
};

typedef std::vector<ChallengeEnemyInfo*> ChallengeEnemyList;

struct ChallengeResult
{
	int result; //结果
    int succeedExp;//挑战成功后获得的经验
	int succeedGold;//挑战成功后获得的金币
	int failedGold;//挑战失败后获得的金币
};


class ChanllengeProxy : public Singleton<ChanllengeProxy>
{
public:
	ChanllengeProxy();
	~ChanllengeProxy();

	ChallengeEnemyList mChallengeEnemyList;

	ChallengeEnemyInfo* mCurChallengeEnemyInfo;
	ChallengeResult mChallengeResult;
    void clearChallengeEnemyList();
	void testData();
protected:
	
private:
};

#endif // _ChanllengeProxy_h_

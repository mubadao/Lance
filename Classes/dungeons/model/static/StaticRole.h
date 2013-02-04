#ifndef StaticRole_h__
#define StaticRole_h__

#include "StaticData.h"
#include "Global.h"
#include "DataVO.h"

/*角色信息：boss等*/
struct LevelInfo
{
	int id;
	int exp;
	float energytime;
	float powertime;	
};
struct RoleInfo
{
	int id;
	const char* name;
	const char* icon;
};
struct BossInfo : public RoleInfo
{
	int level;
	int life;
	int atk_min;
	int atk_max;
	int def_min;
	int def_max;
	int power;
	int speed;
	int stamina;
};

typedef std::map<int, LevelInfo*> LevelInfoMap;
class StaticRole : public StaticData, public Singleton<StaticRole>
{
	std::map<int, BossInfo*> bossInfoMap;
	LevelInfoMap mLevelInfoMap;
public:
	StaticRole();
	~StaticRole();
	void parse();
	BossInfo* getBossInfo(int id);
	RoleInfo* getRoleInfo(int id);
	LevelInfo* getLevelInfo(int level);
};
#endif // StaticRole_h__
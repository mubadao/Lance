#ifndef _StaticRole_H_
#define _StaticRole_H_

#include "Global.h"
#include "UserVO.h"

struct xmlLevelInfo
{
	int level;
	int exp;
	float energyTime;
	float powerTime;
};
typedef map<int, xmlLevelInfo> xmlLevelInfoMap;

struct xmlRoleInfo
{
	int id;
	string icon;
};

struct xmlBossInfo : public xmlRoleInfo
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
typedef map<int, xmlBossInfo> xmlBossInfoMap;

class StaticRole : public Singleton<StaticRole>
{
	xmlBossInfoMap mBossMap;
	xmlLevelInfoMap mLevelMap;
	
public:
	StaticRole();
	~StaticRole();
	
	void parse();
	
	xmlBossInfo* getBossInfo(int id);
	xmlLevelInfo* getLevelInfo(int level);
};

#endif
#ifndef DataVO_h__
#define DataVO_h__
#include <vector>
using namespace std;

//玩家信息
struct UserVO
{
	int gid;
	string pid;
	int platform;
    int createTime;
    int energyTime;
    int powerTime;

	string name;
	int sex;		//0男1女
	int avatar;
	int level;
	int exp;
	int	coin;	//游戏币
	int money;	//钻石
	int energyCur;
	int energyMax;
	int powerCur;
	int powerMax;
	int life;
    int lifeCur;
	int proficiency;
    int fusion;

	int atkMin;
	int atkMax;
	int defMin;
	int defMax;
	int atkMaxReappear;
	int defMaxReappear;
	int expGainRatio;
	int coinGainRatio;
	int equipageDropRatio;
	int energyRecoverRatio;
	int powerRecoverRatio;
	
	int dropRate;
	
	int strength;
	int agility;
	int naili;
	
	
	int rEnergy;

	void wirte(UserVO& userVO)
	{
		userVO.atkMin = atkMin;
		userVO.atkMax = atkMax;
		userVO.defMin = defMin;
		userVO.defMax = defMax;
		userVO.life = life;
		userVO.energyMax = energyMax;
		userVO.level = level;
	}
	
	UserVO():name("Player"),sex(0),avatar(0),level(1),exp(0),coin(0),money(0),energyCur(0),
		energyMax(0),powerCur(0),powerMax(0),life(0),proficiency(0),fusion(0),atkMin(0),
		atkMax(0),defMin(0),defMax(0),atkMaxReappear(0),defMaxReappear(0),expGainRatio(0),
		coinGainRatio(0),equipageDropRatio(0),energyRecoverRatio(0),powerRecoverRatio(0),
		rEnergy(0)
	{}
};

//角色类型
enum RoleType
{
	ROLE_TYPE_BOSS=0,	//白装
} ;

//角色
struct RoleVO
{
	int id;
	RoleType type;
};
#endif // DataVO_h__
#ifndef _UserVO_H_
#define _UserVO_H_

#include "Global.h"

struct UserVO
{
	int gid;					// 服务器分配的ID
	string pid;					// 设备号或其他平台唯一编号
	int platform;				// 平台编码
    int createTime;				// 创建时间
    int energyTime;				// 上一次能量更新时间
    int powerTime;				// 上一次体力更新时间
	
	string name;				// 姓名
	int sex;					// 性别
	int avatar;					// 形象编号
	int level;					// 等级
	int exp;					// 经验
	int	coin;					// 铜币
	int money;					// 付费币
	int energyCur;				// 当前能量
	int energyMax;				// 最大能量
	int powerCur;				// 当前体力
	int powerMax;				// 最大体力
	int life;					// 当前生命
    int lifeCur;				// 最大生命
	int proficiency;			// 潜能点
    int fusion;					// 总熔炼值
	
	int atkMin;					// 最小攻击
	int atkMax;					// 最大攻击
	int defMin;					// 最小防御
	int defMax;					// 最大防御
	int atkMaxReappear;			// 最大攻击打出几率
	int defMaxReappear;			// 最大防御打出几率
	int expGainRatio;			// 经验获得加成
	int coinGainRatio;			// 铜币获得加成
	int equipageDropRatio;		// 魔法物品掉落率加成
	int energyRecoverRatio;		// 能量恢复速度加成
	int powerRecoverRatio;		// 体力恢复速度加成
	
	UserVO():name("Player"),sex(0),avatar(0),level(1),exp(0),coin(0),money(0),energyCur(0),
	energyMax(0),powerCur(0),powerMax(0),life(0),proficiency(0),fusion(0),atkMin(0),
	atkMax(0),defMin(0),defMax(0),atkMaxReappear(0),defMaxReappear(0),expGainRatio(0),
	coinGainRatio(0),equipageDropRatio(0),energyRecoverRatio(0),powerRecoverRatio(0)
	{}
};

#endif


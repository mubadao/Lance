#ifndef _TypeDefine_H_
#define _TypeDefine_H_

#include "Global.h"

// 品质
enum EquipQuality
{
	EQUIP_QUALITY_WHITE = 0,	// 白
	EQUIP_QUALITY_BLUE,			// 兰
	EQUIP_QUALITY_YELLOW,		// 黄
	EQUIP_QUALITY_GOLD,			// 金
	EQUIP_QUALITY_PURPLE,		// 紫
	EQUIP_QUALITY_ORANGE		// 橙
};

// 词条类型
enum AffixType
{
	AFFIX_TYPE_MIN_ATTACK_SIN		= 1,			// +最小攻击(单体)
	AFFIX_TYPE_MAX_ATTACK_SIN		= 2,			// +最大攻击(单体)
	AFFIX_TYPE_MIN_DEFENSE_SIN		= 3,			// +最小防御(单体)
	AFFIX_TYPE_MAX_DEFENSE_SIN		= 4,			// +最大防御(单体)
	AFFIX_TYPE_MIN_ATTACK_SIN_PER	= 5,			// +最小攻击%(单体)：增加全身所有最小攻击的百分比
	AFFIX_TYPE_MAX_ATTACK_SIN_PER	= 6,			// +最大攻击%(单体)：增加全身所有最大攻击的百分比
	AFFIX_TYPE_MIN_DEFENSE_SIN_PER	= 7,			// +最小防御%(单体)：增加全身所有最小防御的百分比
	AFFIX_TYPE_MAX_DEFENSE_SIN_PER	= 8,			// +最大防御%(单体)：增加本件装备基础部分的百分比
	AFFIX_TYPE_MIN_ATTACK_ALL_PER	= 9,			// +最小攻击%(全体)：增加全身所有最小攻击的百分比
	AFFIX_TYPE_MAX_ATTACK_ALL_PER	= 10,			// +最大攻击%(全体)：增加全身所有最大攻击的百分比
	AFFIX_TYPE_MIN_DEFENSE_ALL_PER	= 11,			// +最小防御%(全体)：增加全身所有最小防御的百分比
	AFFIX_TYPE_MAX_DEFENSE_ALL_PER	= 12,			// +最大防御%(全体)：增加全身所有最大防御的百分比
	AFFIX_TYPE_MAX_ATTACK_RATE_PER	= 13,			// +最大攻击打出概率%(单体)：出现攻击上限的概率
	AFFIX_TYPE_MAX_DEFENSE_RATE_PER	= 14,			// +最大防御打出概率%(单体)：出现防御上限的概率
	AFFIX_TYPE_ENERGY_UP			= 15,			// +能量上限：
	AFFIX_TYPE_ENERGY_SPEED_PER		= 16,			// +能量回复速度%：
	AFFIX_TYPE_POWER_UP				= 17,			// +体力上限：
	AFFIX_TYPE_POWER_SPEED_PER		= 18,			// +体力回复速度%：
	AFFIX_TYPE_LIFE					= 19,			// +血量
	AFFIX_TYPE_LIFE_SIN_PER			= 20,			// +血量（全体）%：单件装备血量的百分比
	AFFIX_TYPE_MF_PER				= 21,			//
	AFFIX_TYPE_GET_COIN_PER			= 22,			// +铜币获得量%：只增加地下城，神秘洞穴战斗时金币的获得
	AFFIX_TYPE_GET_EXP_PER			= 23			// +经验获得量%：只增加地下城，神秘洞穴战斗时经验的获得
};

// 装备部位
enum EquipType
{
	EQUIP_TYPE_HELM					= 0,			// 头盔
	EQUIP_TYPE_NECKLACE				= 1,			// 项链
	EQUIP_TYPE_WEAPON				= 2,			// 武器
	EQUIP_TYPE_CLOTH				= 3,			// 衣服
	EQUIP_TYPE_RING					= 4,			// 戒指
	EQUIP_TYPE_SHOES				= 5,			// 鞋
};

// 货币类型
enum MoneyType
{
    MONEY_TYPE_NONE = 0,
	MONEY_TYPE_COIN,
	MONEY_TYPE_MONEY,
};

// 探索事件类型
enum ExploreEventType
{
	EVENT_TYPE_NONE = 0,
	EVENT_TYPE_LOST_LIFE,
	EVENT_TYPE_GET_COIN,
	EVENT_TYPE_GET_ENERGY,
	EVENT_TYPE_GET_EQUIP
};

#endif
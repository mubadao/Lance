#ifndef _EquipProxy_H_
#define _EquipProxy_H_

#include "Global.h"
#include "TypeDefine.h"
#include "UserVO.h"
#include "StaticItem.h"

extern const ccColor3B EquipQualityColor_White;
extern const ccColor3B EquipQualityColor_Blue;
extern const ccColor3B EquipQualityColor_Yellow;
extern const ccColor3B EquipQualityColor_Gold;

// 词条
struct Affix
{
	AffixType type;		// 类型
	int value;			// 值
	
	const char* getTitle();
	bool isPer();
};
typedef vector<Affix> AffixList;

struct EquipInfo
{
	EquipInfo():index(0),baseId(0),quality(0),state(0),level(0),exp(0),atkMin(0),atkMax(0),defMin(0),defMax(0),life(0),intensifyNum(0),intensifyValue(0) {}
	
	int state;				// 当前状态 0：背包，1：装备中
	int index;				// 背包中的编号
	int baseId;				// xml中的编号
	int level;				// 基础等级
	int exp;				// 经验
	int atkMin;				// 最小攻击
	int atkMax;				// 最大攻击
	int defMin;				// 最小防御
	int defMax;				// 最大防御
	int life;				// 生命
	int quality;			// 品质
	int intensifyNum;		// 强化次数
	int intensifyValue;		// 强化值
	AffixList affixs;		// 词条
	
	bool isPutOn() { return state == 1; }
	bool isAttack();

	//主属性加词缀后的值. 0：最小，1：最大
	int getAttachProperty(int style);
	
	//主属性基础值. 0：最小，1：最大
	int getBaseProperty(int style);
	
	const char* getAttachPropertyStr();
	const char* getBasePropertyStr();
	const char* getPropertyTitle();
	
	const ccColor3B& getNameColor();
	static const ccColor3B& getNameColor(int quality);
	
	EquipType getType();
	const char* getTypeTitle();
	
	int getSellPrize();
};
typedef vector<EquipInfo*> EquipList;

struct IntensifyResult
{
	int perfect;
	int addProperty;
	IntensifyResult():perfect(0),addProperty(0){}
};

class EquipProxy : public Singleton<EquipProxy>
{
	void testData();

public:
	EquipProxy();
	~EquipProxy();

	int mBagMax;							// 背包上限
	EquipList mList;						// 装备列表
	int putonIndex;							// 当前换装的装备baseId
	vector<int> mSellList;

	EquipInfo lastQiangHuaEquip;			// 上次强化的装备信息
	EquipInfo curQiangHuaEquip;				// 本次强化的装备信息
	vector<int> mMeltList;					// 准备强化的装备列表
	IntensifyResult mIntensifyResult;		// 强化结果

	// 取得装备数量
	int getCount();

	// 取得已装备列表数量
	int getLoadedCount();

	// 取得装备信息
	EquipInfo* getEquip(int index);
	
	// 获得当前已装的装备
	EquipInfo* getLoadedEquip(EquipType type);

	// 换上装备
	void load(int index);

	// 卸载装备
	void unload(int index);
	
	// 卸载某类型的装备
	void unloadByType(EquipType type);

	// 卖出装备
	void sell(const vector<int>& sellList);

	// 删除装备
	void remove(int index);

	// 追加
	EquipInfo* addEquip(const EquipInfo& equipInfo);

	// 背包是否装满
	bool isBagFull();

	void setLastQiangHuaEquip(const EquipInfo& info);
};

#endif
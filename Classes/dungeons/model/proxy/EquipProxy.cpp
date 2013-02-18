#include "EquipProxy.h"
#include "CCFileUtils.h"
#include "StaticItem.h"
#include "LocalString.h"

extern const ccColor3B EquipQualityColor_White = ccWHITE;
extern const ccColor3B EquipQualityColor_Blue = ccc3(46, 200, 202);
extern const ccColor3B EquipQualityColor_Yellow = ccc3(227, 224, 134);
extern const ccColor3B EquipQualityColor_Gold = ccc3(254, 188, 67);

EquipProxy::EquipProxy()
{
//	testData();
}

EquipProxy::~EquipProxy()
{
	for (int i = 0; i < mList.size(); i++)
		delete mList[i];
	mList.clear();
}

void EquipProxy::testData()
{
	vector<int> tempList;
	tempList.push_back(10000);
	tempList.push_back(11000);
	tempList.push_back(12000);
	tempList.push_back(13000);
	tempList.push_back(14000);
	tempList.push_back(15000);
	tempList.push_back(15000);
	tempList.push_back(15000);
	tempList.push_back(15000);
	mBagMax = 10;
//	mBagid = 5;
	for (int i = 0; i < 9; i++)
	{
		EquipInfo equip;
		equip.atkMax = 20 + i;
		equip.atkMin = 10 + i;
		equip.defMax = 15 + i;
		equip.defMin = 16 + i;
		equip.exp = 20 + i;
		equip.baseId = tempList[i];
		equip.index = i;
		equip.level = 2 + i;
		equip.life = 5 + i;
		equip.state = i<6?1:0;
		addEquip(equip);
	}

	lastQiangHuaEquip = *mList[0];
	curQiangHuaEquip = *mList[0];
}

void EquipProxy::load(int index)
{
	EquipInfo* info = getEquip(index);
	unloadByType(info->getType());
	info->state = 1;
}

void EquipProxy::unload(int index)
{
	EquipInfo* info = getEquip(index);
	unloadByType(info->getType());
	info->state = 0;
}

void EquipProxy::unloadByType(EquipType type)
{
	for(int i = 0; i < mList.size(); i++)
	{
		if(type == mList[i]->getType() && mList[i]->state == 1)
		{
			mList[i]->state = 0;
			break;
		}
	}
}

void EquipProxy::sell(const vector<int>& sellsList)
{
	EquipList::iterator itr;
	for (int i = 0; i < sellsList.size(); i++)
	{
		for (itr = mList.begin(); itr != mList.end(); ++itr)
		{
			if((*itr)->index == sellsList[i])
			{
				mList.erase(itr);
				break;
			}
		}
	}
}

void EquipProxy::remove(int index)
{
	EquipList::iterator itr;
	for (itr = mList.begin(); itr != mList.end(); ++itr)
	{
		if((*itr)->index == index)
		{
			delete *itr;
			mList.erase(itr);
			break;
		}
	}
}

EquipInfo* EquipProxy::getEquip(int index)
{
	for(int i = 0; i < mList.size(); i++)
	{
		if(mList[i]->index == index)
			return mList[i];
	}
	return NULL;
}

EquipInfo* EquipProxy::addEquip(const EquipInfo& info)
{
	EquipInfo* equip = getEquip(info.index);
	if (equip == NULL)
	{
		equip = new EquipInfo;
		mList.push_back(equip);
	}	
	*equip = info;
	return equip;
}

void EquipProxy::setLastQiangHuaEquip(const EquipInfo& info)
{
	lastQiangHuaEquip = info;
}

int EquipProxy::getLoadedCount()
{
	int count = 0;
	for (int i = 0; i < mList.size(); i++)
	{
		if(mList[i]->state == 1)
			count++;
	}
	return count;
}

int EquipProxy::getCount()
{
	return mList.size();
}

bool EquipProxy::isBagFull()
{
	return mList.size() >= mBagMax;
}

EquipInfo* EquipProxy::getLoadedEquip(EquipType type)
{
	for(int i = 0; i < mList.size(); i++)
	{
		if(mList[i]->isPutOn() && mList[i]->getType() == type)
			return mList[i];
	}
	return NULL;
}

#pragma mark - Affix

const char* Affix::getTitle()
{
	return gls(fcs("affix_%d", type));
}

bool Affix::isPer()
{
	switch(type)
	{
		case AFFIX_TYPE_MIN_ATTACK_SIN_PER:		return true;		//+最小攻击%(单体)：增加全身所有最小攻击的百分比
		case AFFIX_TYPE_MAX_ATTACK_SIN_PER:		return true;		//+最大攻击%(单体)：增加全身所有最大攻击的百分比
		case AFFIX_TYPE_MIN_DEFENSE_SIN_PER:	return true;		//+最小防御%(单体)：增加全身所有最小防御的百分比
		case AFFIX_TYPE_MAX_DEFENSE_SIN_PER:	return true;		//+最大防御%(单体)：增加本件装备基础部分的百分比
		case AFFIX_TYPE_MIN_ATTACK_ALL_PER:		return true;		//+最小攻击%(全体)：增加全身所有最小攻击的百分比
		case AFFIX_TYPE_MAX_ATTACK_ALL_PER:		return true;		//+最大攻击%(全体)：增加全身所有最大攻击的百分比
		case AFFIX_TYPE_MIN_DEFENSE_ALL_PER:	return true;		//+最小防御%(全体)：增加全身所有最小防御的百分比
		case AFFIX_TYPE_MAX_DEFENSE_ALL_PER:	return true;		//+最大防御%(全体)：增加全身所有最大防御的百分比
		case AFFIX_TYPE_MAX_ATTACK_RATE_PER:	return true;		//+最大攻击打出概率%(单体)：出现攻击上限的概率
		case AFFIX_TYPE_MAX_DEFENSE_RATE_PER:	return true;		//+最大防御打出概率%(单体)：出现防御上限的概率
		case AFFIX_TYPE_ENERGY_SPEED_PER:		return true;		//+能量回复速度%：
		case AFFIX_TYPE_POWER_SPEED_PER:		return true;		//+体力回复速度%：
		case AFFIX_TYPE_LIFE_SIN_PER:			return true;		//+血量（全体）%：单件装备血量的百分比
		case AFFIX_TYPE_MF_PER:					return true;
		case AFFIX_TYPE_GET_COIN_PER:			return true;		//+铜币获得量%：只增加地下城，神秘洞穴战斗时金币的获得
		case AFFIX_TYPE_GET_EXP_PER:			return true;		//+经验获得量%：只增加地下城，神秘洞穴战斗时经验的获得
		default:								return false;
	}
	return false;
}

#pragma mark - EquipInfo

int EquipInfo::getAttachProperty(int style)
{
	int atkMaxResult = atkMax;
	int defMaxResult = defMax;
	
	int atkMinResult = atkMin;
	int defMinResult = defMin;
	
	int atkMinAllPercent = 0;
	int defMinAllPercent = 0;
	
	int atkMaxAllPercent = 0;
	int defMaxAllPercent = 0;
	
	for (int i = 0; i < affixs.size(); i++)
	{
		Affix& affix = affixs[i];
		int type = affix.type;
		int value = affix.value;
		
		switch(type)
		{
			case AFFIX_TYPE_MIN_ATTACK_SIN:			atkMinResult += value;		break;	//+最小攻击(单体)
			case AFFIX_TYPE_MAX_ATTACK_SIN:			atkMaxResult += value;		break;	//+最大攻击(单体)
			case AFFIX_TYPE_MIN_DEFENSE_SIN:		defMinResult += value;		break;	//+最小防御(单体)
			case AFFIX_TYPE_MAX_DEFENSE_SIN:		defMaxResult += value;		break;	//+最大防御(单体)
			case AFFIX_TYPE_MIN_ATTACK_SIN_PER:		atkMinAllPercent += value;	break;	//+最小攻击%(单体)：增加全身所有最小攻击的百分比
			case AFFIX_TYPE_MAX_ATTACK_SIN_PER:		atkMaxAllPercent += value;	break;	//+最大攻击%(单体)：增加全身所有最大攻击的百分比
			case AFFIX_TYPE_MIN_DEFENSE_SIN_PER:	defMinAllPercent += value;	break;	//+最小防御%(单体)：增加全身所有最小防御的百分比
			case AFFIX_TYPE_MAX_DEFENSE_SIN_PER:	defMaxAllPercent += value;	break;	//+最大防御%(单体)：增加本件装备基础部分的百分比
			case AFFIX_TYPE_MIN_ATTACK_ALL_PER:		atkMinAllPercent += value;	break;	//+最小攻击%(全体)：增加全身所有最小攻击的百分比
			case AFFIX_TYPE_MAX_ATTACK_ALL_PER:		atkMaxAllPercent += value;	break;	//+最大攻击%(全体)：增加全身所有最大攻击的百分比
			case AFFIX_TYPE_MIN_DEFENSE_ALL_PER:	defMinAllPercent += value;	break;	//+最小防御%(全体) ：增加全身所有最小防御的百分比
			case AFFIX_TYPE_MAX_DEFENSE_ALL_PER:	defMaxAllPercent += value;	break;	//+最大防御%(全体) ：增加全身所有最大防御的百分比
			default:															break;
		}
	}
	
	atkMinResult += atkMinResult * atkMinAllPercent / 100;
	atkMaxResult += atkMaxResult * atkMaxAllPercent / 100;
	defMinResult += defMinResult * defMinAllPercent / 100;
	defMaxResult += defMaxResult * defMaxAllPercent / 100;

	return isAttack() ? (style == 0 ? atkMinResult : atkMaxResult) : (style == 0 ? defMinResult : defMaxResult);
}

//主属性基础值
int EquipInfo::getBaseProperty(int style)
{
	return isAttack() ? (style == 0 ? atkMin : atkMax) : (style == 0 ? defMin : defMax);
}

const char* EquipInfo::getAttachPropertyStr()
{
	return fcs("%d--%d", getAttachProperty(0), getAttachProperty(1));
}

const char* EquipInfo::getBasePropertyStr()
{
	return fcs("%d--%d", getBaseProperty(0), getBaseProperty(1));
}

const char* EquipInfo::getPropertyTitle()
{
	return isAttack() ? gls("Attack") : gls("Defense");
}

const ccColor3B& EquipInfo::getNameColor()
{
	switch(StaticItem::shared()->getEquipInfo(baseId)->quality)
	{
		case EQUIP_QUALITY_WHITE:
		case EQUIP_QUALITY_BLUE:
			return affixs.size() > 0 ? EquipQualityColor_Blue : EquipQualityColor_White;
		case EQUIP_QUALITY_YELLOW:
			return EquipQualityColor_Yellow;
		case EQUIP_QUALITY_GOLD:
			return EquipQualityColor_Gold;
		default:
			return EquipQualityColor_White;
	}
}

const ccColor3B& EquipInfo::getNameColor(int quality)
{
	switch(quality)
	{
		case EQUIP_QUALITY_WHITE:	return EquipQualityColor_White;			break;
		case EQUIP_QUALITY_BLUE:	return EquipQualityColor_Blue;			break;
		case EQUIP_QUALITY_YELLOW:	return EquipQualityColor_Yellow;		break;
		case EQUIP_QUALITY_GOLD:	return EquipQualityColor_Gold;			break;
		default:					return EquipQualityColor_White;			break;
	}
}

EquipType EquipInfo::getType()
{
	return StaticItem::shared()->getEquipInfo(baseId)->type;
}

int EquipInfo::getSellPrize()
{
	return int(30 * level * StaticItem::shared()->getEquipInfo(baseId)->quality * (1 + affixs.size() * 0.15));
}

bool EquipInfo::isAttack()
{
	xmlEquipInfo* info = StaticItem::shared()->getEquipInfo(baseId);
	if (info->type == EQUIP_TYPE_WEAPON ||
		info->type == EQUIP_TYPE_RING ||
		info->type == EQUIP_TYPE_NECKLACE )
		return true;
	else
		return false;
}

const char* EquipInfo::getTypeTitle()
{
	switch(StaticItem::shared()->getEquipInfo(baseId)->type)
	{
		case EQUIP_TYPE_HELM:			return gls("helm");			break;
		case EQUIP_TYPE_NECKLACE:		return gls("necklace");		break;
		case EQUIP_TYPE_WEAPON:			return gls("weapon");		break;
		case EQUIP_TYPE_CLOTH:			return gls("cloth");		break;
		case EQUIP_TYPE_RING:			return gls("ring");			break;
		case EQUIP_TYPE_SHOES:			return gls("shoes");		break;
		default:						return "";
	}
}

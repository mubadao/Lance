#ifndef ItemProxy_h__
#define ItemProxy_h__
#include "Global.h"
#include "DataVO.h"
#include "NCDefines.h"
#include "StaticItem.h"

#define ITEM_ID_ZHURONGJI 26001
#define ITEM_ID_TILI 28001
//鈼娾垶卤鈭忊墹酶艗陋
enum EquipPart
{
	EQUIP_PART_HELM=0,		//脮鈭懨嘎?
	EQUIP_PART_NECKLACE,	//艙脫隆楼
	EQUIP_PART_WEAPON,		//艗鈥扳垎藴
	EQUIP_PART_CLOTH,		//鈥溌垜藳
	EQUIP_PART_RING,		//惟鈥懊封垙
	EQUIP_PART_SHOES		//鈥撀ㄢ棅鈥?
} ;

//鈼娾垶卤鈭忊垎鈭懨仿?
enum EquipQuality
{
	EQUIP_QUALITY_WHITE=0,	//鈭炩棅鈼娾垶
	EQUIP_QUALITY_BLUE,		//驴鈭傗棅鈭?
	EQUIP_QUALITY_YELLOW,	//陋鈭嗏棅鈭?
	EQUIP_QUALITY_GOLD,		//惟铮库棅鈭?
	EQUIP_QUALITY_PURPLE,	//鈼娕撯棅鈭?
	EQUIP_QUALITY_ORANGE	//鈮ヂ烩棅鈭?
} ;

//楼聽鈼娾埆驴鈥♀€撁?
enum AffixType
{
	AFFIX_TYPE_MIN_ATTACK_SIN=1,        //+最小攻击(单体)
    AFFIX_TYPE_MAX_ATTACK_SIN=2,        //+最大攻击(单体)
    AFFIX_TYPE_MIN_DEFENSE_SIN=3,         //+最小防御(单体)
    AFFIX_TYPE_MAX_DEFENSE_SIN=4,         //+最大防御(单体)
    AFFIX_TYPE_MIN_ATTACK_SIN_PER=5,     //+最小攻击%(单体)：增加全身所有最小攻击的百分比
    AFFIX_TYPE_MAX_ATTACK_SIN_PER=6,     //+最大攻击%(单体) ：增加全身所有最大攻击的百分比
    AFFIX_TYPE_MIN_DEFENSE_SIN_PER=7,     //+最小防御%(单体) ：增加全身所有最小防御的百分比
    AFFIX_TYPE_MAX_DEFENSE_SIN_PER=8,     //+最大防御%(单体) :增加本件装备基础部分的百分比
    AFFIX_TYPE_MIN_ATTACK_ALL_PER=9,     //+最小攻击%(全体)：增加全身所有最小攻击的百分比
    AFFIX_TYPE_MAX_ATTACK_ALL_PER=10,     //+最大攻击%(全体) ：增加全身所有最大攻击的百分比
    AFFIX_TYPE_MIN_DEFENSE_ALL_PER=11,     //+最小防御%(全体) ：增加全身所有最小防御的百分比
    AFFIX_TYPE_MAX_DEFENSE_ALL_PER=12,     //+最大防御%(全体) ：增加全身所有最大防御的百分比
    AFFIX_TYPE_MAX_ATTACK_RATE_PER=13,         //+最大攻击打出概率%(单体)：出现攻击上限的概率
    AFFIX_TYPE_MAX_DEFENSE_RATE_PER=14,     //+最大防御打出概率%(单体)：出现防御上限的概率
    AFFIX_TYPE_ENERGY_UP=15,     //+能量上限：
    AFFIX_TYPE_ENERGY_SPEED_PER=16,     //+能量回复速度%：
    AFFIX_TYPE_POWER_UP=17,     //+体力上限：
    AFFIX_TYPE_POWER_SPEED_PER=18,     //+体力回复速度%：
    AFFIX_TYPE_LIFE=19,     //+血量
    AFFIX_TYPE_LIFE_SIN_PER=20,     //+血量（全体）%：单件装备血量的百分比
    AFFIX_TYPE_MF_PER=21,     //+血量（全体）%：单件装备血量的百分比
    AFFIX_TYPE_GET_COIN_PER=22,     //+铜币获得量%：只增加地下城，神秘洞穴战斗时金币的获得
    AFFIX_TYPE_GET_EXP_PER=23     //+经验获得量%：只增加地下城，神秘洞穴战斗时经验的获得
    
} ;

//楼聽鈼娾埆
struct Affix
{
	AffixType type;
	int value;
    void convert(EquipageExtInfo& info)
    {
        type = (AffixType)info.id;
        value = info.value;
    }
	void convert(Affix* affix)
	{
		type = affix->type;
		value = affix->value;
	}
    
    const char* getTitle()
    {
        return gls(fcs("affix_%d",type));
    }
    
    bool isPer()
    {
        switch(type)
        {
            case AFFIX_TYPE_MIN_ATTACK_SIN:return false;        //+最小攻击(单体)
            case AFFIX_TYPE_MAX_ATTACK_SIN:return false;        //+最大攻击(单体)
            case AFFIX_TYPE_MIN_DEFENSE_SIN:return false;         //+最小防御(单体)
            case AFFIX_TYPE_MAX_DEFENSE_SIN:return false;         //+最大防御(单体)
            case AFFIX_TYPE_MIN_ATTACK_SIN_PER:return true;     //+最小攻击%(单体)：增加全身所有最小攻击的百分比
            case AFFIX_TYPE_MAX_ATTACK_SIN_PER:return true;     //+最大攻击%(单体) ：增加全身所有最大攻击的百分比
            case AFFIX_TYPE_MIN_DEFENSE_SIN_PER:return true;     //+最小防御%(单体) ：增加全身所有最小防御的百分比
            case AFFIX_TYPE_MAX_DEFENSE_SIN_PER:return true;     //+最大防御%(单体) :增加本件装备基础部分的百分比
            case AFFIX_TYPE_MIN_ATTACK_ALL_PER:return true;     //+最小攻击%(全体)：增加全身所有最小攻击的百分比
            case AFFIX_TYPE_MAX_ATTACK_ALL_PER:return true;     //+最大攻击%(全体) ：增加全身所有最大攻击的百分比
            case AFFIX_TYPE_MIN_DEFENSE_ALL_PER:return true;     //+最小防御%(全体) ：增加全身所有最小防御的百分比
            case AFFIX_TYPE_MAX_DEFENSE_ALL_PER:return true;     //+最大防御%(全体) ：增加全身所有最大防御的百分比
            case AFFIX_TYPE_MAX_ATTACK_RATE_PER:return true;         //+最大攻击打出概率%(单体)：出现攻击上限的概率
            case AFFIX_TYPE_MAX_DEFENSE_RATE_PER:return true;     //+最大防御打出概率%(单体)：出现防御上限的概率
            case AFFIX_TYPE_ENERGY_UP:return false;     //+能量上限：
            case AFFIX_TYPE_ENERGY_SPEED_PER:return true;     //+能量回复速度%：
            case AFFIX_TYPE_POWER_UP:return false;     //+体力上限：
            case AFFIX_TYPE_POWER_SPEED_PER:return true;     //+体力回复速度%：
            case AFFIX_TYPE_LIFE:return false;     //+血量
            case AFFIX_TYPE_LIFE_SIN_PER:return true;     //+血量（全体）%：单件装备血量的百分比
            case AFFIX_TYPE_MF_PER:return true;
            case AFFIX_TYPE_GET_COIN_PER:return true;     //+铜币获得量%：只增加地下城，神秘洞穴战斗时金币的获得
            case AFFIX_TYPE_GET_EXP_PER:return true;     //+经验获得量%：只增加地下城，神秘洞穴战斗时经验的获得
        }
        return false;
    }
};

struct ItemInfo
{
    int index;
    int id;
    int count;
    void convert(ItemInfo* info)
    {
        id = info->id;
        index = info->index;
        count = info->count;
    }
};

typedef vector<Affix*> AffixList;
struct EquipInfo : public ItemInfo
{
    int state;
	int level;
	int exp;
	int atkMin;
	int atkMax;
	int defMin;
    int defMax;
	int life;
	int quality;
    int intensifyNum;
    int intensifyValue;
	AffixList affixs;
    bool isPutOn(){return state == 1;}
    void convert(EquipageInfo& info)
    {
        id = info.id;
        index = info.index;
        level = info.level;
        exp = info.exp;
        atkMin = info.atkMin;
        atkMax = info.atkMax;
        defMin = info.def;
        defMax = info.def;
        life = info.life;
        state = info.state;
		affixs.clear();
        std::vector<EquipageExtInfo>& ext = info.ext;
        for(int i = 0; i < ext.size(); i++)
        {
            Affix* affix = new Affix();
            affix->convert(ext[i]);
			affixs.push_back(affix);
        }
    }

	void convert(EquipInfo* info)
	{
		id = info->id;
		index = info->index;
		level = info->level;
		exp = info->exp;
		atkMin = info->atkMin;
		atkMax = info->atkMax;
		defMin = info->defMin;
        defMax = info->defMax;
		life = info->life;
		state = info->state;
        intensifyNum = info->intensifyNum;
        intensifyValue = info->intensifyValue;
		clearAffix();
		std::vector<Affix*> ext = info->affixs;
		for(int i = 0; i < ext.size(); i++)
		{
			Affix* affix = new Affix();
			affix->convert(ext[i]);
			affixs.push_back(affix);
		}
	}
    //主属性加词缀后的最小值
    int getMinAttachProperty()
    {
		int atkMaxResult = atkMax;
		int defMaxResult = defMax;
        
		int atkMinResult = atkMin;
		int defMinResult = defMin;
        
		int atkMinAllPercent = 0;
		int defMinAllPercent = 0;
        
		int atkMaxAllPercent = 0;
		int defMaxAllPercent = 0;
        
		int size = affixs.size();
		for (int i=0; i<size; i++)
		{
			Affix* affix = affixs[i];
			int type = affix->type;
			int value = affix->value;
			
	        switch(type)
	        {
                case AFFIX_TYPE_MIN_ATTACK_SIN:
                    //+最小攻击(单体)
                    atkMinResult += value;
                    break;
                case AFFIX_TYPE_MAX_ATTACK_SIN:
                    //+最大攻击(单体)
                    atkMaxResult += value;
                    break;
                case AFFIX_TYPE_MIN_DEFENSE_SIN:
                    //+最小防御(单体)
                    defMinResult += value;
                    break;
                case AFFIX_TYPE_MAX_DEFENSE_SIN:
                    //+最大防御(单体)
                    defMaxResult += value;
                    break;
                case AFFIX_TYPE_MIN_ATTACK_SIN_PER:
                    //+最小攻击%(单体)：增加全身所有最小攻击的百分比
                    atkMinResult += atkMin * value / 100;
                    break;
                case AFFIX_TYPE_MAX_ATTACK_SIN_PER:
                    //+最大攻击%(单体) ：增加全身所有最大攻击的百分比
                    atkMaxResult += atkMax * value / 100;
                    break;
                case AFFIX_TYPE_MIN_DEFENSE_SIN_PER:
                    //+最小防御%(单体) ：增加全身所有最小防御的百分比
                    defMinResult += defMin * value / 100;
                    break;
                case AFFIX_TYPE_MAX_DEFENSE_SIN_PER:
                    //+最大防御%(单体) :增加本件装备基础部分的百分比
                    defMaxResult += defMax * value / 100;
                    break;
                case AFFIX_TYPE_MIN_ATTACK_ALL_PER:
                    //+最小攻击%(全体)：增加全身所有最小攻击的百分比
                    atkMinAllPercent += value;
                    break;
                case AFFIX_TYPE_MAX_ATTACK_ALL_PER:
                    //+最大攻击%(全体) ：增加全身所有最大攻击的百分比
                    atkMaxAllPercent += value;
                    break;
                case AFFIX_TYPE_MIN_DEFENSE_ALL_PER:
                    //+最小防御%(全体) ：增加全身所有最小防御的百分比
                    defMinAllPercent += value;
                    break;
                case AFFIX_TYPE_MAX_DEFENSE_ALL_PER:
                    //+最大防御%(全体) ：增加全身所有最大防御的百分比
                    defMaxAllPercent += value;
                    break;
                case AFFIX_TYPE_MAX_ATTACK_RATE_PER:
                    //+最大攻击打出概率%(单体)：出现攻击上限的概率
                    break;
                case AFFIX_TYPE_MAX_DEFENSE_RATE_PER:
                    //+最大防御打出概率%(单体)：出现防御上限的概率
                    break;
                case AFFIX_TYPE_ENERGY_UP:
                    //+能量上限：
                    break;
                case AFFIX_TYPE_ENERGY_SPEED_PER:
                    //+能量回复速度%：
                    break;
                case AFFIX_TYPE_POWER_UP:
                    //+体力上限：
                    break;
                case AFFIX_TYPE_POWER_SPEED_PER:
                    //+体力回复速度%：
                    break;
                case AFFIX_TYPE_LIFE:
                    //+血量
                    break;
                case AFFIX_TYPE_LIFE_SIN_PER:
                    //+血量（单体）%：单件装备血量的百分比
                    break;
                case AFFIX_TYPE_MF_PER:
                    //+血量
                    break;
                case AFFIX_TYPE_GET_COIN_PER:
                    //+铜币获得量%：只增加地下城，神秘洞穴战斗时金币的获得
                    break;
                case AFFIX_TYPE_GET_EXP_PER:
                    //+经验获得量%：只增加地下城，神秘洞穴战斗时经验的获得
                    break;
                default:
                    break;
	        }
		}
        
		if (isAttack())
		{
			return atkMinResult;
		}
		else
		{
			return defMinResult;
		}
    }
    
    //主属性加词缀后的最大值
    int getMaxAttachProperty()
    {
		int atkMaxResult = atkMax;
		int defMaxResult = defMax;
        
		int atkMinResult = atkMin;
		int defMinResult = defMin;
        
		int atkMinAllPercent = 0;
		int defMinAllPercent = 0;
        
		int atkMaxAllPercent = 0;
		int defMaxAllPercent = 0;
        
		int size = affixs.size();
		for (int i=0; i<size; i++)
		{
			Affix* affix = affixs[i];
			int type = affix->type;
			int value = affix->value;
			
	        switch(type)
	        {
                case AFFIX_TYPE_MIN_ATTACK_SIN:
                    //+最小攻击(单体)
                    atkMinResult += value;
                    break;
                case AFFIX_TYPE_MAX_ATTACK_SIN:
                    //+最大攻击(单体)
                    atkMaxResult += value;
                    break;
                case AFFIX_TYPE_MIN_DEFENSE_SIN:
                    //+最小防御(单体)
                    defMinResult += value;
                    break;
                case AFFIX_TYPE_MAX_DEFENSE_SIN:
                    //+最大防御(单体)
                    defMaxResult += value;
                    break;
                case AFFIX_TYPE_MIN_ATTACK_SIN_PER:
                    //+最小攻击%(单体)：增加全身所有最小攻击的百分比
                    atkMinResult += atkMin * value / 100;
                    break;
                case AFFIX_TYPE_MAX_ATTACK_SIN_PER:
                    //+最大攻击%(单体) ：增加全身所有最大攻击的百分比
                    atkMaxResult += atkMax * value / 100;
                    break;
                case AFFIX_TYPE_MIN_DEFENSE_SIN_PER:
                    //+最小防御%(单体) ：增加全身所有最小防御的百分比
                    defMinResult += defMin * value / 100;
                    break;
                case AFFIX_TYPE_MAX_DEFENSE_SIN_PER:
                    //+最大防御%(单体) :增加本件装备基础部分的百分比
                    defMaxResult += defMax * value / 100;
                    break;
                case AFFIX_TYPE_MIN_ATTACK_ALL_PER:
                    //+最小攻击%(全体)：增加全身所有最小攻击的百分比
                    atkMinAllPercent += value;
                    break;
                case AFFIX_TYPE_MAX_ATTACK_ALL_PER:
                    //+最大攻击%(全体) ：增加全身所有最大攻击的百分比
                    atkMaxAllPercent += value;
                    break;
                case AFFIX_TYPE_MIN_DEFENSE_ALL_PER:
                    //+最小防御%(全体) ：增加全身所有最小防御的百分比
                    defMinAllPercent += value;
                    break;
                case AFFIX_TYPE_MAX_DEFENSE_ALL_PER:
                    //+最大防御%(全体) ：增加全身所有最大防御的百分比
                    defMaxAllPercent += value;
                    break;
                case AFFIX_TYPE_MAX_ATTACK_RATE_PER:
                    //+最大攻击打出概率%(单体)：出现攻击上限的概率
                    break;
                case AFFIX_TYPE_MAX_DEFENSE_RATE_PER:
                    //+最大防御打出概率%(单体)：出现防御上限的概率
                    break;
                case AFFIX_TYPE_ENERGY_UP:
                    //+能量上限：
                    break;
                case AFFIX_TYPE_ENERGY_SPEED_PER:
                    //+能量回复速度%：
                    break;
                case AFFIX_TYPE_POWER_UP:
                    //+体力上限：
                    break;
                case AFFIX_TYPE_POWER_SPEED_PER:
                    //+体力回复速度%：
                    break;
                case AFFIX_TYPE_LIFE:
                    //+血量
                    break;
                case AFFIX_TYPE_LIFE_SIN_PER:
                    //+血量（单体）%：单件装备血量的百分比
                    break;
                case AFFIX_TYPE_MF_PER:
                    //+血量（单体）%：单件装备血量的百分比
                    break;
                case AFFIX_TYPE_GET_COIN_PER:
                    //+铜币获得量%：只增加地下城，神秘洞穴战斗时金币的获得
                    break;
                case AFFIX_TYPE_GET_EXP_PER:
                    //+经验获得量%：只增加地下城，神秘洞穴战斗时经验的获得
                    break;
                default:
                    break;
	        }
		}
        
		if (isAttack())
		{
			return atkMaxResult;
		}
		else
		{
			return defMaxResult;
		}
    }
    
    //主属性基础最大值
    int getMinBaseProperty()
    {
        if(atkMax != 0 || atkMin != 0)
            return atkMin;
        else
            return defMin;
    }
    
    //主属性基础最小值
    int getMaxBaseProperty()
    {
        if(atkMax != 0 || atkMin != 0)
            return atkMax;
        else
            return defMax;
    }
    
    static const char* getAttachPropertyStr(EquipInfo* equipInfo)
    {
        return equipInfo->getAttachPropertyStr();
    }
    
    static const char* getBasePropertyStr(EquipInfo* equipInfo)
    {
        return equipInfo->getBasePropertyStr();
    }
    
    const char* getAttachPropertyStr()
    {
        return fcs("%d--%d", getMinAttachProperty(), getMaxAttachProperty());
    }
    
    const char* getBasePropertyStr()
    {
        return fcs("%d--%d", getMinBaseProperty(), getMaxBaseProperty());
    }
    
    const char* getPropertyTitle()
    {
        if(isAttack())
        {
            return gls("attack");
        }
        else
        {
            return gls("defense");
        }
    }
    
    bool isAttack()
    {
        return atkMax != 0 || atkMin != 0;
    }
    
    ccColor3B getNameColor()
    {
        EquipStatic* equipStatic = StaticItem::shared()->getEquipInfo(id);
        ccColor3B color = ccWHITE;
        switch(equipStatic->quality)
        {
            case EQUIP_QUALITY_WHITE:
                color.r = 255;
                color.g = 255;
                color.b = 255;
                break;
            case EQUIP_QUALITY_BLUE:
                if(affixs.size() > 0)
                {
                    color.r = 46;
                    color.g = 200;
                    color.b = 202;
                }
                else
                {
                    color.r = 255;
                    color.g = 255;
                    color.b = 255;
                }
                break;
            case EQUIP_QUALITY_YELLOW:
                color.r = 227;
                color.g = 224;
                color.b = 134;
                break;
            case EQUIP_QUALITY_GOLD:
                color.r = 254;
                color.g = 188;
                color.b = 67;
                break;
        }
        return color;
    }
    
    static ccColor3B getNameColor(int quality)
    {
        ccColor3B color = ccWHITE;
        if(quality == EQUIP_QUALITY_WHITE)
        {
            color.r = 255;
            color.g = 255;
            color.b = 255;
        }
        else if(quality == EQUIP_QUALITY_BLUE)
        {
            color.r = 46;
            color.g = 200;
            color.b = 202;
        }
        else if(quality == EQUIP_QUALITY_YELLOW)
        {
            color.r = 227;
            color.g = 224;
            color.b = 134;
        }
        else if(quality == EQUIP_QUALITY_GOLD)
        {
            color.r = 254;
            color.g = 188;
            color.b = 67;
        }
        
        return color;
    }
    
    void clearAffix()
    {
        std::vector<Affix*>::iterator iter = affixs.begin();
        while(iter != affixs.end())
        {
            delete *iter;
            iter++;
        }
    }
    
    ItemKind getKind()
    {
        EquipStatic* equipStatic = StaticItem::shared()->getEquipInfo(id);
        return equipStatic->kind;
    }
    
    int getSellPrize()
    {
        EquipStatic* equipStatic = StaticItem::shared()->getEquipInfo(id);
        return int(30*level*equipStatic->quality*(1+affixs.size()*0.15));
    }

	EquipInfo():quality(0){}
    ~EquipInfo(){clearAffix();}
};

struct BagInfo
{
	int bagmax;
	int bagid;
	std::vector<EquipInfo*> equipList;
    void convert(PlayerBagInfo& info)
    {
        bagmax = info.bagmax;
        bagid = info.bagid;
        std::vector<EquipageInfo>& baginfo = info.baginfo;
        for(int i = 0; i < baginfo.size(); i++)
        {
            EquipInfo* equipInfo = new EquipInfo();
            equipInfo->convert(baginfo[i]);
			equipList.push_back(equipInfo);
        }
    }
};

typedef vector<EquipInfo*> EquipList;
typedef vector<ItemInfo*> ItemList;

class ItemProxy : public Singleton<ItemProxy>
{
	void testData();

public:
	ItemProxy();
	~ItemProxy();

	BagInfo bagInfo;
    ItemList itemList;
    int putonIndex;
    vector<int> sellList;
    int mBagMax;

	int mRefreshMysteryShopNeedMoney;

	EquipInfo* lastQiangHuaEquip;
	EquipInfo* curQiangHuaEquip;
	vector<int> mSelectList;

	EquipList& getEquipList();
    ItemList& getItemList();
	void getPutOnList(EquipList& retEquipList);
	void getTakeOffList(EquipList& retEquipList);
    EquipInfo* getPutOnEquip(ItemKind kind);

	int getBagMax();

	int getBagID();

	//鈮堚€撯垈艙碌驴忙铿偮犅垜脪艗鈩⑩棅鈭灺扁垙
	bool isEquip(int id);
	static bool isEquip(ItemKind kind);
	ItemKind getItemKind(int id);

	//鈮堚€撯垈艙鈼娾垶卤鈭徛犅垜脪鈼娾垶卤鈭忊€ε?
	bool isEquipPutOn(int index);

	//鈮堚€撯垈艙鈼娾垶卤鈭徛犅垜脪鈥撯垈艙卢
	bool isEquipTakeOff(int index);

	//楼漏鈥ε撯棅鈭灺扁垙
	void putOnEquip(int index);

	//脮庐蟺藵鈼娾垶卤鈭廼d脮鈥斉撀棅鈭灺扁垙
	void takeOffEquip(int index);

	//脮庐蟺藵鈼娾垶卤鈭忊墹酶艗陋脮鈥斉撀棅鈭灺扁垙
	void takeOffEquip(ItemKind part);
    
    void sellItem(vector<int>& sellList);
    
    void removeEquip(int index);
    
    EquipInfo* getEquip(int index);

	int getPutonCount();
	int getEquipCount();

	int getItemCount(int id);

	void clearMergeList();

	void addEquip(std::vector<EquipageInfo>& equipList);
	void addEquip(EquipageInfo& equipageInfo);
	void addEquip(EquipInfo* equipInfo, bool isNew=false);
    
    void addItem(ItemInfo* itemInfo, bool isNew=false);
    ItemInfo* getItem(int index);

    void setLastQiangHuaEquip(EquipInfo* equipInfo);
	void getPropertyValue(EquipInfo* equipInfo, string& ret);

	const char* getTypeTitle(int id);
    
    bool isBagFull();
};

#endif
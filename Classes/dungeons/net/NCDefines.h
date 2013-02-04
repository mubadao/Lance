/**
 * @file
 * @brief   网络命令定义文件。
 * @author  赵一
 * @date    2012/08/01
 * @version 0.1
 */

#ifndef _NCDefines_h_
#define _NCDefines_h_

#include "Global.h"
/**
 * @brief 网络命令名称定义。
 */
//登陆
#define kNCGameInit                       "GameInit"
#define kNCRegist                         "Regist"

//信息
#define kNCGetSelfInfo                    "GetSelfInfo"

//地下城
#define kNCDungeonExplore                 "DungeonExplore"
#define kNCDungeonStart                   "DungeonStart"

//背包装备
#define kNCLoadEquipage                   "LoadEquipage"
#define kNCSellEquipage                   "SellEquipage"
#define kNCUnloadEquipage                 "UnloadEquipage"
#define kNCResetEquipage                  "ResetEquipage"
#define kNCFusionEquipage                 "FusionEquipage"
#define kNCIntensifyEquipage              "IntensifyEquipage"

//挑战
#define kNCFindChallengePlayerByName      "FindChallengePlayerByName"
#define kNCFindChallengePlayerByPid       "FindChallengePlayerByPid"
#define kNCGetChallengeList               "GetChallengeList"
#define kNCGetChallengeEnemyList          "GetChallengeEnemyList"
#define kNCChallengePlayer                "ChallengePlayer"

//开宝箱
#define kNCOpenBox                        "OpenBox"
#define kNCBuyEnergy                      "BuyEnergy"
#define kNCBuyPower                       "BuyPower"
#define kNCBuyLife                        "BuyLife"
#define kNCBuyCoin                        "BuyCoin"
#define kNCBuyMoney                       "BuyMoney"

//抢夺+合成
#define kNCGetComposeList                 "GetComposeList"
#define kNCComposeEquipage                "ComposeEquipage"
#define kNCGetAmuletEnemyList             "GetAmuletEnemyList"
#define kNCGetFragmentEnemyList           "GetFragmentEnemyList"
#define kNCFindSnatchAmuletInfo           "FindSnatchAmuletInfo"
#define kNCFindSnatchFragmentInfo         "FindSnatchFragmentInfo"
#define kNCSnatchPlayer                   "SnatchPlayer"

//购买道具
#define kNCBuyItem                        "BuyItem"
//使用道具
#define kNCUseItem                        "UseItem"
//领奖
#define kNCGetPrize                       "GetPrize"
//刷新神秘商店
#define kNCRefreshMysteryShop             "RefreshMysteryShop"
//得到所有事件
#define kNCGetAllEvent                    "GetAllEvent"
//得到战斗事件
#define kNCGetFightEvent                  "GetFightEvent"
//刷新系统事件
#define kNCGetSystemEvent                 "GetSystemEvent"

  
#define kNCVersionError                   "VersionError"

/**
 * @brief 网络命令选项定义。
 */
//版本
#define kNCVersion                        "0.9.1"
//服务
#define kNCService                        "BaseService"
//方法
#define kNCMethod                         "dispatch"

//平台类型
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define kNCPlatform                       (4)
#else
#define kNCPlatform                       (0xff)
#endif


//错误类型定义
#define kNCNetError                       "NetError"      //错误通知。
#define kNCErrorPID                       (0x00000001)    //pid错误。
#define kNCErrorPlatform                  (0x00000002)    //platform错误。
#define kNCErrorParams                    (0x00000003)    //参数错误
#define kNCErrorGID                       (0x00000004)    //gid错误

#define kNCErrorRegist                    (0x10000001)    //注册错误
#define kNCErrorGetSelfInfo               (0x10000002)    //取得自己信息错误
#define kNCErrorGetInfo                   (0x10000003)    //取得信息错误
#define kNCErrorReadXML                   (0x10000004)    //服务器读取xml错误
#define kNCErrorSystem                    (0x10000005)    //服务器系统错误
#define kNCErrorResetDungeonInfo          (0x10000006)    //初始化地下城信息失败

#define kNCErrorCoin                      (0x20000001)    //玩家游戏币不足
#define kNCErrorFreeTime                  (0x20000002)    //玩家免费机会不足
#define kNCErrorCoinTime                  (0x20000003)    //玩家游戏币机会不足
#define kNCErrorMoneyTime                 (0x20000004)    //玩家付费币机会不足
#define kNCErrorMoney                     (0x20000005)    //玩家付费币不足
#define kNCErrorEnergy                    (0x20000006)    //玩家能量不足
#define kNCErrorLife                      (0x20000007)    //玩家生命不足
#define kNCErrorEnergyFull                (0x20000008)    //玩家能量以满
#define kNCErrorLifeFull                  (0x20000009)    //玩家生命以满
#define kNCErrorPowerFull                 (0x2000000a)    //玩家体力以满
#define kNCErrorDollar                    (0x2000000b)    //玩家美金不足
#define kNCErrorReceipt                   (0x2000000c)    //玩家花费验证码错误
#define kNCErrorBagFull                   (0x2000000d)    //玩家背包已满

/**
 * @brief 背包中装备元素数组的索引定义。
 */
#if NETCONTROLLER_USE_JSON
#define kNCBagEquipageFieldIndex          "0"     //装备索引
#define kNCBagEquipageFieldBaseID         "1"     //装备ID
#define kNCBagEquipageFieldLevel          "2"     //装备等级
#define kNCBagEquipageFieldExp            "3"     //装备经验值
#define kNCBagEquipageFieldAtkMin         "4"     //装备最小攻击力值
#define kNCBagEquipageFieldAtkMax         "5"     //装备最大攻击力值
#define kNCBagEquipageFieldDefMin         "6"     //装备最小防御力值
#define kNCBagEquipageFieldDefMax         "7"     //装备最大防御力值
#define kNCBagEquipageFieldLife           "8"     //装备生命值
#define kNCBagEquipageFieldState          "9"     //装备状态(0:未使用;1:使用中)
#define kNCBagEquipageFieldIntensifyNum   "10"    //装备强化次数
#define kNCBagEquipageFieldIntensifyValue "11"    //装备强化数值
#define kNCBagEquipageFieldExt            "12"    //装备扩展词条
#else
#define kNCBagEquipageFieldIndex          (0)     //装备索引
#define kNCBagEquipageFieldBaseID         (1)     //装备ID
#define kNCBagEquipageFieldLevel          (2)     //装备等级
#define kNCBagEquipageFieldExp            (3)     //装备经验值
#define kNCBagEquipageFieldAtkMin         (4)     //装备最小攻击力值
#define kNCBagEquipageFieldAtkMax         (5)     //装备最大攻击力值
#define kNCBagEquipageFieldDefMin         (6)     //装备最小防御力值
#define kNCBagEquipageFieldDefMax         (7)     //装备最大防御力值
#define kNCBagEquipageFieldLife           (8)     //装备生命值
#define kNCBagEquipageFieldState          (9)     //装备状态(0:未使用;1:使用中)
#define kNCBagEquipageFieldIntensifyNum   (10)    //装备强化次数
#define kNCBagEquipageFieldIntensifyValue (11)    //装备强化数值
#define kNCBagEquipageFieldExt            (12)    //装备扩展词条
#endif

/**
 * @brief 背包中道具元素数组的索引定义。
 */
#define kNCBagPropFieldIndex              (0)     //道具索引
#define kNCBagPropFieldBaseID             (1)     //道具ID
#define kNCBagPropFieldNum                (2)     //道具数量

/**
 * @brief 任务信息中任务元素数组的索引定义。
 */
#define kNCTaskFieldFloor                 (0)     //任务楼层
#define kNCTaskFieldTask                  (1)     //任务ID
#define kNCTaskFieldProgress              (2)     //任务进度

struct NetError
{
    std::string cmdName;
    int errorCode;
};
/**
 * @brief 装备词条属性信息定义。
 */
typedef struct stEquipageExtInfo
{
    int id;
    int value;
}EquipageExtInfo;

/**
 * @brief 装备属性信息定义。
 */
typedef struct stEquipageInfo
{
    int index;
    int id;
    int level;
    int exp;
    int atkMin;
    int atkMax;
    int def;
    int life;
    int state;
    bool isPutOn(){return state==1;}
    std::vector<EquipageExtInfo> ext;
}EquipageInfo;



#if 0
typedef struct stTaskInfo
{
    TaskItemInfo cur;
    TaskItemInfo max;
}TaskInfo;
#endif

/**
 * @brief 玩家验证信息定义。
 */
typedef struct stPlayerCheckInfo
{
    std::string pid;
    int gid;
    int platform;
}PlayerCheckInfo;

/**
 * @brief 玩家时间信息定义。
 */
typedef struct stPlayerTimeInfo
{
    int createtime;
    int energetime;
}PlayerTimeInfo;

/**
 * @brief 玩家基础信息定义。
 */
typedef struct stPlayerBaseInfo
{
    std::string name;
    int avata;
    int level;
    int exp;
    int energycur;
    int energymax;
    int point;
}PlayerBaseInfo;

/**
 * @brief 玩家战斗属性信息定义。
 */
typedef struct stPlayerBattleInfo
{
    int life;
    int attack;
    int defense;
    int power;
    int speed;
    int stamina;
    int vigour;
}PlayerBattleInfo;

/**
 * @brief 玩家金融信息定义。
 */
typedef struct stPlayerFinanceInfo
{
    int coin;
    int money;
}PlayerFinanceInfo;

/**
 * @brief 玩家背包信息定义。
 */
typedef struct stPlayerBagInfo
{
    int bagmax;
    int bagid;
    std::vector<EquipageInfo> baginfo;
}PlayerBagInfo;


/**
 * @brief 玩家信息定义。
 */
typedef struct stPlayerInfo
{
    PlayerCheckInfo checkInfo;
    PlayerTimeInfo timeInfo;
    PlayerBaseInfo baseInfo;
    PlayerFinanceInfo financeInfo;
    PlayerBattleInfo battleInfo;
    PlayerBagInfo bagInfo;
}PlayerInfo;

/**
 * @brief 奖励信息定义。
 */
typedef struct stAwardInfo
{
    int exp;
    int coin;
    std::vector<EquipageInfo> equipageList;
}AwardInfo;

/**
 * @brief 对战回合定义。
 */
typedef struct stRoundInfo
{
    int act;        //攻击方
    int type;       //攻击类型
    int value;      //攻击失血
}RoundInfo;

/**
 * @brief 对战信息定义。
 */
typedef struct stBattleInfo
{
    int win;
    std::vector<RoundInfo> roundInfo;
}BattleInfo;

/**
 * @brief 对战结果信息定义。
 */
typedef struct stBattleResult
{
    int dungeon;
    AwardInfo awardInfo;
    BattleInfo battleInfo;
}BattleResult;

/**
 * @brief 同步信息定义。
 */
typedef struct stAsyncInfo
{
    int point;
}AsyncInfo;

#endif // _NCDefines_h_

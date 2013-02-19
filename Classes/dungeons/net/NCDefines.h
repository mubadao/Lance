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

// 网络命令名称定义。
//登陆
#define kNCGameInit							"GameInit"
#define kNCRegist							"Regist"

//信息
#define kNCGetSelfInfo						"GetSelfInfo"

//地下城
#define kNCDungeonExplore					"DungeonExplore"
#define kNCDungeonStart						"DungeonStart"

//背包装备
#define kNCLoadEquipage						"LoadEquipage"
#define kNCSellEquipage						"SellEquipage"
#define kNCUnloadEquipage					"UnloadEquipage"
#define kNCResetEquipage					"ResetEquipage"
#define kNCFusionEquipage					"FusionEquipage"
#define kNCIntensifyEquipage				"IntensifyEquipage"

//挑战
#define kNCFindChallengePlayerByName		"FindChallengePlayerByName"
#define kNCFindChallengePlayerByPid			"FindChallengePlayerByPid"
#define kNCGetChallengeList					"GetChallengeList"
#define kNCGetChallengeEnemyList			"GetChallengeEnemyList"
#define kNCChallengePlayer					"ChallengePlayer"

//开宝箱
#define kNCOpenBox							"OpenBox"
#define kNCBuyEnergy						"BuyEnergy"
#define kNCBuyPower							"BuyPower"
#define kNCBuyLife							"BuyLife"
#define kNCBuyCoin							"BuyCoin"
#define kNCBuyMoney							"BuyMoney"
#define kNCBuyFusion						"BuyFusion"

//抢夺+合成
#define kNCGetComposeList					"GetComposeList"
#define kNCComposeEquipage					"ComposeEquipage"
#define kNCGetAmuletEnemyList				"GetAmuletEnemyList"
#define kNCGetFragmentEnemyList				"GetFragmentEnemyList"
#define kNCFindSnatchAmuletInfo				"FindSnatchAmuletInfo"
#define kNCFindSnatchFragmentInfo			"FindSnatchFragmentInfo"
#define kNCSnatchPlayer						"SnatchPlayer"


#define kNCBuyItem							"BuyItem"						//购买道具
#define kNCUseItem							"UseItem"						//使用道具
#define kNCGetPrize							"GetPrize"						//领奖
#define kNCRefreshMysteryShop				"RefreshMysteryShop"			//刷新神秘商店
#define kNCGetAllEvent						"GetAllEvent"					//得到所有事件
#define kNCGetFightEvent					"GetFightEvent"					//得到战斗事件
#define kNCGetSystemEvent					"GetSystemEvent"				//刷新系统事件
  
#define kNCVersionError						"VersionError"

// 网络命令选项定义。
#define kNCVersion							"0.9.1"							//版本
#define kNCService							"BaseService"					//服务
#define kNCMethod							"dispatch"						//方法

//平台类型
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define kNCPlatform							(4)
#else
#define kNCPlatform							(0xff)
#endif


//错误类型定义
#define kNCNetError							"NetError"						//错误通知。
#define kNCErrorPID							(0x00000001)					//pid错误。
#define kNCErrorPlatform					(0x00000002)					//platform错误。
#define kNCErrorParams						(0x00000003)					//参数错误
#define kNCErrorGID							(0x00000004)					//gid错误

#define kNCErrorRegist						(0x10000001)					//注册错误
#define kNCErrorGetSelfInfo					(0x10000002)					//取得自己信息错误
#define kNCErrorGetInfo						(0x10000003)					//取得信息错误
#define kNCErrorReadXML						(0x10000004)					//服务器读取xml错误
#define kNCErrorSystem						(0x10000005)					//服务器系统错误
#define kNCErrorResetDungeonInfo			(0x10000006)					//初始化地下城信息失败

#define kNCErrorCoin						(0x20000001)					//玩家游戏币不足
#define kNCErrorFreeTime					(0x20000002)					//玩家免费机会不足
#define kNCErrorCoinTime					(0x20000003)					//玩家游戏币机会不足
#define kNCErrorMoneyTime					(0x20000004)					//玩家付费币机会不足
#define kNCErrorMoney						(0x20000005)					//玩家付费币不足
#define kNCErrorEnergy						(0x20000006)					//玩家能量不足
#define kNCErrorLife						(0x20000007)					//玩家生命不足
#define kNCErrorEnergyFull					(0x20000008)					//玩家能量以满
#define kNCErrorLifeFull					(0x20000009)					//玩家生命以满
#define kNCErrorPowerFull					(0x2000000a)					//玩家体力以满
#define kNCErrorDollar						(0x2000000b)					//玩家美金不足
#define kNCErrorReceipt						(0x2000000c)					//玩家花费验证码错误
#define kNCErrorBagFull						(0x2000000d)					//玩家背包已满
#define kNCErrorIntenfityLack				(0x2000000f)					//玩家熔炼值不足

// 背包中装备元素数组的索引定义。
#if NETCONTROLLER_USE_JSON
#define kNCBagEquipageFieldIndex			"0"								//装备索引
#define kNCBagEquipageFieldBaseID			"1"								//装备ID
#define kNCBagEquipageFieldLevel			"2"								//装备等级
#define kNCBagEquipageFieldExp				"3"								//装备经验值
#define kNCBagEquipageFieldAtkMin			"4"								//装备最小攻击力值
#define kNCBagEquipageFieldAtkMax			"5"								//装备最大攻击力值
#define kNCBagEquipageFieldDefMin			"6"								//装备最小防御力值
#define kNCBagEquipageFieldDefMax			"7"								//装备最大防御力值
#define kNCBagEquipageFieldLife				"8"								//装备生命值
#define kNCBagEquipageFieldState			"9"								//装备状态(0:未使用;1:使用中)
#define kNCBagEquipageFieldIntensifyNum		"10"							//装备强化次数
#define kNCBagEquipageFieldIntensifyValue	"11"							//装备强化数值
#define kNCBagEquipageFieldExt				"12"							//装备扩展词条
#else
#define kNCBagEquipageFieldIndex			(0)								//装备索引
#define kNCBagEquipageFieldBaseID			(1)								//装备ID
#define kNCBagEquipageFieldLevel			(2)								//装备等级
#define kNCBagEquipageFieldExp				(3)								//装备经验值
#define kNCBagEquipageFieldAtkMin			(4)								//装备最小攻击力值
#define kNCBagEquipageFieldAtkMax			(5)								//装备最大攻击力值
#define kNCBagEquipageFieldDefMin			(6)								//装备最小防御力值
#define kNCBagEquipageFieldDefMax			(7)								//装备最大防御力值
#define kNCBagEquipageFieldLife				(8)								//装备生命值
#define kNCBagEquipageFieldState			(9)								//装备状态(0:未使用;1:使用中)
#define kNCBagEquipageFieldIntensifyNum		(10)							//装备强化次数
#define kNCBagEquipageFieldIntensifyValue	(11)							//装备强化数值
#define kNCBagEquipageFieldExt				(12)							//装备扩展词条
#endif

// 背包中道具元素数组的索引定义。
#define kNCBagPropFieldIndex				(0)								//道具索引
#define kNCBagPropFieldBaseID				(1)								//道具ID
#define kNCBagPropFieldNum					(2)								//道具数量

// 任务信息中任务元素数组的索引定义。
#define kNCTaskFieldFloor					(0)								//任务楼层
#define kNCTaskFieldTask					(1)								//任务ID
#define kNCTaskFieldProgress				(2)								//任务进度

struct NetError
{
	string cmdName;
	int errorCode;
};

#endif // _NCDefines_h_

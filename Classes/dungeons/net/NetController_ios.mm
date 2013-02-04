/**
 * @file
 * @brief   网络命令类定义文件。
 * @author  赵一
 * @date    2012/08/01
 * @version 0.1
 */

#include "NetController.h"
#include "CommonHelper.h"

#if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && (!NETCONTROLLER_USE_JSON))

#import "AMFCaller.h"
#include "../model/proxy/DungeonsProxy.h"
#include "../Model/proxy/UserProxy.h"
#include "../Model/proxy/ItemProxy.h"
#include "../Model/proxy/FightProxy.h"
#include "../Model/proxy/ChanllengeProxy.h"
#include "../Model/proxy/CommonProxy.h"
#include "../Model/proxy/ShopProxy.h"
#include "Waitting.h"
#include "CommonHelper.h"

NSMutableArray* packageList_;
bool isWaitReceive;

/**
 * @brief 构造函数。
 * @note  初始化内部变量。
 */
NetController::NetController()
    : mPlatform(-1)
    , mGid(-1)
{
    //NSLog(@"NetController::NetController() start");

    //NSLog(@"NetController::NetController() end");
    
    packageList_ = [[NSMutableArray alloc] init];
    isWaitReceive = false;
}

/**
 * @brief 析构函数。
 */
NetController::~NetController()
{
    //NSLog(@"NetController::~NetController() start");

    //NSLog(@"NetController::~NetController() end");
    
    [packageList_ release];
}

/**
 * @brief     初始化函数。
 * @param[in] url   服务器地址URL。
 * @return    true  成功。
 * @return    false 失败。
 * @note      初始化网络命令参数。
 */
bool NetController::init(const char* url)
{
    //NSLog(@"NetController::init() start");

    bool result = false;

    if (url != nil)
    {
        //NSLog(@"NetController::init(): url: %s", url);

        [[AMFCaller shared] setURL:[NSString stringWithFormat:@"%s", url]];
        mPlatform = _getPlatform();
        mPid = _getPid();
        mVersion = _getVersion();

        result = true;
    }
    else
    {
        //NSLog(@"NetController::init(): paramater url is null.");
    }

    //NSLog(@"NetController::init() end");

    return result;
}

/**
 * @brief     数据解析函数。
 * @param[in] data 接收到的数据。
 * @note      解析数据包的基础信息，并根据命令名称进行命令分解调用。(用于网络接口回调使用)
 */
void NetController::parseData(void* data)
{
    //NSLog(@"NetController::parseData() start");

    isWaitReceive = false;

    NSDictionary *dict = (NSDictionary*)data;
    if (dict == nil || [dict isEqual:[NSNull null]] || [dict isEqual:@""])
        return;
    
    NSDictionary* result = [((NSArray*)[dict objectForKey:@"result"]) objectAtIndex:0];
    if (result == nil || [result isEqual:[NSNull null]] || [result isEqual:@""])
        return;

    //取得命令名称
    NSString* cmd = [result objectForKey:@"cmd"];
    //NSLog(@"cmd: %@", cmd);
    if (cmd == nil || [cmd isEqual:[NSNull null]] || [cmd isEqual:@""])
        return;

    //取得命令名称
    string cmdName = [cmd UTF8String];

    //取得命令版本信息
    NSString* version = [dict objectForKey:@"version"];
    //NSLog(@"version: %@", version);

    // 版本号错误
    if ( version == nil || [version isEqual:[NSNull null]] || [version isEqual:@""] ||
        (![version isEqualToString:[NSString stringWithFormat:@"%s", mVersion.c_str()]] && cmdName != kNCGameInit) )
    {
        Post_Net_Notification(kNCVersionError, NULL);
        return;
    }
    
    //取得结果状态（0：命令执行成功。1：命令执行出错）
    int status = [[result objectForKey:@"status"] intValue];
    switch (status)
    {
    case 1:
        {
            int errorCode = [[result objectForKey:@"__code"] intValue];
            NSString* errorMessage = [result objectForKey:@"__message"];
            NSString* errorLine = [result objectForKey:@"__line"];

            //NSLog(@"errorCode: %i", errorCode);
            //NSLog(@"errorMessage: %@", errorMessage);
            //NSLog(@"errorLine: %@", errorLine);

            _parseError(cmdName, errorCode);
        }
        break;

    case 0:
        {
            //取得返回数据
            NSObject* realData = [result objectForKey:@"data"];

            //调用解析处理
            if (cmdName == kNCGameInit)
            {
                _parseGameInit((void*)realData);
            }
            else if (cmdName == kNCRegist)
            {
                _parseRegist((void*)realData);
            }
            else if (cmdName == kNCGetSelfInfo)
            {
                _parseGetSelfInfo((void*)realData);
            }
            else if (cmdName == kNCDungeonExplore)
            {
                _parseDungeonExplore((void*)realData);
            }
            else if (cmdName == kNCDungeonStart)
            {
                _parseDungeonStart((void*)realData);
            }
            else if (cmdName == kNCLoadEquipage)
            {
                _parseLoadEquipage((void*)realData);
            }
            else if (cmdName == kNCSellEquipage)
            {
                _parseSellEquipage((void*)realData);
            }
            else if (cmdName == kNCUnloadEquipage)
            {
                _parseUnloadEquipage((void*)realData);
            }
            else if (cmdName == kNCResetEquipage)
            {
                _parseResetEquipage((void*)realData);
            }
            else if (cmdName == kNCFusionEquipage)
            {
                _parseFusionEquipage((void*)realData);
            }
            else if (cmdName == kNCIntensifyEquipage)
            {
                _parseIntensifyEquipage((void*)realData);
            }
            else if (cmdName == kNCGetChallengeList)
            {
                _parseGetChallengeList((void*)realData);
            }
            else if (cmdName == kNCChallengePlayer)
            {
                _parseChallengePlayer((void*)realData);
            }
            else if (cmdName == kNCFindChallengePlayerByName)
            {
                //_parseGetChallengeEnemyList((void*)realData);
            }
            else if (cmdName == kNCGetChallengeEnemyList)
            {
                _parseGetChallengeEnemyList((void*)realData);
            }
            else if (cmdName == kNCOpenBox)
            {
                _parseOpenBox((void*)realData);
            }
            else if (cmdName == kNCBuyEnergy)
            {
                _parseBuyEnergy((void*)realData);
            }
            else if (cmdName == kNCBuyPower)
            {
                _parseBuyPower((void*)realData);
            }
            else if (cmdName == kNCBuyLife)
            {
                _parseBuyLife((void*)realData);
            }
            else if (cmdName == kNCBuyMoney) {
                _parseBuyMoney((void*)realData);
            }
            else if (cmdName == kNCBuyCoin) {
                _parseBuyCoin((void*)realData);
            }
            else
            {
                //TODO: 解析出错
                //NSLog(@"NetController::parseData(): unknow cmdName.");
            }

            if(packageList_.count > 0)
            {
                if(cmdName != kNCRegist && cmdName != kNCGameInit && cmdName != kNCGetSelfInfo)
                    Waitting::shared()->show();
                NSArray* package = [packageList_ objectAtIndex:0];
                [[AMFCaller shared] sendPackage:package];
                [packageList_ removeObjectAtIndex:0];
            }
            else
            {
                Waitting::shared()->hide();
            }
        }
        break;

    default:
        {
            //TODO: 解析出错
            //NSLog(@"NetController::parseData(): unknow status.");
        }
        break;
    }

    //NSLog(@"NetController::parseData() end");
}

/**
 * @brief 网络错误处理函数。
 * @note  解析网络错误信息。(用于网络接口回调使用)
 */
void NetController::receiveError()
{
    //NSLog(@"NetController::receiveError() start");

    //TODO: 网络错误处理
    isWaitReceive = false;

    //NSLog(@"NetController::receiveError() end");
}

/**
 * @brief  游戏初始化命令函数。
 * @return true  成功。
 * @return false 失败。
 * @note   发送游戏初始化命令到服务器。
 */
bool NetController::gameInit()
{
    //NSLog(@"NetController::gameInit() start");
    //NSLog(@"NetController::gameInit() end");

    return _sendCommand(kNCGameInit, nil);
}

/**
 * @brief     注册命令函数。
 * @param[in] name  用户名称。
 * @param[in] avata 用户形象。
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送注册命令到服务器。
 */
bool NetController::regist(const std::string& name, const int avata)
{
    //NSLog(@"NetController::regist() start");
    //NSLog(@"NetController::regist(): name: %s", name.c_str());
    //NSLog(@"NetController::regist(): avata: %i", avata);

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                               [NSString stringWithFormat:@"%s", name.c_str()], @"name",
                               [NSNumber numberWithInt:avata], @"avata",
                               nil];

    //NSLog(@"NetController::regist() end");

    //命令发送
    return _sendCommand(kNCRegist, params);
}

/**
 * @brief  取得自己的用户信息命令函数。
 * @return true  成功。
 * @return false 失败。
 * @note   发送取得用户信息命令到服务器。
 */
bool NetController::getSelfInfo()
{
    //NSLog(@"NetController::getSelfInfo() start");
    //NSLog(@"NetController::getSelfInfo() end");

    //命令发送
    return _sendCommand(kNCGetSelfInfo, nil);
}

/**
 * @brief     地下城探险命令函数。
 * @param[in] dungeon 地下城ID。
 * @param[in] floor   地下城层级ID。(地下城中的子ID)
 * @param[in] task    地下城任务ID。(层级中的子ID)
 * @return    true    成功。
 * @return    false   失败。
 * @note      发送地下城探险命令到服务器。
 */
bool NetController::dungeonExplore(int dungeon, int floor, int task)
{
    //NSLog(@"NetController::dungeonExplore() start");
    //NSLog(@"NetController::dungeonExplore(): dungeon: %i", dungeon);
    //NSLog(@"NetController::dungeonExplore(): floor: %i", floor);
    //NSLog(@"NetController::dungeonExplore(): task: %i", task);

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                               [NSNumber numberWithInt:dungeon], @"dungeon",
                               [NSNumber numberWithInt:floor], @"floor",
                               [NSNumber numberWithInt:task], @"task",
                               nil];

    //NSLog(@"NetController::dungeonExplore() end");

    //命令发送
    return _sendCommand(kNCDungeonExplore, params);
}

/**
 * @brief     地下开始重置险命令函数。
 * @param[in] dungeon 地下城ID。
 * @param[in] floor   地下城层级ID。(地下城中的子ID)
 * @return    true    成功。
 * @return    false   失败。
 * @note      发送地下城探险命令到服务器。
 */
bool NetController::dungeonStart(int dungeon, int floor)
{
    //NSLog(@"NetController::dungeonStart() start");
    //NSLog(@"NetController::dungeonStart(): dungeon: %i", dungeon);
    //NSLog(@"NetController::dungeonStart(): floor: %i", floor);

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                               [NSNumber numberWithInt:dungeon], @"dungeon",
                               [NSNumber numberWithInt:floor], @"floor",
                               nil];

    //NSLog(@"NetController::dungeonStart() end");

    //命令发送
    return _sendCommand(kNCDungeonStart, params);
}

/**
 * @brief     加载装备命令函数。
 * @param[in] index 装备在用户背包中的索引。
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送加载装备命令到服务器。
 */
bool NetController::loadEquipage(int index)
{
    //NSLog(@"NetController::loadEquipage() start");
    //NSLog(@"NetController::loadEquipage(): index: %i", index);
    
    ItemProxy::shared()->putonIndex = index;

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                               [NSNumber numberWithInt:index], @"index",
                               nil];

    //NSLog(@"NetController::loadEquipage() end");

    //命令发送
    return _sendCommand(kNCLoadEquipage, params);
}

/**
 * @brief     卸载装备命令函数。
 * @param[in] index 装备在用户背包中的索引。
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送卸载装备命令到服务器。
 */
bool NetController::unloadEquipage(int index)
{
    //NSLog(@"NetController::unloadEquipage() start");
    //NSLog(@"NetController::unloadEquipage(): index: %i", index);

    ItemProxy::shared()->putonIndex = index;
    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                               [NSNumber numberWithInt:index], @"index",
                               nil];

    //NSLog(@"NetController::unloadEquipage() end");

    //命令发送
    return _sendCommand(kNCUnloadEquipage, params);
}

/**
 * @brief     贩卖装备命令函数。
 * @param[in] index 装备在用户背包中的索引。
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送贩卖装备命令到服务器。
 */
bool NetController::sellEquipage(std::vector<int>& indexArray)
{
    //NSLog(@"NetController::sellEquipage() start");

    //转换装备在用户背包中的索引数组
    NSMutableArray* indexList = [[NSMutableArray alloc] init];

    for (std::vector<int>::iterator itr=indexArray.begin(); itr!=indexArray.end(); itr++)
    {
        int index = *itr;
        [indexList addObject:[NSNumber numberWithInt:index]];
    }

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                               indexList, @"index",
                               nil];

    //NSLog(@"NetController::sellEquipage() end");

    //命令发送
    return _sendCommand(kNCSellEquipage, params);
}


/**
 * @brief     洗练装备命令函数。
 * @param[in] index 装备在用户背包中的索引。
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送洗练装备命令到服务器。
 */
bool NetController::resetEquipage(int index)
{
    //NSLog(@"NetController::resetEquipage() start");
    //NSLog(@"NetController::resetEquipage(): index: %i", index);

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                               [NSNumber numberWithInt:index], @"index",
                               nil];

    //NSLog(@"NetController::resetEquipage() end");

    //命令发送
    return _sendCommand(kNCResetEquipage, params);
}

/**
 * @brief     熔炼装备命令函数。
 * @param[in] indexArray 装备在用户背包中的索引数组。
 * @return    true       成功。
 * @return    false      失败。
 * @note      发送熔炼装备命令到服务器。
 */
bool NetController::fusionEquipage(std::vector<int>& indexArray)
{
    //NSLog(@"NetController::fusionEquipage() start");

    //转换装备在用户背包中的索引数组
    NSMutableArray* indexList = [[NSMutableArray alloc] init];

    for (std::vector<int>::iterator itr=indexArray.begin(); itr!=indexArray.end(); itr++)
    {
        int index = *itr;
        [indexList addObject:[NSNumber numberWithInt:index]];
        //NSLog(@"NetController::intensifyEquipage(): index: %i", index);
    }

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                               indexList, @"index",
                               nil];

    //NSLog(@"NetController::fusionEquipage() end");

    //命令发送
    return _sendCommand(kNCFusionEquipage, params);
}

/**
 * @brief     强化装备命令函数。
 * @param[in] index  装备在用户背包中的索引。
 * @param[in] number 助溶剂数量。
 * @return    true   成功。
 * @return    false  失败。
 * @note      发送熔炼装备命令到服务器。
 */
bool NetController::intensifyEquipage(int index, int number)
{
    //NSLog(@"NetController::intensifyEquipage() start");
    //NSLog(@"NetController::intensifyEquipage(): index: %i", index);
    //NSLog(@"NetController::intensifyEquipage(): number: %i", number);

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                               [NSNumber numberWithInt:index], @"index",
                               [NSNumber numberWithInt:number], @"number",
                               nil];

    //NSLog(@"NetController::intensifyEquipage() end");

    //命令发送
    return _sendCommand(kNCIntensifyEquipage, params);
}

/**
 * @brief     搜素需要挑战的玩家命令函数
 * @param[in] name  需要挑战的玩家名称。
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送搜素需要挑战的玩家命令到服务器。
 */
bool NetController::findChallengePlayerByName(const std::string& name)
{
    //NSLog(@"NetController::findChallengePlayer() start");
    //NSLog(@"NetController::findChallengePlayer(): name: %s", name.c_str());

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                            [NSString stringWithFormat:@"%s", name.c_str()], @"name",
                            nil];

    //NSLog(@"NetController::findChallengePlayer() end");
    
    //命令发送
    return _sendCommand(kNCFindChallengePlayerByName, params);
}

/**
 * @brief  获取挑战玩家列表命令函数。
 * @return true  成功。
 * @return false 失败。
 * @note   发送请求挑战玩家列表命令到服务器。
 */
bool NetController::getChallengeList()
{
    //NSLog(@"NetController::getChallengeList() start");

    //NSLog(@"NetController::getChallengeList() end");

    //命令发送
    return _sendCommand(kNCGetChallengeList, nil);
}

/**
 * @brief  请求宿敌列表命令函数。
 * @return true  成功。
 * @return false 失败。
 * @note   发送请求宿敌列表命令到服务器。
 */
bool NetController::getChallengeEnemyList()
{
    //NSLog(@"NetController::getGetChallengeEnemyList() start");

    //NSLog(@"NetController::getGetChallengeEnemyList() end");

    //命令发送
    return _sendCommand(kNCGetChallengeEnemyList, nil);
}

/**
 * @brief     挑战玩家命令函数。
 * @param[in] gid  对手的gid。
 * @note      发送挑战对手命令到服务器。
 */
bool NetController::challengePlayer(const int gid)
{
    //NSLog(@"NetController::challengePlayer() start");
    //NSLog(@"NetController::challengePlayer(): gid: %i", gid);

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                            [NSNumber numberWithInt:gid], @"gid",
                            nil];

    //NSLog(@"NetController::challengePlayer() end");

    //命令发送
    return _sendCommand(kNCChallengePlayer, params);
}

/**
 * @brief     开宝箱命令函数。
 * @param[in] type  开宝箱的形式。(0:免费;1:游戏币;2:付费币)
 * @param[in] id    宝箱的id。
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送开宝箱命令到服务器。
 */
bool NetController::openBox(int type, const int id)
{
    //NSLog(@"NetController::openBox() start");
    //NSLog(@"NetController::openBox(): id: %i", id);
    //NSLog(@"NetController::openBox(): type: %i", type);

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                            [NSNumber numberWithInt:id], @"id",
                            [NSNumber numberWithInt:type], @"type",
                            nil];

    //NSLog(@"NetController::openBox() end");

    //命令发送
    return _sendCommand(kNCOpenBox, params);
}

/**
 * @brief     购买(补充)能量命令函数。
 * @param[in] type  购买(补充)能量的形式。(0:免费;1:游戏币;2:付费币)
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送购买(补充)能量命令到服务器。
 */
bool NetController::buyEnergy(int type)
{
    //NSLog(@"NetController::buyEnergy() start");
    //NSLog(@"NetController::buyEnergy(): type: %i", type);

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                            [NSNumber numberWithInt:type], @"type",
                            nil];

    //NSLog(@"NetController::buyEnergy() end");

    //命令发送
    return _sendCommand(kNCBuyEnergy, params);
}

/**
 * @brief     购买(补充)体力命令函数。
 * @param[in] type  购买(补充)体力的形式。(0:免费;1:游戏币;2:付费币)
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送购买(补充)体力命令到服务器。
 */
bool NetController::buyPower(int type)
{
    //NSLog(@"NetController::buyPower() start");
    //NSLog(@"NetController::buyPower(): type: %i", type);

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                            [NSNumber numberWithInt:type], @"type",
                            nil];

    //NSLog(@"NetController::buyPower() end");

    //命令发送
    return _sendCommand(kNCBuyPower, params);
}

/**
 * @brief     购买(补充)生命命令函数。
 * @param[in] type  购买(补充)体力的形式。(0:免费;1:游戏币;2:付费币)
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送购买(补充)体力命令到服务器。
 */
bool NetController::buyLife(int type)
{
    //NSLog(@"NetController::buyLife() start");
    //NSLog(@"NetController::buyLife(): type: %i", type);

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                            [NSNumber numberWithInt:type], @"type",
                            nil];

    //NSLog(@"NetController::buyLife() end");

    //命令发送
    return _sendCommand(kNCBuyLife, params);
}

bool NetController::buyCoin(int id)
{
    //NSLog(@"NetController::buyCoin() start");
    //NSLog(@"NetController::buyCoin(): id: %i", id);
    
    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                            [NSNumber numberWithInt:id], @"id",
                            nil];
    
    //NSLog(@"NetController::buyCoin() end");
    
    //命令发送
    return _sendCommand(kNCBuyCoin, params);
}

bool NetController::snatchPlayer(const int pid, int itemID)
{
    return true;
}

bool NetController::composeEquipage(int itemID)
{
    return true;
}

bool NetController::getComposeEquipageList()
{
    return true;
}

bool NetController::getAmuletEnemyList()
{
    return true;
}

bool NetController::getFragmentEnemyList(int itemID)
{
    return true;
}

/**
 * @brief     发送网络命令函数。
 * @param[in] cmd   命令名称。
 * @param[in] data  命令数据。
 * @return    true  成功。
 * @return    false 失败。
 * @note      发送网络命令到服务器。(对外发布的命令发送接口的共同私有接口)
 */
bool NetController::_sendCommand(const string& cmd, void* params)
{
    //NSLog(@"NetController::_sendCommand() start");

    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    bool result = false;

    //TODO: 测试程序 start
//    mGid = 2;
    //TODO: 测试程序 end

    if ((mPlatform != -1)
        || (mGid != -1))
    {
        //命令组装
        NSString* command = [NSString stringWithFormat:@"%s", cmd.c_str()];
        NSDictionary* cmdParams = (NSDictionary*)params;
        NSDictionary* dataItem;
        //命令以及参数进行组合
        if (cmdParams != nil)
        {
            dataItem = [NSDictionary dictionaryWithObjectsAndKeys:
                           command, @"cmd",
                           params, @"params",
                           nil];
        }
        else
        {
            dataItem = [NSDictionary dictionaryWithObjectsAndKeys:
                           command, @"cmd",
                           nil];
        }
        NSArray* data = [NSArray arrayWithObject:dataItem];
        NSDictionary* arguments = [NSDictionary dictionaryWithObjectsAndKeys:
                                      data, @"data",
                                      [NSString stringWithFormat:@"%s", mPid.c_str()], @"pid",
                                      [NSString stringWithFormat:@"%s", mVersion.c_str()], @"version",
                                      [NSNumber numberWithInt:mGid], @"gid",
                                      [NSNumber numberWithInt:mPlatform], @"platform",
                                      nil];
        NSArray* package = [NSArray arrayWithObject:arguments];
        
        if(isWaitReceive)
        {
            [packageList_ addObject:package];
        }
        else
        {
            //发送命令
            if(cmd != kNCRegist && cmd != kNCGameInit && cmd != kNCGetSelfInfo)
                Waitting::shared()->show();
            isWaitReceive = true;
            [[AMFCaller shared] sendPackage:package];
        }

        result = true;
    }

    [pool release];

    //NSLog(@"NetController::_sendCommand() end");

    return result;
}

/**
 * @brief      服务器处理错误函数。
 * @param[in]  cmdName 命令。
 * @param[out] error   错误代码。
 */
void NetController::_parseError(std::string cmdName, int error)
{
    //NSLog(@"NetController::_parseError() start");

    Waitting::shared()->hide();

    if (cmdName == kNCGameInit)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCRegist)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorRegist:
            //TODO: 注册错误
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCGetSelfInfo)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGetSelfInfo:
            //TODO: 取得自己信息错误
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCDungeonExplore)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorReadXML:
            //TODO: 服务器读取xml错误
            break;
        case kNCErrorEnergy:
            //TODO: 玩家能量不足
            break;
        case kNCErrorLife:
            //TODO: 玩家生命不足
            break;
        case kNCErrorSystem:
            //TODO: 服务器系统错误
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCDungeonStart)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorResetDungeonInfo:
            //TODO: 初始化地下城信息失败
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCLoadEquipage)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorReadXML:
            //TODO: 服务器读取xml错误
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCSellEquipage)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorReadXML:
            //TODO: 服务器读取xml错误
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCUnloadEquipage)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorReadXML:
            //TODO: 服务器读取xml错误
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCResetEquipage)
    {

    }
    else if (cmdName == kNCFusionEquipage)
    {

    }
    else if (cmdName == kNCIntensifyEquipage)
    {

    }
    else if (cmdName == kNCGetChallengeList)
    {

    }
    else if (cmdName == kNCChallengePlayer)
    {

    }
    else if (cmdName == kNCFindChallengePlayerByName)
    {

    }
    else if (cmdName == kNCGetChallengeEnemyList)
    {

    }
    else if (cmdName == kNCOpenBox)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorReadXML:
            //TODO: 服务器读取xml错误
            break;
        case kNCErrorCoin:
            //TODO: 玩家游戏币不足
            break;
        case kNCErrorFreeTime:
            //TODO: 玩家免费机会不足
            break;
        case kNCErrorCoinTime:
            //TODO: 玩家游戏币机会不足
            break;
        case kNCErrorMoneyTime:
            //TODO: 玩家付费币机会不足
            break;
        case kNCErrorMoney:
            //TODO: 玩家付费币不足
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCBuyEnergy)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorReadXML:
            //TODO: 服务器读取xml错误
            break;
        case kNCErrorCoin:
            //TODO: 玩家游戏币不足
            break;
        case kNCErrorFreeTime:
            //TODO: 玩家免费机会不足
            break;
        case kNCErrorCoinTime:
            //TODO: 玩家游戏币机会不足
            break;
        case kNCErrorMoneyTime:
            //TODO: 玩家付费币机会不足
            break;
        case kNCErrorMoney:
            //TODO: 玩家付费币不足
            break;
        case kNCErrorEnergyFull:
            //TODO: 玩家能量已满
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCBuyPower)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorReadXML:
            //TODO: 服务器读取xml错误
            break;
        case kNCErrorCoin:
            //TODO: 玩家游戏币不足
            break;
        case kNCErrorFreeTime:
            //TODO: 玩家免费机会不足
            break;
        case kNCErrorCoinTime:
            //TODO: 玩家游戏币机会不足
            break;
        case kNCErrorMoneyTime:
            //TODO: 玩家付费币机会不足
            break;
        case kNCErrorMoney:
            //TODO: 玩家付费币不足
            break;
        case kNCErrorPowerFull:
            //TODO: 玩家体力已满
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCBuyLife)
    {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorReadXML:
            //TODO: 服务器读取xml错误
            break;
        case kNCErrorCoin:
            //TODO: 玩家游戏币不足
            break;
        case kNCErrorFreeTime:
            //TODO: 玩家免费机会不足
            break;
        case kNCErrorCoinTime:
            //TODO: 玩家游戏币机会不足
            break;
        case kNCErrorMoneyTime:
            //TODO: 玩家付费币机会不足
            break;
        case kNCErrorMoney:
            //TODO: 玩家付费币不足
            break;
        case kNCErrorLifeFull:
            //TODO: 玩家生命已满
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCBuyMoney) {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorDollar:
            //TODO: 玩家美金不足
            break;
        case kNCErrorReceipt:
            //TODO: 玩家花费验证码错误
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else if (cmdName == kNCBuyCoin) {
        switch (error)
        {
        case kNCErrorPID:
            //TODO: PID错误
            break;
        case kNCErrorPlatform:
            //TODO: Platform错误
            break;
        case kNCErrorGID:
            //TODO: GID错误
            break;
        case kNCErrorParams:
            //TODO: 参数错误
            break;
        case kNCErrorGetInfo:
            //TODO: 取得信息错误
            break;
        case kNCErrorMoney:
            //TODO: 玩家付费币不足
            break;
        default:
            //NSLog(@"NetController::_parseError(): %s: unknow error id(%d)!", cmdName.c_str(), error);
            break;
        }
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::parseData(): unknow cmdName.");
    }


    //NSLog(@"NetController::_parseError() start");
    NetError netError;
    netError.cmdName = cmdName;
    netError.errorCode = error;
    Post_Net_Notification(kNCNetError, (CCObject*)(&netError));
}

/**
 * @brief     游戏初始化命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseGameInit(void* params)
{
    //NSLog(@"NetController::_parseGameInit() start");

    CCObject* postData;

    NSDictionary* data = (NSDictionary*)params;
    if (data != nil)
    {
        //取得用户状态
        NSNumber* result = [data objectForKey:@"result"];
        int initResult = [result intValue];
        switch (initResult)
        {
        case 1:
            //玩家帐户已经存在
            break;
        case 2:
            //玩家账户不存在
            break;
        default:
            //NSLog(@"NetController::_parseGameInit(): unknow result!");
            break;
        }

        NSString* notice = [data objectForKey:@"notice"];
        if ((notice != nil)
            && (![notice isEqual:[NSNull null]])
            && (![notice isEqual:@""]))
        {
            //有网页通知
            std::string noticeUrl = [notice UTF8String];
            noticeUrl += "/";
            //NSLog(@"noticeUrl config:%s", noticeUrl.c_str());
            UserProxy::shared()->mHtmlUrl = noticeUrl + "html/notice.html";
        }
        else {
            //无网页通知
        }

        NSString* config = [data objectForKey:@"config"];
        std::string configUrl = [config UTF8String];
        configUrl += "/";
        //NSLog(@"configUrl config:%s", configUrl.c_str());
        UserProxy::shared()->mServerUrl = configUrl;
        UserProxy::shared()->mConfigUrl = configUrl + "config/";
        UserProxy::shared()->mResourceUrl = configUrl + "sprite/";

        NSDictionary* version = [data objectForKey:@"version"];
        if ((version != nil)
            && (![version isEqual:[NSNull null]])
            && (![version isEqual:@""]))
        {
            NSString* bossVersion = [version objectForKey:@"Boss"];
            NSString* boxVersion = [version objectForKey:@"Box"];
            NSString* buyMoneyVersion = [version objectForKey:@"BuyMoney"];
            NSString* composeVersion = [version objectForKey:@"Compose"];
            NSString* dropVersion = [version objectForKey:@"Drop"];
            NSString* dungeonVersion = [version objectForKey:@"Dungeon"];
            NSString* equipageVersion = [version objectForKey:@"Equipage"];
            NSString* eventVersion = [version objectForKey:@"Event"];
            NSString* localStringVersion = [version objectForKey:@"LocalString"];
            NSString* playerVersion = [version objectForKey:@"Player"];
            NSString* ruleVersion = [version objectForKey:@"Rule"];
            NSString* supplementVersion = [version objectForKey:@"Supplement"];
            NSString* taskVersion = [version objectForKey:@"Task"];

            XMLVersionMap& xmlVersionMap = UserProxy::shared()->mXMLVersionMap;
            xmlVersionMap["Boss.xml"] = [bossVersion UTF8String];
            xmlVersionMap["Box.xml"] = [boxVersion UTF8String];
            xmlVersionMap["BuyMoney.xml"] = [buyMoneyVersion UTF8String];
            xmlVersionMap["Compose.xml"] = [composeVersion UTF8String];
            xmlVersionMap["Drop.xml"] = [dropVersion UTF8String];
            xmlVersionMap["Dungeon.xml"] = [dungeonVersion UTF8String];
            xmlVersionMap["Equipage.xml"] = [equipageVersion UTF8String];
            xmlVersionMap["Event.xml"] = [eventVersion UTF8String];
            xmlVersionMap["LocalString.xml"] = [localStringVersion UTF8String];
            xmlVersionMap["Player.xml"] = [playerVersion UTF8String];
            xmlVersionMap["Rule.xml"] = [ruleVersion UTF8String];
            xmlVersionMap["Supplement.xml"] = [supplementVersion UTF8String];
            xmlVersionMap["Task.xml"] = [taskVersion UTF8String];
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseGameInit(): version is null.");
        }

        Post_Net_Notification(kNCGameInit, (CCObject*)initResult);
    }

    //NSLog(@"NetController::_parseGameInit() end");
}

/**
 * @brief     注册命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseRegist(void* params)
{
    //NSLog(@"NetController::_parseRegist() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        _parseSelfInfo(data);
        Post_Net_Notification(kNCRegist, NULL);
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseRegist(): data is null.");
    }

    //NSLog(@"NetController::_parseRegist() end");
}

/**
 * @brief     取得用户信息命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseGetSelfInfo(void* params)
{
    //NSLog(@"NetController::_parseGetSelfInfo() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        _parseSelfInfo(data);
        Post_Net_Notification(kNCGetSelfInfo, NULL);
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseGetSelfInfo(): data is null.");
    }

    //NSLog(@"NetController::_parseGetSelfInfo() end");
}

/**
 * @brief     地下城探险命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseDungeonExplore(void* params)
{
    //NSLog(@"NetController::_parseDungeonExplore() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        //探险成功
        NSDictionary* taskInfo = [data objectForKey:@"task"];
        if ((taskInfo != nil)
            && (![taskInfo isEqual:[NSNull null]])
            && (![taskInfo isEqual:@""]))
        {
            NSNumber* dungeon = [taskInfo objectForKey:@"dungeon"];
            DungeonsProxy::shared()->curTaskInfo.dungeonID = [dungeon intValue];
            DungeonsProxy::shared()->maxTaskInfo.dungeonID = [dungeon intValue];

            //NSLog(@"dungeon: %@", dungeon);

            NSArray* taskCur = [taskInfo objectForKey:@"taskCur"];
            if ((taskCur != nil)
                && (![taskCur isEqual:[NSNull null]])
                && (![taskCur isEqual:@""]))
            {
                _parseTaskInfo(taskCur,&(DungeonsProxy::shared()->curTaskInfo));
            }
            else
            {
                //TODO: 解析出错
                //NSLog(@"NetController::_parseDungeonExplore(): taskCur is null.");
            }

            //NSLog(@"taskCur: %@", taskCur);

            NSArray* taskMax = [taskInfo objectForKey:@"taskMax"];
            if ((taskMax != nil)
                && (![taskMax isEqual:[NSNull null]])
                && (![taskMax isEqual:@""]))
            {
                _parseTaskInfo(taskMax, &(DungeonsProxy::shared()->maxTaskInfo));
            }
            else{
                //TODO: 解析出错
                //NSLog(@"NetController::_parseDungeonExplore(): taskMax is null.");
            }

            //NSLog(@"taskMax: %@", taskMax);
        }
        else
        {
            //NSLog(@"NetController::_parseDungeonExplore(): taskInfo is null.");
        }

        FightProxy::shared()->awardInfo.clear();
        NSDictionary* awardInfo = [data objectForKey:@"award"];
        if ((awardInfo != nil)
            && (![awardInfo isEqual:[NSNull null]])
            && (![awardInfo isEqual:@""]))
        {
            //NSLog(@"awardInfo: %@", awardInfo);
            //固定奖励
            NSNumber* exp = [awardInfo objectForKey:@"exp"];
            NSNumber* coin = [awardInfo objectForKey:@"coin"];
            NSNumber* bagFull = [awardInfo objectForKey:@"bagFull"];

            Award& award = FightProxy::shared()->awardInfo;
            award.clear();
            award.exp = [exp intValue];
            award.coin = [coin intValue];

            award.eventType = EVENT_TYPE_NONE;
            //事件奖励
            NSString* eventType = [awardInfo objectForKey:@"eventType"];
            if ((eventType != nil)
                && (![eventType isEqual:[NSNull null]])
                && (![eventType isEqual:@""]))
            {
                string eventTypeString = [eventType UTF8String];
                if (eventTypeString == "none")
                {
                    //没有事件发生
                    award.eventType = EVENT_TYPE_NONE;
                }
                else if (eventTypeString == "coin")
                {
                    //金币掉落事件发生
                    NSNumber* eventCoin = [awardInfo objectForKey:@"eventValue"];
                    award.eventCoin = [eventCoin intValue];
                    award.eventType = EVENT_TYPE_GET_COIN;
                }
                else if (eventTypeString == "energy")
                {
                    //能量掉落事件发生
                    NSNumber* eventEnergy = [awardInfo objectForKey:@"eventValue"];
                    award.energy = [eventEnergy intValue];
                    award.eventType = EVENT_TYPE_GET_ENERGY;
                }
                else if (eventTypeString == "life")
                {
                    //能量掉落事件发生
                    NSNumber* eventLife = [awardInfo objectForKey:@"eventValue"];
                    award.life = [eventLife intValue];
                    award.eventType = EVENT_TYPE_LOST_LIFE;
                }
                else if (eventTypeString == "drop")
                {
                    if (!ItemProxy::shared()->isBagFull()) 
                    {
                        //装备掉落事件发生
                        NSArray* eventEquipageArray = [awardInfo objectForKey:@"eventValue"];
                        if ((eventEquipageArray != nil)
                            && (![eventEquipageArray isEqual:[NSNull null]])
                            && (![eventEquipageArray isEqual:@""]))
                        {
                            //NSLog(@"eventEquipageArray: %@", eventEquipageArray);
                            award.eventType = EVENT_TYPE_GET_EQUIP;
                            int count = [eventEquipageArray count];
                            for (int i=0; i<count; i++)
                            {
                                NSArray* equipage = [eventEquipageArray objectAtIndex:i];
                                if ((equipage != nil)
                                    && (![equipage isEqual:[NSNull null]])
                                    && (![equipage isEqual:@""]))
                                {
                                    //TODO: 波波确认
                                    EquipInfo* equipInfo = new EquipInfo();
                                    _parseEquipageInfo(equipage, equipInfo);
                                    ItemProxy::shared()->addEquip(equipInfo);
                                    award.equipList.push_back(equipInfo);
                                }
                                else
                                {
                                    //TODO: 解析出错
                                    //NSLog(@"NetController::_parseDungeonExplore(): equipage[%i] is null.", i);
                                }
                            }
                        }
                        else {
                            
                        }
                    }
                    else
                    {
                        //TODO: 背包已经满了
                        NetError netError;
                        netError.cmdName = kNCNetError;
                        netError.errorCode = kNCErrorBagFull;
                        Post_Net_Notification(kNCNetError, (CCObject*)(&netError));
                    }
                }
            }

            //掉落奖励
            NSArray* equipageArray = [awardInfo objectForKey:@"equipage"];
            if ((equipageArray != nil)
                && (![equipageArray isEqual:[NSNull null]])
                && (![equipageArray isEqual:@""]))
            {
                //NSLog(@"equipageArray: %@", equipageArray);

                if (!ItemProxy::shared()->isBagFull()) {
                    int count = [equipageArray count];
                    for (int i=0; i<count; i++)
                    {
                        NSArray* equipage = [equipageArray objectAtIndex:i];
                        if ((equipage != nil)
                            && (![equipage isEqual:[NSNull null]])
                            && (![equipage isEqual:@""]))
                        {
                            EquipInfo* equipInfo = new EquipInfo();
                            _parseEquipageInfo(equipage, equipInfo);
                            ItemProxy::shared()->addEquip(equipInfo);
                            award.equipList.push_back(equipInfo);
                        }
                        else
                        {
                            //TODO: 解析出错
                            //NSLog(@"NetController::_parseDungeonExplore(): equipage[%i] is null.", i);
                        }
                    }
                }
                else {
                    //TODO: 背包已经满了
                    NetError netError;
                    netError.cmdName = kNCNetError;
                    netError.errorCode = kNCErrorBagFull;
                    Post_Net_Notification(kNCNetError, (CCObject*)(&netError));
                }
            }
            else
            {
                //TODO: 解析出错
                //NSLog(@"NetController::_parseDungeonExplore(): equipageArray is null.");
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseDungeonExplore(): awardInfo is null.");
        }

        FightProxy::shared()->battleInfo.win = 0;
        NSDictionary* battleInfo = [data objectForKey:@"battle"];
        if ((battleInfo != nil)
            && (![battleInfo isEqual:[NSNull null]])
            && (![battleInfo isEqual:@""]))
        {
            NSDictionary* bossInfo = [battleInfo objectForKey:@"boss"];
            if ((bossInfo != nil)
                && (![bossInfo isEqual:[NSNull null]])
                && (![bossInfo isEqual:@""]))
            {
                NSNumber* bossLevel = [bossInfo objectForKey:@"level"];
                NSNumber* bossLife = [bossInfo objectForKey:@"life"];
                NSNumber* bossAtkMin = [bossInfo objectForKey:@"atkMin"];
                NSNumber* bossAtkMax = [bossInfo objectForKey:@"atkMax"];
                NSNumber* bossDefMin = [bossInfo objectForKey:@"defMin"];
                NSNumber* bossDefMax = [bossInfo objectForKey:@"defMax"];
                
                FightBoss& fightBoss = FightProxy::shared()->mFightBoss;
                fightBoss.level = [bossLevel intValue];
                fightBoss.life = [bossLife intValue];
                fightBoss.atkMin= [bossAtkMin intValue];
                fightBoss.atkMax = [bossAtkMax intValue];
                fightBoss.defMin = [bossDefMin intValue];
                fightBoss.defMax = [bossDefMax intValue];
            }
            else {
                //NSLog(@"NetController::_parseDungeonExplore(): bossInfo is null.");
            }

            NSArray* roundInfo = [battleInfo objectForKey:@"round"];
            if ((roundInfo != nil)
                && (![roundInfo isEqual:[NSNull null]])
                && (![roundInfo isEqual:@""]))
            {
                int count = [roundInfo count];
                for (int i=0; i<count; i++)
                {
                    NSArray* round = [roundInfo objectAtIndex:i];
                    if ((round != nil)
                        && (![round isEqual:[NSNull null]])
                        && (![round isEqual:@""]))
                    {
                        NSNumber* atkUsr = [round objectAtIndex:0];  //1: 玩家为攻击方, 2: boss为攻击方
                        NSNumber* atkMax = [round objectAtIndex:1];  //是否发生了最大攻击 1: 发生了最大攻击力， 0：没发生最大攻击力
                        NSNumber* defMax = [round objectAtIndex:2];  //是否发生了最大防御 1: 发生了最大防御力， 0：没发生最大防御力
                        NSNumber* life = [round objectAtIndex:3];    //攻击对于life造成的伤害
                    }
                    else {
                        //NSLog(@"NetController::_parseDungeonExplore(): round is null.");
                    }
                }
            }
            else {
                //NSLog(@"NetController::_parseDungeonExplore(): roundInfo is null.");
            }

            NSNumber* win = [battleInfo objectForKey:@"win"];  //1: 玩家为获胜方, 2: boss为获胜方
            FightProxy::shared()->battleInfo.win = [win intValue];
        }
        else
        {
            //NSLog(@"NetController::_parseDungeonExplore(): battleInfo is null.");
        }

        NSDictionary* synchro = [data objectForKey:@"synchro"];
        if ((synchro != nil)
            && (![synchro isEqual:[NSNull null]])
            && (![synchro isEqual:@""]))
        {
            _parseLevelInfo(synchro);
        }
        else
        {
            //NSLog(@"NetController::_parseDungeonExplore(): awardInfo is null.");
        }

        NSNumber* remainderRechargingEnergyTime = [data objectForKey:@"remainderRechargingEnergyTime"];

        UserProxy::shared()->userVO.energyTime = [remainderRechargingEnergyTime intValue] * 1000;

    }

    //NSLog(@"NetController::_parseDungeonExplore() end");
    Post_Net_Notification(kNCDungeonExplore, NULL);
}

/**
 * @brief     地下城开始重置命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseDungeonStart(void* params)
{
    //NSLog(@"NetController::_parseDungeonStart() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        /**
         *任务信息
         */
        //当前任务信息。
        NSDictionary* taskCur = [data objectForKey:@"taskCur"];
        if ((taskCur != nil)
            && (![taskCur isEqual:[NSNull null]])
            && (![taskCur isEqual:@""]))
        {
            NSArray* keys = [taskCur allKeys];
            for (int i=0; i<[keys count]; i++)
            {
                NSNumber* key = [keys objectAtIndex:i];
                NSArray* taskInfo = [taskCur objectForKey:key];

                //TODO: 需要客户端修改
                DungeonsProxy::shared()->curTaskInfo.dungeonID = [key intValue];
                _parseTaskInfo(taskInfo, &(DungeonsProxy::shared()->curTaskInfo));
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseDungeonStart(): taskCur is null.");
        }

        /**
         *玩家当前生命数值
         */
        NSNumber* lifeCur = [data objectForKey:@"lifeCur"];
        NSNumber* life = [data objectForKey:@"life"];
        UserProxy::shared()->userVO.lifeCur = [lifeCur intValue];
        UserProxy::shared()->userVO.life = [life intValue];
        //TODO: 玩家当前生命数值
    }

    //NSLog(@"NetController::_parseDungeonStart() end");
    Post_Net_Notification(kNCDungeonStart, NULL);
}

/**
 * @brief     装载装备命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseLoadEquipage(void* params)
{
    //NSLog(@"NetController::_parseLoadEquipage() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSNumber* result = [data objectForKey:@"result"];
        if ((result != nil)
            && (![result isEqual:[NSNull null]])
            && (![result isEqual:@""]))
        {
            if ([result intValue] == 1)
            {
                //装备成功
                ItemProxy::shared()->putOnEquip(ItemProxy::shared()->putonIndex);
                NSDictionary* player = [data objectForKey:@"player"];
                _syncEquipInfo(player);
            }
            else
            {
                //TODO: 解析出错
                //NSLog(@"NetController::_parseLoadEquipage(): unknow result.");
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseLoadEquipage(): data is null.");
        }
       
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseLoadEquipage(): data is null.");
    }

    //NSLog(@"NetController::_parseLoadEquipage() end");
    Post_Net_Notification(kNCLoadEquipage, NULL);
}

/**
 * @brief     卸载装备命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseUnloadEquipage(void* params)
{
    //NSLog(@"NetController::_parseUnloadEquipage() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSNumber* result = [data objectForKey:@"result"];
        if ((result != nil)
            && (![result isEqual:[NSNull null]])
            && (![result isEqual:@""]))
        {
            if ([result intValue] == 1)
            {
                //卸载成功
                ItemProxy::shared()->takeOffEquip(ItemProxy::shared()->putonIndex);
                NSDictionary* player = [data objectForKey:@"player"];
                _syncEquipInfo(player);
            }
            else
            {
                //TODO: 解析出错
                //NSLog(@"NetController::_parseUnloadEquipage(): unknow result.");
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseUnloadEquipage(): data is null.");
        }
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseUnloadEquipage(): data is null.");
    }

    //NSLog(@"NetController::_parseUnloadEquipage() end");
    Post_Net_Notification(kNCUnloadEquipage, NULL);
}

/**
 * @brief     贩卖装备命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseSellEquipage(void* params)
{
    //NSLog(@"NetController::_parseSellEquipage() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSNumber* coin = [data objectForKey:@"coin"];
        UserProxy::shared()->userVO.coin = [coin intValue];
        vector<int>& sellList = ItemProxy::shared()->sellList;
        ItemProxy::shared()->sellItem(sellList);
        sellList.clear();
        
        //TODO: 孙波确认
//        _parseSelfInfo(data);
        NSDictionary* player = [data objectForKey:@"player"];
        _syncEquipInfo(player);
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseUnloadEquipage(): data is null.");
    }

    //NSLog(@"NetController::_parseSellEquipage() end");
    Post_Net_Notification(kNCSellEquipage, NULL);
}

/**
 * @brief     洗练装备命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseResetEquipage(void* params)
{
    //NSLog(@"NetController::_parseResetEquipage() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSArray* equipage = [data objectForKey:@"equipage"];
        if ((equipage != nil)
            && (![equipage isEqual:[NSNull null]])
            && (![equipage isEqual:@""]))
        {
            EquipInfo equipInfo;
            _parseEquipageInfo(equipage, &equipInfo);
            ItemProxy::shared()->addEquip(&equipInfo);
            ItemProxy::shared()->setLastQiangHuaEquip(ItemProxy::shared()->getEquip(equipInfo.index));
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseResetEquipage(): equipage[%@] is null.");
        }
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseResetEquipage(): data is null.");
    }

    //NSLog(@"NetController::_parseResetEquipage() end");
    Post_Net_Notification(kNCResetEquipage, NULL);
}

/**
 * @brief     熔炼装备命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseFusionEquipage(void* params)
{
    //NSLog(@"NetController::_parseFusionEquipage() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSNumber* fusion = [data objectForKey:@"fusion"];
        vector<int>& items = ItemProxy::shared()->mSelectList;
        for(int i = 0; i < items.size(); i++)
            ItemProxy::shared()->removeEquip(items[i]);
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseFusionEquipage(): data is null.");
    }

    //NSLog(@"NetController::_parseFusionEquipage() end");
    Post_Net_Notification(kNCFusionEquipage, NULL);
}

/**
 * @brief     强化装备命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseIntensifyEquipage(void* params)
{
    //NSLog(@"NetController::_parseIntensifyEquipage() start");


    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSNumber* coin = [data objectForKey:@"coin"];
        NSNumber* energyCur = [data objectForKey:@"energyCur"];
        NSNumber* fusion = [data objectForKey:@"fusion"];
        UserVO& userVO = UserProxy::shared()->userVO;
        userVO.coin = [coin intValue];
        userVO.energyCur = [energyCur intValue];
        userVO.fusion = [fusion intValue];

        NSArray* equipage = [data objectForKey:@"equipage"];
        if ((equipage != nil)
            && (![equipage isEqual:[NSNull null]])
            && (![equipage isEqual:@""]))
        {
            EquipInfo equipInfo;
            _parseEquipageInfo(equipage, &equipInfo);
            ItemProxy::shared()->addEquip(&equipInfo, true);
            ItemProxy::shared()->curQiangHuaEquip = ItemProxy::shared()->getEquip(equipInfo.index);
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseIntensifyEquipage(): intensifyEquipage is null.");
        }
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseIntensifyEquipage(): data is null.");
    }

    //NSLog(@"NetController::_parseIntensifyEquipage() end");
    Post_Net_Notification(kNCIntensifyEquipage, NULL);
}

/**
 * @brief     查找挑战玩家信息命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseFindChallengePlayer(void* params)
{
    //NSLog(@"NetController::_parseFindChallengePlayer() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        ChanllengeProxy::shared()->clearChallengeEnemyList();
        ChallengeEnemyList& challengeEnemyList = ChanllengeProxy::shared()->mChallengeEnemyList;
        NSArray* playerList = [data objectForKey:@"playerList"];
        if ((playerList != nil)
            && (![playerList isEqual:[NSNull null]])
            && (![playerList isEqual:@""]))
        {
            int count = [playerList count];
            for (int i=0; i<count; i++)
            {
                NSDictionary* player = [playerList objectAtIndex:i];
                if ((player != nil)
                    && (![player isEqual:[NSNull null]])
                    && (![player isEqual:@""]))
                {
                    
                    ChallengeEnemyInfo* challengeEnemyInfo = new ChallengeEnemyInfo();
                    _parseChallengeEnemyInfo(player, challengeEnemyInfo, false);
                    challengeEnemyList.push_back(challengeEnemyInfo);
                }
                else
                {
                    //TODO: 解析出错
                    //NSLog(@"NetController::_parseFindChallengePlayer(): player is null.");
                }
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseIntensifyEquipage(): playerList is null.");
        }
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseFindChallengePlayer(): data is null.");
    }

    //NSLog(@"NetController::_parseFindChallengePlayer() end");
    Post_Net_Notification(kNCFindChallengePlayerByName, NULL);
}

/**
 * @brief     获取挑战玩家列表信息命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseGetChallengeList(void* params)
{
    //NSLog(@"NetController::_parseGetChallengeList() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        ChanllengeProxy::shared()->clearChallengeEnemyList();
        ChallengeEnemyList& challengeEnemyList = ChanllengeProxy::shared()->mChallengeEnemyList;
        NSArray* playerList = [data objectForKey:@"playerList"];
        if ((playerList != nil)
            && (![playerList isEqual:[NSNull null]])
            && (![playerList isEqual:@""]))
        {
            int count = [playerList count];
            for (int i=0; i<count; i++)
            {
                NSDictionary* player = [playerList objectAtIndex:i];
                if ((player != nil)
                    && (![player isEqual:[NSNull null]])
                    && (![player isEqual:@""]))
                {
                    ChallengeEnemyInfo* challengeEnemyInfo = new ChallengeEnemyInfo();
                    _parseChallengeEnemyInfo(player, challengeEnemyInfo, false);
                    challengeEnemyList.push_back(challengeEnemyInfo);
                }
                else
                {
                    //TODO: 解析出错
                    //NSLog(@"NetController::_parseGetChallengeList(): player is null.");
                }
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseGetChallengeList(): playerList is null.");
        }
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseGetChallengeList(): data is null.");
    }

    //NSLog(@"NetController::_parseGetChallengeList() end");
    Post_Net_Notification(kNCGetChallengeList, NULL);
}

/**
 * @brief     获取挑战宿敌列表信息命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseGetChallengeEnemyList(void* params)
{
    //NSLog(@"NetController::_parseGetChallengeEnemyList() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        ChanllengeProxy::shared()->clearChallengeEnemyList();
        ChallengeEnemyList& challengeEnemyList = ChanllengeProxy::shared()->mChallengeEnemyList;
        NSArray* playerList = [data objectForKey:@"challengeEnemyList"];
        if ((playerList != nil)
            && (![playerList isEqual:[NSNull null]])
            && (![playerList isEqual:@""]))
        {
            int count = [playerList count];
            for (int i=0; i<count; i++)
            {
                NSDictionary* player = [playerList objectAtIndex:i];
                if ((player != nil)
                    && (![player isEqual:[NSNull null]])
                    && (![player isEqual:@""]))
                {
                    ChallengeEnemyInfo* challengeEnemyInfo = new ChallengeEnemyInfo();
                    _parseChallengeEnemyInfo(player, challengeEnemyInfo);
                    challengeEnemyList.push_back(challengeEnemyInfo);
                }
                else
                {
                    //TODO: 解析出错
                    //NSLog(@"NetController::_parseGetChallengeEnemyList(): player is null.");
                }
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseGetChallengeEnemyList(): playerList is null.");
        }
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseGetChallengeEnemyList(): data is null.");
    }

    //NSLog(@"NetController::_parseGetChallengeEnemyList() end");
    Post_Net_Notification(kNCGetChallengeEnemyList, NULL);
}

/**
 * @brief     开宝箱命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseOpenBox(void* params)
{
    //NSLog(@"NetController::_parseOpenBox() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        //NSLog(@"_parseOpenBox: %@", data);
        NSNumber* result = [data objectForKey:@"result"];
        int openResult = [result intValue];

        NSNumber* coin = [data objectForKey:@"coin"];
        int playerCoin = [coin intValue];

        NSNumber* money = [data objectForKey:@"money"];
        int playerMoney = [money intValue];

        /**
         *下次免费开宝箱的剩余秒数(0:拥有一次开宝箱机会)
         */
        NSNumber* remainderOpenBoxTime = [data objectForKey:@"remainderOpenBoxTime"];
        ShopProxy::shared()->mRemainderOpenBoxTime = [remainderOpenBoxTime intValue];
        NSLog(@"remainderOpenBoxTime: %@", remainderOpenBoxTime);
        
        UserProxy::shared()->userVO.coin = playerCoin;
        UserProxy::shared()->userVO.money = playerMoney;
        ShopProxy::shared()->mSellResult.result = openResult;
        NSArray* equipage;
        switch (openResult)
        {
        case 1:
            //开宝箱开出奖励
            equipage = [data objectForKey:@"equipage"];
            if ((equipage != nil)
                && (![equipage isEqual:[NSNull null]])
                && (![equipage isEqual:@""]))
            {
                EquipInfo* equipInfo = new EquipInfo();
                _parseEquipageInfo(equipage, equipInfo);
                ItemProxy::shared()->addEquip(equipInfo, false);
                ShopProxy::shared()->mSellResult.clear();
                ShopProxy::shared()->mSellResult.mEquipInfo = equipInfo;
            }
            else
            {
                //TODO: 解析出错
                //NSLog(@"NetController::_parseIntensifyEquipage(): intensifyEquipage is null.");
            }
            break;
        case 2:
            //开宝箱没有开出奖励

            break;
        default:
            //TODO: 未知结果
            break;
        }
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseOpenBox(): data is null.");
    }

    //NSLog(@"NetController::_parseOpenBox() end");
    Post_Net_Notification(kNCOpenBox, NULL);
}

/**
 * @brief     购买(补充)能量命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseBuyEnergy(void* params)
{
    //NSLog(@"NetController::_parseBuyEnergy() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSNumber* type = [data objectForKey:@"type"];
        int buyType = [type intValue];

        NSNumber* energyCur = [data objectForKey:@"energyCur"];
        int playerEnergyCur = [energyCur intValue];

        NSNumber* energyMax = [data objectForKey:@"energyMax"];
        int playerEnergyMax = [energyMax intValue];

        NSNumber* coin = [data objectForKey:@"coin"];
        int playerCoin = [coin intValue];

        NSNumber* money = [data objectForKey:@"money"];
        int playerMoney = [money intValue];
        
        UserVO& userVO = UserProxy::shared()->userVO;
        userVO.energyCur = playerEnergyCur;
        userVO.energyMax = playerEnergyMax;
        userVO.coin = playerCoin;
        userVO.money = playerMoney;
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseBuyEnergy(): data is null.");
    }

    //NSLog(@"NetController::_parseBuyEnergy() end");
    Post_Net_Notification(kNCBuyEnergy, NULL);
}

/**
 * @brief     购买(补充)体力命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseBuyPower(void* params)
{
    //NSLog(@"NetController::_parseBuyPower() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSNumber* type = [data objectForKey:@"type"];
        int buyType = [type intValue];

        NSNumber* powerCur = [data objectForKey:@"powerCur"];
        int playerPowerCur = [powerCur intValue];

        NSNumber* coin = [data objectForKey:@"coin"];
        int playerCoin = [coin intValue];

        NSNumber* money = [data objectForKey:@"money"];
        int playerMoney = [money intValue];
        
        UserVO& userVO = UserProxy::shared()->userVO;
        userVO.powerCur = playerPowerCur;
        userVO.coin = playerCoin;
        userVO.money = playerMoney;
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseBuyPower(): data is null.");
    }

    //NSLog(@"NetController::_parseBuyPower() end");
    Post_Net_Notification(kNCBuyPower, NULL);
}

/**
 * @brief     购买(补充)生命命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseBuyLife(void* params)
{
    //NSLog(@"NetController::_parseBuyLife() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSNumber* type = [data objectForKey:@"type"];
        int buyType = [type intValue];

        NSNumber* playerLife = [data objectForKey:@"lifeCur"];
        int lifeCur = [playerLife intValue];

        NSNumber* coin = [data objectForKey:@"coin"];
        int playerCoin = [coin intValue];

        NSNumber* money = [data objectForKey:@"money"];
        int playerMoney = [money intValue];
        
        UserVO& userVO = UserProxy::shared()->userVO;
        userVO.coin = playerCoin;
        userVO.money = playerMoney;
        userVO.lifeCur = lifeCur;

        //TODO: 需要上层对应
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseBuyLife(): data is null.");
    }

    //NSLog(@"NetController::_parseBuyLife() end");
    Post_Net_Notification(kNCBuyLife, NULL);
}

/**
 * @brief     购买(补充)宝石命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseBuyMoney(void* params)
{
    //NSLog(@"NetController::_parseBuyMoney() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSNumber* money = [data objectForKey:@"money"];
        UserProxy::shared()->userVO.money = [money intValue];

        NSString* md5 = [data objectForKey:@"md5"];

        //TODO: 需要上层对应
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseBuyMoney(): data is null.");
    }

    //NSLog(@"NetController::_parseBuyMoney() end");
    Post_Net_Notification(kNCBuyMoney, NULL);
}

/**
 * @brief     购买(补充)金币命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseBuyCoin(void* params)
{
    //NSLog(@"NetController::_parseBuyCoin() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSNumber* coin = [data objectForKey:@"coin"];

        NSNumber* money = [data objectForKey:@"money"];
        
        UserProxy::shared()->userVO.coin = [coin intValue];
        UserProxy::shared()->userVO.money = [money intValue];
        //TODO: 需要上层对应
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseBuyCoin(): data is null.");
    }

    //NSLog(@"NetController::_parseBuyCoin() end");
    Post_Net_Notification(kNCBuyCoin, NULL);
}

/**
 * @brief     挑战命令返回数据解析函数。
 * @param[in] params 接收到的数据。
 */
void NetController::_parseChallengePlayer(void* params)
{
    //NSLog(@"NetController::_parseChallengePlayer() start");

    NSDictionary* data = (NSDictionary*)params;
    if ((data != nil)
        && (![data isEqual:[NSNull null]])
        && (![data isEqual:@""]))
    {
        NSDictionary* challenge = [data objectForKey:@"challenge"];
        if ((challenge != nil)
            && (![challenge isEqual:[NSNull null]])
            && (![challenge isEqual:@""]))
        {
            //验证信息
            NSNumber* win = [challenge objectForKey:@"win"];  //1: 玩家为获胜方, 2: 对手为获胜方
            NSArray* roundInfo = [challenge objectForKey:@"round"];
            ChallengeResult& mChallengeResult = ChanllengeProxy::shared()->mChallengeResult;
            mChallengeResult.result = [win intValue];
            if ((roundInfo != nil)
                && (![roundInfo isEqual:[NSNull null]])
                && (![roundInfo isEqual:@""]))
            {
                int count = [roundInfo count];
                for (int i=0; i<count; i++)
                {
                    NSArray* round = [roundInfo objectAtIndex:i];
                    if ((round != nil)
                        && (![round isEqual:[NSNull null]])
                        && (![round isEqual:@""]))
                    {
                        NSNumber* atkUsr = [round objectAtIndex:0];  //1: 玩家为攻击方, 2: 对手为攻击方
                        NSNumber* atkMax = [round objectAtIndex:1];  //是否发生了最大攻击 1: 发生了最大攻击力， 0：没发生最大攻击力
                        NSNumber* defMax = [round objectAtIndex:2];  //是否发生了最大防御 1: 发生了最大防御力， 0：没发生最大防御力
                        NSNumber* life = [round objectAtIndex:3];    //攻击对于life造成的伤害
                    }
                    else {
                        //NSLog(@"NetController::_parseChallengePlayer(): round is null.");
                    }
                }
            }
            else {
                //NSLog(@"NetController::_parseChallengePlayer(): roundInfo is null.");
            }

        }
        else {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseChallengePlayer(): challenge is null.");
        }


        NSNumber* succeedExp = [data objectForKey:@"succeedExp"];
        NSNumber* succeedGold = [data objectForKey:@"succeedGold"];
        NSNumber* failedGold = [data objectForKey:@"failedGold"];
        ChanllengeProxy::shared()->mCurChallengeEnemyInfo->succeedExp=[succeedExp intValue];
        ChanllengeProxy::shared()->mCurChallengeEnemyInfo->succeedGold=[succeedGold intValue];
        ChanllengeProxy::shared()->mCurChallengeEnemyInfo->failedGold=[failedGold intValue];

        NSDictionary* asyncInfo = [data objectForKey:@"asyncInfo"];
        if ((asyncInfo != nil)
            && (![asyncInfo isEqual:[NSNull null]])
            && (![asyncInfo isEqual:@""]))
        {
            NSNumber* coin = [asyncInfo objectForKey:@"coin"];
            NSNumber* level = [asyncInfo objectForKey:@"level"];
            NSNumber* exp = [asyncInfo objectForKey:@"exp"];
            NSNumber* energyCur = [asyncInfo objectForKey:@"energyCur"];
            NSNumber* energyMax = [asyncInfo objectForKey:@"energyMax"];
            NSNumber* powerCur = [asyncInfo objectForKey:@"powerCur"];
            NSNumber* powerMax = [asyncInfo objectForKey:@"powerMax"];
            NSNumber* energyTime = [asyncInfo objectForKey:@"energyTime"];
            NSNumber* powerTime = [asyncInfo objectForKey:@"powerTime"];
            UserVO& userVO = UserProxy::shared()->userVO;
            userVO.coin = [coin intValue];
            userVO.level = [level intValue];
            userVO.exp = [exp intValue];
            userVO.energyCur = [energyCur intValue];
            userVO.energyMax = [energyMax intValue];
            userVO.powerCur = [powerCur intValue];
            userVO.powerMax = [powerMax intValue];
            userVO.energyTime = [energyTime intValue];
            userVO.powerTime = [powerTime intValue];
        }
    }
    else
    {
        //TODO: 解析出错
        //NSLog(@"NetController::_parseChallengePlayer(): data is null.");
    }

    //NSLog(@"NetController::_parseChallengePlayer() end");
    Post_Net_Notification(kNCChallengePlayer, NULL);
}

/**
 * @brief  取得PID函数。
 * @return PID。
 */
std::string NetController::_getPid()
{
    //NSLog(@"NetController::_getPid() start");
    //NSLog(@"NetController::_getPid() end");

    // TODO: pid要取得方
    return getDeviceID();
//    return "k211111112";
//    return "k211111113";
}

/**
 * @brief  取得平台类型函数。
 * @return 平台类型。
 */
int NetController::_getPlatform()
{
    //NSLog(@"NetController::_getPlatform() start");
    //NSLog(@"NetController::_getPlatform() end");

    return kNCPlatform;
}

/**
 * @brief  取得网络命令版本号函数。
 * @return 网络命令版本号。
 */
std::string NetController::_getVersion()
{
    //NSLog(@"NetController::_getVersion() start");
    //NSLog(@"NetController::_getVersion() end");

    return kNCVersion;
}

/**
 * @brief      解析装备函数。
 * @param[in]  data 装备数据。
 * @param[out] info 装备信息。
 */
void NetController::_parseEquipageInfo(void* data, void* info)
{
    //NSLog(@"NetController::_parseEquipageInfo() start");
    
    NSArray* arrayData = (NSArray*)data;
    //NSLog(@"arrayData: %@", arrayData);
    if ((arrayData != nil)
        && (![arrayData isEqual:[NSNull null]])
        && (![arrayData isEqual:@""])
        && (info != NULL))
    {
        NSNumber* equipageIndex = [arrayData objectAtIndex:kNCBagEquipageFieldIndex];
        NSNumber* equipageID = [arrayData objectAtIndex:kNCBagEquipageFieldBaseID];
        NSNumber* equipageLevel = [arrayData objectAtIndex:kNCBagEquipageFieldLevel];
        NSNumber* equipageExp = [arrayData objectAtIndex:kNCBagEquipageFieldExp];
        NSNumber* equipageAtkMin = [arrayData objectAtIndex:kNCBagEquipageFieldAtkMin];
        NSNumber* equipageAtkMax = [arrayData objectAtIndex:kNCBagEquipageFieldAtkMax];
        NSNumber* equipageDefMin = [arrayData objectAtIndex:kNCBagEquipageFieldDefMin];
        NSNumber* equipageDefMax = [arrayData objectAtIndex:kNCBagEquipageFieldDefMax];
        NSNumber* equipageLife = [arrayData objectAtIndex:kNCBagEquipageFieldLife];
        NSNumber* equipageState = [arrayData objectAtIndex:kNCBagEquipageFieldState];
        NSNumber* equipageIntensifyNum = [arrayData objectAtIndex:kNCBagEquipageFieldIntensifyNum];
        NSNumber* equipageIntensifyValue = [arrayData objectAtIndex:kNCBagEquipageFieldIntensifyValue];
        NSArray* equipageExt = [arrayData objectAtIndex:kNCBagEquipageFieldExt];
        int count = [equipageExt count];
        
        EquipInfo* equipInfo = ((EquipInfo*)info);
        equipInfo->clearAffix();
        for (int j=0; j<count; j++)
        {
            //词条解析
            NSArray* property = [equipageExt objectAtIndex:j];
            //词条类型
            NSNumber* type = [property objectAtIndex: 0];
            //词条数值
            NSNumber* value = [property objectAtIndex: 1];
            
            Affix* affix = new Affix();
            affix->value = [value intValue];
            affix->type = (AffixType)[type intValue];
            equipInfo->affixs.push_back(affix);
        }

        ((EquipInfo*)info)->index = [equipageIndex intValue];
        ((EquipInfo*)info)->id = [equipageID intValue];
        ((EquipInfo*)info)->level = [equipageLevel intValue];
        ((EquipInfo*)info)->exp = [equipageExp intValue];
        ((EquipInfo*)info)->atkMin = [equipageAtkMin intValue];
        ((EquipInfo*)info)->atkMax = [equipageAtkMax intValue];
        ((EquipInfo*)info)->defMin = [equipageDefMin intValue];
        ((EquipInfo*)info)->defMax = [equipageDefMax intValue];
        ((EquipInfo*)info)->life = [equipageLife intValue];
        ((EquipInfo*)info)->state = [equipageState intValue];
        ((EquipInfo*)info)->intensifyNum = [equipageIntensifyNum intValue];
        ((EquipInfo*)info)->intensifyValue = [equipageIntensifyValue intValue];
    }

    //NSLog(@"NetController::_parseEquipageInfo() end");
}

/**
 * @brief      解析道具函数。
 * @param[in]  data 道具数据。
 * @param[out] info 道具信息。
 */
void NetController::_parsePropInfo(void* data, void* info)
{
    //NSLog(@"NetController::_parsePropInfo() start");

    NSArray* arrayData = (NSArray*)data;

    if ((arrayData != nil)
        && (![arrayData isEqual:[NSNull null]])
        && (![arrayData isEqual:@""])
        && (info != NULL))
    {
        NSNumber* propIndex = [arrayData objectAtIndex:kNCBagPropFieldIndex];
        NSNumber* propID = [arrayData objectAtIndex:kNCBagPropFieldBaseID];
        NSNumber* propNum = [arrayData objectAtIndex:kNCBagPropFieldNum];

        ((ItemInfo*)info)->index = [propIndex intValue];
        ((ItemInfo*)info)->id = [propID intValue];
        ((ItemInfo*)info)->count = [propNum intValue];
    }

    //NSLog(@"NetController::_parsePropInfo() end");
}

/**
 * @brief      解析任务函数。
 * @param[in]  data 任务数据。
 * @param[out] info 任务信息。
 */
void NetController::_parseTaskInfo(void* data, void* info)
{
    //NSLog(@"NetController::_parseTaskInfo() start");

    NSArray* arrayData = (NSArray*)data;

    if ((arrayData != nil)
        && (![arrayData isEqual:[NSNull null]])
        && (![arrayData isEqual:@""])
        && (info != NULL))
    {
        NSNumber* floor = [arrayData objectAtIndex:kNCTaskFieldFloor];
        NSNumber* task = [arrayData objectAtIndex:kNCTaskFieldTask];
        NSNumber* progress = [arrayData objectAtIndex:kNCTaskFieldProgress];

        ((TaskInfo*)info)->floor = [floor intValue];
        ((TaskInfo*)info)->task = [task intValue];
        ((TaskInfo*)info)->progress = [progress intValue];
    }

    //NSLog(@"NetController::_parseTaskInfo() end");
}

/**
 * @brief      解析挑战宿敌函数。
 * @param[in]  data 挑战宿敌数据。
 * @param[out] info 挑战宿敌信息。
 */
void NetController::_parseChallengeEnemyList(void* data, void* info)
{
    //NSLog(@"NetController::_parseChallengeEnemyList() start");

    NSDictionary* arrayData = (NSDictionary*)data;

    if ((arrayData != nil)
        && (![arrayData isEqual:[NSNull null]])
        && (![arrayData isEqual:@""])
        && (info != NULL))
    {
        NSNumber* gid = [arrayData objectForKey:@"gid"];
        NSString* name = [arrayData objectForKey:@"name"];
        NSNumber* time = [arrayData objectForKey:@"time"];
        NSNumber* coin = [arrayData objectForKey:@"coin"];

        //TODO: 上层对应
    }

    //NSLog(@"NetController::_parseChallengeEnemyList() end");
}

/**
 * @brief      解析抢夺宿敌函数。
 * @param[in]  data 抢夺宿敌数据。
 * @param[out] info 抢夺宿敌信息。
 */
void NetController::_parseSnatchEnemyList(void* data, void* info)
{
    //NSLog(@"NetController::_parseSnatchEnemyList() start");

    NSDictionary* arrayData = (NSDictionary*)data;

    if ((arrayData != nil)
        && (![arrayData isEqual:[NSNull null]])
        && (![arrayData isEqual:@""])
        && (info != NULL))
    {
        NSNumber* gid = [arrayData objectForKey:@"gid"];
        NSString* name = [arrayData objectForKey:@"name"];
        NSNumber* time = [arrayData objectForKey:@"time"];
        NSNumber* id = [arrayData objectForKey:@"id"];

        //TODO: 上层对应
    }

    //NSLog(@"NetController::_parseSnatchEnemyList() end");
}

/**
 * @brief      解析碎片列表函数。
 * @param[in]  data 碎片列表数据。
 * @param[out] info 碎片列表信息。
 */
void NetController::_parseFragmentArray(void* data, void* info)
{
    //NSLog(@"NetController::_parseFragmentArray() start");

    NSDictionary* arrayData = (NSDictionary*)data;

    if ((arrayData != nil)
        && (![arrayData isEqual:[NSNull null]])
        && (![arrayData isEqual:@""])
        && (info != NULL))
    {
        NSNumber* id = [arrayData objectForKey:@"id"];
        NSNumber* count = [arrayData objectForKey:@"count"];

        //TODO: 上层对应
    }

    //NSLog(@"NetController::_parseFragmentArray() end");
}

/**
 * @brief      解析挑战玩家函数。
 * @param[in]  data 挑战宿敌数据。
 * @param[out] info 挑战宿敌信息。
 */
void NetController::_parseChallengeEnemyInfo(void* data, void* info, bool isParseEnemy)
{
    //NSLog(@"NetController::_parseChallengeEnemyInfo() start");

    NSDictionary* player = (NSDictionary*)data;
    if ((player != nil)
        && (![player isEqual:[NSNull null]])
        && (![player isEqual:@""])
        && (info != NULL))
    {
        NSNumber* gid = [player objectForKey:@"gid"];
        NSString* name = [player objectForKey:@"name"];
        NSNumber* sex = [player objectForKey:@"sex"];
        NSNumber* avata = [player objectForKey:@"avata"];
        NSNumber* level = [player objectForKey:@"level"];
        NSNumber* exp = [player objectForKey:@"exp"];
        NSNumber* atkMin = [player objectForKey:@"atkMin"];
        NSNumber* atkMax = [player objectForKey:@"atkMax"];
        NSNumber* defMin = [player objectForKey:@"defMin"];
        NSNumber* defMax = [player objectForKey:@"defMax"];
        NSNumber* succeedExp = [player objectForKey:@"succeedExp"];
        NSNumber* succeedGold = [player objectForKey:@"succeedGold"];
        NSNumber* failedGold = [player objectForKey:@"failedGold"];

        ChallengeEnemyInfo* challengeEnemyInfo = (ChallengeEnemyInfo*)info;
        challengeEnemyInfo->gid = [gid intValue];
        challengeEnemyInfo->name = [name UTF8String];
//        challengeEnemyInfo->sex = [sex intValue];
        challengeEnemyInfo->avatar = [avata intValue];
        challengeEnemyInfo->level = [level intValue];
        challengeEnemyInfo->atkMin = [atkMin intValue];
        challengeEnemyInfo->atkMax = [atkMax intValue];
        challengeEnemyInfo->succeedExp = [succeedExp intValue];
        challengeEnemyInfo->succeedGold = [succeedGold intValue];
        challengeEnemyInfo->failedGold = [failedGold intValue];

        //NSLog(@"gid: %@", gid);
        //NSLog(@"name: %@", name);
        //NSLog(@"sex: %@", sex);
        //NSLog(@"avata: %@", avata);
        //NSLog(@"level: %@", level);
        //NSLog(@"exp: %@", exp);
        //NSLog(@"atkMin: %@", atkMin);
        //NSLog(@"atkMax: %@", atkMax);
        //NSLog(@"defMin: %@", defMin);
        //NSLog(@"defMax: %@", defMax);
        //NSLog(@"succeedExp: %@", succeedExp);
        //NSLog(@"succeedGold: %@", succeedGold);
        //NSLog(@"failedGold: %@", failedGold);
        if(isParseEnemy)
        {
            NSNumber* challengeTime = [player objectForKey:@"challengeTime"];
            NSNumber* challengeCoin = [player objectForKey:@"challengeCoin"];
            challengeEnemyInfo->time = [challengeTime intValue];
            challengeEnemyInfo->gold = [challengeCoin intValue];
            //NSLog(@"challengeTime: %@", challengeTime);
            //NSLog(@"challengeCoin: %@", challengeCoin);
        }
    }

    //NSLog(@"NetController::_parseChallengeEnemyInfo() end");
}

/**
 * @brief      解析玩家自身信息函数。
 * @param[in]  params 玩家自身数据数据。
 */
void NetController::_parseSelfInfo(void* params)
{
    //NSLog(@"NetController::_parseSelfInfo() start");

    NSDictionary* data = (NSDictionary*)params;
    NSDictionary* player = [data objectForKey:@"player"];
    if ((player != nil)
        && (![player isEqual:[NSNull null]])
        && (![player isEqual:@""]))
    {
        /**
         * 验证信息
         */
        //游戏中分配的玩家唯一id标识。
        NSNumber* gid = [player objectForKey:@"gid"];
        //客户端通过mac或者其他唯一标识生成的唯一硬件id序列。
        NSString* pid = [player objectForKey:@"pid"];
        //玩家平台类型。
        NSNumber* platform = [player objectForKey:@"platform"];

        UserVO& userVO = UserProxy::shared()->userVO;
        userVO.gid = [gid intValue];
        userVO.pid = [pid UTF8String];
        userVO.platform = [platform intValue];

        //取得gid
        mGid = [gid intValue];

        //NSLog(@"gid: %@", gid);
        //NSLog(@"pid: %@", pid);
        //NSLog(@"platform: %@", platform);

        /**
         *时间信息
         */
        //玩家注册日期。
        NSNumber* createTime = [player objectForKey:@"createTime"];
        //玩家能量点给予日期。
        NSNumber* energyTime = [player objectForKey:@"energyTime"];
        //玩家体力点给予日期。
        NSNumber* powerTime = [player objectForKey:@"powerTime"];
        //TODO:玩家上次开宝箱的日期。
        NSNumber* freeBoxTime = [player objectForKey:@"freeBoxTime"];
        userVO.createTime = [createTime intValue];
        userVO.energyTime = [energyTime intValue];
        userVO.powerTime = [powerTime intValue];
        ShopProxy::shared()->mRemainderOpenBoxTime = [freeBoxTime intValue];

        //NSLog(@"createTime: %@", createTime);
        //NSLog(@"energyTime: %@", energyTime);
        //NSLog(@"powerTime: %@", powerTime);
        NSLog(@"freeBoxTime: %@", freeBoxTime);

        /**
         *基础信息
         */
        //玩家名字。（最大32个英文字符）
        NSString* name = [player objectForKey:@"name"];
        //玩家性别。（0:男;1:女）
        NSString* sex = [player objectForKey:@"sex"];
        //玩家形象。
        NSNumber* avata = [player objectForKey:@"avata"];
        //玩家等级。（升级参照玩家等级表）
        NSNumber* level = [player objectForKey:@"level"];
        //玩家经验值。（升级参照玩家等级表）
        NSNumber* exp = [player objectForKey:@"exp"];
        userVO.name = [name UTF8String];
        userVO.sex = [sex intValue];
        userVO.avatar = [avata intValue];
        userVO.level = [level intValue];
        userVO.exp = [exp intValue];

        //NSLog(@"name: %@", name);
        //NSLog(@"sex: %@", sex);
        //NSLog(@"avata: %@", avata);
        //NSLog(@"level: %@", level);
        //NSLog(@"exp: %@", exp);

        /**
         *金融信息
         */
        //游戏币。（玩家游戏中可以免费获得的虚拟货币）
        NSNumber* coin = [player objectForKey:@"coin"];
        //付费币。（玩家花钱购买的虚拟货币）
        NSNumber* money = [player objectForKey:@"money"];
        userVO.coin = [coin intValue];
        userVO.money = [money intValue];

        //NSLog(@"coin: %@", coin);
        //NSLog(@"money: %@", money);

        /**
         *能力信息
         */
        //当前能量值。初始20点，可用潜能1:1分配，默认3分钟恢复1点。
        NSNumber* energyCur = [player objectForKey:@"energyCur"];
        //最大能量值。
        NSNumber* energyMax = [player objectForKey:@"energyMax"];
        //当前体力值。初始3点，默认2小时恢复1点。
        NSNumber* powerCur = [player objectForKey:@"powerCur"];
        //最大体力值。
        NSNumber* powerMax = [player objectForKey:@"powerMax"];
        //当前地下城内的生命值。
        NSNumber* lifeCur = [player objectForKey:@"lifeCur"];
        //生命值。初始200点（暂定），可用潜能分配，每次增加50点（暂定）。
        NSNumber* life = [player objectForKey:@"life"];
        //潜能。每次升级自动获得2点。
        NSNumber* proficiency = [player objectForKey:@"proficiency"];
        //熔炼值。
        NSNumber* fusion = [player objectForKey:@"fusion"];
        userVO.energyCur = [energyCur intValue];
        userVO.energyMax = [energyMax intValue];
        userVO.powerCur = [powerCur intValue];
        userVO.powerMax = [powerMax intValue];
        userVO.life = [life intValue];
        userVO.lifeCur = [lifeCur intValue];
        userVO.proficiency = [proficiency intValue];
        userVO.fusion = [fusion intValue];

        //NSLog(@"energyCur: %@", energyCur);
        //NSLog(@"energyMax: %@", energyMax);
        //NSLog(@"powerCur: %@", powerCur);
        //NSLog(@"powerMax: %@", powerMax);
        //NSLog(@"lifeCur: %@", lifeCur);
        //NSLog(@"life: %@", life);
        //NSLog(@"proficiency: %@", proficiency);
        //NSLog(@"fusion: %@", fusion);

        /**
         *对战信息
         */
        //最小攻击力：人物基础+装备提供，基础部分会随等级增长。
        NSNumber* atkMin = [player objectForKey:@"atkMin"];
        //最大攻击力：同上
        NSNumber* atkMax = [player objectForKey:@"atkMax"];
        //最小防御力：同上
        NSNumber* defMin = [player objectForKey:@"defMin"];
        //最大防御力：同上
        NSNumber* defMax = [player objectForKey:@"defMax"];
        //最大攻击出现频率：初始为0%
        NSNumber* atkMaxReappear = [player objectForKey:@"atkMaxReappear"];
        //最大防御出现频率：初始值为0%
        NSNumber* defMaxReappear = [player objectForKey:@"defMaxReappear"];
        //经验获得比率：初始为100%
        NSNumber* expGainRatio = [player objectForKey:@"expGainRatio"];
        //铜钱获得比率：初始为100%
        NSNumber* coinGainRatio = [player objectForKey:@"coinGainRatio"];
        //装备掉率几率：初始为100%
        NSNumber* equipageDropRatio = [player objectForKey:@"equipageDropRatio"];
        //能量恢复速度：初始为100%
        NSNumber* energyRecoverRatio = [player objectForKey:@"energyRecoverRatio"];
        //体力恢复速度：初始为100%
        NSNumber* powerRecoverRatio = [player objectForKey:@"powerRecoverRatio"];
        userVO.atkMin = [atkMin intValue];
        userVO.atkMax = [atkMax intValue];
        userVO.defMin = [defMin intValue];
        userVO.defMax = [defMax intValue];
        userVO.atkMaxReappear = [atkMaxReappear intValue];
        userVO.defMaxReappear = [defMaxReappear intValue];
        userVO.expGainRatio = [expGainRatio intValue];
        userVO.coinGainRatio = [coinGainRatio intValue];
        userVO.equipageDropRatio = [equipageDropRatio intValue];
        userVO.energyRecoverRatio = [energyRecoverRatio intValue];
        userVO.powerRecoverRatio = [powerRecoverRatio intValue];

        //NSLog(@"atkMin: %@", atkMin);
        //NSLog(@"atkMax: %@", atkMax);
        //NSLog(@"defMin: %@", defMin);
        //NSLog(@"defMax: %@", defMax);
        //NSLog(@"atkMaxReappear: %@", atkMaxReappear);
        //NSLog(@"defMaxReappear: %@", defMaxReappear);
        //NSLog(@"expGainRatio: %@", expGainRatio);
        //NSLog(@"coinGainRatio: %@", coinGainRatio);
        //NSLog(@"equipageDropRatio: %@", equipageDropRatio);
        //NSLog(@"energyRecoverRatio: %@", energyRecoverRatio);
        //NSLog(@"powerRecoverRatio: %@", powerRecoverRatio);

        /**
         *装备背包信息
         */
        //装备列表中的装备最大容量。
        NSNumber* equipageBagItemMax = [player objectForKey:@"equipageBagItemMax"];
        ItemProxy::shared()->mBagMax = [equipageBagItemMax intValue];

        //玩家自身的装备唯一id值当前所分配到的索引。
        NSNumber* equipageBagItemCurID = [player objectForKey:@"equipageBagItemCurID"];
        //装备列表、不可叠加。
        NSArray* equipageBagItemArray = [player objectForKey:@"equipageBagItemArray"];
        if ((equipageBagItemArray != nil)
            && (![equipageBagItemArray isEqual:[NSNull null]])
            && (![equipageBagItemArray isEqual:@""]))
        {
            int count = [equipageBagItemArray count];
            for (int i=0; i<count; i++)
            {
                NSArray* equipage = [equipageBagItemArray objectAtIndex:i];
                if ((equipage != nil)
                    && (![equipage isEqual:[NSNull null]])
                    && (![equipage isEqual:@""]))
                {
                    EquipInfo* equipInfo = new EquipInfo();
                    _parseEquipageInfo(equipage, equipInfo);
                    ItemProxy::shared()->addEquip(equipInfo);
                }
                else
                {
                    //TODO: 解析出错
                    //NSLog(@"NetController::_parseRegist(): equipage[%@] is null.", i);
                }
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseRegist(): equipageBagItemArray is null.");
        }

        //NSLog(@"equipageBagItemMax: %@", equipageBagItemMax);
        //NSLog(@"equipageBagItemCurID: %@", equipageBagItemCurID);
        //NSLog(@"equipageBagItemArray: %@", equipageBagItemArray);

        /**
         *道具背包信息
         */
        //道具列表、可叠加。
        NSArray* propBagItemArray = [player objectForKey:@"propBagItemArray"];
        if ((propBagItemArray != nil)
            && (![propBagItemArray isEqual:[NSNull null]])
            && (![propBagItemArray isEqual:@""]))
        {
            int count = [propBagItemArray count];
            for (int i=0; i<count; i++)
            {
                NSArray* prop = [propBagItemArray objectAtIndex:i];
                if ((prop != nil)
                    && (![prop isEqual:[NSNull null]])
                    && (![prop isEqual:@""]))
                {
                    ItemInfo* itemInfo = new ItemInfo();
                    _parsePropInfo(prop, itemInfo);
                    ItemProxy::shared()->addItem(itemInfo);
                }
                else
                {
                    //TODO: 解析出错
                    //NSLog(@"NetController::_parseRegist(): prop[%@] is null.", i);
                }
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseRegist(): propBagItemArray is null.");
        }

        //NSLog(@"propBagItemArray: %@", propBagItemArray);

        /**
         *任务信息
         */
        //当前任务信息。
        NSDictionary* taskCur = [player objectForKey:@"taskCur"];
        if ((taskCur != nil)
            && (![taskCur isEqual:[NSNull null]])
            && (![taskCur isEqual:@""]))
        {
            NSArray* keys = [taskCur allKeys];
            for (int i=0; i<[keys count]; i++)
            {
                NSNumber* key = [keys objectAtIndex:i];
                NSArray* taskInfo = [taskCur objectForKey:key];

                DungeonsProxy::shared()->curTaskInfo.dungeonID = [key intValue];
                _parseTaskInfo(taskInfo, &(DungeonsProxy::shared()->curTaskInfo));
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseRegist(): taskCur is null.");
        }

        //NSLog(@"taskCur: %@", taskCur);

        //最大任务信息
        NSDictionary* taskMax = [player objectForKey:@"taskMax"];
        if ((taskMax != nil)
            && (![taskMax isEqual:[NSNull null]])
            && (![taskMax isEqual:@""]))
        {
            NSArray* keys = [taskMax allKeys];
            for (int i=0; i<[keys count]; i++)
            {
                NSNumber* key = [keys objectAtIndex:i];
                NSArray* taskInfo = [taskMax objectForKey:key];

                DungeonsProxy::shared()->maxTaskInfo.dungeonID = [key intValue];
                _parseTaskInfo(taskInfo, &(DungeonsProxy::shared()->maxTaskInfo));
            }
        }
        else{
            //TODO: 解析出错
            //NSLog(@"NetController::_parseRegist(): taskMax is null.");
        }

        //NSLog(@"taskMax: %@", taskMax);

        /**
         *挑战宿敌信息
         */
        NSDictionary* challengeEnemyList = [player objectForKey:@"challengeEnemyList"];
        if ((challengeEnemyList != nil)
            && (![challengeEnemyList isEqual:[NSNull null]])
            && (![challengeEnemyList isEqual:@""]))
        {
            int count = [challengeEnemyList count];
            for (int i=0; i<count; i++)
            {
                NSArray* enemy = [challengeEnemyList objectAtIndex:i];
                if ((enemy != nil)
                    && (![enemy isEqual:[NSNull null]])
                    && (![enemy isEqual:@""]))
                {
                    //TODO: 上层对应
                    _parseChallengeEnemyList(enemy, NULL);
                }
                else
                {
                    //TODO: 解析出错
                    //NSLog(@"NetController::_parseRegist(): enemy[%@] is null.", i);
                }
            }
        }
        else{
            //TODO: 解析出错
            //NSLog(@"NetController::_parseRegist(): challengeEnemyList is null.");
        }

        //NSLog(@"challengeEnemyList: %@", challengeEnemyList);

        /**
         *抢夺宿敌信息
         */
        NSDictionary* snatchEnemyList = [player objectForKey:@"snatchEnemyList"];
        if ((snatchEnemyList != nil)
            && (![snatchEnemyList isEqual:[NSNull null]])
            && (![snatchEnemyList isEqual:@""]))
        {
            int count = [snatchEnemyList count];
            for (int i=0; i<count; i++)
            {
                NSArray* enemy = [snatchEnemyList objectAtIndex:i];
                if ((enemy != nil)
                    && (![enemy isEqual:[NSNull null]])
                    && (![enemy isEqual:@""]))
                {
                    //TODO: 上层对应
                    _parseSnatchEnemyList(enemy, NULL);
                }
                else
                {
                    //TODO: 解析出错
                    //NSLog(@"NetController::_parseRegist(): enemy[%@] is null.", i);
                }
            }
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseRegist(): snatchEnemyList is null.");
        }

        //NSLog(@"snatchEnemyList: %@", snatchEnemyList);

        /**
         *碎片信息
         */
        NSDictionary* fragmentArray = [player objectForKey:@"fragmentArray"];
        if ((fragmentArray != nil)
            && (![fragmentArray isEqual:[NSNull null]])
            && (![fragmentArray isEqual:@""]))
        {
            //TODO: 上层对应
            _parseFragmentArray(fragmentArray, NULL);
        }
        else
        {
            //TODO: 解析出错
            //NSLog(@"NetController::_parseRegist(): fragmentArray is null.");
        }

        //NSLog(@"fragmentArray: %@", fragmentArray);

        /**
         *下次免费开宝箱的剩余秒数(0:拥有一次开宝箱机会)
         */
        NSNumber* remainderOpenBoxTime = [player objectForKey:@"remainderOpenBoxTime"];
        ShopProxy::shared()->mRemainderOpenBoxTime = [remainderOpenBoxTime intValue];
        NSLog(@"remainderOpenBoxTime: %@", remainderOpenBoxTime);

        NSNumber* remainderRechargingEnergyTime = [player objectForKey:@"remainderRechargingEnergyTime"];
        //NSLog(@"remainderRechargingEnergyTime: %@", remainderRechargingEnergyTime);
        
        userVO.energyTime = [remainderRechargingEnergyTime intValue] * 1000;
        
        UserProxy::shared()->saveUserInfo();
    }

    //NSLog(@"NetController::_parseSelfInfo() end");
}

bool NetController::buyItem(int itemID, int count)
{
    return true;
}

/**
 * @brief     使用道具命令函数。
 * @param[in] itemID   道具id
 * @return    true  成功。
 * @return    false 失败。
 */
bool NetController::useItem(int itemID)
{
    return true;
}

/**
 * @brief     领奖命令函数。
 * @return    true  成功。
 * @return    false 失败。
 */
bool NetController::getPrize()
{
    return true;
}

/**
 * @brief     请求刷新神秘商店命令函数。
 * @return    true  成功。
 * @return    false 失败。
 */
bool NetController::refreshMysteryShop()
{
    return true;
}

/**
 * @brief     请求刷新神秘商店命令函数。
 * @return    true  成功。
 * @return    false 失败。
 */
bool NetController::getAllEvent()
{
    return true;
}

/**
 * @brief     请求刷新神秘商店命令函数。
 * @return    true  成功。
 * @return    false 失败。
 */
bool NetController::getFightEvent()
{
    return true;
}

/**
 * @brief     请求刷新神秘商店命令函数。
 * @return    true  成功。
 * @return    false 失败。
 */
bool NetController::getSystemEvent()
{
    return true;
}

bool NetController::buyMoney(const std::string& identifier, const std::string& receipt)
{
    //NSLog(@"NetController::buyMoney() start");
    //NSLog(@"NetController::buyMoney(): receipt: %s", receipt.c_str());
    //NSLog(@"NetController::buyMoney(): identifier: %s", identifier.c_str());

    //将参数进行组合
    NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                            [NSString stringWithFormat:@"%s", receipt.c_str()], @"receipt",
                            [NSString stringWithFormat:@"%s", identifier.c_str()], @"identifier",
                            nil];

    //NSLog(@"NetController::buyMoney() end");

    //命令发送
    return _sendCommand(kNCBuyMoney, params);
}

void NetController::_parseLevelInfo(void* params)
{
    NSDictionary* synchro = (NSDictionary*)params;
    //NSLog(@"synchro: %@", synchro);
    NSNumber* level = [synchro objectForKey:@"level"];
    NSNumber* exp = [synchro objectForKey:@"exp"];
    NSNumber* coin = [synchro objectForKey:@"coin"];
    NSNumber* money = [synchro objectForKey:@"money"];
    NSNumber* energyCur = [synchro objectForKey:@"energyCur"];
    NSNumber* energyMax = [synchro objectForKey:@"energyMax"];
    NSNumber* powerCur = [synchro objectForKey:@"powerCur"];
    NSNumber* powerMax = [synchro objectForKey:@"powerMax"];
    NSNumber* lifeCur = [synchro objectForKey:@"lifeCur"];
    NSNumber* life = [synchro objectForKey:@"life"];
    NSNumber* atkMin = [synchro objectForKey:@"atkMin"];
    NSNumber* atkMax = [synchro objectForKey:@"atkMax"];
    NSNumber* defMin = [synchro objectForKey:@"defMin"];
    NSNumber* defMax = [synchro objectForKey:@"defMax"];
    NSNumber* atkMaxReappear = [synchro objectForKey:@"atkMaxReappear"];
    NSNumber* defMaxReappear = [synchro objectForKey:@"defMaxReappear"];
    NSNumber* expGainRatio = [synchro objectForKey:@"expGainRatio"];
    NSNumber* coinGainRatio = [synchro objectForKey:@"coinGainRatio"];
    NSNumber* equipageDropRatio = [synchro objectForKey:@"equipageDropRatio"];
    NSNumber* energyRecoverRatio = [synchro objectForKey:@"energyRecoverRatio"];
    NSNumber* powerRecoverRatio = [synchro objectForKey:@"powerRecoverRatio"];

    UserVO& userVO = UserProxy::shared()->userVO;
    userVO.level = [level intValue];
    userVO.exp = [exp intValue];
    userVO.coin = [coin intValue];
    userVO.money = [money intValue];
    userVO.energyCur = [energyCur intValue];
    userVO.energyMax = [energyMax intValue];
    userVO.powerCur = [powerCur intValue];
    userVO.powerMax = [powerMax intValue];
    userVO.lifeCur = [lifeCur intValue];
    userVO.life = [life intValue];
    userVO.atkMin = [atkMin intValue];
    userVO.atkMax = [atkMax intValue];
    userVO.defMin = [defMin intValue];
    userVO.defMax = [defMax intValue];
    userVO.atkMaxReappear = [atkMaxReappear intValue];
    userVO.defMaxReappear = [defMaxReappear intValue];
    userVO.expGainRatio = [expGainRatio intValue];
    userVO.coinGainRatio = [coinGainRatio intValue];
    userVO.equipageDropRatio = [equipageDropRatio intValue];
    userVO.energyRecoverRatio = [energyRecoverRatio intValue];
    userVO.powerRecoverRatio = [powerRecoverRatio intValue];

    //NSLog(@"level: %@", level);
    //NSLog(@"exp: %@", exp);
    //NSLog(@"coin: %@", coin);
    //NSLog(@"money: %@", money);
    //NSLog(@"energyCur: %@", energyCur);
    //NSLog(@"energyMax: %@", energyMax);
    //NSLog(@"powerCur: %@", powerCur);
    //NSLog(@"powerMax: %@", powerMax);
    //NSLog(@"lifeCur: %@", lifeCur);
    //NSLog(@"life: %@", life);
    //NSLog(@"atkMin: %@", atkMin);
    //NSLog(@"atkMax: %@", atkMax);
    //NSLog(@"defMin: %@", defMin);
    //NSLog(@"defMax: %@", defMax);
    //NSLog(@"atkMaxReappear: %@", atkMaxReappear);
    //NSLog(@"defMaxReappear: %@", defMaxReappear);
    //NSLog(@"expGainRatio: %@", expGainRatio);
    //NSLog(@"coinGainRatio: %@", coinGainRatio);
    //NSLog(@"equipageDropRatio: %@", equipageDropRatio);
    //NSLog(@"energyRecoverRatio: %@", energyRecoverRatio);
    //NSLog(@"powerRecoverRatio: %@", powerRecoverRatio);
}

void NetController::_syncEquipInfo(void* params)
{
    NSDictionary* player = (NSDictionary*)params;
    if ((player != nil)
        && (![player isEqual:[NSNull null]])
        && (![player isEqual:@""]))
    {
        NSNumber* atkMin = [player objectForKey:@"atkMin"];
        NSNumber* atkMax = [player objectForKey:@"atkMax"];
        NSNumber* defMin = [player objectForKey:@"defMin"];
        NSNumber* defMax = [player objectForKey:@"defMax"];
        
        NSNumber* atkMaxReappear = [player objectForKey:@"atkMaxReappear"];
        NSNumber* defMaxReappear = [player objectForKey:@"defMaxReappear"];
        
        NSNumber* energyMax = [player objectForKey:@"energyMax"];
        NSNumber* energyRecoverRatio = [player objectForKey:@"energyRecoverRatio"];
        
        NSNumber* life = [player objectForKey:@"life"];
        NSNumber* lifeRecoverRatio = [player objectForKey:@"lifeRecoverRatio"];
        
        NSNumber* mf = [player objectForKey:@"mf"];
        
        NSNumber* expGainRatio = [player objectForKey:@"expGainRatio"];
        NSNumber* coinGainRatio = [player objectForKey:@"coinGainRatio"];
        
        UserVO& userVO = UserProxy::shared()->userVO;
        userVO.atkMin = [atkMin intValue];
        userVO.atkMax = [atkMax intValue];
        userVO.defMin = [defMin intValue];
        userVO.defMax = [defMax intValue];
        userVO.atkMaxReappear = [atkMaxReappear intValue];
        userVO.defMaxReappear = [defMaxReappear intValue];
        userVO.energyMax = [energyMax intValue];
        userVO.energyRecoverRatio = [energyRecoverRatio intValue];
        userVO.life = [life intValue];
//        userVO.lifeRecoverRatio = [lifeRecoverRatio intValue];
        userVO.expGainRatio = [expGainRatio intValue];
        userVO.coinGainRatio = [coinGainRatio intValue];
    }
    else
    {
        
    }
}

#endif

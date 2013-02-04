/**
 * @file
 * @brief   网络命令类定义头文件。
 * @author  赵一
 * @date    2012/08/01
 * @version 0.1
 */

#ifndef _NetController_h_
#define _NetController_h_

#include "Global.h"
#include "NCDefines.h"
#include "DungeonsProxy.h"
#include "UserProxy.h"
#include "ItemProxy.h"
#include "FightProxy.h"
#include "ChanllengeProxy.h"
#include "ShopProxy.h"

#if NETCONTROLLER_USE_JSON
#include "json.h"
#endif

#define Post_Net_Notification(ncName, params) \
CCLOG("PostNotification:%s", ncName);   \
NotificationCenter::shared()->postNotification(ncName, params);

class NetController : public CCObject, public Singleton<NetController>
{
public:
    NetController();
    ~NetController();

    /// 初始化函数。
    bool init(const char* url);

    /// 数据解析函数。
    void parseData(void* data);

    /// 网络错误处理函数。
    void receiveError();


    /// 发送的网络消息
    bool gameInit();
    bool regist(const string& name, int avata);
    bool getSelfInfo();
    bool dungeonExplore(int dungeon, int floor, int task);
    bool dungeonStart(int dungeon, int floor);
    bool loadEquipage(int index);
    bool unloadEquipage(int index);
    bool sellEquipage(const vector<int>& indexArray);
    bool resetEquipage(int index);
    bool fusionEquipage(const vector<int>& indexArray);
    bool intensifyEquipage(int index, int number);
    bool findChallengePlayerByName(const string& name);
    bool findChallengePlayerByPid(int pid);
    bool getChallengeList();
    bool getChallengeEnemyList();
    bool challengePlayer(int pid);
    bool openBox(int type, int id);
    bool buyEnergy(int type);
    bool buyPower(int type);
    bool buyLife(int type);
    bool buyCoin(int id);
    bool getAmuletEnemyList();
    bool getFragmentEnemyList(int itemID);
    bool findSnatchAmuletInfo(int id);
    bool findSnatchFragmentInfo(int id);
    bool snatchPlayer(int pid, int itemID);
    bool composeEquipage(int itemID);
    bool getComposeEquipageList();
    bool buyItem(int itemID, int count);
    bool useItem(int itemID);
    bool getPrize();
    bool refreshMysteryShop();
    bool getAllEvent();
    bool getFightEvent();
    bool getSystemEvent();
    bool buyMoney(const string& identifier, const string& receipt);

private:
    /// 发送队列中下一个包，如果没有，则关闭遮挡层
    void _sendNext();

    /// 发送网络命令函数。
    bool _sendCommand(const string& cmd, void* data);
    
    /// 真实发送接口
    void _trueSend(const string& data);

    /// 服务器处理错误函数。
    void _parseError(const string& cmd, int error);

    /// 取得PID函数。
    string _getPid();
    
    /// 取得平台类型函数。
    int _getPlatform();
    
    /// 取得网络命令版本号函数。
    string _getVersion();

    /// 同步装备信息
    void _syncEquipInfo(void* params);

    /// 解析细节数据
    void _parseEquipageInfo(void* data, EquipInfo* info);
    void _parsePropInfo(void* data, ItemInfo* info);
    void _parseTaskInfo(void* data, TaskInfo* info);
    void _parseChallengeEnemyList(void* data, void* info);
    void _parseSnatchEnemyList(void* data, void* info);
    void _parseFragmentArray(void* data, void* info);
    void _parseChallengeEnemyInfo(void* data, ChallengeEnemyInfo* info, bool isParseEnemy=true);

    /// 解析网络命令
    void _parseGameInit(void* params);
    void _parseRegist(void* params);
    void _parseGetSelfInfo(void* params);
    void _parseDungeonExplore(void* params);
    void _parseDungeonStart(void* params);
    void _parseLoadEquipage(void* params);
    void _parseUnloadEquipage(void* params);
    void _parseSellEquipage(void* params);
    void _parseResetEquipage(void* params);
    void _parseFusionEquipage(void* params);
    void _parseIntensifyEquipage(void* params);
    void _parseGetChallengeList(void* params);
    void _parseChallengePlayer(void* params);
    void _parseGetChallengeEnemyList(void* params);
    void _parseFindChallengePlayer(void* params);
    void _parseOpenBox(void* params);
    void _parseBuyEnergy(void* params);
    void _parseBuyPower(void* params);
    void _parseBuyLife(void* params);
    void _parseBuyMoney(void* params);
    void _parseBuyCoin(void* params);
    void _parseSelfInfo(void* params);
    void _parseBuyItem(void* params);
    void _parseUseItem(void* params);
    void _parseGetPrize(void* params);
    bool _parseRefreshMysteryShop(void* params);
    void _parseLevelInfo(void* params);
    
#if NETCONTROLLER_USE_JSON
    void onHttpRequestCompleted(CCObject* sender, void* data);
    int _readJsonInt(Json::Value& value);
#endif
    
private:
    /// 平台类型
    int mPlatform;

    /// 用户PID。
    string mPid;

    /// 版本号。
    string mVersion;

    /// 用户GID。(通过注册命令返回的信息中读取)
    int mGid;

    /// 服务器地址
    string mServerAddress;
};

#define NCCTRL  NetController::shared()

#endif

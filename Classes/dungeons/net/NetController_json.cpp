#include "NetController.h"
#include "CommonHelper.h"

#if NETCONTROLLER_USE_JSON

#include "NCUtils.h"
#include "Waitting.h"

struct PackageInfo
{
    string cmd;
    string package;
};

queue<PackageInfo> gsPackageList;
bool isWaitReceive;
static const char* gHttpRequestTag = "POST HB JSON";

NetController::NetController()
    : mPlatform(-1)
    , mGid(-1)
{
    isWaitReceive = false;
}

NetController::~NetController()
{
}

bool NetController::init(const char* url)
{
    assert(url);
    
    mPlatform = _getPlatform();
    mPid = _getPid();
    mVersion = _getVersion();
    mServerAddress = url;

    CCHttpClient::getInstance()->setTimeoutForConnect(20);
    CCHttpClient::getInstance()->setTimeoutForRead(30);
    
    return true;
}

void NetController::parseData(void* data)
{
    CCLOG("%s start", __FUNCTION__);
    
    isWaitReceive = false;
    
    CCHttpResponse* response = (CCHttpResponse*)data;
    
	if (!response)
	{
		CCLOG("%s response is NULL", __FUNCTION__);
        _sendNext();
		return;
	}
    
	int statusCode = response->getResponseCode();
	if( statusCode != 200 )
	{
		CCLOG("%s response code is [%d]", __FUNCTION__, statusCode);
        _sendNext();
		return;
	}
    
    if (0 != strcmp(gHttpRequestTag, response->getHttpRequest()->getTag()))
    {
        CCLOG("%s request tag[%s] is different", __FUNCTION__, response->getHttpRequest()->getTag());
        _sendNext();
        return;
    }
    
    if (!response->isSucceed())
    {
        CCLOG("%s response failed", __FUNCTION__);
        CCLOG("%s error buffer: %s", __FUNCTION__, response->getErrorBuffer());
        _sendNext();
        return;
    }
    
    // dump data
    vector<char>* buffer = response->getResponseData();
    string bufferStr = string(buffer->begin(), buffer->end());
    CCLOG("%s content:%s", __FUNCTION__, bufferStr.c_str());

	Json::Reader reader;
	Json::Value value;
    
	if(reader.parse(bufferStr, value))
	{
        if (!value.isObject())
        {
            CCLOG("%s is not object", __FUNCTION__);
            _sendNext();
            return;
        }
        
        string version = value["version"].asString();

		Json::Value result = value["result"][0];
        string cmd = result["cmd"].asString();
        
        // 版本号错误
        if ( version.empty() || (version != mVersion && cmd != kNCGameInit) )
        {
            Post_Net_Notification(kNCVersionError, NULL);
            return;
        }

        //取得结果状态（0：命令执行成功。1：命令执行出错）
        int status = _readJsonInt(result["status"]);
        if (status == 1)
        {
            int errorCode = _readJsonInt(result["__code"]);
            string errorMessage = result["__message"].asString();
            string errorLine = result["__line"].asString();
            
            _parseError(cmd, errorCode);
            _sendNext();
            return;
        }
        
        Json::Value data = result["data"];
        
        //调用解析处理
             if (cmd == kNCGameInit)                _parseGameInit(&data);
        else if (cmd == kNCRegist)                  _parseRegist(&data);
        else if (cmd == kNCGetSelfInfo)             _parseGetSelfInfo(&data);
        else if (cmd == kNCDungeonExplore)          _parseDungeonExplore(&data);
        else if (cmd == kNCDungeonStart)            _parseDungeonStart(&data);
        else if (cmd == kNCLoadEquipage)            _parseLoadEquipage(&data);
        else if (cmd == kNCSellEquipage)            _parseSellEquipage(&data);
        else if (cmd == kNCUnloadEquipage)          _parseUnloadEquipage(&data);
        else if (cmd == kNCResetEquipage)           _parseResetEquipage(&data);
        else if (cmd == kNCFusionEquipage)          _parseFusionEquipage(&data);
        else if (cmd == kNCIntensifyEquipage)       _parseIntensifyEquipage(&data);
        else if (cmd == kNCGetChallengeList)        _parseGetChallengeList(&data);
        else if (cmd == kNCChallengePlayer)         _parseChallengePlayer(&data);
        else if (cmd == kNCGetChallengeEnemyList)   _parseGetChallengeEnemyList(&data);
        else if (cmd == kNCOpenBox)                 _parseOpenBox(&data);
        else if (cmd == kNCBuyEnergy)               _parseBuyEnergy(&data);
        else if (cmd == kNCBuyPower)                _parseBuyPower(&data);
        else if (cmd == kNCBuyLife)                 _parseBuyLife(&data);
        else if (cmd == kNCBuyMoney)                _parseBuyMoney(&data);
        else if (cmd == kNCBuyCoin)                 _parseBuyCoin(&data);
	}
    else
    {
        CCLOG("%s reader.parse failed", __FUNCTION__);
    }

    _sendNext();
    
    CCLOG("%s end", __FUNCTION__);    
}

void NetController::receiveError()
{
    isWaitReceive = false;
}

#pragma mark - 发送接口
bool NetController::gameInit()
{
    return _sendCommand(kNCGameInit, NULL);
}

bool NetController::regist(const string& name, int avata)
{
    Json::Value params;
    params["name"] = name;
    params["avata"] = avata;
    return _sendCommand(kNCRegist, &params);
}

bool NetController::getSelfInfo()
{
    return _sendCommand(kNCGetSelfInfo, NULL);
}

bool NetController::dungeonExplore(int dungeon, int floor, int task)
{
    Json::Value params;
    params["dungeon"] = dungeon;
    params["floor"] = floor;
    params["task"] = task;
    return _sendCommand(kNCDungeonExplore, &params);
}

bool NetController::dungeonStart(int dungeon, int floor)
{
    Json::Value params;
    params["dungeon"] = dungeon;
    params["floor"] = floor;
    return _sendCommand(kNCDungeonStart, &params);
}

bool NetController::loadEquipage(int index)
{
    ItemProxy::shared()->putonIndex = index;
    Json::Value params;
    params["index"] = index;
    return _sendCommand(kNCLoadEquipage, &params);
}

bool NetController::unloadEquipage(int index)
{
    ItemProxy::shared()->putonIndex = index;
    Json::Value params;
    params["index"] = index;
    return _sendCommand(kNCUnloadEquipage, &params);
}

bool NetController::sellEquipage(const vector<int>& indexArray)
{
    Json::Value list;
    for (int i = 0; i < indexArray.size(); i++)
        list[i] = indexArray[i];
    
    Json::Value params;
    params["index"] = list;
    return _sendCommand(kNCSellEquipage, &params);
}

bool NetController::resetEquipage(int index)
{
    Json::Value params;
    params["index"] = index;
    return _sendCommand(kNCResetEquipage, &params);
}

bool NetController::fusionEquipage(const vector<int>& indexArray)
{
    Json::Value list;
    for (int i = 0; i < indexArray.size(); i++)
        list[i] = indexArray[i];
    
    Json::Value params;
    params["index"] = list;
    return _sendCommand(kNCFusionEquipage, &params);
}

bool NetController::intensifyEquipage(int index, int number)
{
    Json::Value params;
    params["index"] = index;
    params["number"] = number;
    return _sendCommand(kNCIntensifyEquipage, &params);
}

bool NetController::findChallengePlayerByName(const string& name)
{
    Json::Value params;
    params["name"] = name;
    return _sendCommand(kNCFindChallengePlayerByName, &params);
}

bool NetController::getChallengeList()
{
    return _sendCommand(kNCGetChallengeList, NULL);
}

bool NetController::getChallengeEnemyList()
{
    return _sendCommand(kNCGetChallengeEnemyList, NULL);
}

bool NetController::challengePlayer(int gid)
{
    Json::Value params;
    params["gid"] = gid;
    return _sendCommand(kNCChallengePlayer, &params);
}

bool NetController::openBox(int type, int id)
{
    Json::Value params;
    params["id"] = id;
    params["type"] = type;
    return _sendCommand(kNCOpenBox, &params);
}

bool NetController::buyEnergy(int type)
{
    Json::Value params;
    params["type"] = type;
    return _sendCommand(kNCBuyEnergy, &params);
}

bool NetController::buyPower(int type)
{
    Json::Value params;
    params["type"] = type;
    return _sendCommand(kNCBuyPower, &params);
}

bool NetController::buyLife(int type)
{
    Json::Value params;
    params["type"] = type;
    return _sendCommand(kNCBuyLife, &params);
}

bool NetController::buyCoin(int id)
{
    Json::Value params;
    params["id"] = id;
    return _sendCommand(kNCBuyCoin, &params);
}

bool NetController::snatchPlayer(int pid, int itemID)
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

bool NetController::buyItem(int itemID, int count)
{
    return true;
}

bool NetController::useItem(int itemID)
{
    return true;
}

bool NetController::getPrize()
{
    return true;
}

bool NetController::refreshMysteryShop()
{
    return true;
}

bool NetController::getAllEvent()
{
    return true;
}

bool NetController::getFightEvent()
{
    return true;
}

bool NetController::getSystemEvent()
{
    return true;
}

bool NetController::buyMoney(const string& identifier, const string& receipt)
{
    Json::Value params;
    params["receipt"] = receipt;
    params["identifier"] = identifier;
    return _sendCommand(kNCBuyMoney, &params);
}

#pragma mark - 解析数据

void NetController::_parseGameInit(void* params)
{
    Json::Value& p = (Json::Value&)*params;
    
    int initResult = _readJsonInt(p["result"]);

    string notice = p["notice"].asString();
    if (!notice.empty())
    {
        //有网页通知
        notice += "/html/notice.html";
        UserProxy::shared()->mHtmlUrl = notice;
    }

    string config = p["config"].asString();
    config += "/";
    UserProxy::shared()->mServerUrl = config;
    UserProxy::shared()->mConfigUrl = config + "config/";
    UserProxy::shared()->mResourceUrl = config + "sprite/";

    Json::Value& version = p["version"];
    XMLVersionMap& xmlVersionMap = UserProxy::shared()->mXMLVersionMap;

    xmlVersionMap["Boss.xml"] = version["Boss"].asString();
    xmlVersionMap["Box.xml"] = version["Box"].asString();
    xmlVersionMap["BuyMoney.xml"] = version["BuyMoney"].asString();
    xmlVersionMap["Compose.xml"] = version["Compose"].asString();
    xmlVersionMap["Drop.xml"] = version["Drop"].asString();
    xmlVersionMap["Dungeon.xml"] = version["Dungeon"].asString();
    xmlVersionMap["Equipage.xml"] = version["Equipage"].asString();
    xmlVersionMap["Event.xml"] = version["Event"].asString();
    xmlVersionMap["LocalString.xml"] = version["LocalString"].asString();
    xmlVersionMap["Player.xml"] = version["Player"].asString();
    xmlVersionMap["Rule.xml"] = version["Rule"].asString();
    xmlVersionMap["Supplement.xml"] = version["Supplement"].asString();
    xmlVersionMap["Task.xml"] = version["Task"].asString();

    Post_Net_Notification(kNCGameInit, (CCObject*)initResult);
}

void NetController::_parseRegist(void* params)
{
    _parseSelfInfo(params);
    Post_Net_Notification(kNCRegist, NULL);
}

void NetController::_parseGetSelfInfo(void* params)
{
    _parseSelfInfo(params);
    Post_Net_Notification(kNCGetSelfInfo, NULL);
}

void NetController::_parseDungeonExplore(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    Json::Value& taskInfo = data["task"];

    DungeonsProxy::shared()->curTaskInfo.dungeonID = _readJsonInt(taskInfo["dungeon"]);
    DungeonsProxy::shared()->maxTaskInfo.dungeonID = _readJsonInt(taskInfo["dungeon"]);

    _parseTaskInfo(&taskInfo["taskCur"], &(DungeonsProxy::shared()->curTaskInfo));
    _parseTaskInfo(&taskInfo["taskMax"], &(DungeonsProxy::shared()->maxTaskInfo));

    Json::Value& awardInfo = data["award"];

    //固定奖励
    Award& award = FightProxy::shared()->awardInfo;
    award.clear();
    award.exp = _readJsonInt(awardInfo["exp"]);
    award.coin = _readJsonInt(awardInfo["coin"]);
    award.eventType = EVENT_TYPE_NONE;
    
    //事件奖励
    string eventType = awardInfo["eventType"].asString();
    if (eventType == "none")
    {
        //没有事件发生
        award.eventType = EVENT_TYPE_NONE;
    }
    else if (eventType == "coin")
    {
        //金币掉落事件发生
        award.eventCoin = _readJsonInt(awardInfo["eventValue"]);
        award.eventType = EVENT_TYPE_GET_COIN;
    }
    else if (eventType == "energy")
    {
        //能量掉落事件发生
        award.energy = _readJsonInt(awardInfo["eventValue"]);
        award.eventType = EVENT_TYPE_GET_ENERGY;
    }
    else if (eventType == "life")
    {
        //掉血事件发生
        award.life = _readJsonInt(awardInfo["eventValue"]);
        award.eventType = EVENT_TYPE_LOST_LIFE;
    }
    else if (eventType == "drop")
    {
        if (!ItemProxy::shared()->isBagFull())
        {
            //装备掉落事件发生
            Json::Value& eventEquipageArray = awardInfo["eventValue"];
            award.eventType = EVENT_TYPE_GET_EQUIP;
            for (int i = 0; i < eventEquipageArray.size(); i++)
            {
                EquipInfo* equipInfo = new EquipInfo();
                _parseEquipageInfo(&eventEquipageArray[i], equipInfo);
                ItemProxy::shared()->addEquip(equipInfo);
                award.equipList.push_back(equipInfo);
            }
        }
        else
        {
            NetError netError;
            netError.cmdName = kNCNetError;
            netError.errorCode = kNCErrorBagFull;
            Post_Net_Notification(kNCNetError, (CCObject*)(&netError));
        }
    }

    //掉落奖励
    //TODO:又一个掉落？
    Json::Value& equipageArray = awardInfo["equipage"];
    if (!ItemProxy::shared()->isBagFull())
    {
        for (int i = 0; i < equipageArray.size(); i++)
        {
            EquipInfo* equipInfo = new EquipInfo();
            _parseEquipageInfo(&equipageArray[i], equipInfo);
            ItemProxy::shared()->addEquip(equipInfo);
            award.equipList.push_back(equipInfo);
        }
    }
    else
    {
        NetError netError;
        netError.cmdName = kNCNetError;
        netError.errorCode = kNCErrorBagFull;
        Post_Net_Notification(kNCNetError, (CCObject*)(&netError));
    }

    FightProxy::shared()->battleInfo.win = 0;
    Json::Value& battleInfo = data["battle"];
    if (!battleInfo.isNull())
    {
        Json::Value& bossInfo = battleInfo["boss"];
        FightBoss& fightBoss = FightProxy::shared()->mFightBoss;
        fightBoss.level = _readJsonInt(bossInfo["level"]);
        fightBoss.life = _readJsonInt(bossInfo["life"]);
        fightBoss.atkMin= _readJsonInt(bossInfo["atkMin"]);
        fightBoss.atkMax = _readJsonInt(bossInfo["atkMax"]);
        fightBoss.defMin = _readJsonInt(bossInfo["defMin"]);
        fightBoss.defMax = _readJsonInt(bossInfo["defMax"]);

        Json::Value& roundInfo = battleInfo["round"];
        for (int i = 0; i < roundInfo.size(); i++)
        {
//            int atkUsr = _readJsonInt(roundInfo[i][0]);  //1: 玩家为攻击方, 2: boss为攻击方
//            int atkMax = _readJsonInt(roundInfo[i][1]);  //是否发生了最大攻击 1: 发生了最大攻击力， 0：没发生最大攻击力
//            int defMax = _readJsonInt(roundInfo[i][2]);  //是否发生了最大防御 1: 发生了最大防御力， 0：没发生最大防御力
//            int life = _readJsonInt(roundInfo[i][3]);    //攻击对于life造成的伤害
        }

        //1: 玩家为获胜方, 2: boss为获胜方
        FightProxy::shared()->battleInfo.win = _readJsonInt(battleInfo["win"]);
    }

    _parseLevelInfo(&data["synchro"]);

    UserProxy::shared()->userVO.energyTime = _readJsonInt(data["remainderRechargingEnergyTime"]) * 1000;

    Post_Net_Notification(kNCDungeonExplore, NULL);
}

void NetController::_parseDungeonStart(void* params)
{
    Json::Value& data = (Json::Value&)*params;

    //当前任务信息。
    Json::Value& taskCur = data["taskCur"];
    Json::Value::Members taskCurMemeber = taskCur.getMemberNames();
    for (int i = 0; i < taskCurMemeber.size(); i++)
    {
        DungeonsProxy::shared()->curTaskInfo.dungeonID = atoi(taskCurMemeber[i].c_str());
        _parseTaskInfo(&taskCur[taskCurMemeber[i]], &(DungeonsProxy::shared()->curTaskInfo));
    }

    //玩家当前生命数值
    UserProxy::shared()->userVO.lifeCur = _readJsonInt(data["lifeCur"]);
    UserProxy::shared()->userVO.life = _readJsonInt(data["life"]);

    Post_Net_Notification(kNCDungeonStart, NULL);
}

void NetController::_parseLoadEquipage(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    if (_readJsonInt(data["result"]) == 1)
    {
        //装备成功
        ItemProxy::shared()->putOnEquip(ItemProxy::shared()->putonIndex);
        _syncEquipInfo(&data["player"]);
    }
    
    Post_Net_Notification(kNCLoadEquipage, NULL);
}

void NetController::_parseUnloadEquipage(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    if (_readJsonInt(data["result"]) == 1)
    {
        //卸载成功
        ItemProxy::shared()->takeOffEquip(ItemProxy::shared()->putonIndex);
        _syncEquipInfo(&data["player"]);
    }

    Post_Net_Notification(kNCUnloadEquipage, NULL);
}

void NetController::_parseSellEquipage(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    UserProxy::shared()->userVO.coin = _readJsonInt(data["coin"]);
    vector<int>& sellList = ItemProxy::shared()->sellList;
    ItemProxy::shared()->sellItem(sellList);
    sellList.clear();
        
    _syncEquipInfo(&data["player"]);

    Post_Net_Notification(kNCSellEquipage, NULL);
}

void NetController::_parseResetEquipage(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    EquipInfo equipInfo;
    _parseEquipageInfo(&data["equipage"], &equipInfo);
    ItemProxy::shared()->addEquip(&equipInfo);
    ItemProxy::shared()->setLastQiangHuaEquip(ItemProxy::shared()->getEquip(equipInfo.index));

    Post_Net_Notification(kNCResetEquipage, NULL);
}

void NetController::_parseFusionEquipage(void* params)
{
//    Json::Value& data = (Json::Value&)*params;
//    int fusion = data["fusion"].asInt();
    vector<int>& items = ItemProxy::shared()->mSelectList;
    for(int i = 0; i < items.size(); i++)
        ItemProxy::shared()->removeEquip(items[i]);

    Post_Net_Notification(kNCFusionEquipage, NULL);
}

void NetController::_parseIntensifyEquipage(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    UserVO& userVO = UserProxy::shared()->userVO;
    userVO.coin = _readJsonInt(data["coin"]);
    userVO.energyCur = _readJsonInt(data["energyCur"]);
    userVO.fusion = _readJsonInt(data["fusion"]);

    EquipInfo equipInfo;
    _parseEquipageInfo(&data["equipage"], &equipInfo);
    ItemProxy::shared()->addEquip(&equipInfo, true);
    ItemProxy::shared()->curQiangHuaEquip = ItemProxy::shared()->getEquip(equipInfo.index);

    Post_Net_Notification(kNCIntensifyEquipage, NULL);
}

void NetController::_parseFindChallengePlayer(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    
    ChanllengeProxy::shared()->clearChallengeEnemyList();
    ChallengeEnemyList& challengeEnemyList = ChanllengeProxy::shared()->mChallengeEnemyList;
    Json::Value& playerList = data["playerList"];
    for (int i = 0; i < playerList.size(); i++)
    {
        ChallengeEnemyInfo* challengeEnemyInfo = new ChallengeEnemyInfo();
        _parseChallengeEnemyInfo(&playerList[i], challengeEnemyInfo, false);
        challengeEnemyList.push_back(challengeEnemyInfo);
    }

    Post_Net_Notification(kNCFindChallengePlayerByName, NULL);
}

void NetController::_parseGetChallengeList(void* params)
{
    Json::Value& data = (Json::Value&)*params;

    ChanllengeProxy::shared()->clearChallengeEnemyList();
    ChallengeEnemyList& challengeEnemyList = ChanllengeProxy::shared()->mChallengeEnemyList;
    Json::Value& playerList = data["playerList"];
    for (int i = 0; i < playerList.size(); i++)
    {
        ChallengeEnemyInfo* challengeEnemyInfo = new ChallengeEnemyInfo();
        _parseChallengeEnemyInfo(&playerList[i], challengeEnemyInfo, false);
        challengeEnemyList.push_back(challengeEnemyInfo);
    }

    Post_Net_Notification(kNCGetChallengeList, NULL);
}

void NetController::_parseGetChallengeEnemyList(void* params)
{
    Json::Value& data = (Json::Value&)*params;

    ChanllengeProxy::shared()->clearChallengeEnemyList();
    ChallengeEnemyList& challengeEnemyList = ChanllengeProxy::shared()->mChallengeEnemyList;
    Json::Value& playerList = data["challengeEnemyList"];
    for (int i = 0; i < playerList.size(); i++)
    {
        ChallengeEnemyInfo* challengeEnemyInfo = new ChallengeEnemyInfo();
        _parseChallengeEnemyInfo(&playerList[i], challengeEnemyInfo);
        challengeEnemyList.push_back(challengeEnemyInfo);
    }

    Post_Net_Notification(kNCGetChallengeEnemyList, NULL);
}

void NetController::_parseOpenBox(void* params)
{
    Json::Value& data = (Json::Value&)*params;

    //下次免费开宝箱的剩余秒数(0:拥有一次开宝箱机会)
    ShopProxy::shared()->mRemainderOpenBoxTime = _readJsonInt(data["remainderOpenBoxTime"]);
    
    UserProxy::shared()->userVO.coin = _readJsonInt(data["coin"]);
    UserProxy::shared()->userVO.money = _readJsonInt(data["money"]);
    ShopProxy::shared()->mSellResult.result = _readJsonInt(data["result"]);

    EquipInfo* equipInfo = new EquipInfo();
    _parseEquipageInfo(&data["equipage"], equipInfo);
    ItemProxy::shared()->addEquip(equipInfo, false);
    ShopProxy::shared()->mSellResult.clear();
    ShopProxy::shared()->mSellResult.mEquipInfo = equipInfo;

    Post_Net_Notification(kNCOpenBox, NULL);
}

void NetController::_parseBuyEnergy(void* params)
{
    Json::Value& data = (Json::Value&)*params;
//    int buyType = _readJsonInt(data["type"]);

    UserVO& userVO = UserProxy::shared()->userVO;
    userVO.energyCur = _readJsonInt(data["energyCur"]);
    userVO.energyMax = _readJsonInt(data["energyMax"]);
    userVO.coin = _readJsonInt(data["coin"]);
    userVO.money = _readJsonInt(data["money"]);

    Post_Net_Notification(kNCBuyEnergy, NULL);
}

void NetController::_parseBuyPower(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    //    int buyType = _readJsonInt(data["type"]);
    
    UserVO& userVO = UserProxy::shared()->userVO;
    userVO.powerCur = _readJsonInt(data["powerCur"]);
    userVO.coin = _readJsonInt(data["coin"]);
    userVO.money = _readJsonInt(data["money"]);

    Post_Net_Notification(kNCBuyPower, NULL);
}

void NetController::_parseBuyLife(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    //    int buyType = _readJsonInt(data["type"]);
    
    UserVO& userVO = UserProxy::shared()->userVO;
    userVO.lifeCur = _readJsonInt(data["lifeCur"]);
    userVO.coin = _readJsonInt(data["coin"]);
    userVO.money = _readJsonInt(data["money"]);

    Post_Net_Notification(kNCBuyLife, NULL);
}

void NetController::_parseBuyMoney(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    UserProxy::shared()->userVO.money = _readJsonInt(data["money"]);
//    string md5 = data["md5"];

    Post_Net_Notification(kNCBuyMoney, NULL);
}

void NetController::_parseBuyCoin(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    UserProxy::shared()->userVO.coin = _readJsonInt(data["coin"]);
    UserProxy::shared()->userVO.money = _readJsonInt(data["money"]);

    Post_Net_Notification(kNCBuyCoin, NULL);
}

void NetController::_parseChallengePlayer(void* params)
{
    Json::Value& data = (Json::Value&)*params;
    Json::Value& challenge = data["challenge"];

    ChallengeResult& mChallengeResult = ChanllengeProxy::shared()->mChallengeResult;
    //1: 玩家为获胜方, 2: 对手为获胜方
    mChallengeResult.result = _readJsonInt(challenge["win"]);
    Json::Value& roundInfo = challenge["round"];
    for (int i = 0; i < roundInfo.size(); i++)
    {
//        int atkUsr = _readJsonInt(roundInfo[i][0]);  //1: 玩家为攻击方, 2: 对手为攻击方
//        int atkMax = _readJsonInt(roundInfo[i][1]);  //是否发生了最大攻击 1: 发生了最大攻击力， 0：没发生最大攻击力
//        int defMax = _readJsonInt(roundInfo[i][2]);  //是否发生了最大防御 1: 发生了最大防御力， 0：没发生最大防御力
//        int life = _readJsonInt(roundInfo[i][3]);    //攻击对于life造成的伤害
    }

    ChanllengeProxy::shared()->mCurChallengeEnemyInfo->succeedExp = _readJsonInt(data["succeedExp"]);
    ChanllengeProxy::shared()->mCurChallengeEnemyInfo->succeedGold = _readJsonInt(data["succeedGold"]);
    ChanllengeProxy::shared()->mCurChallengeEnemyInfo->failedGold = _readJsonInt(data["failedGold"]);

    Json::Value& asyncInfo = data["asyncInfo"];
    UserVO& userVO = UserProxy::shared()->userVO;
    userVO.coin = _readJsonInt(asyncInfo["coin"]);
    userVO.level = _readJsonInt(asyncInfo["level"]);
    userVO.exp = _readJsonInt(asyncInfo["exp"]);
    userVO.energyCur = _readJsonInt(asyncInfo["energyCur"]);
    userVO.energyMax = _readJsonInt(asyncInfo["energyMax"]);
    userVO.powerCur = _readJsonInt(asyncInfo["powerCur"]);
    userVO.powerMax = _readJsonInt(asyncInfo["powerMax"]);
    userVO.energyTime = _readJsonInt(asyncInfo["energyTime"]);
    userVO.powerTime = _readJsonInt(asyncInfo["powerTime"]);

    Post_Net_Notification(kNCChallengePlayer, NULL);
}

void NetController::_parseEquipageInfo(void* data, EquipInfo* info)
{
    Json::Value& p = (Json::Value&)*data;
    Json::Value& equipageExt = p[kNCBagEquipageFieldExt];
    info->clearAffix();
    for (int i = 0; i < equipageExt.size(); i++)
    {
        Affix* affix = new Affix();
        affix->type = (AffixType)_readJsonInt(equipageExt[i][0]);     //词条类型
        affix->value = _readJsonInt(equipageExt[i][1]);               //词条数值
        info->affixs.push_back(affix);
    }

    info->index             = _readJsonInt(p[kNCBagEquipageFieldIndex]);
    info->id                = _readJsonInt(p[kNCBagEquipageFieldBaseID]);
    info->level             = _readJsonInt(p[kNCBagEquipageFieldLevel]);
    info->exp               = _readJsonInt(p[kNCBagEquipageFieldExp]);
    info->atkMin            = _readJsonInt(p[kNCBagEquipageFieldAtkMin]);
    info->atkMax            = _readJsonInt(p[kNCBagEquipageFieldAtkMax]);
    info->defMin            = _readJsonInt(p[kNCBagEquipageFieldDefMin]);
    info->defMax            = _readJsonInt(p[kNCBagEquipageFieldDefMax]);
    info->life              = _readJsonInt(p[kNCBagEquipageFieldLife]);
    info->state             = _readJsonInt(p[kNCBagEquipageFieldState]);
    info->intensifyNum      = _readJsonInt(p[kNCBagEquipageFieldIntensifyNum]);
    info->intensifyValue    = _readJsonInt(p[kNCBagEquipageFieldIntensifyValue]);
}

void NetController::_parsePropInfo(void* data, ItemInfo* info)
{
    Json::Value& p = (Json::Value&)*data;
    info->index     = _readJsonInt(p[kNCBagPropFieldIndex]);
    info->id        = _readJsonInt(p[kNCBagPropFieldBaseID]);
    info->count     = _readJsonInt(p[kNCBagPropFieldNum]);
}

void NetController::_parseTaskInfo(void* data, TaskInfo* info)
{
    Json::Value& p = (Json::Value&)*data;
    info->floor     = _readJsonInt(p[kNCTaskFieldFloor]);
    info->task      = _readJsonInt(p[kNCTaskFieldTask]);
    info->progress  = _readJsonInt(p[kNCTaskFieldProgress]);
}

void NetController::_parseChallengeEnemyList(void* data, void* info)
{
//    Json::Value& p = (Json::Value&)*data;
//    NSNumber* gid = [arrayData objectForKey:@"gid"];
//    NSString* name = [arrayData objectForKey:@"name"];
//    NSNumber* time = [arrayData objectForKey:@"time"];
//    NSNumber* coin = [arrayData objectForKey:@"coin"];
}

void NetController::_parseSnatchEnemyList(void* data, void* info)
{
//    Json::Value& p = (Json::Value&)*data;
//    NSNumber* gid = [arrayData objectForKey:@"gid"];
//    NSString* name = [arrayData objectForKey:@"name"];
//    NSNumber* time = [arrayData objectForKey:@"time"];
//    NSNumber* id = [arrayData objectForKey:@"id"];
}

void NetController::_parseFragmentArray(void* data, void* info)
{
//    Json::Value& p = (Json::Value&)*data;
//    NSNumber* id = [arrayData objectForKey:@"id"];
//    NSNumber* count = [arrayData objectForKey:@"count"];
}

void NetController::_parseChallengeEnemyInfo(void* data, ChallengeEnemyInfo* info, bool isParseEnemy)
{
    Json::Value& p = (Json::Value&)*data;
    //TODO: 多传了数据
//    _readJsonInt(p["sex"]);
//    _readJsonInt(p["exp"]);
//    _readJsonInt(p["defMin"]);
//    _readJsonInt(p["defMax"]);
    info->gid           = _readJsonInt(p["gid"]);
    info->name          = p["name"].asString();
    info->avatar        = _readJsonInt(p["avata"]);
    info->level         = _readJsonInt(p["level"]);
    info->atkMin        = _readJsonInt(p["atkMin"]);
    info->atkMax        = _readJsonInt(p["atkMax"]);
    info->succeedExp    = _readJsonInt(p["succeedExp"]);
    info->succeedGold   = _readJsonInt(p["succeedGold"]);
    info->failedGold    = _readJsonInt(p["failedGold"]);

    if(isParseEnemy)
    {
        info->time = _readJsonInt(p["challengeTime"]);
        info->gold = _readJsonInt(p["challengeCoin"]);
    }
}

void NetController::_parseSelfInfo(void* params)
{
    Json::Value& p = (Json::Value&)*params;
    Json::Value& player = p["player"];
    
    UserVO& userVO = UserProxy::shared()->userVO;
    
    //基础信息
    mGid = userVO.gid   = _readJsonInt(player["gid"]);
    userVO.pid          = player["pid"].asString();
    userVO.platform     = _readJsonInt(player["platform"]);
    userVO.createTime   = _readJsonInt(player["createTime"]);     //玩家注册日期
    userVO.energyTime   = _readJsonInt(player["energyTime"]);     //玩家能量点给予日期
    userVO.powerTime    = _readJsonInt(player["powerTime"]);      //玩家体力点给予日期
    userVO.name         = player["name"].asString();              //玩家名字（最大32个英文字符）
    userVO.sex          = _readJsonInt(player["sex"]);            //玩家性别（0:男;1:女）
    userVO.avatar       = _readJsonInt(player["avata"]);          //玩家形象
    userVO.level        = _readJsonInt(player["level"]);          //玩家等级（升级参照玩家等级表）
    userVO.exp          = _readJsonInt(player["exp"]);            //玩家经验值（升级参照玩家等级表）
    userVO.coin         = _readJsonInt(player["coin"]);           //游戏币（玩家游戏中可以免费获得的虚拟货币）
    userVO.money        = _readJsonInt(player["money"]);          //付费币（玩家花钱购买的虚拟货币）
    userVO.energyCur    = _readJsonInt(player["energyCur"]);      //当前能量值。初始20点，可用潜能1:1分配，默认3分钟恢复1点。
    userVO.energyMax    = _readJsonInt(player["energyMax"]);      //最大能量值。
    userVO.powerCur     = _readJsonInt(player["powerCur"]);       //当前体力值。初始3点，默认2小时恢复1点。
    userVO.powerMax     = _readJsonInt(player["powerMax"]);       //最大体力值。
    userVO.life         = _readJsonInt(player["life"]);           //生命值。初始200点（暂定），可用潜能分配，每次增加50点（暂定）。
    userVO.lifeCur      = _readJsonInt(player["lifeCur"]);        //当前地下城内的生命值。
    userVO.proficiency  = _readJsonInt(player["proficiency"]);    //潜能。每次升级自动获得2点。
    userVO.fusion       = _readJsonInt(player["fusion"]);         //熔炼值。

    //对战信息
    userVO.atkMin               = _readJsonInt(player["atkMin"]);                 //最小攻击力：人物基础+装备提供，基础部分会随等级增长。
    userVO.atkMax               = _readJsonInt(player["atkMax"]);                 //最大攻击力：同上
    userVO.defMin               = _readJsonInt(player["defMin"]);                 //最小防御力：同上
    userVO.defMax               = _readJsonInt(player["defMax"]);                 //最大防御力：同上
    userVO.atkMaxReappear       = _readJsonInt(player["atkMaxReappear"]);         //最大攻击出现频率：初始为0%
    userVO.defMaxReappear       = _readJsonInt(player["defMaxReappear"]);         //最大防御出现频率：初始值为0%
    userVO.expGainRatio         = _readJsonInt(player["expGainRatio"]);           //经验获得比率：初始为100%
    userVO.coinGainRatio        = _readJsonInt(player["coinGainRatio"]);          //铜钱获得比率：初始为100%
    userVO.equipageDropRatio    = _readJsonInt(player["equipageDropRatio"]);      //装备掉率几率：初始为100%
    userVO.energyRecoverRatio   = _readJsonInt(player["energyRecoverRatio"]);     //能量恢复速度：初始为100%
    userVO.powerRecoverRatio    = _readJsonInt(player["powerRecoverRatio"]);      //体力恢复速度：初始为100%

    //装备背包信息
    ItemProxy::shared()->mBagMax = _readJsonInt(player["equipageBagItemMax"]);        //装备列表中的装备最大容量。
    Json::Value& bag = player["equipageBagItemArray"];
    for (int i = 0; i < bag.size(); i++)
    {
        //TODO: 内存泄露
        EquipInfo* equipInfo = new EquipInfo();
        _parseEquipageInfo(&bag[i], equipInfo);
        ItemProxy::shared()->addEquip(equipInfo);
    }
    
    //任务信息
    //TODO: 最好不要使用key作为值来传递
    Json::Value& taskCur = player["taskCur"];
    if (taskCur.type() == Json::objectValue)
    {
        Json::Value::Members taskCurMemeber = taskCur.getMemberNames();
        for (int i = 0; i < taskCurMemeber.size(); i++)
        {
            DungeonsProxy::shared()->curTaskInfo.dungeonID = atoi(taskCurMemeber[i].c_str());
            _parseTaskInfo(&taskCur[taskCurMemeber[i]], &(DungeonsProxy::shared()->curTaskInfo));
        }
    }

    //最大任务信息
    Json::Value& taskMax = player["taskMax"];
    if (taskMax.type() == Json::objectValue)
    {
        Json::Value::Members taskMaxMember = taskMax.getMemberNames();
        for (int i = 0; i < taskMaxMember.size(); i++)
        {
            DungeonsProxy::shared()->maxTaskInfo.dungeonID = atoi(taskMaxMember[i].c_str());
            _parseTaskInfo(&taskMax[taskMaxMember[i]], &(DungeonsProxy::shared()->maxTaskInfo));
        }
    }
    
    //下次免费开宝箱的剩余秒数(0:拥有一次开宝箱机会)
    //TODO: 重复了吧
    ShopProxy::shared()->mRemainderOpenBoxTime = _readJsonInt(player["freeBoxTime"]);
    ShopProxy::shared()->mRemainderOpenBoxTime = _readJsonInt(player["remainderOpenBoxTime"]);
    userVO.energyTime = _readJsonInt(player["remainderRechargingEnergyTime"]) * 1000;

    UserProxy::shared()->saveUserInfo();
}

void NetController::_parseLevelInfo(void* params)
{
    Json::Value& synchro = (Json::Value&)*params;
    UserVO& userVO = UserProxy::shared()->userVO;
    userVO.level                = _readJsonInt(synchro["level"]);
    userVO.exp                  = _readJsonInt(synchro["exp"]);
    userVO.coin                 = _readJsonInt(synchro["coin"]);
    userVO.money                = _readJsonInt(synchro["money"]);
    userVO.energyCur            = _readJsonInt(synchro["energyCur"]);
    userVO.energyMax            = _readJsonInt(synchro["energyMax"]);
    userVO.powerCur             = _readJsonInt(synchro["powerCur"]);
    userVO.powerMax             = _readJsonInt(synchro["powerMax"]);
    userVO.lifeCur              = _readJsonInt(synchro["lifeCur"]);
    userVO.life                 = _readJsonInt(synchro["life"]);
    userVO.atkMin               = _readJsonInt(synchro["atkMin"]);
    userVO.atkMax               = _readJsonInt(synchro["atkMax"]);
    userVO.defMin               = _readJsonInt(synchro["defMin"]);
    userVO.defMax               = _readJsonInt(synchro["defMax"]);
    userVO.atkMaxReappear       = _readJsonInt(synchro["atkMaxReappear"]);
    userVO.defMaxReappear       = _readJsonInt(synchro["defMaxReappear"]);
    userVO.expGainRatio         = _readJsonInt(synchro["expGainRatio"]);
    userVO.coinGainRatio        = _readJsonInt(synchro["coinGainRatio"]);
    userVO.equipageDropRatio    = _readJsonInt(synchro["equipageDropRatio"]);
    userVO.energyRecoverRatio   = _readJsonInt(synchro["energyRecoverRatio"]);
    userVO.powerRecoverRatio    = _readJsonInt(synchro["powerRecoverRatio"]);
}

void NetController::_syncEquipInfo(void* params)
{
    Json::Value& player = (Json::Value&)*params;
    //TODO: 多传了数据
//    _readJsonInt(player["mf"]);
//    _readJsonInt(player["lifeRecoverRatio"]);
    UserVO& userVO = UserProxy::shared()->userVO;
    userVO.atkMin = _readJsonInt(player["atkMin"]);
    userVO.atkMax = _readJsonInt(player["atkMax"]);
    userVO.defMin = _readJsonInt(player["defMin"]);
    userVO.defMax = _readJsonInt(player["defMax"]);
    userVO.atkMaxReappear = _readJsonInt(player["atkMaxReappear"]);
    userVO.defMaxReappear = _readJsonInt(player["defMaxReappear"]);
    userVO.energyMax = _readJsonInt(player["energyMax"]);
    userVO.energyRecoverRatio = _readJsonInt(player["energyRecoverRatio"]);;
    userVO.life = _readJsonInt(player["life"]);
    
    userVO.expGainRatio = _readJsonInt(player["expGainRatio"]);
    userVO.coinGainRatio = _readJsonInt(player["coinGainRatio"]);
}

#pragma mark - 私有函数

string NetController::_getPid()
{
    return getDeviceID();
    //    return "k211111112";
    //    return "k211111113";
}

int NetController::_getPlatform()
{
    return kNCPlatform;
}

string NetController::_getVersion()
{
    return kNCVersion;
}

void NetController::_sendNext()
{
    if(gsPackageList.size() > 0)
    {
        PackageInfo package = gsPackageList.front();
        gsPackageList.pop();
        
        if(package.cmd != kNCRegist && package.cmd != kNCGameInit && package.cmd != kNCGetSelfInfo)
            Waitting::shared()->show();
        
        _trueSend(package.package);
    }
    else
    {
        Waitting::shared()->hide();
    }
}

void NetController::_trueSend(const string& data)
{
    CCHttpRequest* request = new CCHttpRequest();
    
    request->setUrl("http://www.happybluefin.com/Test/backend/www/json/gateway.php");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, callfuncND_selector(NetController::onHttpRequestCompleted));
    request->setTag(gHttpRequestTag);
    
	string senddata = "params=";
	senddata += NCUtils::uriEncode(data);
    request->setRequestData(senddata.c_str(), senddata.length());
    CCLOG("NetController::_trueSend() data:%s", senddata.c_str());
    
    CCHttpClient::getInstance()->send(request);

    request->release();
}

bool NetController::_sendCommand(const string& cmd, void* params)
{
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //        char * ttt=  this->gameBoardDelegate->Get_Andorid_Udid();
    //        _globalData.userInfo_.guid =  * CCString::createWithFormat("%s",ttt);
    //#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //        _globalData.userInfo_.guid =  "ceshiliu3338";
    //#endif
    
    Json::Value p;
    if (params != NULL)
         p = (Json::Value&)*params;
    
	Json::Value data;
    Json::Value package;
    
	data["cmd"] = cmd;
	data["params"] = p;
    
    Json::Value dataArray;
    dataArray.append(data);
    package["data"] = dataArray;
    package["pid"] = mPid;
    package["version"] = mVersion;
    package["gid"] = mGid;
    package["platform"] = mPlatform;
    
    //    string packageStr = package.toStyledString();
    //    CCLOG("NetController_json::_sendCommand() %s", packageStr.c_str());
    
    Json::FastWriter writer;
	string packageStr = writer.write(package);
    
    if(isWaitReceive)
    {
        PackageInfo pack;
        pack.package = packageStr;
        pack.cmd = cmd;
        gsPackageList.push(pack);
    }
    else
    {
        //发送命令
        if(cmd != kNCRegist && cmd != kNCGameInit && cmd != kNCGetSelfInfo)
            Waitting::shared()->show();
        isWaitReceive = true;
        _trueSend(packageStr);
    }
    
    return true;
}

void NetController::_parseError(const string& cmd, int error)
{
    Waitting::shared()->hide();
    
    NetError netError;
    netError.cmdName = cmd;
    netError.errorCode = error;
    Post_Net_Notification(kNCNetError, (CCObject*)(&netError));
}

void NetController::onHttpRequestCompleted(CCObject* sender, void* data)
{
    parseData(data);
}

int NetController::_readJsonInt(Json::Value& value)
{
	if (value.isNull())
		return 0;
	
    if (value.isString())
	{
//		CCLOG("%s need int, but string, ", __FUNCTION__);
		return atoi(value.asString().c_str());
	}
    else if (value.isConvertibleTo(Json::intValue))
    {
        return value.asInt();
    }
    else
    {
        assert(false);
        return 0;
    }
}
#endif

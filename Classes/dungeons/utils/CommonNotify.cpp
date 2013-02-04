#include "CommonNotify.h"
#include "UserProxy.h"
#include "AlertDialog.h"
#include "AlertTitleDialog.h"
//#include "dialog/BuyMoneyDialog.h"
#include "NetController.h"
#include "StaticRole.h"
#include "StaticShop.h"
#include "CommonHelper.h"
//#include "model/proxy/ItemProxy.h"

CommonNotify::CommonNotify()
{
	UpdateManager::shared()->regist(this, schedule_selector(CommonNotify::update));
}

CommonNotify::~CommonNotify()
{
}

void CommonNotify::registerNotify()
{
	CCArray* nameList = CCArray::create(
		ccs(kVCLevelUp),
		ccs(kNCVersionError),
		ccs(kVCSellEquip),
		ccs(kNCNetError),
		ccs(kNCSellEquipage),
		NULL);
	RegisterObservers(this, nameList, callfuncO_selector(CommonNotify::_onNotification)); 
}

void CommonNotify::_onNotification(CCObject* object)
{
	CCLOG("CommonNotify::_onNotification");
	NotificationObserver* observer = (NotificationObserver*)object;
	string name(observer->getName());
	
	if (name == kVCLevelUp)
	{
		if(UserProxy::shared()->userVO.level > UserProxy::shared()->mLastUserVO.level)
		{
			FRAMEWORK->popup("LevelUpDialog");
		}
	}
    else if (name == kNCVersionError)
	{
        AlertDialog::initContent(gls("185"), true, this, callfunc_selector(CommonNotify::_forceUpgrade));
        FRAMEWORK->popup("AlertDialog");
    }
	else if(name == kNCNetError)
	{
		NetError* netError = (NetError*)observer->getObject();
		if(netError->errorCode == kNCErrorMoney)
        {
            if(netError->cmdName == kNCBuyEnergy)
            {
                FRAMEWORK->popup("BuyMoneyDialog");
            }
            else
            {
                AlertDialog::initContent(gls("145"));
                FRAMEWORK->popup("AlertDialog");
            }
        }
        else if(netError->errorCode == kNCErrorReceipt)
        {
            if(netError->cmdName == kNCBuyMoney)
            {
                FloatText::shared()->playAnim(gls("201"));
            }
        }
        else if(netError->errorCode == kNCErrorCoin)
        {
            AlertDialog::initContent(gls("146"));
            FRAMEWORK->popup("AlertDialog");
        }
        else if(netError->errorCode == kNCErrorFreeTime)
        {
            AlertDialog::initContent(gls("147"));
            FRAMEWORK->popup("AlertDialog");
        }
		else if(netError->errorCode == kNCErrorEnergyFull)
		{
			AlertDialog::initContent(gls("162"));
			FRAMEWORK->popup("AlertDialog");
		}
        else if(netError->errorCode == kNCErrorEnergy)
		{
            AlertTitleDialog::initContent(gls("182"), fls("183", StaticShop::shared()->getSupplyCostCount(SUPPLY_TYPE_ENERGY)), false, this, callfunc_selector(CommonNotify::_buyEnergy), NULL, NULL, gls("133"));
			FRAMEWORK->popup("AlertTitleDialog");
		}
        else if(netError->errorCode == kNCErrorLife)
        {
            int cost = StaticShop::shared()->getSupplyCostCount(SUPPLY_TYPE_LIFE);
            AlertDialog::initContent(fls("188",cost), false,this, callfunc_selector(CommonNotify::_buyLife));
            FRAMEWORK->popup("AlertDialog");
        }
        else if(netError->errorCode == kNCErrorBagFull)
        {
            AlertDialog::initContent(gls("190"));
			FRAMEWORK->popup("AlertDialog");
        }
		else
		{
			AlertDialog::initContent(fls("160",netError->cmdName.c_str(), netError->errorCode));
			FRAMEWORK->popup("AlertDialog");
		}
	}
    else if(name == kVCSellEquip)
    {
        AlertDialog::initContent(gls("170"), false, this, callfunc_selector(CommonNotify::_sellItem));
        FRAMEWORK->popup("AlertDialog");
    }
    else if(name == kNCSellEquipage)
    {
        FloatText::shared()->playAnim(gls("197"));
    }
}

void CommonNotify::registerPowerTimeCall(CCObject* target, SEL_SCHEDULE selector)
{
	mPowerSelector.push_back(CallFunc0Selector(target, selector));
}

void CommonNotify::registerAllPowerTimeCall(CCObject* target, SEL_SCHEDULE selector)
{
	mAllPowerSelector.push_back(CallFunc0Selector(target, selector));
}

void CommonNotify::registerAllEnergyTimeCall(CCObject* target, SEL_SCHEDULE selector)
{
	mAllEnergySelector.push_back(CallFunc0Selector(target, selector));
}

void CommonNotify::registerEnergyTimeCall(CCObject* target, SEL_SCHEDULE selector)
{
	mEnergySelector.push_back(CallFunc0Selector(target, selector));
}

void CommonNotify::unregisterPowerTimeCall(CCObject* target, SEL_SCHEDULE selector)
{
	vector<CallFunc0Selector>::iterator iter = mPowerSelector.begin();
	while(iter != mPowerSelector.end())
	{
		if(target == iter->mTarget && selector == iter->mSelector)
			iter = mPowerSelector.erase(iter);
		else
			++iter;
	}
}

void CommonNotify::unregisterEnergyTimeCall(CCObject* target, SEL_SCHEDULE selector)
{
	vector<CallFunc0Selector>::iterator iter = mEnergySelector.begin();
	while(iter != mEnergySelector.end())
	{
		if(target == iter->mTarget && selector == iter->mSelector)
			iter = mEnergySelector.erase(iter);
		else
			++iter;
	}
}

void CommonNotify::unregisterAllPowerTimeCall(CCObject* target, SEL_SCHEDULE selector)
{
	vector<CallFunc0Selector>::iterator iter = mAllPowerSelector.begin();
	while(iter != mAllPowerSelector.end())
	{
		if(target == iter->mTarget && selector == iter->mSelector)
			iter = mAllPowerSelector.erase(iter);
		else
			++iter;
	}
}

void CommonNotify::unregisterAllEnergyTimeCall( CCObject* target, SEL_SCHEDULE selector )
{
	vector<CallFunc0Selector>::iterator iter = mAllEnergySelector.begin();
	while(iter != mAllEnergySelector.end())
	{
		if(target == iter->mTarget && selector == iter->mSelector)
			iter = mAllEnergySelector.erase(iter);
		else
			++iter;
	}
}

void CommonNotify::powerTimeUpdate( float lastTime )
{
}

void CommonNotify::energyTimeUpdate( float lastTime )
{
	UserVO& userVO = UserProxy::shared()->userVO;
	if(userVO.energyCur == userVO.energyMax ||
       userVO.energyMax == 0 ||
       userVO.energyTime <= 0)
		return;
	
	float time = (float)(userVO.energyTime);
	time -= lastTime;
	if (time < 0)
	{
		userVO.energyCur++;
		LevelInfo* levelInfo = StaticRole::shared()->getLevelInfo(userVO.level);
		if(userVO.energyCur < userVO.energyMax)
			time = float(levelInfo->energytime);
		Post_Net_Notification(kVCRefreshEnergy, NULL);
	}
	
	userVO.energyTime = (int)time;
	vector<CallFunc0Selector>::iterator iter = mEnergySelector.begin();
	while(iter != mEnergySelector.end())
	{
		iter->activate(time);
		++iter;
	}
}

void CommonNotify::allPowerTimeUpdate( float lastTime )
{
	UserVO& userVO = UserProxy::shared()->userVO;
	if(userVO.powerCur == userVO.powerMax)
		return;
	LevelInfo* levelInfo = StaticRole::shared()->getLevelInfo(userVO.level);

	int power = userVO.powerMax-userVO.powerCur;
	power = power > 0 ? power - 1 : 0;
	float time = (float)(userVO.powerTime+power*levelInfo->powertime);
	time -= lastTime;
	if (time < 0)
		time = 0;
	
	vector<CallFunc0Selector>::iterator iter = mAllPowerSelector.begin();
	while(iter != mAllPowerSelector.end())
	{
		iter->activate(time);
		++iter;
	}
}

void CommonNotify::allEnergyTimeUpdate( float lastTime )
{
	UserVO& userVO = UserProxy::shared()->userVO;
	if(userVO.energyCur == userVO.energyMax)
		return;
	
	LevelInfo* levelInfo = StaticRole::shared()->getLevelInfo(userVO.level);
	int energy = userVO.energyMax-userVO.energyCur;
	energy = energy > 0 ? energy - 1 : 0;
	float time = (float)(userVO.energyTime+energy*levelInfo->energytime);
	time -= lastTime;
	if (time < 0)
		time = 0;
	
	vector<CallFunc0Selector>::iterator iter = mAllEnergySelector.begin();
	while(iter != mAllEnergySelector.end())
	{
		iter->activate(time);
		++iter;
	}
}

void CommonNotify::update( float object )
{
	powerTimeUpdate(object);
	energyTimeUpdate(object);
	allPowerTimeUpdate(object);
	allEnergyTimeUpdate(object);
}

void CommonNotify::_buyEnergy()
{
	UserVO& userVO = UserProxy::shared()->userVO;
	if(StaticShop::shared()->getSupplyCostCount(SUPPLY_TYPE_ENERGY)>userVO.money)
	{
		FRAMEWORK->popup("BuyMoneyDialog");
	}
	else
	{
		int moneyType = StaticShop::shared()->getSupplyMoneyType(SUPPLY_TYPE_ENERGY);
		NetController::shared()->buyEnergy(moneyType);
	}
}

void CommonNotify::_buyLife()
{
    NetController::shared()->buyLife(2);
}

void CommonNotify::_forceUpgrade()
{
    gJumpToStore();
}

void CommonNotify::_sellItem()
{
	vector<int>& sellList = ItemProxy::shared()->sellList;
	NetController::shared()->sellEquipage(sellList);
}

#include "CommonNotify.h"
#include "UserProxy.h"
#include "AlertDialog.h"
#include "AlertTitleDialog.h"
#include "NetController.h"
#include "StaticRole.h"
#include "StaticShop.h"
#include "CommonHelper.h"

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
		ccs(kVCBuyMoney),
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
    else if(name == kVCBuyMoney)
    {
        FRAMEWORK->popup("BuyMoneyDialog");
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
        else if(netError->errorCode == kNCErrorIntenfityLack)
        {
            xmlBuy& buyFusion = StaticShop::shared()->mBuyFusion[1];
            AlertTitleDialog::initContent(
				gls("213"),
				fls("214", buyFusion.money, buyFusion.count),
				false,
				this,
				callfunc_selector(CommonNotify::_buyFusion),
				NULL,
				NULL,
				gls("133"));
            FRAMEWORK->popup("AlertTitleDialog");
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
    UserVO& userVO = UserProxy::shared()->userVO;

	if(userVO.powerCur == userVO.powerMax ||
       userVO.powerMax == 0 ||
       userVO.powerTime <= 0)
		return;
	
	float time = (float)(userVO.powerTime);
	time -= lastTime;
	if (time < 0)
	{
		userVO.powerCur++;
		if(userVO.powerCur < userVO.powerMax)
			time = float(StaticRole::shared()->getLevelInfo(userVO.level)->powerTime);
		Post_Net_Notification(kVCRefreshPower, NULL);
	}
	
	userVO.powerTime = (int)time;
	vector<CallFunc0Selector>::iterator iter = mPowerSelector.begin();
	while(iter != mPowerSelector.end())
	{
		iter->activate(time);
		++iter;
	}
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
		if(userVO.energyCur < userVO.energyMax)
			time = float(StaticRole::shared()->getLevelInfo(userVO.level)->energyTime);
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

	int power = userVO.powerMax-userVO.powerCur;
	power = power > 0 ? power - 1 : 0;
	float time = (float)(userVO.powerTime + power * StaticRole::shared()->getLevelInfo(userVO.level)->powerTime);
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
	
	int energy = userVO.energyMax-userVO.energyCur;
	energy = energy > 0 ? energy - 1 : 0;
	float time = (float)(userVO.energyTime + energy * StaticRole::shared()->getLevelInfo(userVO.level)->energyTime);
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
		NetController::shared()->buyEnergy(MONEY_TYPE_MONEY);
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
	NetController::shared()->sellEquipage(EquipProxy::shared()->mSellList);
}

void CommonNotify::_buyFusion()
{
    xmlBuy& buyFusion = StaticShop::shared()->mBuyFusion[1];
    UserVO& userVO = UserProxy::shared()->userVO;
	if(buyFusion.count > userVO.money)
    {
        Post_Net_Notification(kVCBuyMoney, NULL);
    }
    else
    {
        NetController::shared()->buyFusion(MONEY_TYPE_MONEY);
    }
    
}

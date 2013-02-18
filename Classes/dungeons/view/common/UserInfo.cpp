#include "UserInfo.h"
#include "UserProxy.h"
#include "NetController.h"
#include "StaticRole.h"
#include "CommonNotify.h"
#include "StaticShop.h"
#include "AlertDialog.h"
#include "BuyMoneyDialog.h"

UserInfo::UserInfo()
	: mLevel(NULL)
	, mName(NULL)
	, mEnergy(NULL)
	, mPower(NULL)
	, mCoin(NULL)
	, mMoney(NULL)
	, mNextEnergyTitle(NULL)
	, mEnergyTime(NULL)
	, mBtnBg(NULL)
	, mBtnAddMoney(NULL)
	, mBtnAddCoin(NULL)
	, mBtnAddEnergy(NULL)
{
	CCLOG("UserInfo::%s()", __FUNCTION__);
}

UserInfo::~UserInfo()
{
	CCLOG("UserInfo::%s()", __FUNCTION__);
	RemoveObserver(this);
	CommonNotify::shared()->unregisterEnergyTimeCall(this, schedule_selector(UserInfo::updateEnergyTime));
	
	CC_SAFE_RELEASE(mLevel);
	CC_SAFE_RELEASE(mName);
	CC_SAFE_RELEASE(mEnergy);
	CC_SAFE_RELEASE(mPower);
	CC_SAFE_RELEASE(mCoin);
	CC_SAFE_RELEASE(mMoney);
	CC_SAFE_RELEASE(mNextEnergyTitle);
	CC_SAFE_RELEASE(mEnergyTime);
	CC_SAFE_RELEASE(mBtnBg);
	CC_SAFE_RELEASE(mBtnAddCoin);
	CC_SAFE_RELEASE(mBtnAddMoney);
	CC_SAFE_RELEASE(mBtnAddEnergy);
}

bool UserInfo::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLevel",     CCLabelTTF*, mLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName",      CCLabelTTF*, mName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnergy",    CCLabelTTF*, mEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPower",     CCLabelTTF*, mPower);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoin",      CCLabelTTF*, mCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMoney",     CCLabelTTF*, mMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnergyTime",CCLabelTTF*, mEnergyTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnBg",     CCControlButton*, mBtnBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnAddCoin",CCControlButton*, mBtnAddCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnAddMoney",CCControlButton*, mBtnAddMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnAddEnergy",CCControlButton*, mBtnAddEnergy);

	CCB_CCLABELTTF_GLUE(this, "mNextEnergyTitle",   mNextEnergyTitle,   gls("151"));

	return false;
}

SEL_MenuHandler UserInfo::onResolveCCBCCMenuItemSelector( CCObject* pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler UserInfo::onResolveCCBCCControlSelector( CCObject* pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnBg",        UserInfo::onBtnBg);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnAddEnergy", UserInfo::onBtnAddEnergy);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnAddMoney",  UserInfo::onBtnAddMoney);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnAddCoin",   UserInfo::onBtnAddCoin);
	return NULL;
}

void UserInfo::onNodeLoaded( CCNode* pNode, CCNodeLoader* pNodeLoader )
{
	CCLOG("UserInfo::%s()", __FUNCTION__);
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
	setTouchPriority(touch_priority_1);
	
	mBtnBg->setDefaultTouchPriority(touch_priority_2);
	mBtnAddCoin->setDefaultTouchPriority(touch_priority_2);
	mBtnAddMoney->setDefaultTouchPriority(touch_priority_2);
	mBtnAddEnergy->setDefaultTouchPriority(touch_priority_2);
	
	mProgress = ProgressText::create("progress_02.png", DEFAULT_FONT, 28);
	mProgress->setMode(PROGRESS_TEXT_FORMAT_CURMAX);
	mProgress->setRange(0, 100);
	mProgress->setPosition(102, 26);
	addChild(mProgress);
	
	CCArray* nameList = CCArray::create(ccs(kNCRegist), ccs(kNCDungeonExplore), ccs(kNCSellEquipage), ccs(kNCChallengePlayer), ccs(kNCGetSelfInfo), ccs(kNCOpenBox), ccs(kNCBuyPower), ccs(kNCBuyEnergy), ccs(kNCBuyMoney), ccs(kNCBuyCoin), ccs(kVCRefreshEnergy), ccs(kNCBuyLife), ccs(kNCLoadEquipage), ccs(kNCUnloadEquipage), ccs(kNCSellEquipage), NULL);
	
	RegisterObservers(this, nameList, callfuncO_selector(UserInfo::_onNotification));
	
	CommonNotify::shared()->registerEnergyTimeCall(this, schedule_selector(UserInfo::updateEnergyTime));
	
	refresh();
}

void UserInfo::refresh()
{
	UserVO& userVO = UserProxy::shared()->userVO;

	mLevel->setString(fcs("%d", userVO.level));
	mName->setString(fcs("%s%d", gls("Player"), userVO.gid)); // up->userVO.name.c_str());
	mEnergy->setString(fcs("%d/%d", userVO.energyCur, userVO.energyMax));
	//mPower->setString(fcs("%d/%d", userVO.powerCur, userVO.powerMax));
	mCoin->setString(fcs("%d", userVO.coin));
	mMoney->setString(fcs("%d", userVO.money));
	mProgress->setRange(0, float(StaticRole::shared()->getLevelInfo(userVO.level+1)->exp));
	mProgress->setPecent(float(userVO.exp));
	updateEnergyTime(float(userVO.energyTime));
}

void UserInfo::_onNotification(CCObject* object)
{
	CCLOG("UserInfo::_onNotification[%x]", this);
	
	NotificationObserver* notification = (NotificationObserver*)object;
	
	string name = notification->getName();
	
	if (name == kNCRegist           ||
		name == kNCDungeonExplore   ||
		name == kNCSellEquipage     ||
		name == kNCChallengePlayer  ||
		name == kNCGetSelfInfo      ||
		name == kNCOpenBox          ||
		name == kNCBuyPower         ||
		name == kNCBuyEnergy        ||
		name == kNCBuyMoney         ||
		name == kNCBuyCoin          ||
		name == kNCBuyLife          ||
		name == kNCLoadEquipage     ||
		name == kNCUnloadEquipage   ||
		name == kNCSellEquipage          
		)
	{
		refresh();
		if(name == kNCBuyPower || name == kNCBuyEnergy || name == kNCBuyCoin ||
		   name == kNCBuyLife)
		{
			FloatText::shared()->playAnim(gls("164"));
		}
	}
	else if(name == kVCRefreshEnergy)
	{
		refreshEnergy();
	}
}

void UserInfo::onBtnBg( CCObject* pSender )
{
	FRAMEWORK->changeState("PlayerDetailScene");
}

void UserInfo::onBtnAddEnergy( CCObject* pSender, CCControlEvent pCCControlEvent )
{
	UserVO& userVO = UserProxy::shared()->userVO;
	if(userVO.energyCur == userVO.energyMax)
	{
		NetError netError;
		netError.cmdName = kNCBuyEnergy;
		netError.errorCode = kNCErrorEnergyFull;
		Post_Net_Notification(kNCNetError, (CCObject*)(&netError));
	}
	else
	{
		AlertDialog::initContent(fls("171", StaticShop::shared()->getSupplyCostCount(SUPPLY_TYPE_ENERGY)), false, this, callfunc_selector(UserInfo::buyEnergy));
		FRAMEWORK->popup("AlertDialog");
	}
}

void UserInfo::onBtnAddMoney( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	FRAMEWORK->popup("BuyMoneyDialog");
}

void UserInfo::onBtnAddCoin( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	xmlBuy* buyCoin = StaticShop::shared()->getBuyCoin(1);
	AlertDialog::initContent(fls("153", buyCoin->money, buyCoin->count), false, this, callfunc_selector(UserInfo::buyCoin));
	FRAMEWORK->popup("AlertDialog");
}

void UserInfo::updateEnergyTime( float object )
{
	long lastTime = (long)object;
	MMSS time(lastTime);
	mEnergyTime->setString(fcs("%02d:%02d", time.minute, time.second));
}

void UserInfo::refreshEnergy()
{
	UserVO& userVO = UserProxy::shared()->userVO;
	mEnergy->setString(fcs("%d/%d",userVO.energyCur, userVO.energyMax));
}

void UserInfo::buyCoin( CCObject* object )
{
	NetController::shared()->buyCoin(1);
}

void UserInfo::buyEnergy()
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

bool UserInfo::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return isTouchInside(pTouch, this);
}

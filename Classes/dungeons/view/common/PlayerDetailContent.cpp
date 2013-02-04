#include "PlayerDetailContent.h"
#include "UserProxy.h"
#include "ItemProxy.h"
#include "StaticRole.h"
#include "CommonNotify.h"
#include "NotifyDefine.h"

PlayerDetailContent::PlayerDetailContent()
	: mBaseTitle(NULL)
	, mName(NULL)
	, mLevel(NULL)
	, mExp(NULL)
	, mCoin(NULL)
	, mMoney(NULL)
	, mEnergy(NULL)
	, mNextEnergyTime(NULL)
	, mAllEnergyTime(NULL)
	, mExpGainRatio(NULL)
	, mCoinGainRatio(NULL)
	, mFightTitle(NULL)
	, mPutonCount(NULL)
	, mLife(NULL)
	, mAttack(NULL)
	, mDefense(NULL)
	, mTeShuTitle(NULL)
	, mAtkMaxReappear(NULL)
	, mDefMaxReappear(NULL)
	, mEquipageDropRatio(NULL)
	, mEnergyRecoverRatio(NULL)
{
}

PlayerDetailContent::~PlayerDetailContent()
{
	RemoveObserver(this);
	CommonNotify::shared()->unregisterEnergyTimeCall(this, schedule_selector(PlayerDetailContent::updateEnergyTime));
	CommonNotify::shared()->unregisterAllEnergyTimeCall(this, schedule_selector(PlayerDetailContent::updateAllEnergyTime));
	
	CC_SAFE_RELEASE(mBaseTitle);
	CC_SAFE_RELEASE(mName);
	CC_SAFE_RELEASE(mLevel);
	CC_SAFE_RELEASE(mExp);
	CC_SAFE_RELEASE(mCoin);
	CC_SAFE_RELEASE(mMoney);
	CC_SAFE_RELEASE(mEnergy);
	CC_SAFE_RELEASE(mNextEnergyTime);
	CC_SAFE_RELEASE(mAllEnergyTime);
	CC_SAFE_RELEASE(mCoinGainRatio);
	CC_SAFE_RELEASE(mExpGainRatio);
	CC_SAFE_RELEASE(mFightTitle);
	CC_SAFE_RELEASE(mPutonCount);
	CC_SAFE_RELEASE(mLife);
	CC_SAFE_RELEASE(mAttack);
	CC_SAFE_RELEASE(mDefense);
	CC_SAFE_RELEASE(mTeShuTitle);
	CC_SAFE_RELEASE(mAtkMaxReappear);
	CC_SAFE_RELEASE(mDefMaxReappear);
	CC_SAFE_RELEASE(mEquipageDropRatio);
	CC_SAFE_RELEASE(mEnergyRecoverRatio);
}

SEL_MenuHandler PlayerDetailContent::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler PlayerDetailContent::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

bool PlayerDetailContent::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBaseTitle", CCLabelTTF*, mBaseTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName", CCLabelTTF*, mName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLevel", CCLabelTTF*, mLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExp", CCLabelTTF*, mExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoin", CCLabelTTF*, mCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMoney", CCLabelTTF*, mMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnergy", CCLabelTTF*, mEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNextEnergyTime", CCLabelTTF*, mNextEnergyTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAllEnergyTime", CCLabelTTF*, mAllEnergyTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExpGainRatio", CCLabelTTF*, mExpGainRatio);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoinGainRatio", CCLabelTTF*, mCoinGainRatio);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFightTitle", CCLabelTTF*, mFightTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPutonCount", CCLabelTTF*, mPutonCount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLife", CCLabelTTF*, mLife);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAttack", CCLabelTTF*, mAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDefense", CCLabelTTF*, mDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTeShuTitle", CCLabelTTF*, mTeShuTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAtkMaxReappear", CCLabelTTF*, mAtkMaxReappear);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDefMaxReappear", CCLabelTTF*, mDefMaxReappear);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipageDropRatio", CCLabelTTF*, mEquipageDropRatio);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnergyRecoverRatio", CCLabelTTF*, mEnergyRecoverRatio);
	return false;
}

void PlayerDetailContent::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCArray* nameList = CCArray::create(ccs(kVCRefreshEnergy),NULL);
	RegisterObservers(this, nameList, callfuncO_selector(PlayerDetailContent::_onNotification));
	CommonNotify::shared()->registerEnergyTimeCall(this, schedule_selector(PlayerDetailContent::updateEnergyTime));
	CommonNotify::shared()->registerAllEnergyTimeCall(this, schedule_selector(PlayerDetailContent::updateAllEnergyTime));

	refresh();
}

void PlayerDetailContent::refresh()
{
	UserVO& userVO = UserProxy::shared()->userVO;
	
	mCurLifeValue = userVO.life;
	mAddLifeValue = 0;
	mCurEnergyValue = userVO.energyMax;
	mAddEnergyValue = 0;
	mCurProficiency = userVO.proficiency;
	mMaxProficiency = userVO.proficiency;
	mName->setString(userVO.name.c_str());

	mBaseTitle->setString(gls("基础信息"));
	mLevel->setString(fcs("%s:%d", gls("Level"), userVO.level));
	LevelInfo* levelInfo = StaticRole::shared()->getLevelInfo(userVO.level + 1);
	mExp->setString(fcs("%s:%d/%d", gls("Exp"), userVO.exp, levelInfo->exp));
	mCoin->setString(fcs("%s:%d", gls("Coin"), userVO.coin));
	mMoney->setString(fcs("%s:%d", gls("Diamond"), userVO.money));
	mEnergy->setString(fcs("%s:%d/%d", gls("Energy"), userVO.energyCur, userVO.energyMax));
	updateEnergyTime((float)userVO.energyTime);
	updateAllEnergyTime((float)UserProxy::shared()->getAllEnergyTime());
	mExpGainRatio->setString(fcs("%s:%d%%", gls("ExpGainRate"), userVO.expGainRatio));
	mCoinGainRatio->setString(fcs("%s:%d%%", gls("CoinGainRate"), userVO.coinGainRatio));

	mFightTitle->setString(gls("BattleInfo"));
	mPutonCount->setString(fcs("%s:%d/%d", gls("Equiped"), ItemProxy::shared()->getPutonCount(), ItemProxy::shared()->getEquipCount()));
	mLife->setString(fcs("%s:%d", gls("Life"), userVO.life));
	mAttack->setString(fcs("%s:%d-%d", gls("Attack"), userVO.atkMin, userVO.atkMax));
	mDefense->setString(fcs("%s:%d-%d", gls("Defense"), userVO.defMin, userVO.defMax));
	
	mTeShuTitle->setString(gls("BonusInfo"));
	mAtkMaxReappear->setString(fcs("%s:%d%%", gls("MaxAttackRate"), userVO.atkMaxReappear));
	mDefMaxReappear->setString(fcs("%s:%d%%", gls("MaxDefenseRate"), userVO.defMaxReappear));
	mEquipageDropRatio->setString(fcs("%s:%d%%", gls("EquipDropRate"), userVO.equipageDropRatio));
	mEnergyRecoverRatio->setString(fcs("%s:%d%%", gls("EnergyRecoverRate"), userVO.energyRecoverRatio));
}

void PlayerDetailContent::_onNotification( CCObject* object )
{
	CCLOG("PlayerDetailContent::_onNotification[%x]", this);

	NotificationObserver* notification = (NotificationObserver*)object;
	string name = string(notification->getName());
	if(name == kVCRefreshEnergy)
	{
		refreshEnergy();
	}
}

void PlayerDetailContent::updateEnergyTime( float object )
{
	long lastTime = (long)object;
	MMSS time(lastTime);
	mNextEnergyTime->setString(fcs("%s:%02d:%02d", gls("NextEnergyRecover"), time.minute, time.second));
}

void PlayerDetailContent::updateAllEnergyTime( float object )
{
	long lastTime = (long)object;
	HHMMSS time(lastTime);
	mAllEnergyTime->setString(fcs("%s:%02d:%02d:%02d", gls("AllEnergyRecover"), time.hour, time.minute, time.second));
}

void PlayerDetailContent::refreshEnergy()
{
	UserVO& userVO = UserProxy::shared()->userVO;
	mEnergy->setString(fcs("%s:%d/%d", gls("Energy"), userVO.energyCur, userVO.energyMax));
}

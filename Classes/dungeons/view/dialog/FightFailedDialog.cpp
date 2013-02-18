#include "FightFailedDialog.h"
#include "StaticRole.h"
#include "NetController.h"

FightFailedDialog::FightFailedDialog()
	: mSelfAttack(NULL)
	, mSelfDefense(NULL)
	, mSelfLife(NULL)
	, mOtherAttack(NULL)
	, mOtherDefense(NULL)
	, mOtherLife(NULL)
	, mSelfTitle(NULL)
	, mOtherTitle(NULL)
	, mTitle(NULL)
	, mDesc(NULL)
	, mRestartBtn(NULL)
	, mBuyLifeBtn(NULL)
{
	CCLOG("FightFailedDialog::%s()", __FUNCTION__);
}

FightFailedDialog::~FightFailedDialog()
{
	CCLOG("FightFailedDialog::%s()", __FUNCTION__);
	RemoveObserver(this);
	
	CC_SAFE_RELEASE(mSelfAttack);
	CC_SAFE_RELEASE(mSelfDefense);
	CC_SAFE_RELEASE(mSelfLife);
	CC_SAFE_RELEASE(mOtherAttack);
	CC_SAFE_RELEASE(mOtherDefense);
	CC_SAFE_RELEASE(mOtherLife);
	CC_SAFE_RELEASE(mSelfTitle);
	CC_SAFE_RELEASE(mOtherTitle);
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mDesc);
	CC_SAFE_RELEASE(mRestartBtn);
	CC_SAFE_RELEASE(mBuyLifeBtn);
}

bool FightFailedDialog::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSelfAttack", CCLabelTTF *, mSelfAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSelfDefense", CCLabelTTF *, mSelfDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSelfLife", CCLabelTTF *, mSelfLife);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mOtherAttack", CCLabelTTF *, mOtherAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mOtherDefense", CCLabelTTF *, mOtherDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mOtherLife", CCLabelTTF *, mOtherLife);

	CCB_CCLABELTTF_GLUE(this, "mSelfTitle", mSelfTitle, gls("107"));
	CCB_CCLABELTTF_GLUE(this, "mOtherTitle", mOtherTitle, gls("108"));
	CCB_CCLABELTTF_GLUE(this, "mTitle", mTitle, gls("battle_failed"));
	CCB_CCLABELTTF_GLUE(this, "mDesc", mDesc, gls("109"));
	CCB_CONTROLBUTTON_GLUE(this, "mRestartBtn", mRestartBtn, gls("198"));
	CCB_CONTROLBUTTON_GLUE(this, "mBuyLifeBtn", mBuyLifeBtn, gls("199"));
	return false;
}

SEL_CCControlHandler FightFailedDialog::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRestartBtnClick", FightFailedDialog::onRestartBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBuyLifeBtnClick", FightFailedDialog::onBuyLifeBtnClick);
	return NULL;
}

void FightFailedDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("FightFailedDialog::%s()", __FUNCTION__);
	mRestartBtn->setDefaultTouchPriority(touch_priority_5);
	mBuyLifeBtn->setDefaultTouchPriority(touch_priority_5);
	
	CCArray* nameList = CCArray::create(ccs(kNCDungeonStart),ccs(kNCBuyLife),NULL);
	RegisterObservers(this, nameList, callfuncO_selector(FightFailedDialog::_onNotification));

	int bossID = FightProxy::shared()->mBossID;
	UserVO& userVO = UserProxy::shared()->userVO;
	xmlBossInfo* xmlBoss = StaticRole::shared()->getBossInfo(bossID);
	BossInfo& boss = FightProxy::shared()->mFightBoss;
	
	mSelfAttack->setString(fcs("%s: %d--%d", gls("Attack"), userVO.atkMin, userVO.atkMax));
	mSelfDefense->setString(fcs("%s: %d--%d", gls("Defense"), userVO.atkMin, userVO.defMax));
	mSelfLife->setString(fcs("%s: %d", gls("93"), userVO.life));
	mOtherAttack->setString(fcs("%s: %d--%d", gls("Attack"), xmlBoss->atk_min, xmlBoss->atk_max));
	mOtherDefense->setString(fcs("%s: %d--%d", gls("Defense"), xmlBoss->def_min, xmlBoss->def_max));
	mOtherLife->setString(fcs("%s: %d", gls("93"), boss.life));
}

void FightFailedDialog::onRestartBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	NetController::shared()->dungeonStart(DungeonsProxy::shared()->getCurDungeon(), DungeonsProxy::shared()->getCurFloor());
}

void FightFailedDialog::onBuyLifeBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	NetController::shared()->buyLife(2);
}

void FightFailedDialog::_onNotification( CCObject* object )
{
	CCLOG("FightFailedDialog::%s()", __FUNCTION__);

	NotificationObserver* notification = (NotificationObserver*)object;
	string name = string(notification->getName());
	
	if (name == kNCDungeonStart || name == kNCBuyLife)
	{
		close();
	}
}

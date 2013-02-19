#include "ChallengeResultDialog.h"
#include "ChallengeProxy.h"
#include "UserProxy.h"

ChallengeResultDialog::ChallengeResultDialog()
	: mName1(NULL)
	, mName2(NULL)
	, mGetGold(NULL)
	, mGetExp(NULL)
	, mTitle(NULL)
	, mVs(NULL)
	, mCloseBtn(NULL)
	, mSelfAttack(NULL)
	, mSelfDefense(NULL)
	, mSelfLife(NULL)
	, mOtherAttack(NULL)
	, mOtherDefense(NULL)
	, mOtherLife(NULL)
	, mGoldIcon(NULL)
	, mExpIcon(NULL)
{
}

ChallengeResultDialog::~ChallengeResultDialog()
{
//	RemoveObserver(this);
	
	CC_SAFE_RELEASE(mName1);
	CC_SAFE_RELEASE(mName2);
	CC_SAFE_RELEASE(mGetGold);
	CC_SAFE_RELEASE(mGetExp);
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mVs);
	CC_SAFE_RELEASE(mCloseBtn);
	CC_SAFE_RELEASE(mSelfAttack);
	CC_SAFE_RELEASE(mSelfDefense);
	CC_SAFE_RELEASE(mSelfLife);
	CC_SAFE_RELEASE(mOtherAttack);
	CC_SAFE_RELEASE(mOtherDefense);
	CC_SAFE_RELEASE(mOtherLife);
	CC_SAFE_RELEASE(mGoldIcon);
	CC_SAFE_RELEASE(mExpIcon);
}

bool ChallengeResultDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName1", CCLabelTTF *, mName1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName2", CCLabelTTF *, mName2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGetGold", CCLabelTTF *, mGetGold);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGetExp", CCLabelTTF *, mGetExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTitle", CCLabelTTF *, mTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGoldIcon", CCSprite *, mGoldIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExpIcon", CCSprite *, mExpIcon);
	CCB_CCLABELTTF_GLUE(this, "mVs", mVs, gls("82"));
	CCB_CONTROLBUTTON_GLUE(this, "mCloseBtn", mCloseBtn, gls("77"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSelfAttack", CCLabelTTF *, mSelfAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSelfDefense", CCLabelTTF *, mSelfDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSelfLife", CCLabelTTF *, mSelfLife);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mOtherAttack", CCLabelTTF *, mOtherAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mOtherDefense", CCLabelTTF *, mOtherDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mOtherLife", CCLabelTTF *, mOtherLife);
	return false;
}

SEL_MenuHandler ChallengeResultDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler ChallengeResultDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", ChallengeResultDialog::onCloseBtnClick);
	return NULL;
}

void ChallengeResultDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
//    CCArray* nameList = CCArray::create(ccs(kNCGetChallengeList),NULL);
//	RegisterObservers(this, nameList, callfuncO_selector(ChallengeResultDialog::_onNotification));
	
	mCloseBtn->setDefaultTouchPriority(touch_priority_5);

	ChallengeResult& challengeResult = ChallengeProxy::shared()->mChallengeResult;
	ChallengeEnemyInfo* challengeEnemyInfo = ChallengeProxy::shared()->mCurChallengeEnemyInfo;
	UserVO& userVO = UserProxy::shared()->userVO;

//	mName1->setString(userVO.name.c_str());
//	mName2->setString(challengeEnemyInfo->name.c_str());
	mName1->setString(fcs("%s%d", gls("Player"), userVO.gid));
	mName2->setString(fcs("%s%d", gls("Player"), challengeEnemyInfo->gid));
	
	if(challengeResult.result == 1)
	{
		mTitle->setString(gls("battle_succeed"));
		mGetGold->setString(fcs("+%d", challengeEnemyInfo->succeedGold));
		mGetExp->setString(fcs("+%d", challengeEnemyInfo->succeedExp));
		mGoldIcon->setPosition(ccp(386, 416));
		mGetGold->setPosition(ccp(420, 416));
	}
	else
	{
		mTitle->setString(gls("battle_failed"));
		mGetGold->setString(fcs("-%d", challengeEnemyInfo->failedGold));
		mGoldIcon->setPosition(ccp(272, 416));
		mGetGold->setPosition(ccp(304, 416));
		mGetExp->setVisible(false);
		mExpIcon->setVisible(false);
	}
	
	mSelfAttack->setString(fcs("%s: %d--%d", gls("Attack"), userVO.atkMin, userVO.atkMax));
	mSelfDefense->setString(fcs("%s: %d--%d", gls("Defense"), userVO.defMin, userVO.defMax));
	mSelfLife->setString(fcs("%s: %d", gls("93"), userVO.life));
	
	mOtherAttack->setString(fcs("%s: %d--%d", gls("Attack"), challengeEnemyInfo->atkMin, challengeEnemyInfo->atkMax));
	mOtherDefense->setString(fcs("%s: %d--%d", gls("Defense"), challengeEnemyInfo->defMin, challengeEnemyInfo->defMax));
	mOtherLife->setString(fcs("%s: %d", gls("93"), challengeEnemyInfo->life));
}

//void ChallengeResultDialog::_onNotification( CCObject* object )
//{
//	NotificationObserver* notification = (NotificationObserver*)object;
//	string name = string(notification->getName());
//	if (name == kNCGetChallengeList)
//	{
//        close();
//    }
//}

void ChallengeResultDialog::onCloseBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
//	NetController::shared()->getChallengeList();
}

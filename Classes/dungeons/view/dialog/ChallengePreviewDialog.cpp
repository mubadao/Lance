#include "ChallengePreviewDialog.h"
#include "ChanllengeProxy.h"
#include "UserProxy.h"
#include "NetController.h"

ChallengePreviewDialog::ChallengePreviewDialog()
	: mName1(NULL)
	, mName2(NULL)
	, mGetGold(NULL)
	, mGetExp(NULL)
	, mLostGold(NULL)
	, mTitle(NULL)
	, mVs(NULL)
	, mSucceedTitle(NULL)
	, mFailedTitle(NULL)
	, mChallengeBtn(NULL)
	, mReturnBtn(NULL)
{
}

ChallengePreviewDialog::~ChallengePreviewDialog(void)
{
	CC_SAFE_RELEASE(mName1);
	CC_SAFE_RELEASE(mName2);
	CC_SAFE_RELEASE(mGetGold);
	CC_SAFE_RELEASE(mGetExp);
	CC_SAFE_RELEASE(mLostGold);
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mVs);
	CC_SAFE_RELEASE(mSucceedTitle);
	CC_SAFE_RELEASE(mFailedTitle);
	CC_SAFE_RELEASE(mChallengeBtn);
	CC_SAFE_RELEASE(mReturnBtn);
}

bool ChallengePreviewDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName1", CCLabelTTF *, mName1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName2", CCLabelTTF *, mName2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGetGold", CCLabelTTF *, mGetGold);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGetExp", CCLabelTTF *, mGetExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLostGold", CCLabelTTF *, mLostGold);
	CCB_CCLABELTTF_GLUE(this, "mTitle", mTitle, gls("81"));
	CCB_CCLABELTTF_GLUE(this, "mVs", mVs, gls("82"));
	CCB_CCLABELTTF_GLUE(this, "mSucceedTitle", mSucceedTitle, gls("83"));
	CCB_CCLABELTTF_GLUE(this, "mFailedTitle", mFailedTitle, gls("84"));
	CCB_CONTROLBUTTON_GLUE(this, "mChallengeBtn", mChallengeBtn, gls("87"));
	CCB_CONTROLBUTTON_GLUE(this, "mReturnBtn", mReturnBtn, gls("80"));
	return false;
}

SEL_MenuHandler ChallengePreviewDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler ChallengePreviewDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onChallengeBtnClick", ChallengePreviewDialog::onChallengeBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReturnBtnClick", ChallengePreviewDialog::onReturnBtnClick);
	return NULL;
}

void ChallengePreviewDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	ChallengeEnemyInfo* challengeEnemyInfo = ChanllengeProxy::shared()->mCurChallengeEnemyInfo;
	mName1->setString(UserProxy::shared()->userVO.name.c_str());
	mName2->setString(challengeEnemyInfo->name.c_str());
	mGetGold->setString(fcs("+%d", challengeEnemyInfo->succeedGold));
	mGetExp->setString(fcs("+%d", challengeEnemyInfo->succeedExp));
	mLostGold->setString(fcs("-%d", challengeEnemyInfo->failedGold));
}

void ChallengePreviewDialog::onChallengeBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	if(UserProxy::shared()->userVO.powerCur <= 0)
		FRAMEWORK->popup("StaminaLackDialog");
	else
	{
		ChallengeEnemyInfo* challengeEnemyInfo = ChanllengeProxy::shared()->mCurChallengeEnemyInfo;
		NetController::shared()->challengePlayer(challengeEnemyInfo->gid);
	}
	close();
}

void ChallengePreviewDialog::onReturnBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
}

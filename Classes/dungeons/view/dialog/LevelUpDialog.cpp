#include "LevelUpDialog.h"
#include "UserProxy.h"

LevelUpDialog::LevelUpDialog()
	: mLevel(NULL)
	, mMinAttack(NULL)
	, mMinDefense(NULL)
	, mMaxAttack(NULL)
	, mMaxDefense(NULL)
	, mLifeTitle(NULL)
	, mLife(NULL)
	, mMaxEnergy(NULL)
	, mTitle(NULL)
	, mLevelTitle(NULL)
	, mMinAttackTitle(NULL)
	, mMinDefenseTitle(NULL)
	, mMaxAttackTitle(NULL)
	, mMaxDefenseTitle(NULL)
	, mMaxEnergyTitle(NULL)
	, mCloseBtn(NULL)
{
	CCLOG("LevelUpDialog::%s()", __FUNCTION__);
}

LevelUpDialog::~LevelUpDialog()
{
	CCLOG("LevelUpDialog::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mLevel);
	CC_SAFE_RELEASE(mMinAttack);
	CC_SAFE_RELEASE(mMinDefense);
	CC_SAFE_RELEASE(mMaxAttack);
	CC_SAFE_RELEASE(mMaxDefense);
	CC_SAFE_RELEASE(mLifeTitle);
	CC_SAFE_RELEASE(mLife);
	CC_SAFE_RELEASE(mMaxEnergy);

	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mLevelTitle);
	CC_SAFE_RELEASE(mMinAttackTitle);
	CC_SAFE_RELEASE(mMaxAttackTitle);
	CC_SAFE_RELEASE(mMinDefenseTitle);
	CC_SAFE_RELEASE(mMaxDefenseTitle);
	CC_SAFE_RELEASE(mMaxEnergyTitle);
	CC_SAFE_RELEASE(mCloseBtn);
}

bool LevelUpDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLevel", CCLabelTTF *, mLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMinAttack", CCLabelTTF *, mMinAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMaxAttack", CCLabelTTF *, mMaxAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMinDefense", CCLabelTTF *, mMinDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMaxDefense", CCLabelTTF *, mMaxDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLife", CCLabelTTF *, mLife);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMaxEnergy", CCLabelTTF *, mMaxEnergy);

	CCB_CCLABELTTF_GLUE(this, "mTitle", mTitle, gls("113"));
	CCB_CCLABELTTF_GLUE(this, "mLevelTitle", mLevelTitle, gls("114"));
	CCB_CCLABELTTF_GLUE(this, "mMinAttackTitle", mMinAttackTitle, gls("154"));
	CCB_CCLABELTTF_GLUE(this, "mMaxAttackTitle", mMaxAttackTitle, gls("155"));
	CCB_CCLABELTTF_GLUE(this, "mMinDefenseTitle", mMinDefenseTitle, gls("156"));
	CCB_CCLABELTTF_GLUE(this, "mMaxDefenseTitle", mMaxDefenseTitle, gls("157"));
	CCB_CCLABELTTF_GLUE(this, "mLifeTitle", mLifeTitle, gls("159"));
	CCB_CCLABELTTF_GLUE(this, "mMaxEnergyTitle", mMaxEnergyTitle, gls("158"));
	CCB_CONTROLBUTTON_GLUE(this, "mCloseBtn", mCloseBtn, gls("77"));
	return false;
}

SEL_MenuHandler LevelUpDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler LevelUpDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", LevelUpDialog::onCloseBtnClick);
	return NULL;
}

void LevelUpDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("LevelUpDialog::%s()", __FUNCTION__);
	mCloseBtn->setDefaultTouchPriority(touch_priority_5);
	
	UserVO& userVO1 = UserProxy::shared()->userVO;
	UserVO& userVO2 = UserProxy::shared()->mLastUserVO;
	mLevel->setString(fcs("%d-->%d", userVO2.level, userVO1.level));
	mMinAttack->setString(fcs("%d-->%d", userVO2.atkMin, userVO1.atkMin));
	mMaxAttack->setString(fcs("%d-->%d", userVO2.atkMax, userVO1.atkMax));
	mMinDefense->setString(fcs("%d-->%d", userVO2.defMin, userVO1.defMin));
	mMaxDefense->setString(fcs("%d-->%d", userVO2.defMax, userVO1.defMax));
	mLife->setString(fcs("%d-->%d", userVO2.life, userVO1.life));
	mMaxEnergy->setString(fcs("%d-->%d", userVO2.energyMax, userVO1.energyMax));
}

void LevelUpDialog::onCloseBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	UserProxy::shared()->saveUserInfo();
	close();
}

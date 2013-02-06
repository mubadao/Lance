#include "GetEnergyEventDialog.h"
#include "FightProxy.h"

GetEnergyEventDialog::GetEnergyEventDialog()
	: mDesc(NULL)
	, mExp(NULL)
	, mCoin(NULL)
	, mCloseBtn(NULL)
{
	CCLOG("GetEnergyEventDialog::%s()", __FUNCTION__);
}

GetEnergyEventDialog::~GetEnergyEventDialog()
{
	CCLOG("GetEnergyEventDialog::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mDesc);
	CC_SAFE_RELEASE(mExp);
	CC_SAFE_RELEASE(mCoin);
	CC_SAFE_RELEASE(mCloseBtn);
}

bool GetEnergyEventDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDesc", CCLabelTTF *, mDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExp", CCLabelTTF *, mExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoin", CCLabelTTF *, mCoin);
	CCB_CONTROLBUTTON_GLUE(this, "mCloseBtn", mCloseBtn, gls("77"));
	return false;
}

SEL_MenuHandler GetEnergyEventDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler GetEnergyEventDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", GetEnergyEventDialog::onCloseBtnClick);
	return NULL;
}

void GetEnergyEventDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("GetEnergyEventDialog::%s()", __FUNCTION__);
	mCloseBtn->setDefaultTouchPriority(touch_priority_5);

	Award& awardInfo = FightProxy::shared()->awardInfo;
	mDesc->setString(fls("168", awardInfo.energy));
	mExp->setString(fcs("+%d", awardInfo.exp));
	mCoin->setString(fcs("+%d", awardInfo.getCoin()));
}

void GetEnergyEventDialog::onCloseBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
}

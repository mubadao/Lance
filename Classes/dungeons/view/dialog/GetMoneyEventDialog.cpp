#include "GetMoneyEventDialog.h"
#include "FightProxy.h"

GetMoneyEventDialog::GetMoneyEventDialog()
	: mDesc(NULL)
	, mExp(NULL)
	, mCoin(NULL)
	, mCloseBtn(NULL)
{
	CCLOG("GetMoneyEventDialog::%s()", __FUNCTION__);
}

GetMoneyEventDialog::~GetMoneyEventDialog()
{
	CCLOG("GetMoneyEventDialog::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mDesc);
	CC_SAFE_RELEASE(mExp);
	CC_SAFE_RELEASE(mCoin);
	CC_SAFE_RELEASE(mCloseBtn);
}

bool GetMoneyEventDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDesc", CCLabelTTF *, mDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExp", CCLabelTTF *, mExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoin", CCLabelTTF *, mCoin);
	CCB_CONTROLBUTTON_GLUE(this, "mCloseBtn", mCloseBtn, gls("77"));
	return false;
}

SEL_MenuHandler GetMoneyEventDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler GetMoneyEventDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", GetMoneyEventDialog::onCloseBtnClick);
	return NULL;
}

void GetMoneyEventDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("GetMoneyEventDialog::%s()", __FUNCTION__);
	mCloseBtn->setDefaultTouchPriority(touch_priority_5);

	ExploreEvent& info = FightProxy::shared()->mEventInfo;
	mDesc->setString(fls("167", info.eventCoin));
	mExp->setString(fcs("+%d", info.exp));
	mCoin->setString(fcs("+%d", info.getCoin()));
}

void GetMoneyEventDialog::onCloseBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
}

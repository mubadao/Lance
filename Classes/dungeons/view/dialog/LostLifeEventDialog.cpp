#include "LostLifeEventDialog.h"
#include "FightProxy.h"

LostLifeEventDialog::LostLifeEventDialog()
	: mDesc(NULL)
	, mExp(NULL)
	, mCoin(NULL)
	, mCloseBtn(NULL)
{
	CCLOG("LostLifeEventDialog::%s()", __FUNCTION__);
}

LostLifeEventDialog::~LostLifeEventDialog()
{
	CCLOG("LostLifeEventDialog::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mDesc);
	CC_SAFE_RELEASE(mExp);
	CC_SAFE_RELEASE(mCoin);
	CC_SAFE_RELEASE(mCloseBtn);
}

bool LostLifeEventDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDesc", CCLabelTTF *, mDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExp", CCLabelTTF *, mExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoin", CCLabelTTF *, mCoin);
	CCB_CONTROLBUTTON_GLUE(this, "mCloseBtn", mCloseBtn, gls("77"));
	return false;
}

SEL_MenuHandler LostLifeEventDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler LostLifeEventDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", LostLifeEventDialog::onCloseBtnClick);
	return NULL;
}

void LostLifeEventDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("LostLifeEventDialog::%s()", __FUNCTION__);
	mCloseBtn->setDefaultTouchPriority(touch_priority_5);

	ExploreEvent& info = FightProxy::shared()->mEventInfo;
	mDesc->setString(fls("165", -info.life));
	mExp->setString(fcs("+%d", info.exp));
	mCoin->setString(fcs("+%d", info.getCoin()));
}

void LostLifeEventDialog::onCloseBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
}

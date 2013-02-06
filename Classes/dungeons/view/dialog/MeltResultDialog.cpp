#include "MeltResultDialog.h"
#include "ItemProxy.h"

MeltResultDialog::MeltResultDialog()
	: mTitle(NULL)
	, mPerfect(NULL)
	, mAttack(NULL)
	, mCloseBtn(NULL)
{
	CCLOG("MeltResultDialog::%s()", __FUNCTION__);
}

MeltResultDialog::~MeltResultDialog()
{
	CCLOG("MeltResultDialog::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mAttack);
	CC_SAFE_RELEASE(mCloseBtn);
	CC_SAFE_RELEASE(mPerfect);
}

bool MeltResultDialog::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_CCLABELTTF_GLUE(this, "mTitle", mTitle, gls("205"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAttack", CCLabelTTF *, mAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPerfect", CCLabelTTF *, mPerfect);
	CCB_CONTROLBUTTON_GLUE(this, "mCloseBtn", this->mCloseBtn, gls("77"));
	return false;
}

SEL_MenuHandler MeltResultDialog::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MeltResultDialog::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", MeltResultDialog::onCloseBtnClick);
	return NULL;
}

void MeltResultDialog::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	CCLOG("MeltResultDialog::%s()", __FUNCTION__);
	mCloseBtn->setDefaultTouchPriority(touch_priority_5);
	
	IntensifyResult& intensifyResult = ItemProxy::shared()->mIntensifyResult;
	mPerfect->setString(fcs("%s: %d%%", gls("206"), intensifyResult.perfect));
	EquipInfo* equipInfo1 = ItemProxy::shared()->curQiangHuaEquip;
	EquipInfo* equipInfo2 = ItemProxy::shared()->lastQiangHuaEquip;
	mAttack->setString(fcs("%s: +%d", gls("207"), equipInfo1->getMaxBaseProperty()-equipInfo2->getMaxBaseProperty()));
}

void MeltResultDialog::onCloseBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
}

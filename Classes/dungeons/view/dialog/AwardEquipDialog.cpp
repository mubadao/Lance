#include "AwardEquipDialog.h"

AwardEquipDialog::AwardEquipDialog()
	: mTitle(NULL)
	, mEquipDetail(NULL)
	, mCloseBtn(NULL)
{
}

AwardEquipDialog::~AwardEquipDialog()
{
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mCloseBtn);
	CC_SAFE_RELEASE(mEquipDetail);
}

bool AwardEquipDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_CCLABELTTF_GLUE(this, "mTitle", mTitle, gls("78"));
	CCB_CONTROLBUTTON_GLUE(this, "mCloseBtn", mCloseBtn, gls("77"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipDetail", EquipDetail*, mEquipDetail);
	return false;
}

SEL_MenuHandler AwardEquipDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler AwardEquipDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", AwardEquipDialog::onCloseBtnClick);
	return NULL;
}

void AwardEquipDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	mCloseBtn->setDefaultTouchPriority(touch_priority_5);
}

void AwardEquipDialog::onCloseBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
}

#include "XiLianOkDialog.h"
//#include "../../../model/proxy/ItemProxy.h"
#include "NetController.h"

EquipInfo* XiLianOkDialog::msEquipInfo = NULL;

XiLianOkDialog::XiLianOkDialog()
	: mTitle(NULL)
	, mDesc(NULL)
	, mCostTitle(NULL)
	, mOkBtn(NULL)
	, mCancelBtn(NULL)
	, mMoneyIcon(NULL)
{
}

XiLianOkDialog::~XiLianOkDialog()
{
	CC_SAFE_RELEASE(mMoneyIcon);
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mDesc);
	CC_SAFE_RELEASE(mCostTitle);
	CC_SAFE_RELEASE(mOkBtn);
	CC_SAFE_RELEASE(mCancelBtn);
}

bool XiLianOkDialog::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMoneyIcon", MoneyIcon*, mMoneyIcon);

	CCB_CCLABELTTF_GLUE(this, "mTitle", mTitle, gls("105"));
	CCB_CCLABELTTF_GLUE(this, "mDesc", mDesc, gls("143"));
	CCB_CCLABELTTF_GLUE(this, "mCostTitle", mCostTitle, gls("79"));
	CCB_CONTROLBUTTON_GLUE(this, "mOkBtn", mOkBtn, gls("74"));
	CCB_CONTROLBUTTON_GLUE(this, "mCancelBtn", mCancelBtn, gls("75"));
	return false;
}

SEL_MenuHandler XiLianOkDialog::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler XiLianOkDialog::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOkBtnClick", XiLianOkDialog::onOkBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCancelBtnClick", XiLianOkDialog::onCancelBtnClick);
	return NULL;
}

void XiLianOkDialog::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	mOkBtn->setDefaultTouchPriority(touch_priority_5);
	mCancelBtn->setDefaultTouchPriority(touch_priority_5);

	mMoneyIcon->setType(MONEY_TYPE_GOLD);
	mMoneyIcon->setCount(100);
}

void XiLianOkDialog::onOkBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	NetController::shared()->resetEquipage(msEquipInfo->index);
	close();
}

void XiLianOkDialog::onCancelBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
}

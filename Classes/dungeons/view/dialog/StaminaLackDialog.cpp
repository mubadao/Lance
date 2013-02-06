#include "StaminaLackDialog.h"
#include "UserProxy.h"
#include "NetController.h"
#include "StaticShop.h"
#include "CommonNotify.h"

StaminaLackDialog::StaminaLackDialog()
	: mTitle(NULL)
	, mTotalTime(NULL)
	, mCostTitle(NULL)
	, mBuyBtn(NULL)
	, mCancelBtn(NULL)
	, mMoneyIcon(NULL)
{
}

StaminaLackDialog::~StaminaLackDialog()
{
	CommonNotify::shared()->unregisterAllPowerTimeCall(
		this, schedule_selector(StaminaLackDialog::updateAllPowerTime));
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mTotalTime);
	CC_SAFE_RELEASE(mCostTitle);
	CC_SAFE_RELEASE(mBuyBtn);
	CC_SAFE_RELEASE(mCancelBtn);
	CC_SAFE_RELEASE(mMoneyIcon);
}

bool StaminaLackDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTitle", CCLabelTTF*, mTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTotalTime", CCLabelTTF*, mTotalTime);
	CCB_CCLABELTTF_GLUE(this, "mCostTitle", mCostTitle, gls("202"));

	CCB_CONTROLBUTTON_GLUE(this, "mBuyBtn", mBuyBtn, gls("133"));
	CCB_CONTROLBUTTON_GLUE(this, "mCancelBtn", mCancelBtn, gls("75"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMoneyIcon", MoneyIcon*, mMoneyIcon);
	return false;
}

SEL_MenuHandler StaminaLackDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler StaminaLackDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBuyBtnClick", StaminaLackDialog::onBuyBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCancelBtnClick", StaminaLackDialog::onCancelBtnClick);
	return NULL;
}

void StaminaLackDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	mBuyBtn->setDefaultTouchPriority(touch_priority_5);
	mCancelBtn->setDefaultTouchPriority(touch_priority_5);
	
	CommonNotify::shared()->registerAllPowerTimeCall(
		this, schedule_selector(StaminaLackDialog::updateAllPowerTime));

	mMoneyIcon->setType(StaticShop::shared()->getSupplyMoneyType(SUPPLY_TYPE_POWER));
	mMoneyIcon->setCount(StaticShop::shared()->getSupplyCostCount(SUPPLY_TYPE_POWER));
	updateAllPowerTime(UserProxy::shared()->getAllPowerTime());
}

void StaminaLackDialog::onBuyBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	int moneyType = StaticShop::shared()->getSupplyMoneyType(SUPPLY_TYPE_POWER);
	NetController::shared()->buyPower(moneyType);
	close();
}

void StaminaLackDialog::onCancelBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
}

void StaminaLackDialog::updateAllPowerTime( float object )
{
	HHMMSS time((long)object);
	mTotalTime->setString(fcs("%s: %02d:%02d:%02d", gls("203"), time.hour, time.minute, time.second));
}

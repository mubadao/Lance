#include "EquipDetailDialog.h"
#include "UserProxy.h"
#include "NetController.h"
#include "NotifyDefine.h"
#include "MeltOkDialog.h"

EquipDetailDialog::EquipDetailDialog()
	: mEquipBtn(NULL)
	, mSellBtn(NULL)
	, mCloseBtn(NULL)
	, mEquipDetail(NULL)
	, mMoneyIcon(NULL)
	, mSellTitle(NULL)
	, mUpgradeBtn(NULL)
	, mMeltBtn(NULL)
{
	CCLOG("EquipDetailDialog::%s()", __FUNCTION__);
}

EquipDetailDialog::~EquipDetailDialog()
{
	CCLOG("EquipDetailDialog::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mEquipBtn);
	CC_SAFE_RELEASE(mSellBtn);
	CC_SAFE_RELEASE(mCloseBtn);
	CC_SAFE_RELEASE(mUpgradeBtn);
	CC_SAFE_RELEASE(mMeltBtn);
	CC_SAFE_RELEASE(mSellTitle);
	CC_SAFE_RELEASE(mEquipDetail);
	CC_SAFE_RELEASE(mMoneyIcon);
}

bool EquipDetailDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_CONTROLBUTTON_GLUE(this, "mEquipBtn", mEquipBtn, gls("70"));
	CCB_CONTROLBUTTON_GLUE(this, "mSellBtn", mSellBtn, gls("76"));
	CCB_CONTROLBUTTON_GLUE(this, "mUpgradeBtn", mUpgradeBtn, gls("72"));
	CCB_CONTROLBUTTON_GLUE(this, "mMeltBtn", mMeltBtn, gls("73"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCloseBtn", CCControlButton*, mCloseBtn);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipDetail", EquipDetail*, mEquipDetail);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMoneyIcon", MoneyIcon*, mMoneyIcon);
	CCB_CCLABELTTF_GLUE(this, "mSellTitle", mSellTitle, gls("193"));
	return false;
}

SEL_CCControlHandler EquipDetailDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onEquipBtnClick", EquipDetailDialog::onEquipBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSellBtnClick", EquipDetailDialog::onSellBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", EquipDetailDialog::onCloseBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onUpgradeBtnClick", EquipDetailDialog::onUpgradeBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMeltBtnClick", EquipDetailDialog::onMeltBtnClick);
	return NULL;
}

SEL_MenuHandler EquipDetailDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

void EquipDetailDialog::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	CCLOG("EquipDetailDialog::%s()", __FUNCTION__);
	mCloseBtn->setDefaultTouchPriority(touch_priority_5);
	mEquipBtn->setDefaultTouchPriority(touch_priority_5);
	mSellBtn->setDefaultTouchPriority(touch_priority_5);
	mUpgradeBtn->setDefaultTouchPriority(touch_priority_5);
	mMeltBtn->setDefaultTouchPriority(touch_priority_5);

	bool isPutOn = ItemProxy::shared()->isEquipPutOn(gsEquipInfo->index);

	if(!isPutOn)
	{
		mEquipBtn->setTitleForState(ccs(gls("70")), CCControlStateNormal);
		mEquipBtn->setTitleForState(ccs(gls("70")), CCControlStateHighlighted);
	}
	else
	{
		mEquipBtn->setTitleForState(ccs(gls("71")), CCControlStateNormal);
		mEquipBtn->setTitleForState(ccs(gls("71")), CCControlStateHighlighted);
	}
	
	mMoneyIcon->setType(MONEY_TYPE_GOLD);
	mMoneyIcon->setCount(gsEquipInfo->getSellPrize());
}

void EquipDetailDialog::onEquipBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	if(ItemProxy::shared()->isEquipPutOn(gsEquipInfo->index))
	{
		NetController::shared()->unloadEquipage(gsEquipInfo->index);
		close();
	}
	else
	{
		EquipStatic* equipStatic = StaticItem::shared()->getEquipInfo(gsEquipInfo->id);
		if(equipStatic->level > UserProxy::shared()->userVO.level)
		{
			FloatText::shared()->playAnim(gls("194"));
		}
		else
		{
			NetController::shared()->loadEquipage(gsEquipInfo->index);
			close();
		}
	}
}

void EquipDetailDialog::onSellBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	vector<int>& sellList = ItemProxy::shared()->sellList;
	sellList.clear();
	sellList.push_back(gsEquipInfo->index);
	Post_Net_Notification(kVCSellEquip, NULL);
	close();
}

void EquipDetailDialog::onCloseBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	close();
}

void EquipDetailDialog::onUpgradeBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	ItemProxy::shared()->curQiangHuaEquip = gsEquipInfo;
	FRAMEWORK->changeState("EquipMergeScene");
	close();
}

void EquipDetailDialog::onMeltBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	MeltOkDialog::msEquipInfo = gsEquipInfo;
	FRAMEWORK->popup("MeltOkDialog");
    close();
}


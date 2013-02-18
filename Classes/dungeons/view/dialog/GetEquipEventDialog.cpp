#include "GetEquipEventDialog.h"
#include "FightProxy.h"
#include "NotifyDefine.h"
#include "NetController.h"
#include "MeltOkDialog.h"

GetEquipEventDialog::GetEquipEventDialog()
	: mDesc(NULL)
	, mExp(NULL)
	, mCoin(NULL)
	, mItemName(NULL)
	, mSellTitle(NULL)
	, mCloseBtn(NULL)
	, mSellBtn(NULL)
	, mMeltBtn(NULL)
	, mEquipDetail(NULL)
	, mMoneyIcon(NULL)
{
	CCLOG("GetEquipEventDialog::%s()", __FUNCTION__);
}

GetEquipEventDialog::~GetEquipEventDialog()
{
	CCLOG("GetEquipEventDialog::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mDesc);
	CC_SAFE_RELEASE(mExp);
	CC_SAFE_RELEASE(mCoin);
	CC_SAFE_RELEASE(mItemName);
	CC_SAFE_RELEASE(mSellTitle);
	CC_SAFE_RELEASE(mCloseBtn);
	CC_SAFE_RELEASE(mSellBtn);
	CC_SAFE_RELEASE(mEquipDetail);
	CC_SAFE_RELEASE(mMoneyIcon);
}

bool GetEquipEventDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExp", CCLabelTTF *, mExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoin", CCLabelTTF *, mCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItemName", CCLabelTTF *, mItemName);
	CCB_CCLABELTTF_GLUE(this, "mDesc", mDesc, gls("169"));
	CCB_CCLABELTTF_GLUE(this, "mSellTitle", mSellTitle, gls("193"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipDetail", EquipDetail*, mEquipDetail);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMoneyIcon", MoneyIcon*, mMoneyIcon);
	CCB_CONTROLBUTTON_GLUE(this, "mCloseBtn", mCloseBtn, gls("77"));
	CCB_CONTROLBUTTON_GLUE(this, "mSellBtn", mSellBtn, gls("76"));
    CCB_CONTROLBUTTON_GLUE(this, "mMeltBtn", this->mMeltBtn, gls("73"));
	return false;
}

SEL_MenuHandler GetEquipEventDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler GetEquipEventDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMeltBtnClick", GetEquipEventDialog::onMeltBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", GetEquipEventDialog::onCloseBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSellBtnClick", GetEquipEventDialog::onSellBtnClick);
	return NULL;
}

void GetEquipEventDialog::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	CCLOG("GetEquipEventDialog::%s()", __FUNCTION__);	
	mSellBtn->setDefaultTouchPriority(touch_priority_5);
	mCloseBtn->setDefaultTouchPriority(touch_priority_5);
	mMeltBtn->setDefaultTouchPriority(touch_priority_5);
}

void GetEquipEventDialog::refresh()
{
	ExploreEvent& info = FightProxy::shared()->mEventInfo;
	EquipInfo* equip = FightProxy::shared()->getAwardEquip();
	
	mItemName->setColor(equip->getNameColor());
	const char* a = fcs("item%05d", equip->baseId);
	mItemName->setString(fcs("【%s】", gls(a)));
	mExp->setString(fcs("+%d", info.exp));
	mCoin->setString(fcs("+%d", info.getCoin()));
	mMoneyIcon->setType(MONEY_TYPE_COIN);
	mMoneyIcon->setCount(equip->getSellPrize());

	mEquipDetail->setUserData(equip);
	mEquipDetail->refresh();
}

void GetEquipEventDialog::onCloseBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
}

void GetEquipEventDialog::onSellBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	ExploreEvent& info = FightProxy::shared()->mEventInfo;
	vector<int>& sellList = EquipProxy::shared()->mSellList;
	sellList.clear();
	sellList.push_back(info.equipList[0].index);
	Post_Net_Notification(kVCSellEquip, NULL);
	close();
}

void GetEquipEventDialog::onMeltBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	FRAMEWORK->popup("MeltOkDialog", FightProxy::shared()->getAwardEquip());
    close();
}

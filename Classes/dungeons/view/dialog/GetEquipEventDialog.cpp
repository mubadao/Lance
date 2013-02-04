#include "GetEquipEventDialog.h"
#include "FightProxy.h"
#include "NotifyDefine.h"
#include "NetController.h"

GetEquipEventDialog::GetEquipEventDialog()
	: mDesc(NULL)
	, mExp(NULL)
	, mCoin(NULL)
	, mItemName(NULL)
	, mSellTitle(NULL)
	, mCloseBtn(NULL)
	, mSellBtn(NULL)
	, mEquipDetail(NULL)
	, mMoneyIcon(NULL)
{
}

GetEquipEventDialog::~GetEquipEventDialog()
{
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
	return false;
}

SEL_MenuHandler GetEquipEventDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler GetEquipEventDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseBtnClick", GetEquipEventDialog::onCloseBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSellBtnClick", GetEquipEventDialog::onSellBtnClick);
	return NULL;
}

void GetEquipEventDialog::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	Award& awardInfo = FightProxy::shared()->awardInfo;
	gsEquipInfo = awardInfo.equipList[0];
	EquipStatic* equipStatic = StaticItem::shared()->getEquipInfo(gsEquipInfo->id);
	mItemName->setColor(gsEquipInfo->getNameColor());
	mItemName->setString(fcs("【%s】", equipStatic->name));
	mExp->setString(fcs("+%d", awardInfo.exp));
	mCoin->setString(fcs("+%d", awardInfo.getCoin()));
	mMoneyIcon->setType(MONEY_TYPE_GOLD);
	mMoneyIcon->setCount(gsEquipInfo->getSellPrize());
}

void GetEquipEventDialog::onCloseBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	close();
}

void GetEquipEventDialog::onSellBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
	vector<int>& sellList = ItemProxy::shared()->sellList;
	sellList.clear();
	Award& awardInfo = FightProxy::shared()->awardInfo;
	EquipInfo* equipInfo = awardInfo.equipList[0];
	sellList.push_back(equipInfo->index);
	Post_Net_Notification(kVCSellEquip, NULL);
	close();
}

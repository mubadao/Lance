#include "FightSucceedDialog.h"
#include "NetController.h"

FightSucceedDialog::FightSucceedDialog()
	: mEquipDetail(NULL)
	, mGold(NULL)
	, mExp(NULL)
	, mTitle(NULL)
	, mReturnBtn(NULL)
	, mTalk(NULL)
{
	CCLOG("FightSucceedDialog::%s()", __FUNCTION__);
}

FightSucceedDialog::~FightSucceedDialog()
{
	CCLOG("FightSucceedDialog::%s()", __FUNCTION__);
	RemoveObserver(this);
	
	CC_SAFE_RELEASE(mGold);
	CC_SAFE_RELEASE(mExp);
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mTalk);
	CC_SAFE_RELEASE(mReturnBtn);
	CC_SAFE_RELEASE(mEquipDetail);
}

bool FightSucceedDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGold", CCLabelTTF*, mGold);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExp", CCLabelTTF*, mExp);

	CCB_CCLABELTTF_GLUE(this, "mTitle", mTitle, gls("battle_succeed"));
	CCB_CONTROLBUTTON_GLUE(this, "mReturnBtn", mReturnBtn, gls("111"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTalk", CCLabelTTF *, mTalk);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipDetail", EquipDetail*, mEquipDetail);
	return NULL;
}

SEL_CCControlHandler FightSucceedDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReturnBtnClick", FightSucceedDialog::onReturnBtnClick);
	return NULL;
}

void FightSucceedDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("FightSucceedDialog::%s()", __FUNCTION__);
	mReturnBtn->setDefaultTouchPriority(touch_priority_5);

	CCArray* nameList = CCArray::create(ccs(kNCDungeonStart),NULL);
	RegisterObservers(this, nameList, callfuncO_selector(FightSucceedDialog::_onNotification));

	mTalk->setString(gls(fcs("talk_01_%02d", DungeonsProxy::shared()->getCurFloor())));
}

void FightSucceedDialog::refresh()
{
	FightProxy::shared()->mEventInfo.equipList[0];
	ExploreEvent& info = FightProxy::shared()->mEventInfo;
	mGold->setString(fcs("+%d", info.coin));
	mExp->setString(fcs("+%d", info.exp));
	
	mEquipDetail->setUserData(FightProxy::shared()->getAwardEquip());
	mEquipDetail->refresh();
}

void FightSucceedDialog::onReturnBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	int dungeonsID = DungeonsProxy::shared()->getCurDungeon();
	int floorID = DungeonsProxy::shared()->getCurFloor();
	NetController::shared()->dungeonStart(dungeonsID, floorID);
}

void FightSucceedDialog::_onNotification( CCObject* object )
{
	CCLOG("FightSucceedDialog::%s()", __FUNCTION__);
	NotificationObserver* notification = (NotificationObserver*)object;
	string name = string(notification->getName());
	
	if (name == kNCDungeonStart)
	{
		close();
	}
}

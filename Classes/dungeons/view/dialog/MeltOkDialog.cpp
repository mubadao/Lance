#include "MeltOkDialog.h"
#include "NetController.h"

MeltOkDialog::MeltOkDialog()
	: mGetEnergy(NULL)
	, mTitle(NULL)
	, mDesc(NULL)
	, mOkBtn(NULL)
	, mCancelBtn(NULL)
{
	CCLOG("MeltOkDialog::%s()", __FUNCTION__);
}

MeltOkDialog::~MeltOkDialog()
{
	CCLOG("MeltOkDialog::%s()", __FUNCTION__);
	RemoveObserver(this);
	CC_SAFE_RELEASE(mGetEnergy);
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mDesc);
	CC_SAFE_RELEASE(mOkBtn);
	CC_SAFE_RELEASE(mCancelBtn);
}

bool MeltOkDialog::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGetEnergy", CCLabelTTF*, mGetEnergy);

	CCB_CCLABELTTF_GLUE(this, "mTitle", mTitle, gls("73"));
	CCB_CCLABELTTF_GLUE(this, "mDesc", mDesc, gls("130"));
	CCB_CONTROLBUTTON_GLUE(this, "mOkBtn", mOkBtn, gls("74"));
	CCB_CONTROLBUTTON_GLUE(this, "mCancelBtn", mCancelBtn, gls("75"));
	return false;
}

SEL_MenuHandler MeltOkDialog::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MeltOkDialog::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOkBtnClick", MeltOkDialog::onOkBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCancelBtnClick", MeltOkDialog::onCancelBtnClick);
	return NULL;
}

void MeltOkDialog::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	CCLOG("MeltOkDialog::%s()", __FUNCTION__);
	
	mOkBtn->setDefaultTouchPriority(touch_priority_5);
	mCancelBtn->setDefaultTouchPriority(touch_priority_5);

	CCArray* nameList = CCArray::create(ccs(kNCFusionEquipage),NULL);
	RegisterObservers(this, nameList, callfuncO_selector(MeltOkDialog::_onNotification));
}

void MeltOkDialog::refresh()
{
	mGetEnergy->setString(fcs("%s: %d", gls("131"), _getMeltCost()));
}

void MeltOkDialog::_onNotification(CCObject* object)
{
	CCLOG("MeltOkDialog::%s()", __FUNCTION__);
	NotificationObserver* observer = (NotificationObserver*)object;
	string name(observer->getName());
	
	if (name == kNCFusionEquipage)
	{
		FloatText::shared()->playAnim(gls("205"));
		close();
	}
}

void MeltOkDialog::onOkBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	EquipInfo* equip = (EquipInfo*)getUserData();
	vector<int>& meltList = EquipProxy::shared()->mMeltList;
	meltList.clear();
	meltList.push_back(equip->index);
	NetController::shared()->fusionEquipage(meltList);
}

void MeltOkDialog::onCancelBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	close();
}

int MeltOkDialog::_getMeltCost()
{
	EquipInfo* equipInfo = (EquipInfo*)getUserData();
	return StaticItem::shared()->getEquipInfo(equipInfo->baseId)->fusion;;
}

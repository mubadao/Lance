#include "DungeonsItem.h"
#include "StaticDungeons.h"
#include "DungeonsProxy.h"
#include "NetController.h"
#include "AlertDialog.h"
#include "DungeonsItemLoader.h"

DungeonsItem::DungeonsItem()
	: mName(NULL)
	, mLock(NULL)
	, mGoBtn(NULL)
	, mNodeBg(NULL)
{
	CCLOG("DungeonsItem::%s()", __FUNCTION__);
}

DungeonsItem::~DungeonsItem()
{
	CCLOG("DungeonsItem::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mNodeBg);
	CC_SAFE_RELEASE(mName);
	CC_SAFE_RELEASE(mLock);
	CC_SAFE_RELEASE(mGoBtn);
}

SEL_MenuHandler DungeonsItem::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler DungeonsItem::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onGoBtnClick", DungeonsItem::onGoBtnClick);
	return NULL;
}

bool DungeonsItem::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeBg", CCNode*, mNodeBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName", CCLabelTTF*, mName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLock", CCSprite*, mLock);
	CCB_CONTROLBUTTON_GLUE(this, "mGoBtn", mGoBtn, gls("90"));
	return true;
}

void DungeonsItem::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	CCLOG("DungeonsItem::%s()", __FUNCTION__);
}

void DungeonsItem::setInfo(int dungeonId, int floorId)
{
	mDungeonID = dungeonId;
	mFloorID = floorId;
	
	FloorStatic* floorInfo = StaticDungeons::shared()->getFloorInfo(dungeonId, floorId);
	int maxFloorID = DungeonsProxy::shared()->getMaxFloorID();
	
	mName->setString(floorInfo->name);

	if(floorId > maxFloorID)
	{
		BYGraySprite* bg = BYGraySprite::create(fcs("scene/scene%d_thum.jpg", floorId));
		mNodeBg->addChild(bg);
		mLock->setVisible(true);
		mGoBtn->setVisible(false);
	}
	else
	{
		CCSprite* bg = CCSprite::create(fcs("scene/scene%d_thum.jpg",floorId));
		mNodeBg->addChild(bg);
		mLock->setVisible(false);
		mGoBtn->setVisible(true);
	}
}

void DungeonsItem::onGoBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	if(DungeonsProxy::shared()->getMaxDungeonsID() == 1 &&
	   DungeonsProxy::shared()->getMaxFloorID() == 1 &&
	   DungeonsProxy::shared()->getMaxTaskID() == 1 &&
	   DungeonsProxy::shared()->getMaxProgress() == 0)
	{
		FRAMEWORK->changeState("DungeonsScene");
	}
	else
	{
		AlertDialog::initContent(gls("148"), false, this, callfunc_selector(DungeonsItem::_gotoExplore));
		FRAMEWORK->popup("AlertDialog");
	}
}

void DungeonsItem::_gotoExplore()
{
	NetController::shared()->dungeonStart(mDungeonID, mFloorID);
}

DungeonsItem* DungeonsItem::create(CCObject* pOwer)
{
	return (DungeonsItem*)ReadItem("DungeonsItem", DungeonsItemLoader::loader());
}

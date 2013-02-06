#include "DungeonsListScene.h"
#include "NetController.h"

DungeonsListScene::DungeonsListScene()
	: mScrollView(NULL)
	, mReturnBtn(NULL)
{
	CCLOG("DungeonsListScene::%s()", __FUNCTION__);
}

DungeonsListScene::~DungeonsListScene()
{
	CCLOG("DungeonsListScene::%s()", __FUNCTION__);
	RemoveObserver(this);

	CC_SAFE_RELEASE(mScrollView);
	CC_SAFE_RELEASE(mReturnBtn);
}

SEL_MenuHandler DungeonsListScene::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler DungeonsListScene::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReturnBtnClick", DungeonsListScene::onReturnBtnClick);
	return NULL;
}

bool DungeonsListScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollView", CCScrollView*, mScrollView);
	CCB_CONTROLBUTTON_GLUE(this, "mReturnBtn", mReturnBtn, gls("161"));
	return true;
}

void DungeonsListScene::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	CCLOG("DungeonsListScene::%s()", __FUNCTION__);
	CCArray* nameList = CCArray::create(ccs(kNCDungeonStart), NULL);
	RegisterObservers(this, nameList, callfuncO_selector(DungeonsListScene::_onNotification));

	FloorStaticMap floorMap = DungeonsProxy::shared()->getCurDungeonsStatic()->floorList;

	int maxCount = floorMap.size();
	CCPoint contentPos = ccp(0, maxCount * 166);
	mScrollView->setContentSize(CCSizeMake(640, contentPos.y));
	mScrollView->setContentOffset(ccp(0, mScrollView->getViewSize().height - contentPos.y));
	for (int i = 0; i < maxCount; i++)
	{
		DungeonsItem* item = DungeonsItem::create(NULL);
		item->setInfo(DungeonsProxy::shared()->getCurDungeonsID(), floorMap[i+1]->floorID);
		item->setPosition(ccp(0, contentPos.y - (i + 1) * 166));
		mScrollView->getContainer()->addChild(item);
	}
}

void DungeonsListScene::_onNotification( CCObject* object )
{
	CCLOG("DungeonsListScene::%s()", __FUNCTION__);
	NotificationObserver* notification = (NotificationObserver*)object;
	string name = string(notification->getName());

	if (name == kNCDungeonStart)
	{
		FRAMEWORK->changeState("DungeonsScene");
	}
}

void DungeonsListScene::onReturnBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	FRAMEWORK->changeState("DungeonsScene");
}

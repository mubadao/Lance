#include "ChallengeScene.h"
#include "ChallengeItem.h"
#include "NetController.h"

ChallengeScene::ChallengeScene()
	: mScrollView(NULL)
	, mAttack(NULL)
	, mDefense(NULL)
	, mLife(NULL)
	, mRefreshBtn(NULL)
{
	CCLOG("ChallengeScene::%s()", __FUNCTION__);
}

ChallengeScene::~ChallengeScene()
{
	CCLOG("ChallengeScene::%s()", __FUNCTION__);
	RemoveObserver(this);
	
	CC_SAFE_RELEASE(mScrollView);
	CC_SAFE_RELEASE(mAttack);
	CC_SAFE_RELEASE(mDefense);
	CC_SAFE_RELEASE(mLife);
	CC_SAFE_RELEASE(mRefreshBtn);
}

SEL_MenuHandler ChallengeScene::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler ChallengeScene::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRefreshBtnClick", ChallengeScene::onRefreshBtnClick);
	return NULL;
}

bool ChallengeScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_CONTROLBUTTON_GLUE(this, "mRefreshBtn", mRefreshBtn, gls("204"));
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollView", CCScrollView*, mScrollView);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAttack", CCLabelTTF*, mAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDefense", CCLabelTTF*, mDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLife", CCLabelTTF*, mLife);
	return false;
}

void ChallengeScene::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("ChallengeScene::%s()", __FUNCTION__);

	UserVO& userVO = UserProxy::shared()->userVO;
	mAttack->setString(fcs("%s:%d-%d", gls("Attack"), userVO.atkMin, userVO.atkMax));
	mDefense->setString(fcs("%s:%d-%d", gls("Defense"), userVO.defMin, userVO.defMax));
	mLife->setString(fcs("%s:%d", gls("93"), userVO.life));

	CCArray* nameList = CCArray::create(
		ccs(kNCGetChallengeList),
		ccs(kNCChallengePlayer),
		ccs(kNCGetChallengeEnemyList),
		NULL);
	RegisterObservers(this, nameList, callfuncO_selector(ChallengeScene::_onNotification));

	NetController::shared()->getChallengeList();
}

void ChallengeScene::_refresh()
{
	ChallengeEnemyList& list = ChallengeProxy::shared()->mChallengeEnemyList;
	CCPoint contentPos = ccp(0, list.size() * 176 + 100);
	mScrollView->setContentSize(CCSizeMake(640, contentPos.y));
	mScrollView->setContentOffset(ccp(0, mScrollView->getViewSize().height - contentPos.y));

	mScrollView->getContainer()->removeAllChildrenWithCleanup(true);
	for(int i = 0; i < list.size(); i++)
	{
		ChallengeItem* item = ChallengeItem::create(NULL);
		item->setUserData(&list[i]);
		item->refresh();
		item->setPosition(ccp(0, contentPos.y - ((i + 1) * 176)));
		mScrollView->getContainer()->addChild(item);
	}

	mRefreshBtn->removeFromParent();
	mRefreshBtn->setPosition(ccp(320, 40));
	mScrollView->getContainer()->addChild(mRefreshBtn);
}

void ChallengeScene::_onNotification( CCObject* object )
{
	CCLOG("ChallengeScene::%s()", __FUNCTION__);

	NotificationObserver* observer = (NotificationObserver*)object;
	string name(observer->getName());
	
	if (name == kNCGetChallengeList || name == kNCGetChallengeEnemyList)
	{
		_refresh();
	}
	else if (name == kNCChallengePlayer)
	{
		_refresh();
		FRAMEWORK->popup("ChallengeResultDialog");
	}
}

void ChallengeScene::onRefreshBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	NetController::shared()->getChallengeList();
}
#include "HomeScene.h"

HomeScene::HomeScene()
	: mScrollView(NULL)
{
	CCLOG("HomeScene::%s()", __FUNCTION__);
}

HomeScene::~HomeScene()
{
	CCLOG("HomeScene::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mScrollView);
}

bool HomeScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollView", CCScrollView*, mScrollView);
	return true;
}

void HomeScene::onNodeLoaded( CCNode* pNode, CCNodeLoader* pNodeLoader )
{
	CCLOG("HomeScene::%s()", __FUNCTION__);
	mScrollView->setContentOffset(ccp(0, mScrollView->getViewSize().height - mScrollView->getContainer()->getContentSize().height));
}

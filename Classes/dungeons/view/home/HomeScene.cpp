#include "HomeScene.h"

HomeScene::HomeScene()
	: mScrollView(NULL)
{
}

HomeScene::~HomeScene()
{
	CC_SAFE_RELEASE(mScrollView);
}

bool HomeScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollView", CCScrollView*, mScrollView);
	return true;
}

void HomeScene::onNodeLoaded( CCNode* pNode, CCNodeLoader* pNodeLoader )
{
	mScrollView->setContentOffset(ccp(0, mScrollView->getViewSize().height - mScrollView->getContainer()->getContentSize().height));
}

#include "PlayerDetailScene.h"

PlayerDetailScene::PlayerDetailScene()
	: mScrollView(NULL)
{
	CCLOG("PlayerDetailScene::%s()", __FUNCTION__);
}

PlayerDetailScene::~PlayerDetailScene()
{
	CCLOG("PlayerDetailScene::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mScrollView);
}

bool PlayerDetailScene::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollView", CCScrollView *, mScrollView);
	return false;
}

void PlayerDetailScene::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	mScrollView->setContentOffset(ccp(0, mScrollView->getViewSize().height - mScrollView->getContentSize().height));
}

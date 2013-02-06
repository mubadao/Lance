#include "EquipDetail.h"
#include "EquipIconLoader.h"
#include "EquipDetailLoader.h"

EquipDetail::EquipDetail()
	:mScrollView(NULL)
{
	CCLOG("EquipDetail::%s()", __FUNCTION__);
}

EquipDetail::~EquipDetail()
{
	CCLOG("EquipDetail::%s()", __FUNCTION__);
	CC_SAFE_RELEASE(mScrollView);
}

bool EquipDetail::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollView", CCScrollView *, mScrollView);
	return false;
}

void EquipDetail::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
	CCLOG("EquipDetail::%s()", __FUNCTION__);
	mScrollView->setTouchPriority(touch_priority_4);
	EquipDetailContent* content = (EquipDetailContent*)mScrollView->getContainer();
	mScrollView->setContentOffset(ccp(0, mScrollView->getViewSize().height - content->getContentSize().height));
}

EquipDetail* EquipDetail::create( CCObject* pOwer )
{
	CCNodeLoaderLibrary* pLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	
	pLoaderLibrary->registerCCNodeLoader("EquipIcon", EquipIconLoader::loader());
	pLoaderLibrary->registerCCNodeLoader("EquipDetail", EquipDetailLoader::loader());
	
	CCBReader* ccbReader = new CCBReader(pLoaderLibrary);
	CCNode* node = ccbReader->readNodeGraphFromFile("EquipDetail.ccbi", NULL);
	ccbReader->release();
	return (EquipDetail*)node;
}

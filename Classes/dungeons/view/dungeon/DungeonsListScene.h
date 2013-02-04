#ifndef _DungeonsListScene_H_
#define _DungeonsListScene_H_

#include "Global.h"
#include "DungeonsItem.h"

class DungeonsListScene
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(DungeonsListScene, create);

	DungeonsListScene();
	virtual ~DungeonsListScene();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

private:
	CCScrollView* mScrollView;
	CCControlButton* mReturnBtn;

	void _onNotification( CCObject* object );
	virtual void onReturnBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
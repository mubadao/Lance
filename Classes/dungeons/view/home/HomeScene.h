#ifndef _HomeScene_H_
#define _HomeScene_H_

#include "Global.h"

class HomeScene
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HomeScene, create);

	HomeScene();
	virtual ~HomeScene();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
private:
	CCScrollView* mScrollView;
};

#endif
#ifndef _PlayerDetailScene_H_
#define _PlayerDetailScene_H_

#include "Global.h"

class PlayerDetailScene
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PlayerDetailScene, create);

	PlayerDetailScene();
	~PlayerDetailScene();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCScrollView* mScrollView;
};

#endif
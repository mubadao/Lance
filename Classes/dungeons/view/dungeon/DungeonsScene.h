#ifndef _DungeonScene_H_
#define _DungeonScene_H_

#include "Global.h"
#include "TaskDesc.h"
#include "TaskBoss.h"
#include "TaskNormal.h"
#include "MainMenu.h"

class DungeonsScene
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(DungeonsScene, create);
	
	DungeonsScene();
	virtual ~DungeonsScene();
	
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName){return NULL;}
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){return NULL;}
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	void refresh();

private:
	TaskDesc* mTaskDesc;
	TaskBoss* mTaskBoss;
	TaskNormal* mTaskNormal;
	MainMenu* mMainMenu;
	
	void _onNotification(CCObject* object);
	void _playAwardAnim();
};

#endif
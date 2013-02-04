#ifndef _TaskDesc_H_
#define _TaskDesc_H_

#include "Global.h"

class TaskDesc
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TaskDesc, create);

	TaskDesc();
	virtual ~TaskDesc();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	void refresh();
	void shakeScene();
	void setDesc(const char* desc);

private:
	CCLabelTTF* mName;
	CCLabelTTF* mDesc;
	CCSprite* mSelect;
	CCNode* mNodeBg;
	CCControlButton* mBtnList;

	void onBtnList(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
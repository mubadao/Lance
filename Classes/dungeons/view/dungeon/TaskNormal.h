#ifndef _TaskNormal_H_
#define _TaskNormal_H_

#include "Global.h"

class TaskNormal
	: public CCNode
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TaskNormal, create);

	TaskNormal();
	~TaskNormal();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	void refresh();

private:
	CCLabelTTF* mLifeTitle;
	CCLabelTTF* mProgressTitle;
	CCLabelTTF* mExp;
	CCLabelTTF* mCoin;
	CCLabelTTF* mEnergy;
	CCControlButton* mDoItBtn;

	ProgressText* mProgress;
	ProgressText* mLifeProgress;
	
	void onDoItBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
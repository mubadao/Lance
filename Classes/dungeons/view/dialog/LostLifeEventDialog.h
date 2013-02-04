#ifndef _LostLifeEventDialog_H_
#define _LostLifeEventDialog_H_

#include "Global.h"

class LostLifeEventDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LostLifeEventDialog, create);

	LostLifeEventDialog();
	~LostLifeEventDialog();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCLabelTTF* mDesc;
	CCLabelTTF* mExp;
	CCLabelTTF* mCoin;
	CCControlButton* mCloseBtn;

	void onCloseBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
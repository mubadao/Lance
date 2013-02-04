#ifndef _BuyMoneyDialog_H_
#define _BuyMoneyDialog_H_

#include "Global.h"

class BuyMoneyDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BuyMoneyDialog, create);

	BuyMoneyDialog();
	~BuyMoneyDialog();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCLabelTTF* mTitle;
	CCControlButton* mBtnClose;
	CCScrollView* mScrollView;

	void _onNotification(CCObject* object);
	void onCloseBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
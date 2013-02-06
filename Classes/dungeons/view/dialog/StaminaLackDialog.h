#ifndef _StaminaLackDialog_H_
#define _StaminaLackDialog_H_

#include "Global.h"
#include "MoneyIcon.h"

class StaminaLackDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(StaminaLackDialog, create);

	StaminaLackDialog();
	~StaminaLackDialog();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCLabelTTF* mTitle;
	CCLabelTTF* mTotalTime;
	CCLabelTTF* mCostTitle;

	CCControlButton* mBuyBtn;
	CCControlButton* mCancelBtn;

	MoneyIcon* mMoneyIcon;

	void _onNotification(CCObject* object);
	void updateAllPowerTime( float object );
	void onBuyBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onCancelBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
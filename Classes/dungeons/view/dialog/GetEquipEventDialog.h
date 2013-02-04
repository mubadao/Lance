#ifndef _GetEquipEventDialog_H_
#define _GetEquipEventDialog_H_

#include "Global.h"
#include "EquipDetail.h"
#include "MoneyIcon.h"

class GetEquipEventDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GetEquipEventDialog, create);

	GetEquipEventDialog();
	~GetEquipEventDialog();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCLabelTTF* mDesc;
	CCLabelTTF* mItemName;
	CCLabelTTF* mExp;
	CCLabelTTF* mCoin;
	CCLabelTTF* mSellTitle;
	
	CCControlButton* mCloseBtn;
	CCControlButton* mSellBtn;

	EquipDetail* mEquipDetail;
	MoneyIcon* mMoneyIcon;

	void onCloseBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onSellBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
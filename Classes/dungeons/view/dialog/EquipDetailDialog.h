#ifndef _EquipDetailDialog_H_
#define _EquipDetailDialog_H_

#include "Global.h"
#include "EquipDetail.h"
#include "MoneyIcon.h"

class EquipDetailDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EquipDetailDialog, create);

	EquipDetailDialog();
	~EquipDetailDialog();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
	virtual void refresh();

private:
	CCControlButton* mEquipBtn;
	CCControlButton* mSellBtn;
	CCControlButton* mCloseBtn;
	CCControlButton* mUpgradeBtn;
	CCControlButton* mMeltBtn;
	CCLabelTTF* mSellTitle;
	EquipDetail* mEquipDetail;
	MoneyIcon* mMoneyIcon;

	void onEquipBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onSellBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onCloseBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onMeltBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onUpgradeBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
#ifndef _XiLianOkDialog_H_
#define _XiLianOkDialog_H_

#include "Global.h"
#include "MoneyIcon.h"

class XiLianOkDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(XiLianOkDialog, create);

	XiLianOkDialog();
	~XiLianOkDialog();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

	static EquipInfo* msEquipInfo;

private:
	CCLabelTTF* mTitle;
	CCLabelTTF* mDesc;
	CCLabelTTF* mCostTitle;

	CCControlButton* mOkBtn;
	CCControlButton* mCancelBtn;

	MoneyIcon* mMoneyIcon;

	void onOkBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent);
	void onCancelBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent);
};

#endif
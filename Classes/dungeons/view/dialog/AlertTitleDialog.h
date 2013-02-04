#ifndef _AlertTitleDialog_H_
#define _AlertTitleDialog_H_

#include "Global.h"

class AlertTitleDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AlertTitleDialog, create);

	AlertTitleDialog();
	~AlertTitleDialog();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	virtual void close();

	static void initContent(const string& title,
		const string& content,
		bool onlyOneBtn = false,
		CCObject* okTarget = NULL,
		SEL_CallFunc okCall = NULL,
		CCObject* cancelTarget = NULL,
		SEL_CallFunc cancelCall = NULL,
		const string& okLabel = "",
		const string& cancelLabel = "");

private:
	CCLabelTTF* mTitle;
	CCLabelTTF* mContent;
	CCControlButton* mOkBtn;
	CCControlButton* mCancelBtn;
	
	void onOkBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent);
	void onCancelBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent);

	static string msTitle;
	static string msContent;
	static string msOkLabel;
	static string msCancelLabel;
	static bool msOnlyOneBtn;
	static CCObject* msOKTarget;
	static SEL_CallFunc msOKSelector;
	static CCObject* msCancelTarget;
	static SEL_CallFunc msCancelSelector;
};

#endif
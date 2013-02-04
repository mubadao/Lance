#ifndef _AlertDialog_H_
#define _AlertDialog_H_

#include "Global.h"

class AlertDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AlertDialog, create);

	AlertDialog();
	virtual ~AlertDialog();

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	virtual void close();

	static void initContent(const string& content, bool onlyOneBtn = true, CCObject* okTarget = NULL, SEL_CallFunc okCall = NULL, CCObject* cancelTarget = NULL, SEL_CallFunc cancelCall = NULL);
    
private:
	static string msContent;
	static bool msOnlyOneBtn;
	static CCObject* msOKTarget;
	static SEL_CallFunc msOKSelector;
	static CCObject* msCancelTarget;
	static SEL_CallFunc msCancelSelector;

	CCLabelTTF* mContent;
	CCControlButton* mOkBtn;
	CCControlButton* mCancelBtn;

	void onOkBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onCancelBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
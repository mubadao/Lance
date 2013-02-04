#include "AlertDialog.h"

string AlertDialog::msContent = "";
bool AlertDialog::msOnlyOneBtn = false;
CCObject* AlertDialog::msOKTarget = NULL;
SEL_CallFunc AlertDialog::msOKSelector = NULL;
CCObject* AlertDialog::msCancelTarget = NULL;
SEL_CallFunc AlertDialog::msCancelSelector = NULL;

AlertDialog::AlertDialog()
	: mContent(NULL)
    , mOkBtn(NULL)
    , mCancelBtn(NULL)
{
}

AlertDialog::~AlertDialog()
{
	CC_SAFE_RELEASE(mContent);
	CC_SAFE_RELEASE(mOkBtn);
	CC_SAFE_RELEASE(mCancelBtn);
}

bool AlertDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDesc", CCLabelTTF *, mContent);
	CCB_CONTROLBUTTON_GLUE(this, "mOkBtn", mOkBtn, gls("74"));
	CCB_CONTROLBUTTON_GLUE(this, "mCancelBtn", mCancelBtn, gls("75"));
	return false;
}

SEL_MenuHandler AlertDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler AlertDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOkBtnClick", AlertDialog::onOkBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCancelBtnClick", AlertDialog::onCancelBtnClick);
	return NULL;
}

void AlertDialog::onNodeLoaded( CCNode * pNode, CCNodeLoader * pNodeLoader )
{
    mOkBtn->setDefaultTouchPriority(touch_priority_5);
    mCancelBtn->setDefaultTouchPriority(touch_priority_5);
    
    mContent->setString(msContent.c_str());

	if(msOnlyOneBtn)
	{
		mCancelBtn->setVisible(false);
		mOkBtn->setPositionX(320);
	}
}

void AlertDialog::onOkBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	if (msOKTarget && msOKSelector)
		(msOKTarget->*msOKSelector)();
	close();
}

void AlertDialog::onCancelBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent )
{
	if (msCancelTarget && msCancelSelector)
		(msCancelTarget->*msCancelSelector)();
	close();
}

void AlertDialog::initContent(const string& content, bool onlyOneBtn, CCObject* okTarget, SEL_CallFunc okCall, CCObject* cancelTarget, SEL_CallFunc cancelCall)
{
	msContent = content;
	msOnlyOneBtn = onlyOneBtn;
	msOKTarget = okTarget;
	msOKSelector = okCall;
	msCancelTarget = cancelTarget;
	msCancelSelector = cancelCall;
}

void AlertDialog::close()
{
	msContent = "";
    msOnlyOneBtn = false;
	msOKTarget = NULL;
	msOKSelector = NULL;
	msCancelTarget = NULL;
	msCancelSelector = NULL;
	Dialog::close();
}

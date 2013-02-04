#include "AlertTitleDialog.h"

string AlertTitleDialog::msTitle = "";
string AlertTitleDialog::msContent = "";
string AlertTitleDialog::msOkLabel = "";
string AlertTitleDialog::msCancelLabel = "";
bool AlertTitleDialog::msOnlyOneBtn = false;
CCObject* AlertTitleDialog::msOKTarget = NULL;
SEL_CallFunc AlertTitleDialog::msOKSelector = NULL;
CCObject* AlertTitleDialog::msCancelTarget = NULL;
SEL_CallFunc AlertTitleDialog::msCancelSelector = NULL;

AlertTitleDialog::AlertTitleDialog()
	: mTitle(NULL)
	, mContent(NULL)
	, mOkBtn(NULL)
	, mCancelBtn(NULL)
{
}

AlertTitleDialog::~AlertTitleDialog()
{
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mContent);
	CC_SAFE_RELEASE(mOkBtn);
	CC_SAFE_RELEASE(mCancelBtn);
}

bool AlertTitleDialog::onAssignCCBMemberVariable( CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTitle", CCLabelTTF *, mTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDesc", CCLabelTTF *, mContent);
	CCB_CONTROLBUTTON_GLUE(this, "mOkBtn", mOkBtn, gls("74"));
	CCB_CONTROLBUTTON_GLUE(this, "mCancelBtn", mCancelBtn, gls("75"));
	return false;
}

SEL_MenuHandler AlertTitleDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler AlertTitleDialog::onResolveCCBCCControlSelector( CCObject * pTarget, const char * pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOkBtnClick", AlertTitleDialog::onOkBtnClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCancelBtnClick", AlertTitleDialog::onCancelBtnClick);
	return NULL;
}

void AlertTitleDialog::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	mTitle->setString(msTitle.c_str());
	mContent->setString(msContent.c_str());
	
	if(!msOkLabel.empty())
		mOkBtn->setTitleForState(ccs(msOkLabel), CCControlStateNormal);
	else
		mOkBtn->setTitleForState(ccs(gls("74")), CCControlStateNormal);

	if(!msCancelLabel.empty())
		mCancelBtn->setTitleForState(ccs(msCancelLabel),CCControlStateNormal);
	else
		mCancelBtn->setTitleForState(ccs(gls("75")),CCControlStateNormal);
	
	if (msOnlyOneBtn)
	{
		mCancelBtn->setVisible(false);
		mOkBtn->setPositionX(320);
	}
}

void AlertTitleDialog::onOkBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	if (msOKTarget && msOKSelector)
		(msOKTarget->*msOKSelector)();
	close();
}

void AlertTitleDialog::onCancelBtnClick(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	if (msCancelTarget && msCancelSelector)
		(msCancelTarget->*msCancelSelector)();
	close();
}

void AlertTitleDialog::initContent(const string& title, const string& content, bool onlyOneBtn, CCObject* okTarget, SEL_CallFunc okCall, CCObject* cancelTarget, SEL_CallFunc cancelCall, const string& okLabel, const string& cancelLabel)
{
	msTitle = title;
	msContent = content;
	msOnlyOneBtn = onlyOneBtn;
	msOKTarget = okTarget;
	msOKSelector = okCall;
	msCancelTarget = cancelTarget;
	msCancelSelector = cancelCall;
	msOkLabel = okLabel;
	msCancelLabel = cancelLabel;
}

void AlertTitleDialog::close()
{
	msTitle = "";
	msContent = "";
	msOkLabel = "";
	msCancelLabel = "";
	msOnlyOneBtn = false;
	msOKTarget = NULL;
	msOKSelector = NULL;
	msCancelTarget = NULL;
	msCancelSelector = NULL;
	Dialog::close();
}

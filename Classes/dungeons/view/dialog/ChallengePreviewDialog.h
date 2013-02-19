#ifndef _ChallengePreviewDialog_H_
#define _ChallengePreviewDialog_H_

#include "Global.h"

class ChallengePreviewDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChallengePreviewDialog, create);

	ChallengePreviewDialog();
	~ChallengePreviewDialog();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
	virtual void refresh();

private:
	CCLabelTTF* mTitle;
	CCLabelTTF* mName1;
	CCLabelTTF* mVs;
	CCLabelTTF* mName2;
	CCLabelTTF* mSucceedTitle;
	CCLabelTTF* mGetExp;
	CCLabelTTF* mGetGold;
	CCLabelTTF* mFailedTitle;
	CCLabelTTF* mLostGold;

	CCControlButton* mChallengeBtn;
	CCControlButton* mReturnBtn;

	void onChallengeBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onReturnBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
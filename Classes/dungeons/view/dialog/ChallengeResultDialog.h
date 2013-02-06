#ifndef _ChallengeResultDialog_H_
#define _ChallengeResultDialog_H_

#include "Global.h"

class ChallengeResultDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChallengeResultDialog, create);

	ChallengeResultDialog();
	~ChallengeResultDialog();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCLabelTTF* mName1;
	CCLabelTTF* mName2;
	CCLabelTTF* mGetGold;
	CCLabelTTF* mGetExp;
	CCLabelTTF* mTitle;
	CCLabelTTF* mVs;
	CCLabelTTF* mSelfAttack;
	CCLabelTTF* mSelfDefense;
	CCLabelTTF* mSelfLife;
	CCLabelTTF* mOtherAttack;
	CCLabelTTF* mOtherDefense;
	CCLabelTTF* mOtherLife;

	CCControlButton* mCloseBtn;

	CCSprite* mGoldIcon;
	CCSprite* mExpIcon;

//	void _onNotification( CCObject* object );
	void onCloseBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
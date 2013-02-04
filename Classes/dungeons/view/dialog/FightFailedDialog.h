#ifndef _FightFailedDialog_H_
#define _FightFailedDialog_H_

#include "Global.h"

class FightFailedDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(FightFailedDialog, create);

	FightFailedDialog();
	~FightFailedDialog();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName){return NULL;}
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCLabelTTF* mSelfAttack;
	CCLabelTTF* mSelfDefense;
	CCLabelTTF* mSelfLife;
	CCLabelTTF* mOtherAttack;
	CCLabelTTF* mOtherDefense;
	CCLabelTTF* mOtherLife;
	CCLabelTTF* mSelfTitle;
	CCLabelTTF* mOtherTitle;
	CCLabelTTF* mTitle;
	CCLabelTTF* mDesc;

	CCControlButton* mRestartBtn;
	CCControlButton* mBuyLifeBtn;

	void onRestartBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void onBuyLifeBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	void _onNotification( CCObject* object );
};

#endif

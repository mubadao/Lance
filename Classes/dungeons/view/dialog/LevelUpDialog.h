#ifndef _LevelUpDialog_H_
#define _LevelUpDialog_H_

#include "Global.h"

class LevelUpDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LevelUpDialog, create);

	LevelUpDialog();
	~LevelUpDialog();

	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

private:
	CCLabelTTF* mLevel;
	CCLabelTTF* mMinAttack;
	CCLabelTTF* mMaxAttack;
	CCLabelTTF* mMinDefense;
	CCLabelTTF* mMaxDefense;
	CCLabelTTF* mLife;
	CCLabelTTF* mMaxEnergy;

	CCLabelTTF* mTitle;
	CCLabelTTF* mLevelTitle;
	CCLabelTTF* mMinAttackTitle;
	CCLabelTTF* mMaxAttackTitle;
	CCLabelTTF* mMinDefenseTitle;
	CCLabelTTF* mMaxDefenseTitle;
	CCLabelTTF* mLifeTitle;
	CCLabelTTF* mMaxEnergyTitle;

	CCControlButton* mCloseBtn;

	void onCloseBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
};

#endif
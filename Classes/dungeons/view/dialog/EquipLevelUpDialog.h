#ifndef _EquipLevelUpDialog_h__
#define _EquipLevelUpDialog_h__

#include "Global.h"





class EquipLevelUpDialog
	: public Dialog
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EquipLevelUpDialog, create);

	EquipLevelUpDialog(void);
	~EquipLevelUpDialog(void);

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	bool init();
	void refresh();
	void onEnter();
	void onExit();
	virtual void touchScreen();
private:
	CCLabelTTF* mLastLevel;
	CCLabelTTF* mCurLevel;
	CCLabelTTF* mLastAttack;
	CCLabelTTF* mCurAttack;
	CCLabelTTF* mLastDefense;
	CCLabelTTF* mCurDefense;
	CCLabelTTF* mLastLife;
	CCLabelTTF* mCurLife;
	CCLabelTTF* mAttackTitle;
	CCLabelTTF* mDefenseTitle;
	CCLabelTTF* mLifeTitle;

	void _onNotification(CCObject* pSender);
	void onDoItClick(CCObject* pSender);
	void onMergeBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
	
};

#endif
#ifndef _HomeSceneContent_H_
#define _HomeSceneContent_H_

#include "Global.h"

class HomeSceneContent
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HomeSceneContent, create);

	HomeSceneContent();
	virtual ~HomeSceneContent();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

public:
	void onAttributeBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);

private:
	CCLabelTTF* mAttack;
	CCLabelTTF* mDefense;
	CCLabelTTF* mLife;

	CCLabelTTF* mAttackTitle;
	CCLabelTTF* mDefenseTitle;
	CCLabelTTF* mLifeTitle;

	CCControlButton* mAttributeBtn;

	CCNode* mNodeEquip[6];

	void _onNotification(CCObject* object);
	void _refresh();
};

#endif
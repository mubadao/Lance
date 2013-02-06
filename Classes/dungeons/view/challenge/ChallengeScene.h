#ifndef _ChallengeScene_H_
#define _ChallengeScene_H_

#include "Global.h"

class ChallengeScene
	: public CCLayer
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
	, public CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChallengeScene, create);

	ChallengeScene();
	~ChallengeScene();

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
				   
private:
	CCLabelTTF* mAttack;
	CCLabelTTF* mDefense;
	CCLabelTTF* mLife;
	CCLabelTTF* mAttackTitle;
	CCLabelTTF* mDefenseTitle;
	CCLabelTTF* mLifeTitle;
	CCScrollView* mScrollView;
	CCControlButton* mRefreshBtn;

	void _onNotification(CCObject* object);
	void _refresh();

	void onRefreshBtnClick( CCObject * pSender, CCControlEvent pCCControlEvent );
};

#endif